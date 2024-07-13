#include "GUI.h"
#include <Windows.h>
#include "Cheat.h"
#include "iostream"

static bool is_init{};
static bool do_draw{true};

bool GUI::init(HWND wnd_handle)
{
	if (is_init)
		return false;

	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplWin32_Init(wnd_handle);
	ImGui_ImplOpenGL3_Init();

	is_init = true;

	return false;
}

void GUI::shutdown()
{
	if (!is_init)
		return;

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();

	is_init = false;
}

//
// Global functions
//

void GUI::draw()
{
	if (GetAsyncKeyState(VK_DELETE) & 0x8000)
	{
		do_draw = !do_draw;
		Sleep(150);
	}

	if (!do_draw)
		return;

	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	ImGui::SetNextWindowSize(ImVec2(600, 400));

	if (do_draw = true)
	{
		ImGui::Begin("1.20.2 Client", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse);
		{
			ImGui::Text("1.20.2 Minecraft Client");
			ImGui::Checkbox("Sprint (only on 'W' key)", &settings.sprint);
			ImGui::Checkbox("Invisible", &settings.invisible);
			ImGui::Checkbox("Jump In Air", &settings.onground);
			ImGui::Checkbox("No Gravity", &settings.gravity);
			ImGui::Checkbox("Set Swimming", &settings.swimming);
			ImGui::Checkbox("Swimming Animation", &settings.visualswimming);
			ImGui::Checkbox("Crawling Animation", &settings.visualcrawl);
			ImGui::Checkbox("Enable Infinite Air Supply", &settings.airsupplybool);
			ImGui::Checkbox("Sprint (Sprint Any Time)", &settings.cansprint);
			if (settings.airsupplybool == true)
			{
				ImGui::SliderInt("Air Supply Amount", &settings.airsupply, 1, 1000);
			}
			ImGui::Checkbox("Jump Height", &settings.jump);
			if (settings.jump == true)
			{
				ImGui::SliderFloat("Jump Height", &settings.jumpheight, 1.f, 1000.f);
			}
		}
		ImGui::End();
		ImGui::EndFrame();
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	}
}

//
// Get & Set functions
//

bool GUI::getIsInit()
{
	return is_init;
}

bool GUI::getDoDraw()
{
	return do_draw;
}

void GUI::setDoDraw(bool new_value)
{
	do_draw = new_value;
}
