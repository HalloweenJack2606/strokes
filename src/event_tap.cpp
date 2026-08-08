#include "core.h"
#include "event_tap.h"
#include "macros.h"
#include "keycodes.h"
#include <ApplicationServices/ApplicationServices.h>
#include <dispatch/dispatch.h>
#include <unistd.h>
#include <cstdlib>

void type_text(const char* s)
{
	UniChar buf[256];
	UniCharCount n = 0;
	while(s[n] && n < 256) { buf[n] = (UniChar)(unsigned char)s[n]; ++n; }

	CGEventRef down = CGEventCreateKeyboardEvent(NULL, 0, true);
	CGEventKeyboardSetUnicodeString(down, n, buf);
	CGEventPost(kCGHIDEventTap, down);
	CFRelease(down);

	CGEventRef up = CGEventCreateKeyboardEvent(NULL, 0, false);
	CGEventKeyboardSetUnicodeString(up, n, buf);
	CGEventPost(kCGHIDEventTap, up);
	CFRelease(up);
}

void press_key(CGKeyCode key)
{
	CGEventRef down = CGEventCreateKeyboardEvent(NULL, key, true);
	CGEventPost(kCGHIDEventTap, down);
	CFRelease(down);

	CGEventRef up = CGEventCreateKeyboardEvent(NULL, key, false);
	CGEventPost(kCGHIDEventTap, up);
	CFRelease(up);
}

CGEventRef on_event(CGEventTapProxy proxy, CGEventType type, CGEventRef event, void* user_info)
{
	// @note: check if os killed tap first
	if(type == kCGEventTapDisabledByTimeout || type == kCGEventTapDisabledByUserInput)
	{
		CFMachPortRef tap = *(CFMachPortRef*)user_info;
		CGEventTapEnable(tap, true);
		return event;
	}

	uint16 keycode = CGEventGetIntegerValueField(event, kCGKeyboardEventKeycode);

	// @hack: emergency kill switch Ctrl+Opt+Cmd+Q always exits
	const CGEventFlags hyper = kCGEventFlagMaskControl | kCGEventFlagMaskAlternate | kCGEventFlagMaskCommand;
	if((CGEventGetFlags(event) & hyper) == hyper && keycode == keycode_from_name("Q"))
	{
		println("strokes: emergency quit");
		exit(0);
	}

	if(const Macro_Def* m = find_macro(keycode))
	{
		const char* command = get_data(m->command);
		dispatch_async(dispatch_get_global_queue(QOS_CLASS_USER_INTERACTIVE, 0), ^{
				type_text(command);
				usleep(20 * 1000); // @note: let chars commit before return
				press_key(36);
		});
		return NULL;
	}

	return event;
}

void create_event_tap()
{
	CFMachPortRef tap = CGEventTapCreate(kCGSessionEventTap, kCGHeadInsertEventTap, kCGEventTapOptionDefault, CGEventMaskBit(kCGEventKeyDown), on_event, &tap);

	mc_panic("failed to create tap", tap != NULL);

	CFRunLoopSourceRef ref = CFMachPortCreateRunLoopSource(kCFAllocatorDefault, tap, 0);
	CGEventTapEnable(tap, true);
	CFRunLoopAddSource(CFRunLoopGetCurrent(), ref, kCFRunLoopCommonModes);
	println("tap installed, listening...");
	CFRunLoopRun();
}
