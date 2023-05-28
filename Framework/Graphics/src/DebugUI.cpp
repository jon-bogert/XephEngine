#include "Pch.h"
#include "DebugUI.h"

#include "GraphicsSystem.h"
#include <ImGui/Inc/imgui_impl_dx11.h>
#include <ImGui/Inc/imgui_impl_win32.h>

//Resources
#include "../res/BasierSquare_Medium_otf.h"
#include "../res/JetBrainsMono_ttf.h"

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND window, UINT message, WPARAM wParam, LPARAM lParam);

namespace ig = ImGui;

using namespace xe::Core;

namespace
{
	WindowMessageHandler windowMessageHandler;

	bool IsMouseInput(UINT message)
	{
		switch (message)
		{
		case WM_LBUTTONDOWN:
		case WM_LBUTTONUP:
		case WM_LBUTTONDBLCLK:
		case WM_RBUTTONDOWN:
		case WM_RBUTTONUP:
		case WM_RBUTTONDBLCLK:
		case WM_MBUTTONDOWN:
		case WM_MBUTTONUP:
		case WM_MBUTTONDBLCLK:
		case WM_MOUSEWHEEL:
		case WM_MOUSEHWHEEL:
			return true;
		default:
			break;
		}

		return false;
	}

	bool IsKeyboardInput(UINT message)
	{
		switch (message)
		{
		case WM_KEYDOWN:
		case WM_SYSKEYDOWN:
		case WM_KEYUP:
		case WM_SYSKEYUP:
		case WM_CHAR:
			return true;
		default:
			break;
		}
		return false;
	}

	void SetUIStyle()
	{
		ImGuiStyle& style = ImGui::GetStyle();

		// Modify the style colors
		//style.Colors[ImGuiCol_Text] = ImVec4(0.80f, 0.80f, 0.80f, 1.00f);             // Text color
		//style.Colors[ImGuiCol_WindowBg] = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);         // Window background color
		//style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.07f, 0.07f, 0.07f, 1.00f);          // Title background color
		//style.Colors[ImGuiCol_Button] = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);            // Button background color
		//style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.35f, 0.35f, 0.35f, 1.00f);     // Button hover color
		//style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.15f, 0.15f, 0.15f, 1.00f);      // Button active color

		style.WindowRounding = 4.0f;  // Set window corner rounding to 4 pixels
		//style.FrameRounding = 2.0f;   // Set frame corner rounding to 2 pixels
		style.ScrollbarSize = 10.0f;  // Set scrollbar size to 10 pixels

		style.Colors[ImGuiCol_Text] = ImVec4(0.80f, 0.80f, 0.80f, 1.00f);
		style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
		style.Colors[ImGuiCol_WindowBg] = ImVec4(0.13f, 0.14f, 0.15f, 1.00f);
		style.Colors[ImGuiCol_ChildBg] = ImVec4(0.13f, 0.14f, 0.15f, 1.00f);
		style.Colors[ImGuiCol_PopupBg] = ImVec4(0.13f, 0.14f, 0.15f, 1.00f);
		style.Colors[ImGuiCol_Border] = ImVec4(0.f, 0.f, 0.f, 0.f);
		style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
		style.Colors[ImGuiCol_FrameBg] = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
		style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.38f, 0.38f, 0.38f, 1.00f);
		style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.67f, 0.67f, 0.67f, 0.39f);
		style.Colors[ImGuiCol_TitleBg] = ImVec4(0.08f, 0.08f, 0.09f, 1.00f);
		style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.08f, 0.08f, 0.09f, 1.00f);
		style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 0.51f);
		style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
		style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.02f, 0.02f, 0.02f, 0.53f);
		style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.31f, 0.31f, 0.31f, 1.00f);
		style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.41f, 0.41f, 0.41f, 1.00f);
		style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.51f, 0.51f, 0.51f, 1.00f);
		style.Colors[ImGuiCol_CheckMark] = ImVec4(0.11f, 0.64f, 0.92f, 1.00f);
		style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.11f, 0.64f, 0.92f, 1.00f);
		style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.08f, 0.50f, 0.72f, 1.00f);
		style.Colors[ImGuiCol_Button] = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
		style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.38f, 0.38f, 0.38f, 1.00f);
		style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.67f, 0.67f, 0.67f, 0.39f);
		style.Colors[ImGuiCol_Header] = ImVec4(0.22f, 0.22f, 0.22f, 1.00f);
		style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
		style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.67f, 0.67f, 0.67f, 0.39f);
		style.Colors[ImGuiCol_Separator] = style.Colors[ImGuiCol_Border];
		style.Colors[ImGuiCol_SeparatorHovered] = ImVec4(0.41f, 0.42f, 0.44f, 1.00f);
		style.Colors[ImGuiCol_SeparatorActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
		style.Colors[ImGuiCol_ResizeGrip] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
		style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.29f, 0.30f, 0.31f, 0.67f);
		style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
		style.Colors[ImGuiCol_Tab] = ImVec4(0.08f, 0.08f, 0.09f, 0.83f);
		style.Colors[ImGuiCol_TabHovered] = ImVec4(0.33f, 0.34f, 0.36f, 0.83f);
		style.Colors[ImGuiCol_TabActive] = ImVec4(0.23f, 0.23f, 0.24f, 1.00f);
		style.Colors[ImGuiCol_TabUnfocused] = ImVec4(0.08f, 0.08f, 0.09f, 1.00f);
		style.Colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.13f, 0.14f, 0.15f, 1.00f);
		style.Colors[ImGuiCol_DockingPreview] = ImVec4(0.26f, 0.59f, 0.98f, 0.70f);
		style.Colors[ImGuiCol_DockingEmptyBg] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
		style.Colors[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
		style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
		style.Colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
		style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
		style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
		style.Colors[ImGuiCol_DragDropTarget] = ImVec4(0.11f, 0.64f, 0.92f, 1.00f);
		style.Colors[ImGuiCol_NavHighlight] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
		style.Colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
		style.Colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
		style.Colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);
		style.GrabRounding = style.FrameRounding = 2.3f;

		//Font
		ImGuiIO& io = ig::GetIO();
		ImFontAtlas* fontAtlas = io.Fonts;
		std::unique_ptr<unsigned char[]> fontData;
		size_t fontDataCount = 0;
		res::BasierSquare_Medium_otf(fontData, fontDataCount);
		ImFontConfig fontConfig;
		fontConfig.FontDataOwnedByAtlas = false; // Important: Set to false so ImGui doesn't try to free the memory
		ImWchar defaultRange[] = { 0x0020, 0x00FF, 0x0100, 0x017F, 0 }; // Specify the character ranges you want to support
		ImFont* font = fontAtlas->AddFontFromMemoryTTF((void*)fontData.get(), fontDataCount, 16, &fontConfig, defaultRange);
		fontAtlas->Build();
		io.FontDefault = font;
		
	}
}

