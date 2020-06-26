#include "Application.h"

#include <sstream>
#include <memory>
#include <algorithm>

#include "Scenes/Scene3D.h"
#include "Scenes/ShaderToyScene.h"

#include "imgui.h"

Application::Application()
	:
	wnd(1600, 900, "DirectX11 Renderer")
{
	wnd.Gfx().SetProjection(DirectX::XMMatrixPerspectiveLH(1.0f, 900.f / 1600.f, 0.5f, 4000.0f));

	m_Scenes.push_back(std::make_unique<Scene3D>(wnd));
	m_Scenes.push_back(std::make_unique<ShaderToyScene>(wnd));

	m_CurScene = m_Scenes.begin();

	OutputSceneName();
}



void Application::HandleInput(float dt)
{
	while (const auto e = wnd.kbd.ReadKey())
	{
		if (!e->IsPress())
		{
			continue;
		}

		switch (e->GetCode())
		{
		case VK_ESCAPE:
			if (wnd.CursorEnabled())
			{
				wnd.DisableCursor();
				wnd.mouse.EnableRaw();
			}
			else
			{
				wnd.EnableCursor();
				wnd.mouse.DisableRaw();
			}
			break;
		case VK_TAB:
			CycleScenes();
			break;
		}
	}

}


int Application::Run()
{

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
}

void Application::CycleScenes()
{
	if (++m_CurScene == m_Scenes.end())
	{
		m_CurScene = m_Scenes.begin();
	}
	OutputSceneName();
}

Application::~Application()
{
}

void Application::Update(float dt)
{
	// update scene
	(*m_CurScene)->Update(dt);
}

void Application::Draw(float dt)
{
	// draw scene
	(*m_CurScene)->Draw(dt);
}

void Application::OutputSceneName() const
{
	std::stringstream ss;
	const std::string SceneName((*m_CurScene)->GetName().size() + 4, '*');

	ss << SceneName << std::endl
		<< "* " << (*m_CurScene)->GetName() << " *" << std::endl
		<< SceneName << std::endl;
	OutputDebugStringA(ss.str().c_str());
}

void Application::DoFrame()
{
	auto dt = timer.Mark() * gameSpeed_factor;

	wnd.Gfx().BeginFrame(0.07f, 0.0f, 0.12f);

	HandleInput(dt);
	Update(wnd.kbd.KeyIsPressed(VK_SPACE) ? 0.0f : dt);

	Draw(dt);

	// imgui window to control simulation speed
	if (ImGui::Begin("Simulation Speed"))
	{
		ImGui::SliderFloat("Speed Factor", &gameSpeed_factor, 0.0f, 4.0f);
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

	}
	ImGui::End();

	// present
	wnd.Gfx().EndFrame();
}
