#ifndef __XE_CORE_WINDOWMESSAGEHANDLER_H__
#define __XE_CORE_WINDOWMESSAGEHANDLER_H__

namespace xe::Core
{
	class WindowMessageHandler
	{
	public:
		using Callback = LRESULT(CALLBACK*)(HWND, UINT, WPARAM, LPARAM);

		void Hook(HWND window, Callback cb);
		void UnHook();

		LRESULT ForwardMessage(HWND window, UINT message, WPARAM wParam, LPARAM lParam);

	private:
		HWND m_window = nullptr;
		Callback m_previousCallback = nullptr;
	};
}

#endif //!__XE_CORE_WINDOWMESSAGEHANDLER_H__
