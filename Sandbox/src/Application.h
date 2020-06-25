#include <myRenderer.h>

#include "Scenes/Scene.h"

class Application
{
public:
	Application();
	// master frame / message loop
	int Run();
	~Application();
private:
	void DoFrame();
	void HandleInput(float dt);
	void Update(float dt);
	void Draw();

	void OutputSceneName()const;

	void CycleScenes();
private:
	dr::Win32Window wnd;
	dr::Timer timer;

	std::vector<std::unique_ptr<dr::Box>> boxes;

	std::vector <std::unique_ptr<Scene>> m_Scenes;
	std::vector <std::unique_ptr<Scene>>::iterator m_CurScene;
};