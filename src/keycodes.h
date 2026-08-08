#pragma once
#include "stl/platform.h"

constexpr uint16 KEYCODE_INVALID = 0xFFFF;

uint16 keycode_from_name(const char* name);

const char* name_from_keycode(uint16 code);
