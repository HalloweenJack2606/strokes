#pragma once
#include "core.h"

struct Macro_Def
{
	uint16 keycode;
	String app_name;
	String command;
};

void load_macros();

bool has_macro_for(uint16 keycode);
void run_command(uint16 keycode);
