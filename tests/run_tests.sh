#!/bin/bash
set -e

echo "🧪 Compiling Unit Tests..."

SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
PROJECT_ROOT="$(dirname "$SCRIPT_DIR")"

# Find Unity
UNITY_DIR="$SCRIPT_DIR/Unity"
if [ ! -d "$UNITY_DIR" ]; then
    echo "❌ Error: Unity not found. Run: git submodule update --init --recursive"
    exit 1
fi

MOCKS_DIR="$SCRIPT_DIR/mocks"

# Compile Command
# 1. Include paths: Tests, Project Src, Mocks, Unity
# 2. Sources: Test file, Mock implementations, Unity core
gcc -I"$SCRIPT_DIR" \
    -I"$PROJECT_ROOT/src" \
    -I"$MOCKS_DIR" \
    -I"$UNITY_DIR/src" \
    "$SCRIPT_DIR/test_m_i2c.c" \
    "$MOCKS_DIR/mock_hardware.c" \
    "$UNITY_DIR/src/unity.c" \
    -o "$SCRIPT_DIR/test_runner"

echo "🏃 Running Tests..."
"$SCRIPT_DIR/test_runner"