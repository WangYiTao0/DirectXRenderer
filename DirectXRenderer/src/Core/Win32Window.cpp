#include "drpch.h"
#include "Win32Window.h"
#include "Debug/ThrowMacros.h"

#include <imgui.h>
#include <imgui_impl_win32.h>


IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);


namespace dr
{
	// Window Class Stuff
	Win32Window::WindowClass Win32Window::WindowClass::wndClass;

	Win32Window::WindowClass::WindowClass() noexcept
		:
		hInst(GetModuleHandle(nullptr))
	{
		WNDCLASSEX wc = { 0 };
		wc.cbSize = sizeof(wc);
		wc.style = CS_OWNDC;
		wc.lpfnWndProc = HandleMsgSetup;
		wc.cbClsExtra = 0;
		wc.cbWndExtra = 0;
		wc.hInstance = GetInstance();
		wc.hIcon = nullptr;
		wc.hCursor = nullptr;
		wc.hbrBackground = nullptr;
		wc.lpszMenuName = nullptr;
		wc.lpszClassName = GetName();
		wc.hIconSm = nullptr;
		RegisterClassEx(&wc);
	}

	Win32Window::WindowClass::~WindowClass()
	{
		UnregisterClass(wndClassName, GetInstance());
	}

	const char* Win32Window::WindowClass::GetName() noexcept
	{
		return wndClassName;
	}

	HINSTANCE Win32Window::WindowClass::GetInstance() noexcept
	{
		return wndClass.hInst;
	}


	Win32Window::Win32Window(int width, int height, const char* name) 
		:
		m_width(width),
		m_height(height)
	{
		// calculate window size based on desired client region size
		RECT window_rect = { 0,0,width, height };

		DWORD window_style = WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU;
		
		if (AdjustWindowRect(&window_rect, window_style, FALSE) == 0)
		{
			throw DRWND_LAST_EXCEPT();
		}

		int window_width = window_rect.right - window_rect.left;
		int window_height = window_rect.bottom - window_rect.top;

		int desktop_width = GetSystemMetrics(SM_CXSCREEN);
		int desktop_height = GetSystemMetrics(SM_CYSCREEN);

		using  std::max;
		int window_x = std::max((desktop_width - window_width) / 2, 0);
		int window_y = std::max((desktop_height - window_height) / 2, 0);

		// create window & get hWnd
		m_hWnd = CreateWindow(
			WindowClass::GetName(), name,
			window_style,
			window_x, window_y, window_width, window_height,
			nullptr, nullptr, WindowClass::GetInstance(), this
		);

		// check for error
		if (m_hWnd == nullptr)
		{
			throw DRWND_LAST_EXCEPT();
		}

		// show window
		ShowWindow(m_hWnd, SW_SHOWDEFAULT);

		// Init ImGui Win32 Impl
		ImGui_ImplWin32_Init(m_hWnd);

		// create graphics object
		m_pGfx = std::make_unique<Graphics>(m_hWnd,m_width,m_height);
	}

	Win32Window::~Win32Window()
	{
		ImGui_ImplWin32_Shutdown();
		DestroyWindow(m_hWnd);
	}
	

	void Win32Window::SetTitle(const std::string& title)
	{
		if (SetWindowText(m_hWnd, title.c_str()) == 0)
		{
			throw DRWND_LAST_EXCEPT();
		}
	}

	std::optional<int> Win32Window::ProcessMessages() noexcept
	{
		MSG msg;
		// while queue has messages, remove and dispatch them (but do not block on empty queue)
		while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			// check for quit because peekmessage does not signal this via return val
			if (msg.message == WM_QUIT)
			{
				// return optional wrapping int (arg to PostQuitMessage is in wparam) signals quit
				return (int)msg.wParam;
			}

			// TranslateMessage will post auxilliary WM_CHAR messages from key msgs
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		// return empty optional when not quitting app
		return {};
	}

