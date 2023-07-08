#ifndef __XE_GRAPHICS_DEBUGUI_H__
#define __XE_GRAPHICS_DEBUGUI_H__

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
