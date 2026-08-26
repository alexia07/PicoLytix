#!/bin/bash
set -e

echo "🧪 Compiling Unit Tests..."

SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
PROJECT_ROOT="$(dirname "$SCRIPT_DIR")"

UNITY_DIR="$SCRIPT_DIR/Unity"
MOCKS_DIR="$SCRIPT_DIR/mocks"

# Define the source files to compile
# 1. Your Test File
TEST_FILE="$SCRIPT_DIR/test_m_i2c.c"

# 2. Your Actual Project Source (The code under test)
SOURCE_FILES=(
    "$PROJECT_ROOT/src/modules/m_i2c.c"
    # "$PROJECT_ROOT/src/modules/m_led.c"
)

# 3. Mock Implementations (Fake hardware)
MOCK_FILE="$MOCKS_DIR/mock_hardware.c"

# 4. Unity Core
UNITY_CORE="$UNITY_DIR/src/unity.c"

# Build the list of all C files
ALL_FILES="$TEST_FILE $MOCK_FILE $UNITY_CORE"
for src in "${SOURCE_FILES[@]}"; do
    if [ -f "$src" ]; then
        ALL_FILES="$ALL_FILES $src"
    else
        echo "⚠️  Warning: Source file not found: $src"
    fi
done

echo "   Compiling: $ALL_FILES"

# Compile Command
gcc -I"$SCRIPT_DIR" \
    -I"$MOCKS_DIR" \
    -I"$PROJECT_ROOT" \
    -I"$PROJECT_ROOT/src" \
    -I"$PROJECT_ROOT/src/modules" \
    -I"$UNITY_DIR/src" \
    $ALL_FILES \
    -o "$SCRIPT_DIR/test_runner"

echo "🏃 Running Tests..."
"$SCRIPT_DIR/test_runner"