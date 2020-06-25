#include "drpch.h"

#include "Win32Window.h"

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
	{
		// calculate window size based on desired client region size
		RECT wr;
		wr.left = 100;
		wr.right = width + wr.left;
		wr.top = 100;
		wr.bottom = height + wr.top;
		if (FAILED(AdjustWindowRect(&wr, WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, FALSE)))
		{
			throw DRWND_LAST_EXCEPT();
		};
		// create window & get hWnd
		m_hWnd = CreateWindow(
			WindowClass::GetName(), name,
			WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU,
			CW_USEDEFAULT, CW_USEDEFAULT, wr.right - wr.left, wr.bottom - wr.top,
			nullptr, nullptr, WindowClass::GetInstance(), this
		);

		// check for error
		if (m_hWnd == nullptr)
		{
			throw DRWND_LAST_EXCEPT();
		}

		// show window
		ShowWindow(m_hWnd, SW_SHOWDEFAULT);
	}

	Win32Window::~Win32Window()
	{
		DestroyWindow(m_hWnd);
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
			if (!(lParam & 0x40000000) || kbd.AutorepeatIsEnabled()) // filter autorepeat
			{
				kbd.OnKeyPressed(static_cast<unsigned char>(wParam));
			}
			break;
		case WM_KEYUP:
		case WM_SYSKEYUP:
			kbd.OnKeyReleased(static_cast<unsigned char>(wParam));
			break;
		case WM_CHAR:
			kbd.OnChar(static_cast<unsigned char>(wParam));
			break;
			/*********** END KEYBOARD MESSAGES ***********/
		}

		return DefWindowProc(hWnd, msg, wParam, lParam);
	}

	Win32Window::Exception::Exception(int line, const char* file, HRESULT hr) noexcept
		:
		DrException(line, file),
		hr(hr)
	{

	}

	const char* Win32Window::Exception::what() const noexcept
	{
		std::ostringstream oss;
		oss << GetType() << std::endl
			<< "[Error Code] " << GetErrorCode() << std::endl
			<< "[Description] " << GetErrorString() << std::endl
			<< GetOriginString();
		whatBuffer = oss.str();
		return whatBuffer.c_str();
	}

	const char* Win32Window::Exception::GetType() const noexcept
	{
		return "Dr Window Exception";
	}

	std::string Win32Window::Exception::TranslateErrorCode(HRESULT hr) noexcept
	{
		char* pMsgBuf = nullptr;
		// windows will allocate memory for err string and make our pointer point to it
		DWORD nMsgLen = FormatMessage(
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

	HRESULT Win32Window::Exception::GetErrorCode() const noexcept
	{
		return hr;
	}

	std::string Win32Window::Exception::GetErrorString() const noexcept
	{
		return TranslateErrorCode(hr);
	}

}