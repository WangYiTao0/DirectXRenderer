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
			using DrException::DrException;
		public:
			static std::string TranslateErrorCode(HRESULT hr) noexcept;
		};

		class HrException : public Exception
		{
		public:
			HrException(int line, const char* file, HRESULT hr) noexcept;
			const char* what() const noexcept override;
			virtual const char* GetType() const noexcept;
			HRESULT GetErrorCode() const noexcept;
			std::string GetErrorDescription() const noexcept;
		private:
			HRESULT hr;
		};

		class NoGfxException : public Exception
		{
		public:
			using Exception::Exception;
			const char* GetType() const noexcept override;
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
		void EnableCursor() noexcept;
		void DisableCursor() noexcept;
		bool CursorEnabled() const noexcept;
		static std::optional<int> ProcessMessages()noexcept;
		Graphics& Gfx();
	private:
		void ConfineCursor() noexcept;
		void FreeCursor() noexcept;
		void ShowCursor() noexcept;
		void HideCursor() noexcept;
		void EnableImGuiMouse()noexcept;
		void DisableImGuiMouse()noexcept;
		static LRESULT CALLBACK HandleMsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
		static LRESULT CALLBACK HandleMsgThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
		LRESULT HandleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
	public:
		Keyboard kbd;
		Mouse mouse;
	private:
		bool cursorEnabled = true;
		int m_width;
		int m_height;
		HWND m_hWnd;
		std::unique_ptr<Graphics> m_pGfx;
		std::vector<BYTE> rawBuffer;
	};
}
