#!/bin/bash
# Dev convenience: after rebuild + re-sign, reload the running agent with the
# fresh binary. (The binary path is fixed, so KeepAlive picks up the new build.)
LABEL="com.strokes.agent"
launchctl kickstart -k "gui/$(id -u)/${LABEL}"
echo "strokes agent restarted."
