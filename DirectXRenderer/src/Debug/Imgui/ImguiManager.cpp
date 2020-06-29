#include "drpch.h"
#include "ImguiManager.h"
#include <imgui.h>
#include <imgui_impl_win32.h>

namespace dr
{
	ImguiManager::ImguiManager()
	{
		namespace fs = std::filesystem;
		if (!fs::exists("imgui.ini") && fs::exists("imgui_default.ini"))
		{
			fs::copy_file("imgui_default.ini", "imgui.ini");
		}
		// Setup Dear ImGui context
		ImGui_ImplWin32_EnableDpiAwareness();

		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
		//io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
		//io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

		io.ConfigFlags |= ImGuiConfigFlags_DpiEnableScaleFonts;
		io.ConfigFlags |= ImGuiConfigFlags_DpiEnableScaleViewports;
		ImGui::StyleColorsDark();

		ImGuiStyle& style = ImGui::GetStyle();
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			style.WindowRounding = 0.0f;
			style.Colors[ImGuiCol_WindowBg].w = 1.0f;
		}
	}

	ImguiManager::~ImguiManager()
	{
		ImGui::DestroyContext();
	}
}
