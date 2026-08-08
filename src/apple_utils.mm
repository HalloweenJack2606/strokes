#include "apple_utils.h"
#import <Cocoa/Cocoa.h>

String get_focused_app_name()
{
	@autoreleasepool
	{
		NSRunningApplication* app = [[NSWorkspace sharedWorkspace] frontmostApplication];
		String app_name = mc::make_string(app.localizedName.UTF8String);
		return app_name;
	}
}
