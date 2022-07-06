#pragma once
#include "../Libraries.h"
#include "../../lib/XephEngine/Engine.h"

namespace xe
{
	enum class Key // NOTE: Can Typecast to sf::Keyboard::Key
	{
        Unkwn = -1, 
        A = 0, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
        _0, _1, _2, _3, _4, _5, _6, _7, _8, _9,
        Escape, LCtrl, LShift, LAlt, LWin, RCtrl, RShift, RAlt, RWin,
        Menu, LBracket, RBracket, Semicolon, Comma, Period,  Quote,  ForwardSlash, Backslash,
        Tilde,  Equal,  Dash,  Space, Enter,  Backspace, Tab,
        PageUp,  PageDown, End, Home, Insert, Delete,
        NumAdd, NumMinus, NumMultiply, NumDivide,
        Left, Right, Up, Down,
        Num0, Num1, Num2, Num3, Num4, Num5, Num6, Num7, Num8, Num9,
        F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12, F13, F14, F15,
        Pause
	};
    enum class Mouse // NOTE Can Typecast sf::Mouse
    {
        Left, Right, Middle, Button4, Button5
    };
    enum class Xbox // NOTE does NOT Typecast
    {
        A, B, X, Y, Start, Select, LB, RB, LT, RT, LS_Press, RS_Press,
        LS_Up, LS_Down, LS_Left, LS_Right,
        RS_Up, RS_Down, RS_Left, RS_Right,
        DPad_Up, DPad_Down, DPad_Left, DPad_Right
    };
    enum class PlayStation // NOTE does NOT Typecast
    {
        Cross, Circle, Square, Triangle, Start, Touchpad, L1, R1, L2, R2, L3, R3,
        LS_Up, LS_Down, LS_Left, LS_Right,
        RS_Up, RS_Down, RS_Left, RS_Right,
        DPad_Up, DPad_Down, DPad_Left, DPad_Right
    };
	namespace InputSystem
	{
		bool Update();

        bool CloseWindow();

		bool KeyHold(const Key key);
        bool KeyPress(const Key key);

        void Typing(std::string& out_str);
	}
}

