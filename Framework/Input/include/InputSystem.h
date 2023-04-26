#ifndef XE_INPUT_INPUTSYSTEM_H
#define XE_INPUT_INPUTSYSTEM_H

#include "InputTypes.h"

namespace xe::Input
{
	class InputSystem final
	{
	public:
		static void Initialize(HWND window);
		static void Terminate();
		static InputSystem& Get();

	public:
		InputSystem() = default;
		~InputSystem();

		InputSystem(const InputSystem&) = delete;
		InputSystem& operator=(const InputSystem&) = delete;

		void _Initialize(HWND window);
		void _Terminate();

		void Update();

		bool IsKeyDown(Key key) const;
		bool IsKeyPressed(Key key) const;

		bool IsMouseDown(MouseButton button) const;
		bool IsMousePressed(MouseButton button) const;

		int GetMouseMoveX() const;
		int GetMouseMoveY() const;
		float GetMouseMoveZ() const;

		int GetMouseScreenX() const;
		int GetMouseScreenY() const;

		bool IsMouseLeftEdge() const;
		bool IsMouseRightEdge() const;
		bool IsMouseTopEdge() const;
		bool IsMouseBottomEdge() const;

		void ShowSystemCursor(bool show);
		void SetMouseClipToWindow(bool clip);
		bool IsMouseClipToWindow() const;

	private:
		static LRESULT CALLBACK InputSystemMessageHandler(HWND window, UINT message, WPARAM wParam, LPARAM lParam);

		HWND mWindow = nullptr;

		bool mCurrKeys[512]{};
		bool mPrevKeys[512]{};
		bool mPressedKeys[512]{};

		bool mClipMouseToWindow = false;

		int mCurrMouseX = -1;
		int mCurrMouseY = -1;
		int mPrevMouseX = -1;
		int mPrevMouseY = -1;
		int mMouseMoveX = 0;
		int mMouseMoveY = 0;

		float mMouseWheel = 0.0f;

		bool mCurrMouseButtons[3]{};
		bool mPrevMouseButtons[3]{};
		bool mPressedMouseButtons[3]{};

		bool mMouseLeftEdge = false;
		bool mMouseRightEdge = false;
		bool mMouseTopEdge = false;
		bool mMouseBottomEdge = false;

		bool mInitialized = false;
	};
}

#endif