LRESULT CALLBACK DebugUIMessageHandler(HWND window, UINT message, WPARAM wParam, LPARAM lParam)
{
	ImGuiIO& io = ig::GetIO();
	if (io.WantCaptureMouse && IsMouseInput(message))
	{
		return ImGui_ImplWin32_WndProcHandler(window, message, wParam, lParam);
	}

	if (io.WantCaptureKeyboard && IsKeyboardInput(message))
	{
		return ImGui_ImplWin32_WndProcHandler(window, message, wParam, lParam);
	}

	LRESULT result = ImGui_ImplWin32_WndProcHandler(window, message, wParam, lParam);
	if (result != 0)
	{
		return result;
	}
	return windowMessageHandler.ForwardMessage(window, message, wParam, lParam);
}

#ifdef _DEBUG
void xe::Graphics::DebugUI::Initialize(HWND window, bool docking, bool multiViewport)
{
	IMGUI_CHECKVERSION();
	ig::CreateContext();
	ImGuiIO& io = ig::GetIO();
	if (docking)
	{
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	}
	if (multiViewport)
	{
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
	}

	ID3D11Device* device = GraphicsSystem::Get().GetDevice();
	ID3D11DeviceContext* context = GraphicsSystem::Get().GetContext();
	ImGui_ImplWin32_Init(window);
	ImGui_ImplDX11_Init(device, context);

	//hook into window listener
	windowMessageHandler.Hook(window, DebugUIMessageHandler);

	//Misc
	DebugUI::SetTheme(DebugUI::Theme::Custom);
}

void xe::Graphics::DebugUI::Terminate()
{
	windowMessageHandler.UnHook();
	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ig::DestroyContext();
}

void xe::Graphics::DebugUI::SetTheme(Theme theme)
{
	switch (theme)
	{
	case Theme::Classic:
		ig::StyleColorsClassic();
		break;
	case Theme::Dark:
		ig::StyleColorsDark();
		break;
	case Theme::Light:
		ig::StyleColorsLight();
		break;
	case Theme::Custom:
		SetUIStyle();
		break;
	}
}

void xe::Graphics::DebugUI::BeginDraw()
{
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ig::NewFrame();
}

void xe::Graphics::DebugUI::EndDraw()
{
	ig::Render();
	ImGui_ImplDX11_RenderDrawData(ig::GetDrawData());

	ImGuiIO& io = ig::GetIO();
	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		ig::UpdatePlatformWindows();
		ig::RenderPlatformWindowsDefault();
	}
}

#else // !_DEBUG
void xe::Graphics::DebugUI::Initialize(HWND window, bool docking, bool multiViewport) {}
void xe::Graphics::DebugUI::Terminate() {}
void xe::Graphics::DebugUI::SetTheme(Theme theme) {}
void xe::Graphics::DebugUI::BeginDraw() {}
void xe::Graphics::DebugUI::EndDraw() {}
#endif // _DEBUG
