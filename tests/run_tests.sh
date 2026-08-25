#!/bin/bash
set -e

echo "🧪 Compiling Unit Tests..."

# Get the directory where this script lives
SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
PROJECT_ROOT="$(dirname "$SCRIPT_DIR")"

# Find Unity (Handle both 'tests/unity' and 'tests/Unity')
UNITY_DIR=""
if [ -d "$SCRIPT_DIR/unity" ]; then
    UNITY_DIR="$SCRIPT_DIR/unity"
elif [ -d "$SCRIPT_DIR/Unity" ]; then
    UNITY_DIR="$SCRIPT_DIR/Unity"
else
    echo "❌ Error: Unity framework not found in $SCRIPT_DIR"
    echo "   Please run: cd tests && git clone https://github.com/ThrowTheSwitch/Unity.git"
    exit 1
fi

echo "   Found Unity at: $UNITY_DIR"

# Compile the test file
# We compile ONLY the test file and unity.c. 
# We do NOT compile your actual m_i2c.c yet to avoid hardware dependencies.
# Instead, we rely on the mocks defined INSIDE test_m_i2c.c.
gcc -I"$SCRIPT_DIR" \
    -I"$PROJECT_ROOT/src" \
    -I"$PROJECT_ROOT/src/modules" \
    -I"$UNITY_DIR/src" \
    "$SCRIPT_DIR/test_m_i2c.c" \
    "$UNITY_DIR/src/unity.c" \
    -o "$SCRIPT_DIR/test_runner"

echo "🏃 Running Tests..."
"$SCRIPT_DIR/test_runner"