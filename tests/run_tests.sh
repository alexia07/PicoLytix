#!/bin/bash
set -e

echo "🧪 Compiling Unit Tests with Coverage..."

SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
PROJECT_ROOT="$(dirname "$SCRIPT_DIR")"

# Ensure coverage artifacts land in a predictable place for lcov capture
cd "$PROJECT_ROOT"

UNITY_DIR="$SCRIPT_DIR/Unity"
MOCKS_DIR="$SCRIPT_DIR/mocks"
COVERAGE_DIR="$SCRIPT_DIR/coverage"

# Create coverage output directory
mkdir -p "$COVERAGE_DIR"

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
    if [[ -f "$src" ]]; then
        ALL_FILES="$ALL_FILES $src"
    else
        echo "⚠️  Warning: Source file not found: $src"
    fi
done

echo "   Compiling: $ALL_FILES"

# Compile Command with Coverage Flags
# -fprofile-arcs -ftest-coverage: Generate data for gcov
# -O0: Disable optimization (crucial for accurate line mapping)
# -g: Include debug symbols
gcc -fprofile-arcs -ftest-coverage -O0 -g \
    -I"$SCRIPT_DIR" \
    -I"$MOCKS_DIR" \
    -I"$PROJECT_ROOT" \
    -I"$PROJECT_ROOT/src" \
    -I"$PROJECT_ROOT/src/modules" \
    -I"$UNITY_DIR/src" \
    $ALL_FILES \
    -o "$SCRIPT_DIR/test_runner"

echo "🏃 Running Tests..."
# Run the tests. This generates .gcda files
"$SCRIPT_DIR/test_runner"

echo "📊 Generating Coverage Report..."

# Capture coverage data using lcov
# --capture: Collect data
# --directory .: Look in current directory for .gcda files
# --output-file: Destination
# --gcov-tool gcov: Explicitly define gcov path if needed
lcov --capture \
     --directory "$PROJECT_ROOT" \
     --output-file "$COVERAGE_DIR/coverage.info" \
     --gcov-tool gcov

# Optional: Remove coverage data for non-source files (like Unity core or mocks) 
# to keep the report clean for SonarCloud
lcov --remove "$COVERAGE_DIR/coverage.info" \
     '*/Unity/*' \
     '*/mocks/*' \
     '*/test_*.c' \
     --output-file "$COVERAGE_DIR/coverage.info"

echo "✅ Coverage report generated at: $COVERAGE_DIR/coverage.info"
echo "   You can now upload this file to SonarCloud."