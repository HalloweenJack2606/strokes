#pragma once
#include "core.h"

struct Macro_Def
{
	uint16 keycode;
	String app_name;
	String command;
};

void load_macros();

const Macro_Def* find_macro(uint16 keycode);
