#ifndef __XE_CORE_WINDOW_H__
#define __XE_CORE_WINDOW_H__

namespace xe::Core
{
	class Window
	{
	public:
		void Initialize(HINSTANCE instance, std::wstring appName, uint32_t width, uint32_t height);
		void Terminate();

		void ProcessMessage();

		HWND GetWindowHandle() const { return m_window; }
		bool IsActive() const { return m_isActive; }

	private:
		HINSTANCE m_instance = nullptr;
		HWND m_window = nullptr;
		std::wstring m_appName;
		bool m_isActive = false;
	};
}

#endif //!__XE_CORE_WINDOW_H__
