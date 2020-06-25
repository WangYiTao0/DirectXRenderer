#pragma once
#include "Win.h"
#include "Debug/DrException.h"

namespace dr
{

	class Win32Window
	{
	public:
		class Exception : public DrException
		{
		public:
			Exception(int line, const char* file, HRESULT hr) noexcept;
			const char* what() const noexcept override;
			virtual const char* GetType() const noexcept;
			static std::string TranslateErrorCode(HRESULT hr) noexcept;
			HRESULT GetErrorCode() const noexcept;
			std::string GetErrorString() const noexcept;
		private:
			HRESULT hr;
		};

	private:
		// singleton manages registration/cleanup of window class
		class WindowClass
		{
		public:
			static const char* GetName() noexcept;
			static HINSTANCE GetInstance() noexcept;
		private:
			WindowClass() noexcept;
			~WindowClass();
			WindowClass(const WindowClass&) = delete;
			WindowClass& operator=(const WindowClass&) = delete;
			static constexpr const char* wndClassName = "Chili Direct3D Engine Window";
			static WindowClass wndClass;
			HINSTANCE hInst;
		};
	public:
		Win32Window(int width, int height, const char* name);
		~Win32Window();
		Win32Window(const Win32Window&) = delete;
		Win32Window& operator=(const Win32Window&) = delete;
	private:
		static LRESULT CALLBACK HandleMsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
		static LRESULT CALLBACK HandleMsgThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
		LRESULT HandleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
	private:
		int m_width;
		int m_height;
		HWND m_hWnd;
	};
// error exception helper macro
#define DRWND_EXCEPT( hr ) Window::Exception( __LINE__,__FILE__,hr )
#define DRWND_LAST_EXCEPT() Window::Exception( __LINE__,__FILE__,GetLastError() )
}
