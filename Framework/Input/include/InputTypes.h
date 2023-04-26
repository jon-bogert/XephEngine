#ifndef XE_INPUT_INPUTTYPE_H
#define XE_INPUT_INPUTTYPE_H

namespace xe::Input
{
	enum class Key : uint32_t
	{
		// Keyboard roll 1
		Escape		= VK_ESCAPE,
		F1			= VK_F1,
		F2			= VK_F2,
		F3			= VK_F3,
		F4			= VK_F4,
		F5			= VK_F5,
		F6			= VK_F6,
		F7			= VK_F7,
		F8			= VK_F8,
		F9			= VK_F9,
		F10			= VK_F10,
		F11			= VK_F11,
		F12			= VK_F12,

		// Keyboard roll 2
		Grave		= VK_OEM_3,
		_1			= '1',
		_2			= '2',
		_3			= '3',
		_4			= '4',
		_5			= '5',
		_6			= '6',
		_7			= '7',
		_8			= '8',
		_9			= '9',
		_0			= '0',
		Dash		= VK_OEM_MINUS,
		Equals		= VK_OEM_PLUS,
		Backspace	= VK_BACK,

		// Keyboard roll 3
		Tab			= VK_TAB,
		Q			= 'Q',
		W			= 'W',
		E			= 'E',
		R			= 'R',
		T			= 'T',
		Y			= 'Y',
		U			= 'U',
		I			= 'I',
		O			= 'O',
		P			= 'P',
		LBracket	= VK_OEM_4,
		RBracket	= VK_OEM_6,
		Backslash	= VK_OEM_5,

		// Keyboard roll 4
		A			= 'A',
		S			= 'S',
		D			= 'D',
		F			= 'F',
		G			= 'G',
		H			= 'H',
		J			= 'J',
		K			= 'K',
		L			= 'L',
		Semicolon	= VK_OEM_1,
		Apostrophe	= VK_OEM_7,
		Enter		= VK_RETURN,

		// Keyboard roll 5
		Z			= 'Z',
		X			= 'X',
		C			= 'C',
		V			= 'V',
		B			= 'B',
		N			= 'N',
		M			= 'M',
		Comma		= VK_OEM_COMMA,
		Period		= VK_OEM_PERIOD,
		Slach		= VK_OEM_2,

		// Lock keys
		CapsLock	= VK_CAPITAL,
		NumLock		= VK_NUMLOCK,
		ScrollLock	= VK_SCROLL,

		// Numpad keys
		NUM1		= VK_NUMPAD1,
		NUM2		= VK_NUMPAD2,
		NUM3		= VK_NUMPAD3,
		NUM4		= VK_NUMPAD4,
		NUM5		= VK_NUMPAD5,
		NUM6		= VK_NUMPAD6,
		NUM7		= VK_NUMPAD7,
		NUM8		= VK_NUMPAD8,
		NUM9		= VK_NUMPAD9,
		NUM0		= VK_NUMPAD0,
		NUMAdd		= VK_ADD,
		NUMSub		= VK_SUBTRACT,
		NUMStar		= VK_MULTIPLY,
		NUMBackslash= VK_DIVIDE,
		NUMEnter	= VK_RETURN,
		NUMPeriod	= VK_DECIMAL,

		// Navigation keys
		Insert		= VK_INSERT,
		Delete		= VK_DELETE,
		Home		= VK_HOME,
		End			= VK_END,
		PageUp		= VK_PRIOR,
		PageDown	= VK_NEXT,

		// Support keys
		LShift		= VK_SHIFT,
		RShift		= VK_SHIFT,
		LCtrl		= VK_CONTROL,
		RCtrl		= VK_CONTROL,
		LAlt		= VK_MENU,
		RAlt		= VK_MENU,
		LWin		= VK_LWIN,
		RWin		= VK_RWIN,
		Space		= VK_SPACE,

		// Arrow keys
		Up			= VK_UP,
		Down		= VK_DOWN,
		Left		= VK_LEFT,
		Right		= VK_RIGHT,
	};

	enum class MouseButton : uint32_t
	{
		Left		= 0,
		Right		= 1,
		Middle		= 2,
	};
}

#endif //XE_INPUT_INPUTTYPE_H