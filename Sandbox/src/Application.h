#include <myRenderer.h>

class Application
{
public:
	Application();
	// master frame / message loop
	int Run();
	~Application();
private:
	void DoFrame();
private:
	dr::Win32Window wnd;
	dr::Timer timer;

	std::vector<std::unique_ptr<dr::Box>> boxes;
};