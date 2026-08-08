#include "core.h"
#include "apple_utils.h"
#include "permissions.h"
#include "event_tap.h"

int main(int argc, char** argv)
{
	if (!ensure_permissions())
		return 1;

	String app_name = get_focused_app_name();
	println("focused app: {}", app_name);

	create_event_tap();

	return 0;
}
