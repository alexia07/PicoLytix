#!/bin/bash

# Check if clang-format is installed
if ! command -v clang-format &> /dev/null; then
    echo "❌ Error: clang-format is not installed."
    exit 1
fi

echo "🎨 Checking and Formatting C/C++ files in PicoLytix..."

SEARCH_DIRS=("src" "config" "board" "tests")

violations=0
total_files=0

for dir in "${SEARCH_DIRS[@]}"; do
    if [[ -d "$dir" ]]; then
        echo "   Scanning: $dir/"
        
        while IFS= read -r file; do
            total_files=$((total_files + 1))
            
            # 1. Capture BEFORE
            before_hash=$(md5sum "$file" | awk '{print $1}')
            
            # 2. Format
            clang-format -i -style=file "$file"
            
            # 3. Capture AFTER
            after_hash=$(md5sum "$file" | awk '{print $1}')
            
            # 4. Compare
            if [[ "$before_hash" != "$after_hash" ]]; then
                echo "      ❌ Modified: $file"
                violations=$((violations + 1))
            fi
        done < <(find "$dir" -type f \( -name "*.c" -o -name "*.h" -o -name "*.cpp" -o -name "*.hpp" \) | grep -v "Unity" | grep -v "CMock")
        
    else
        echo "   ⚠️  Directory $dir not found, skipping."
    fi
done

echo "----------------------------------------"
echo "Total files checked: $total_files"
echo "Files modified:      $violations"

if [[ $violations -gt 0 ]]; then
    echo "❌ Formatting check FAILED! $violations file(s) were not properly formatted."
    echo "   Please commit the changes made by this script."
    exit 1
else
    echo "✅ All files are properly formatted."
    exit 0
fi