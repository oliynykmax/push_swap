#!/bin/bash

# Generate a random permutation of 100 unique integers (1 to 100)
ARRAY=$(shuf -i 1-500 | tr '\n' ' ')

echo "Testing with array:"
echo "$ARRAY"

# Run push_swap and count the number of operations
echo "Operation count:"
./push_swap $ARRAY | tee ops.txt | wc -l

# Check if the output is valid (optional, if you have a checker)
if [ -x ./checker ]; then
    ./push_swap $ARRAY | ./checker $ARRAY
fi

# Run with AddressSanitizer (if compiled with -fsanitize=address)
echo "Running with AddressSanitizer (if enabled in binary):"
ASAN_OPTIONS=detect_leaks=1 ./push_swap $ARRAY

# Or run with Valgrind (uncomment if you want to use Valgrind)
# valgrind --leak-check=full --show-leak-kinds=all ./push_swap $ARRAY

# Clean up
rm -f ops.txt

