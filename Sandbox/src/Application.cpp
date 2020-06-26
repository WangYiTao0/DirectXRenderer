#include "Application.h"

#include <sstream>
#include "Scenes/Scene3D.h"
#include "Scenes/ShaderToyScene.h"

#include "imgui.h"

Application::Application()
	:
	wnd(1600, 900, "DirectX11 Renderer")
{
	std::mt19937 rng(std::random_device{}());
	std::uniform_real_distribution<float> adist(0.0f, 3.1415f * 2.0f);
	std::uniform_real_distribution<float> ddist(0.0f, 3.1415f * 2.0f);
	std::uniform_real_distribution<float> odist(0.0f, 3.1415f * 0.3f);
	std::uniform_real_distribution<float> rdist(6.0f, 20.0f);
	for (auto i = 0; i < 100; i++)
	{
		boxes.push_back(std::make_unique<dr::Box>(
			wnd.Gfx(), rng, adist,
			ddist, odist, rdist
			));
	}
	wnd.Gfx().SetProjection(DirectX::XMMatrixPerspectiveLH(1.0f, 900.f / 1600.f, 0.5f, 40.0f));

	m_Scenes.push_back(std::make_unique<Scene3D>(wnd.Gfx()));
	m_Scenes.push_back(std::make_unique<ShaderToyScene>(wnd.Gfx()));

	m_CurScene = m_Scenes.begin();

	OutputSceneName();
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


void Application::HandleInput(float dt)
{
	if (wnd.kbd.KeyIsPressed(VK_SPACE))
	{
		wnd.Gfx().DisableImgui();
	}
	else
	{
		wnd.Gfx().EnableImgui();
	}

	while (const auto e = wnd.kbd.ReadKey())
	{
		if (!e->IsPress())
		{
			continue;
		}

		switch (e->GetCode())
		{
		case VK_TAB:
			CycleScenes();
			break;
		}

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

void Application::Draw()
{
	// draw scene
	(*m_CurScene)->Draw();
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
	auto dt = timer.Mark();
	wnd.Gfx().BeginFrame(0.07f, 0.0f, 0.12f);

	HandleInput(dt);
	Update(wnd.kbd.KeyIsPressed(VK_SPACE) ? 0.0f : dt);
	Draw();

	for (auto& b : boxes)
	{
		b->Update(dt);
		b->Draw(wnd.Gfx());
	}
	// imgui stuff
	if (show_demo_window)
	{
		ImGui::ShowDemoWindow(&show_demo_window);
	}
	// present

	wnd.Gfx().EndFrame();
}
