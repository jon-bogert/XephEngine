#include "Pch.h"
#include "WindowMessageHandler.h"

#include "DebugUtil.h"

void xe::Core::WindowMessageHandler::Hook(HWND window, Callback cb)
{
	_window = window;
	_previousCallback = (Callback)GetWindowLongPtrA(window, GWLP_WNDPROC);
	SetWindowLongPtrA(window, GWLP_WNDPROC, (LONG_PTR)cb);
}

void xe::Core::WindowMessageHandler::UnHook()
{
	SetWindowLongPtrA(_window, GWLP_WNDPROC, (LONG_PTR)_previousCallback);
	_window = nullptr;
}

LRESULT xe::Core::WindowMessageHandler::ForwardMessage(HWND window, UINT message, WPARAM wParam, LPARAM lParam)
{
	ASSERT(_previousCallback, "WindowMessageHandler -- No callback is hooked");
	return CallWindowProcA((WNDPROC)_previousCallback, window, message, wParam, lParam);
	return LRESULT();
}
