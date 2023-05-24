#ifndef XE_GRAPHICS_DEBUGUI_H
#define XE_GRAPHICS_DEBUGUI_H

namespace xe::Graphics::DebugUI
{
	enum class Theme { Classic, Dark, Light, Custom };

	void Initialize(HWND window, bool docking = false, bool multiViewport = false);
	void Terminate();

	void SetTheme(Theme theme);

	void BeginDraw();
	void EndDraw();
}

#endif
