#include "permissions.h"
#include "core.h"

#include <ApplicationServices/ApplicationServices.h>
#include <IOKit/hidsystem/IOHIDLib.h>
#include <cstdlib>

static const char* perm_name(PERMISSION perm)
{
	switch (perm)
	{
		case PERMISSION::Accessibility:    return "Accessibility";
		case PERMISSION::Input_Monitoring: return "Input Monitoring";
	}
	return "Unknown";
}

bool has_permission(PERMISSION perm)
{
	switch (perm)
	{
		case PERMISSION::Accessibility:
			return AXIsProcessTrusted();
		case PERMISSION::Input_Monitoring:
			return IOHIDCheckAccess(kIOHIDRequestTypeListenEvent) == kIOHIDAccessTypeGranted;
	}
	return false;
}

void request_permission(PERMISSION perm)
{
	switch (perm)
	{
		case PERMISSION::Accessibility:
		{
			const void* keys[]   = { kAXTrustedCheckOptionPrompt };
			const void* values[] = { kCFBooleanTrue };
			CFDictionaryRef opts = CFDictionaryCreate(kCFAllocatorDefault, keys, values, 1, &kCFTypeDictionaryKeyCallBacks, &kCFTypeDictionaryValueCallBacks);
			AXIsProcessTrustedWithOptions(opts);
			CFRelease(opts);
			break;
		}
		case PERMISSION::Input_Monitoring:
			IOHIDRequestAccess(kIOHIDRequestTypeListenEvent);
			break;
	}
}

void open_settings(PERMISSION perm)
{
	const char* url = "";
	switch (perm)
	{
		case PERMISSION::Accessibility:
			url = "x-apple.systempreferences:com.apple.preference.security?Privacy_Accessibility";
			break;
		case PERMISSION::Input_Monitoring:
			url = "x-apple.systempreferences:com.apple.preference.security?Privacy_ListenEvent";
			break;
	}

	char cmd[256];
	int32 len = mc::format_to(cmd, "open \"{}\"", url);
	cmd[len] = '\0';
	system(cmd);
}

bool ensure_permissions()
{
	const PERMISSION needed[] = { PERMISSION::Input_Monitoring, PERMISSION::Accessibility };

	bool all_granted = true;
	for (PERMISSION perm : needed)
	{
		if (has_permission(perm))
		{
			println("[perms] {}: granted", perm_name(perm));
			continue;
		}

		all_granted = false;
		println("[perms] {}: missing -> prompting + opening System Settings", perm_name(perm));
		request_permission(perm);
		open_settings(perm);
	}

	if (!all_granted)
	{
		println("");
		println("strokes needs the permissions listed above.");
		println("Grant them in System Settings > Privacy & Security, then re-run strokes.");
	}

	return all_granted;
}
