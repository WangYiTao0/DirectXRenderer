#include <myRenderer.h>

class Application
{
public:
	Application();
	// master frame / message loop
	int Run();
private:
	void DoFrame();
private:
	dr::Win32Window wnd;
	dr::Timer timer;
};