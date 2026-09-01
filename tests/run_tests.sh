#!/bin/bash
set -e

echo "🧪 Compiling Unit Tests..."

SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
PROJECT_ROOT="$(dirname "$SCRIPT_DIR")"

UNITY_DIR="$SCRIPT_DIR/Unity"
MOCKS_DIR="$SCRIPT_DIR/mocks"

TEST_FILES=(
    "$SCRIPT_DIR/test_m_i2c.c"
)

SOURCE_FILES=(
    "$PROJECT_ROOT/src/modules/m_i2c.c"
)

MOCK_FILE="$MOCKS_DIR/mock_hardware.c"

UNITY_CORE="$UNITY_DIR/src/unity.c"

# Build the list of all C files
ALL_FILES="$TEST_FILES $MOCK_FILE $UNITY_CORE"
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