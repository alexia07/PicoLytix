#!/bin/bash

# Exit immediately if a command exits with a non-zero status
set -e

echo "🔍 Running Cppcheck on PicoLytix..."

# Check if cppcheck is installed
if ! command -v cppcheck &> /dev/null; then
    echo "❌ Error: cppcheck is not installed."
    exit 1
fi

# Define the check command
# --enable=all: Enable all checking classes (warning, style, performance, portability, information)
# --inconclusive: Enable checks that might generate false positives (good for deep dives)
# --error-exitcode=1: CRITICAL - Returns 1 if any issues are found
# --suppress: Ignore specific noisy warnings (adjust as needed)
cppcheck --enable=warning,performance,portability \
         --inconclusive \
         --error-exitcode=1 \
         --std=c11 \
         --suppress=missingIncludeSystem \
         --suppress=missingInclude \
         --suppress=unusedFunction \
         --suppress=constStatement \
         -I src \
         src/

# If cppcheck finishes without errors, it reaches here
echo "✅ Cppcheck passed! No issues found."
exit 0