#!/bin/bash
# Install + start the strokes LaunchAgent.
# Grant Input Monitoring + Accessibility in a foreground run FIRST, or the agent
# won't receive/post events.
set -e

LABEL="com.strokes.agent"
SRC="$(cd "$(dirname "$0")" && pwd)/packaging/${LABEL}.plist"
DST="$HOME/Library/LaunchAgents/${LABEL}.plist"

cp "$SRC" "$DST"

# Reload cleanly: bootout if already loaded (ignore if not), then bootstrap.
launchctl bootout "gui/$(id -u)/${LABEL}" 2>/dev/null || true
launchctl bootstrap "gui/$(id -u)" "$DST"

echo "strokes agent installed and started."
echo "logs:  tail -f $HOME/dev/strokes/strokes.log"
echo "stop:  ./uninstall.sh"
