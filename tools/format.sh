#!/bin/bash

# Check if clang-format is installed
if ! command -v clang-format &> /dev/null; then
    echo "❌ Error: clang-format is not installed."
    echo "   Install it with: sudo apt install clang-format (Ubuntu/Debian)"
    echo "   Or: brew install clang-format (macOS)"
    exit 1
fi

echo "🎨 Formatting C/C++ files in PicoLytix..."

# Define the directories to search (add more if needed)
SEARCH_DIRS=("src" "config" "board")

# Counter for formatted files
count=0

for dir in "${SEARCH_DIRS[@]}"; do
    if [ -d "$dir" ]; then
        echo "   Scanning: $dir/"
        
        # Find all .c and .h files recursively
        # -exec runs clang-format -i (in-place) on each found file
        # We use {} + to batch files for better performance
        found_files=$(find "$dir" -type f \( -name "*.c" -o -name "*.h" -o -name "*.cpp" -o -name "*.hpp" \))
        
        if [ -n "$found_files" ]; then
            echo "$found_files" | xargs clang-format -i -style=file
            count=$((count + $(echo "$found_files" | wc -l)))
        fi
    else
        echo "   ⚠️  Directory $dir not found, skipping."
    fi
done

if [ $count -gt 0 ]; then
    echo "✅ Successfully formatted $count files."
else
    echo "ℹ️  No C/C++ files found to format."
fi