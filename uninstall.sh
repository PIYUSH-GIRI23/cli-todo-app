#!/bin/bash

TARGET="/usr/local/bin/mytodo"
UNINSTALLER="/usr/local/bin/uninstall_mytodo.sh"
FILE_PATH="$HOME/.mytodo_store.txt"

echo "[⚙] Preparing to uninstall mytodo..."

read -p "Are you sure you want to uninstall mytodo and delete all data? [y/N] " confirm
if [[ "$confirm" != "y" && "$confirm" != "Y" ]]; then
    echo "Uninstallation aborted."
    exit 0
fi


if [ -f "$TARGET" ]; then
    sudo rm "$TARGET"
    echo "[✔] Removed binary: $TARGET"
else
    echo "[!] mytodo binary not found."
fi

if [ -f "$UNINSTALLER" ]; then
    sudo rm "$UNINSTALLER"
    echo "[✔] Removed uninstaller script."
else
    echo "[!] Uninstaller script not found."
fi

if [ -f "$FILE_PATH" ]; then
    rm "$FILE_PATH"
    echo "[✔] Removed todo text file: $FILE_PATH"
else
    echo "[!] todo text file not found."
fi

echo "[✔] Uninstallation complete. Bye!"
