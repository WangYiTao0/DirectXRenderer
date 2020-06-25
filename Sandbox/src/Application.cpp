#include "Application.h"



Application::Application()
	:
	wnd(1600, 900, "DirectX11 Renderer")
{
}

int Application::Run()
{

	MSG msg;
	BOOL gResult;

	while (true)
	{
		// process all messages pending, but to not block for new messages
		if (const auto ecode = dr::Win32Window::ProcessMessages())
		{
			// if return optional has value, means we're quitting so return exit code
			return *ecode;
		}
		DoFrame();
	}


	if (gResult == -1)
	{
		throw DRWND_LAST_EXCEPT();
	}

	return msg.wParam;
}

void Application::DoFrame()
{
	wnd.Gfx().EndFrame();
}
