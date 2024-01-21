#ifndef __XE_CORE_WINDOWMESSAGEHANDLER_H__
#define __XE_CORE_WINDOWMESSAGEHANDLER_H__

namespace xe::Core
{
	class WindowMessageHandler
	{
	public:
		using Callback = LRESULT(CALLBACK*)(HWND, UINT, WPARAM, LPARAM);

	private:
		HWND _window = nullptr;
		Callback _previousCallback = nullptr;
	public:

		void Hook(HWND window, Callback cb);
		void UnHook();

		LRESULT ForwardMessage(HWND window, UINT message, WPARAM wParam, LPARAM lParam);
	};
}

#endif
