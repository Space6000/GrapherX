#include "ImguiManager.h"
namespace Grapher
{
	ImguiManager::ImguiManager()
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGui::StyleColorsDark();
	}
	ImguiManager::~ImguiManager()
	{
		ImGui::DestroyContext();
	}
}