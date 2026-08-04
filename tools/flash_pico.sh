#!/bin/bash

# Configuration
PROJECT_NAME="PicoLytix" # Change this if your project name differs
BUILD_DIR="build"
MOUNT_POINT="/run/media/$USER/RP2350"

# Find the .uf2 file
UF2_FILE=$(find "$BUILD_DIR" -name "*.uf2" | head -n 1)

if [ -z "$UF2_FILE" ]; then
    echo "❌ Error: No .uf2 file found in $BUILD_DIR. Did you build the project?"
    exit 1
fi

echo "🔍 Found firmware: $UF2_FILE"

# Check if Pico is mounted
if [ ! -d "$MOUNT_POINT" ]; then
    echo "❌ Error: Pico drive not found at $MOUNT_POINT."
    echo "💡 Action Required: Hold the BOOTSEL button while plugging in the Pico."
    exit 1
fi

# Copy the file
echo "⚡ Flashing $PROJECT_NAME to Pico..."
cp "$UF2_FILE" "$MOUNT_POINT/"

if [ $? -eq 0 ]; then
    echo "✅ Success! The Pico will automatically reboot and run the new code."
    echo "   The drive will disappear shortly."
else
    echo "❌ Error: Failed to copy file."
    exit 1
fi