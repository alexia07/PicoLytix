#!/bin/bash

# Check if clang-format is installed
if ! command -v clang-format &> /dev/null; then
    echo "❌ Error: clang-format is not installed."
    echo "   Install it with: sudo apt install clang-format (Ubuntu/Debian)"
    echo "   Or: brew install clang-format (macOS)"
    exit 1
fi

echo "🎨 Checking and Formatting C/C++ files in PicoLytix..."

# Define the directories to search
SEARCH_DIRS=("src" "config" "board" "tests")

# Counter for files that needed formatting
violations=0
total_files=0

for dir in "${SEARCH_DIRS[@]}"; do
    if [ -d "$dir" ]; then
        echo "   Scanning: $dir/"
        
        # Find all relevant files
        while IFS= read -r -d '' file; do
            total_files=$((total_files + 1))
            
            # 1. Capture the state BEFORE formatting
            before_hash=$(md5sum "$file" | awk '{print $1}')
            
            # 2. Format the file in-place
            clang-format -i -style=file "$file"
            
            # 3. Capture the state AFTER formatting
            after_hash=$(md5sum "$file" | awk '{print $1}')
            
            # 4. Compare hashes
            if [ "$before_hash" != "$after_hash" ]; then
                echo "      ❌ Modified: $file"
                violations=$((violations + 1))
            fi
        done < <(find "$dir" -type f \( -name "*.c" -o -name "*.h" -o -name "*.cpp" -o -name "*.hpp" \) -print0)
        
    else
        echo "   ⚠️  Directory $dir not found, skipping."
    fi
done

echo "----------------------------------------"
echo "Total files checked: $total_files"
echo "Files modified:      $violations"

if [ $violations -gt 0 ]; then
    echo "❌ Formatting check FAILED! $violations file(s) were not properly formatted."
    echo "   Please commit the changes made by this script."
    exit 1
else
    echo "✅ All files are properly formatted."
    exit 0
fi