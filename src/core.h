#pragma once

#include "stl/str.h"
#include "stl/string_id.h"
#include "stl/optional.h"
#include "stl/print.h"
#include "stl/table.h"
#include "stl/pair.h"
#include "stl/dynamic_array.h"
#include "stl/static_array.h"
#include "stl/algorithm.h"

using mc::String_ID;
using mc::String;
using mc::Table;
using mc::Dynamic_Array;
using mc::Static_Array;

using mc::println;

inline String_ID sid(const char* str) { return mc::intern_string(str); }
inline String_ID sid(const mc::String_View& s) { return mc::intern_string(s); }

