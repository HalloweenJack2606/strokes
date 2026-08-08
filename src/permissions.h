#pragma once

enum class PERMISSION
{
	Accessibility,      // @note: input write
	Input_Monitoring,   // @note: input read
};

bool has_permission(PERMISSION perm);
void request_permission(PERMISSION perm);
void open_settings(PERMISSION perm);

bool ensure_permissions();
