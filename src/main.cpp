#include "core.h"
#include "permissions.h"
#include "event_tap.h"
#include "macros.h"

#include "stl/filesystem.h"

void parse_args(int32 argc, char** argv)
{
	for(int32 i = 0; i < argc; i++)
	{
		String arg = argv[i];
		const String prefix = "--working-dir=";
		if(find(arg, prefix, 0) == 0) {
			mc::Path dir = substr(arg, get_size(prefix));
			mc::set_current_path(dir);
		}
	}
}

int main(int argc, char** argv)
{
	parse_args(argc, argv);
	if (!ensure_permissions())
		return 1;

	load_macros();
	create_event_tap();

	return 0;
}
