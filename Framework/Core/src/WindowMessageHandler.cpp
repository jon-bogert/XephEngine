#include "Pch.h"
#include "WindowMessageHandler.h"

#include "DebugUtil.h"

void xe::Core::WindowMessageHandler::Hook(HWND window, Callback cb)
{
	m_window = window;
	m_previousCallback = (Callback)GetWindowLongPtrA(window, GWLP_WNDPROC);
	SetWindowLongPtrA(window, GWLP_WNDPROC, (LONG_PTR)cb);
}

void xe::Core::WindowMessageHandler::UnHook()
{
	SetWindowLongPtrA(m_window, GWLP_WNDPROC, (LONG_PTR)m_previousCallback);
	m_window = nullptr;
}

LRESULT xe::Core::WindowMessageHandler::ForwardMessage(HWND window, UINT message, WPARAM wParam, LPARAM lParam)
{
	ASSERT(m_previousCallback, "WindowMessageHandler -- No callback is hooked");
	return CallWindowProcA((WNDPROC)m_previousCallback, window, message, wParam, lParam);
	return LRESULT();
}
