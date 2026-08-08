#include "core.h"
#include "apple_utils.h"

int main(int argc, char** argv)
{
	String app_name = mc::make_string(get_focused_app_name());
	println("{} {} {}", app_name, app_name == "Termius", app_name == "Not Termius");
	return 0;
}
