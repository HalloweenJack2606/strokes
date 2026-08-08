#include "macros.h"
#include "keycodes.h"
#include "apple_utils.h"

#include "toml/toml.hpp"

namespace
{
	const String macro_path = "macros.toml";
	Table<String_ID, Macro_Def> macros;
}

void print_macro_def(const Macro_Def& def)
{
	println("app={}, key={}, cmd={}", def.app_name, def.keycode, def.command);
}

void print_macros()
{
	for(const auto [k, v] : macros)
		print_macro_def(v);
}

void parse_macro(const toml::table& t)
{
	const char* keycode_trigger = (t["keycode"].value<std::string>())->c_str();

	Macro_Def def {
		.keycode = keycode_from_name(keycode_trigger),
		.app_name = (t["app_name"].value<std::string>())->c_str(),
		.command = (t["command"].value<std::string>())->c_str()
	};

	auto id = sid(format("{}-{}", def.app_name, def.keycode));
	table_add(macros, id, def);
}

void load_macros()
{
	const auto tbl = toml::parse_file(get_data(macro_path));

	if(const auto* arr = tbl["macro"].as_array())
		for(const auto& entry : *arr)
			if(const auto* t = entry.as_table())
				parse_macro(*t);

	print_macros();
}

const Macro_Def* find_macro(uint16 keycode)
{
	String focused_app = get_focused_app_name();
	auto id = sid(format("{}-{}", focused_app, keycode));

	auto it = table_find(macros, id);
	if(it == end(macros))
		return nullptr;

	return &it->second;
}
