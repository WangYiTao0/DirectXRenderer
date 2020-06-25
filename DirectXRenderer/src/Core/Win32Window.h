#pragma once
#include "Win.h"
#include "Debug/DrException.h"
#include "Input/KeyBoard.h"
#include "Input/Mouse.h"

#include "Core/Graphics.h"

#include <optional>
#include <memory>

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
			static constexpr const char* wndClassName = "DRS Direct3D Engine Window";
			static WindowClass wndClass;
			HINSTANCE hInst;
		};
	public:
		Win32Window(int width, int height, const char* name);
		~Win32Window();
		Win32Window(const Win32Window&) = delete;
		Win32Window& operator=(const Win32Window&) = delete;
		void SetTitle(const std::string& title);
		static std::optional<int> ProcessMessages();
		Graphics& Gfx();
	private:
		static LRESULT CALLBACK HandleMsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
		static LRESULT CALLBACK HandleMsgThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
		LRESULT HandleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
	public:
		Keyboard kbd;
		Mouse mouse;
	private:
		int m_width;
		int m_height;
		HWND m_hWnd;
		std::unique_ptr<Graphics> m_pGfx;
	};
}
// error exception helper macro
#define DRWND_EXCEPT( hr ) dr::Win32Window::Exception( __LINE__,__FILE__,hr )
#define DRWND_LAST_EXCEPT() dr::Win32Window::Exception( __LINE__,__FILE__,GetLastError() )
