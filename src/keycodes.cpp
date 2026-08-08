#include "keycodes.h"
#include <Carbon/Carbon.h>

// @note: from
// /System/Library/Frameworks/Carbon.framework/Versions/A/Frameworks/HIToolbox.framework/Versions/A/Headers/Events.h

struct Key_Entry { const char* name; uint16 code; };

// NOTE: canonical name listed first; aliases after (reverse lookup returns the first match).
static const Key_Entry KEY_TABLE[] = {
	// letters
	{ "A", kVK_ANSI_A }, { "B", kVK_ANSI_B }, { "C", kVK_ANSI_C }, { "D", kVK_ANSI_D },
	{ "E", kVK_ANSI_E }, { "F", kVK_ANSI_F }, { "G", kVK_ANSI_G }, { "H", kVK_ANSI_H },
	{ "I", kVK_ANSI_I }, { "J", kVK_ANSI_J }, { "K", kVK_ANSI_K }, { "L", kVK_ANSI_L },
	{ "M", kVK_ANSI_M }, { "N", kVK_ANSI_N }, { "O", kVK_ANSI_O }, { "P", kVK_ANSI_P },
	{ "Q", kVK_ANSI_Q }, { "R", kVK_ANSI_R }, { "S", kVK_ANSI_S }, { "T", kVK_ANSI_T },
	{ "U", kVK_ANSI_U }, { "V", kVK_ANSI_V }, { "W", kVK_ANSI_W }, { "X", kVK_ANSI_X },
	{ "Y", kVK_ANSI_Y }, { "Z", kVK_ANSI_Z },

	// digits
	{ "0", kVK_ANSI_0 }, { "1", kVK_ANSI_1 }, { "2", kVK_ANSI_2 }, { "3", kVK_ANSI_3 },
	{ "4", kVK_ANSI_4 }, { "5", kVK_ANSI_5 }, { "6", kVK_ANSI_6 }, { "7", kVK_ANSI_7 },
	{ "8", kVK_ANSI_8 }, { "9", kVK_ANSI_9 },

	// function keys
	{ "F1", kVK_F1 }, { "F2", kVK_F2 }, { "F3", kVK_F3 }, { "F4", kVK_F4 },
	{ "F5", kVK_F5 }, { "F6", kVK_F6 }, { "F7", kVK_F7 }, { "F8", kVK_F8 },
	{ "F9", kVK_F9 }, { "F10", kVK_F10 }, { "F11", kVK_F11 }, { "F12", kVK_F12 },
	{ "F13", kVK_F13 }, { "F14", kVK_F14 }, { "F15", kVK_F15 }, { "F16", kVK_F16 },
	{ "F17", kVK_F17 }, { "F18", kVK_F18 }, { "F19", kVK_F19 }, { "F20", kVK_F20 },

	// named keys (canonical first, then aliases)
	{ "Return", kVK_Return }, { "Enter", kVK_Return },
	{ "Tab", kVK_Tab },
	{ "Space", kVK_Space },
	{ "Delete", kVK_Delete }, { "Backspace", kVK_Delete },
	{ "ForwardDelete", kVK_ForwardDelete },
	{ "Escape", kVK_Escape }, { "Esc", kVK_Escape },
	{ "Home", kVK_Home }, { "End", kVK_End },
	{ "PageUp", kVK_PageUp }, { "PageDown", kVK_PageDown },
	{ "Help", kVK_Help },

	// arrows
	{ "Left", kVK_LeftArrow }, { "LeftArrow", kVK_LeftArrow },
	{ "Right", kVK_RightArrow }, { "RightArrow", kVK_RightArrow },
	{ "Up", kVK_UpArrow }, { "UpArrow", kVK_UpArrow },
	{ "Down", kVK_DownArrow }, { "DownArrow", kVK_DownArrow },

	// punctuation
	{ "=", kVK_ANSI_Equal }, { "-", kVK_ANSI_Minus },
	{ "[", kVK_ANSI_LeftBracket }, { "]", kVK_ANSI_RightBracket },
	{ "'", kVK_ANSI_Quote }, { ";", kVK_ANSI_Semicolon },
	{ "\\", kVK_ANSI_Backslash }, { ",", kVK_ANSI_Comma },
	{ "/", kVK_ANSI_Slash }, { ".", kVK_ANSI_Period },
	{ "`", kVK_ANSI_Grave },

	// modifier keys (physical) — NOTE: as triggers these are the keys themselves,
	// not the modifier flags used in combos like "cmd+k".
	{ "Command", kVK_Command }, { "Shift", kVK_Shift },
	{ "Option", kVK_Option }, { "Control", kVK_Control },
	{ "CapsLock", kVK_CapsLock }, { "Function", kVK_Function },
};

static bool name_equals(const char* a, const char* b)
{
	// ASCII case-insensitive compare.
	while (*a && *b)
	{
		char ca = *a, cb = *b;
		if (ca >= 'a' && ca <= 'z') ca -= 32;
		if (cb >= 'a' && cb <= 'z') cb -= 32;
		if (ca != cb) return false;
		++a; ++b;
	}
	return *a == *b;
}

uint16 keycode_from_name(const char* name)
{
	for (const Key_Entry& e : KEY_TABLE)
		if (name_equals(e.name, name)) return e.code;
	return KEYCODE_INVALID;
}

const char* name_from_keycode(uint16 code)
{
	for (const Key_Entry& e : KEY_TABLE)
		if (e.code == code) return e.name;
	return nullptr;
}
