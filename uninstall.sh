#!/bin/bash
# Stop + remove the strokes LaunchAgent. This is the real off-switch once the
# agent is running (the emergency-quit hotkey only helps a foreground run).
LABEL="com.strokes.agent"
DST="$HOME/Library/LaunchAgents/${LABEL}.plist"

launchctl bootout "gui/$(id -u)/${LABEL}" 2>/dev/null || true
rm -f "$DST"

echo "strokes agent stopped and removed."