	Graphics& Win32Window::Gfx()
	{
		if (!m_pGfx)
		{
			throw DRWND_NOGFX_EXCEPT();
		}
		return *m_pGfx;
	}

	LRESULT CALLBACK dr::Win32Window::HandleMsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept
	{
		// use create parameter passed in from CreateWindow() to store window class pointer at WinAPI side
		if (msg == WM_NCCREATE)
		{
			// extract ptr to window class from creation data
			const CREATESTRUCTW* const pCreate = reinterpret_cast<CREATESTRUCTW*>(lParam);
			Win32Window* const pWnd = static_cast<Win32Window*>(pCreate->lpCreateParams);
			// set WinAPI-managed user data to store ptr to window class
			SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWnd));
			// set message proc to normal (non-setup) handler now that setup is finished
			SetWindowLongPtr(hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&Win32Window::HandleMsgThunk));
			// forward message to window class handler
			return pWnd->HandleMsg(hWnd, msg, wParam, lParam);
		}
		// if we get a message before the WM_NCCREATE message, handle with default handler
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}

	LRESULT CALLBACK Win32Window::HandleMsgThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept
	{
		// retrieve ptr to window class
		Win32Window* const pWnd = reinterpret_cast<Win32Window*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
		// forward message to window class handler
		return pWnd->HandleMsg(hWnd, msg, wParam, lParam);
	
	}

	LRESULT Win32Window::HandleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept
	{
		if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
		{
			return true;
		}

		const auto& imio = ImGui::GetIO();


		switch (msg)
		{
		case WM_CLOSE:
			PostQuitMessage(0);
			return 0;
		// clear keystate when window loses focus to prevent input getting "stuck"
		case WM_KILLFOCUS:
			kbd.ClearState();
			break;
			/*********** KEYBOARD MESSAGES ***********/
		case WM_KEYDOWN:
		case WM_SYSKEYDOWN:
			// stifle this keyboard message if imgui wants to capture
			if (imio.WantCaptureKeyboard)
			{
				break;
			}
			if (!(lParam & 0x40000000) || kbd.AutorepeatIsEnabled()) // filter autorepeat
			{
				kbd.OnKeyPressed(static_cast<unsigned char>(wParam));
			}
			break;
		case WM_KEYUP:
		case WM_SYSKEYUP:
			// stifle this keyboard message if imgui wants to capture
			if (imio.WantCaptureKeyboard)
			{
				break;
			}
			kbd.OnKeyReleased(static_cast<unsigned char>(wParam));
			break;
		case WM_CHAR:
			// stifle this keyboard message if imgui wants to capture
			if (imio.WantCaptureKeyboard)
			{
				break;
			}
			kbd.OnChar(static_cast<unsigned char>(wParam));
			break;
			/*********** END KEYBOARD MESSAGES ***********/

			/************* MOUSE MESSAGES ****************/
		case WM_MOUSEMOVE:
		{
			// stifle this mouse message if imgui wants to capture
			if (imio.WantCaptureMouse)
			{
				break;
			}
			const POINTS pt = MAKEPOINTS(lParam);
			// in client region -> log move, and log enter + capture mouse (if not previously in window)
			if (pt.x >= 0 && pt.x < m_width && pt.y >= 0 && pt.y < m_height)
			{
				mouse.OnMouseMove(pt.x, pt.y);
				if (!mouse.IsInWindow())
				{
					SetCapture(hWnd);
					mouse.OnMouseEnter();
				}
			}
			// not in client -> log move / maintain capture if button down
			else
			{
				if (wParam & (MK_LBUTTON | MK_RBUTTON))
				{
					mouse.OnMouseMove(pt.x, pt.y);
				}
				// button up -> release capture / log event for leaving
				else
				{
					ReleaseCapture();
					mouse.OnMouseLeave();
				}
			}
			break;
		}
		case WM_LBUTTONDOWN:
		{
			// bring window to foreground on lclick client region
			SetForegroundWindow(hWnd);
			// stifle this mouse message if imgui wants to capture
			if (imio.WantCaptureMouse)
			{
				break;
			}
			const POINTS pt = MAKEPOINTS(lParam);
			mouse.OnLeftPressed(pt.x, pt.y);
			break;
		}
		case WM_RBUTTONDOWN:
		{
			// stifle this mouse message if imgui wants to capture
			if (imio.WantCaptureMouse)
			{
				break;
			}
			const POINTS pt = MAKEPOINTS(lParam);
			mouse.OnRightPressed(pt.x, pt.y);
			break;
		}
		case WM_LBUTTONUP:
		{
			// stifle this mouse message if imgui wants to capture
			if (imio.WantCaptureMouse)
			{
				break;
			}
			const POINTS pt = MAKEPOINTS(lParam);
			mouse.OnLeftReleased(pt.x, pt.y);
			// release mouse if outside of window
			if (pt.x < 0 || pt.x >= m_width || pt.y < 0 || pt.y >= m_height)
			{
				ReleaseCapture();
				mouse.OnMouseLeave();
			}
			break;
		}
		case WM_RBUTTONUP:
		{
			// stifle this mouse message if imgui wants to capture
			if (imio.WantCaptureMouse)
			{
				break;
			}
			const POINTS pt = MAKEPOINTS(lParam);
			mouse.OnRightReleased(pt.x, pt.y);
			// release mouse if outside of window
			if (pt.x < 0 || pt.x >= m_width || pt.y < 0 || pt.y >= m_height)
			{
				ReleaseCapture();
				mouse.OnMouseLeave();
			}
			break;
		}
		case WM_MOUSEWHEEL:
		{
			// stifle this mouse message if imgui wants to capture
			if (imio.WantCaptureMouse)
			{
				break;
			}
			const POINTS pt = MAKEPOINTS(lParam);
			const int delta = GET_WHEEL_DELTA_WPARAM(wParam);
			mouse.OnWheelDelta(pt.x, pt.y, delta);
			break;
		}
		/************** END MOUSE MESSAGES **************/
		}

		return DefWindowProc(hWnd, msg, wParam, lParam);
	}


	std::string Win32Window::Exception::TranslateErrorCode(HRESULT hr) noexcept
	{
		char* pMsgBuf = nullptr;
		// windows will allocate memory for err string and make our pointer point to it
		const DWORD nMsgLen = FormatMessage(
			FORMAT_MESSAGE_ALLOCATE_BUFFER |
			FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
			nullptr, hr, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
			reinterpret_cast<LPSTR>(&pMsgBuf), 0, nullptr
		);
		// 0 string length returned indicates a failure
		if (nMsgLen == 0)
		{
			return "Unidentified error code";
		}
		// copy error string from windows-allocated buffer to std::string
		std::string errorString = pMsgBuf;
		// free windows buffer
		LocalFree(pMsgBuf);
		return errorString;
	}

	Win32Window::HrException::HrException(int line, const char* file, HRESULT hr) noexcept
		:
		Exception(line, file),
		hr(hr)
	{}

	const char* Win32Window::HrException::what() const noexcept
	{
		std::ostringstream oss;
		oss << GetType() << std::endl
			<< "[Error Code] 0x" << std::hex << std::uppercase << GetErrorCode()
			<< std::dec << " (" << (unsigned long)GetErrorCode() << ")" << std::endl
			<< "[Description] " << GetErrorDescription() << std::endl
			<< GetOriginString();
		whatBuffer = oss.str();
		return whatBuffer.c_str();
	}

	const char* Win32Window::HrException::GetType() const noexcept
	{
		return "Chili Window Exception";
	}


	HRESULT Win32Window::HrException::GetErrorCode() const noexcept
	{
		return hr;
	}

	std::string Win32Window::HrException::GetErrorDescription() const noexcept
	{
		return Exception::TranslateErrorCode(hr);
	}

	const char* Win32Window::NoGfxException::GetType() const noexcept
	{
		return "DR Window Exception [No Graphics]";
	}

}