#import <Cocoa/Cocoa.h>

const char* get_focused_app_name() {
	@autoreleasepool {
		NSRunningApplication* app = [[NSWorkspace sharedWorkspace] frontmostApplication];
		return app.localizedName.UTF8String;
	}
}
