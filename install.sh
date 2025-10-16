#!/bin/bash
set -e 

SRC="mytodo.cpp"
BIN="mytodo"
TARGET="/usr/local/bin/$BIN"
UNINSTALLER_SRC="uninstall.sh"
UNINSTALLER_TARGET="/usr/local/bin/uninstall_mytodo.sh"

echo "[+] Compiling $SRC..."
g++ "$SRC" -o "$BIN" -std=c++17

echo "[+] Installing to $TARGET..."

if [ -f "$TARGET" ]; then
    sudo mv "$TARGET" "$TARGET.bak"
    echo "[!] Existing binary found. Backed up to $TARGET.bak"
fi

sudo mv "$BIN" "$TARGET"
sudo chmod +x "$TARGET"

if [ -f "$UNINSTALLER_SRC" ]; then
    sudo cp "$UNINSTALLER_SRC" "$UNINSTALLER_TARGET"
    sudo chmod +x "$UNINSTALLER_TARGET"
    echo "[+] Uninstaller installed at $UNINSTALLER_TARGET"
else
    echo "[!] Uninstall script not found, skipping..."
fi

echo ""
echo "[✔] Installed successfully!"
echo "You can now use the command:"
echo "   mytodo help"

echo ""
echo "Follow:"
echo "  X: https://x.com/shadowkatanax"
echo "  GitHub: https://github.com/PIYUSH-GIRI/"

