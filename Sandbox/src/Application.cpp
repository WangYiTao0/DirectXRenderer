#include "Application.h"

#include <sstream>
#include <memory>
#include <algorithm>

#include "Scenes/Scene3D.h"
#include "Scenes/ShaderToyScene.h"

#include "imgui.h"

void f()
{
	using namespace dr::Dvtx;
	namespace dx = DirectX;


	VertexBuffer vb(std::move(
		VertexLayout{}
		.Append<VertexLayout::Position3D>()
		.Append<VertexLayout::Normal>()
		.Append<VertexLayout::Texture2D>()
	));
	vb.EmplaceBack(
		dx::XMFLOAT3{ 1.0f,1.0f,5.0f },
		dx::XMFLOAT3{ 2.0f,1.0f,4.0f },
		dx::XMFLOAT2{ 6.0f,9.0f }
	);
	vb.EmplaceBack(
		dx::XMFLOAT3{ 6.0f,9.0f,6.0f },
		dx::XMFLOAT3{ 9.0f,6.0f,9.0f },
		dx::XMFLOAT2{ 4.2f,0.0f }
	);
	auto pos = vb[0].Attr<VertexLayout::Position3D>();
	auto nor = vb[0].Attr<VertexLayout::Normal>();
	auto tex = vb[1].Attr<VertexLayout::Texture2D>();
	vb.Back().Attr<VertexLayout::Position3D>().z = 420.0f;
	pos = vb.Back().Attr<VertexLayout::Position3D>();
	const auto& cvb = vb;
	pos = cvb[1].Attr<VertexLayout::Position3D>();
}

Application::Application()
	:
	wnd(1600, 900, "DirectX11 Renderer")
{

	f();

	wnd.Gfx().SetProjection(DirectX::XMMatrixPerspectiveLH(1.0f, 900.f / 1600.f, 0.5f, 4000.0f));

	m_Scenes.push_back(std::make_unique<Scene3D>(wnd));
	m_Scenes.push_back(std::make_unique<ShaderToyScene>(wnd));

	m_CurScene = m_Scenes.begin();

	OutputSceneName();
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
