#!/bin/bash

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[0;33m'
BLUE='\033[0;34m'
PURPLE='\033[0;35m'
CYAN='\033[0;36m'
NC='\033[0m' # No Color

# Checker program based on OS
if [[ "$OSTYPE" == "darwin"* ]]; then
    CHECKER="./checker_Mac"
elif [[ "$OSTYPE" == "linux-gnu"* ]]; then
    CHECKER="./checker_linux"
else
    CHECKER="./checker_OS"
fi

# Make sure the checker is executable
chmod +x $CHECKER 2>/dev/null

# Set up temp directory for test files
TEMP_DIR=$(mktemp -d)
trap 'rm -rf "$TEMP_DIR"' EXIT

# Test function to display results
test_result() {
    if [ $1 -eq 0 ]; then
        echo -e "${GREEN}[PASS]${NC} $2"
        return 0
    else
        echo -e "${RED}[FAIL]${NC} $2"
        return 1
    fi
}

# Count instructions and verify sorting
verify_sorting() {
    ARG="$1"
    DESCRIPTION="$2"
    MAX_INSTRUCTIONS="$3"
    
    # Save instructions to a file
    INSTRUCTIONS_FILE="$TEMP_DIR/instructions.txt"
    ./push_swap $ARG > "$INSTRUCTIONS_FILE"
    
    # Count instructions
    COUNT=$(wc -l < "$INSTRUCTIONS_FILE" | tr -d ' ')
    
    # Check sorting with checker
    RESULT=$(cat "$INSTRUCTIONS_FILE" | $CHECKER $ARG)
    
    # Print test results
    if [[ "$RESULT" == "OK" && $COUNT -le $MAX_INSTRUCTIONS ]]; then
        echo -e "${GREEN}[PASS]${NC} $DESCRIPTION: $COUNT instructions (limit: $MAX_INSTRUCTIONS)"
        return 0
    elif [[ "$RESULT" != "OK" ]]; then
        echo -e "${RED}[FAIL]${NC} $DESCRIPTION: Checker says '$RESULT' instead of 'OK'"
        return 1
    else
        echo -e "${YELLOW}[WARN]${NC} $DESCRIPTION: $COUNT instructions (exceeds limit of $MAX_INSTRUCTIONS)"
        return 1
    fi
}

# Generate random array - more reliable than shuf
generate_random_array() {
    local size=$1
    local min=$2
    local max=$3
    local range=$((max - min + 1))
    local result=""
    
    # Use /dev/urandom as a more reliable source of randomness
    for ((i=0; i<size; i++)); do
        # Get a random number in the range [min, max]
        # Using modulo bias is acceptable for this test
        random_num=$(($(od -An -N4 -i /dev/urandom) % range + min))
        result="$result $random_num"
    done
    
    echo $result
}

# Generate unique random array
generate_unique_random_array() {
    local size=$1
    local min=$2
    local max=$3
    
    # For small arrays, ensure range is large enough
    if [ $((max - min + 1)) -lt $size ]; then
        echo "Error: Range too small for unique values"
        return 1
    fi
    
    local result=""
    local used_values=()
    
    while [ ${#used_values[@]} -lt $size ]; do
        # Get a random number using bash's $RANDOM (portable)
        random_num=$((RANDOM % (max - min + 1) + min))
        
        # Check if this value is already used
        local is_used=0
        for val in "${used_values[@]}"; do
            if [ $val -eq $random_num ]; then
                is_used=1
                break
            fi
        done
        
        # If not used, add it
        if [ $is_used -eq 0 ]; then
            used_values+=($random_num)
            result="$result $random_num"
        fi
    done
    
    echo $result
}

echo -e "${BLUE}============== PUSH_SWAP COMPREHENSIVE TESTER ==============${NC}"
echo -e "${CYAN}Testing push_swap implementation for correctness and efficiency${NC}"
echo -e "${CYAN}$(date)${NC}\n"

# ============= ERROR MANAGEMENT TESTS =============
echo -e "\n${PURPLE}============== ERROR MANAGEMENT ==============${NC}"

error_tests=0
error_passes=0

# Test with non-numeric parameter
echo -e "Testing with non-numeric parameter..."
result=$(./push_swap 42 abc 2>&1)
expected="Error"
if test_result "$(echo $result | grep -q "$expected"; echo $?)" "Non-numeric parameter: $result"; then
    ((error_passes++))
fi
((error_tests++))

# Test with duplicate parameter
echo -e "Testing with duplicate parameter..."
result=$(./push_swap 1 2 3 2 4 2>&1)
expected="Error"
if test_result "$(echo $result | grep -q "$expected"; echo $?)" "Duplicate parameter: $result"; then
    ((error_passes++))
fi
((error_tests++))

# Test with parameter > MAXINT
echo -e "Testing with parameter > MAXINT..."
result=$(./push_swap 2147483648 2>&1)
expected="Error"
if test_result "$(echo $result | grep -q "$expected"; echo $?)" "Parameter > MAXINT: $result"; then
    ((error_passes++))
fi
((error_tests++))

# Test with parameter < MININT
echo -e "Testing with parameter < MININT..."
result=$(./push_swap -2147483649 2>&1)
expected="Error"
if test_result "$(echo $result | grep -q "$expected"; echo $?)" "Parameter < MININT: $result"; then
    ((error_passes++))
fi
((error_tests++))

# Test with no parameters
echo -e "Testing with no parameters..."
result=$(./push_swap 2>&1)
expected=""
if test_result "$([ -z "$result" ]; echo $?)" "No parameters: '$result'"; then
    ((error_passes++))
fi
((error_tests++))

# Print error management summary
echo -e "\n${CYAN}Error Management Summary: $error_passes/$error_tests tests passed${NC}"
if [ $error_passes -eq $error_tests ]; then
    echo -e "${GREEN}All error management tests passed!${NC}"
else
    echo -e "${RED}Some error management tests failed!${NC}"
fi

# ============= IDENTITY TESTS =============
echo -e "\n${PURPLE}============== IDENTITY TESTS ==============${NC}"

identity_tests=0
identity_passes=0

# Test cases with already sorted arrays
test_cases=(
    "42"
    "2 3"
    "0 1 2 3"
    "0 1 2 3 4 5 6 7 8 9"
)

for case in "${test_cases[@]}"; do
    echo -e "Testing with already sorted list: '$case'"
    instructions=$(./push_swap $case | wc -l | tr -d ' ')
    if test_result "$([ $instructions -eq 0 ]; echo $?)" "Expected 0 instructions, got $instructions"; then
        ((identity_passes++))
    fi
    ((identity_tests++))
done

# Print identity test summary
echo -e "\n${CYAN}Identity Test Summary: $identity_passes/$identity_tests tests passed${NC}"
if [ $identity_passes -eq $identity_tests ]; then
    echo -e "${GREEN}All identity tests passed!${NC}"
else
    echo -e "${RED}Some identity tests failed!${NC}"
fi

# ============= SIMPLE VERSION TESTS (3 NUMBERS) =============
echo -e "\n${PURPLE}============== SIMPLE VERSION TESTS (3 NUMBERS) ==============${NC}"

simple3_tests=0
simple3_passes=0

# Test with specific 3-number cases
test_cases=(
    "2 1 0"
    "1 0 2"
    "0 2 1"
    "2 0 1"
    "1 2 0"
    "3 2 1"
)

for case in "${test_cases[@]}"; do
    echo -e "Testing with 3 numbers: '$case'"
    if verify_sorting "$case" "List '$case'" 3; then
        ((simple3_passes++))
    fi
    ((simple3_tests++))
done

# Test with 3 random permutations of 3 numbers
for i in {1..3}; do
    case=$(generate_unique_random_array 3 -50 50)
    echo -e "Testing with random 3 numbers ($i): '$case'"
    if verify_sorting "$case" "Random list '$case'" 3; then
        ((simple3_passes++))
    fi
    ((simple3_tests++))
done

# Print simple 3-number test summary
echo -e "\n${CYAN}Simple 3-Number Test Summary: $simple3_passes/$simple3_tests tests passed${NC}"
if [ $simple3_passes -eq $simple3_tests ]; then
    echo -e "${GREEN}All simple 3-number tests passed!${NC}"
else
    echo -e "${RED}Some simple 3-number tests failed!${NC}"
fi

# ============= SIMPLE VERSION TESTS (5 NUMBERS) =============
echo -e "\n${PURPLE}============== SIMPLE VERSION TESTS (5 NUMBERS) ==============${NC}"

simple5_tests=0
simple5_passes=0

# Test with specific 5-number cases
test_cases=(
    "1 5 2 4 3"
    "5 4 3 2 1"
    "3 1 5 2 4"
    "5 1 3 4 2"
)

for case in "${test_cases[@]}"; do
    echo -e "Testing with 5 numbers: '$case'"
    if verify_sorting "$case" "List '$case'" 12; then
        ((simple5_passes++))
    fi
    ((simple5_tests++))
done

# Test with 3 random permutations of 5 numbers
for i in {1..3}; do
    case=$(generate_unique_random_array 5 -50 50)
    echo -e "Testing with random 5 numbers ($i): '$case'"
    if verify_sorting "$case" "Random list '$case'" 12; then
        ((simple5_passes++))
    fi
    ((simple5_tests++))
done

# Print simple 5-number test summary
echo -e "\n${CYAN}Simple 5-Number Test Summary: $simple5_passes/$simple5_tests tests passed${NC}"
if [ $simple5_passes -eq $simple5_tests ]; then
    echo -e "${GREEN}All simple 5-number tests passed!${NC}"
else
    echo -e "${RED}Some simple 5-number tests failed!${NC}"
fi

# ============= MIDDLE VERSION (100 RANDOM VALUES) =============
echo -e "\n${PURPLE}============== MIDDLE VERSION (100 RANDOM VALUES) ==============${NC}"

middle_scores=()

# Run 2 tests with 100 random numbers
echo -e "${YELLOW}This may take a few moments...${NC}"
for i in {1..2}; do
    echo -e "\n${CYAN}Test run $i for 100 random numbers${NC}"
    
    # Generate random array
    ARG=$(generate_unique_random_array 100 -1000 1000)
    
    # Measure timing
    START_TIME=$(date +%s.%N)
    
    # Save instructions to a file
    INSTRUCTIONS_FILE="$TEMP_DIR/instructions_100_$i.txt"
    ./push_swap $ARG > "$INSTRUCTIONS_FILE"
    
    # Count instructions
    COUNT=$(wc -l < "$INSTRUCTIONS_FILE" | tr -d ' ')
    
    # Measure end time
    END_TIME=$(date +%s.%N)
    ELAPSED=$(echo "$END_TIME - $START_TIME" | bc)
    
    # Verify sorting
    RESULT=$(cat "$INSTRUCTIONS_FILE" | $CHECKER $ARG)
    
    # Print test results
    if [ "$RESULT" = "OK" ]; then
        echo -e "${GREEN}Sorting verification: OK${NC}"
        
        # Score based on instruction count
        if [ $COUNT -lt 700 ]; then
            echo -e "${GREEN}Excellent:${NC} $COUNT instructions (< 700) [5/5]"
            middle_scores+=("5")
        elif [ $COUNT -lt 900 ]; then
            echo -e "${GREEN}Great:${NC} $COUNT instructions (< 900) [4/5]"
            middle_scores+=("4")
        elif [ $COUNT -lt 1100 ]; then
            echo -e "${YELLOW}Good:${NC} $COUNT instructions (< 1100) [3/5]"
            middle_scores+=("3")
        elif [ $COUNT -lt 1300 ]; then
            echo -e "${YELLOW}Satisfactory:${NC} $COUNT instructions (< 1300) [2/5]"
            middle_scores+=("2")
        elif [ $COUNT -lt 1500 ]; then
            echo -e "${RED}Poor:${NC} $COUNT instructions (< 1500) [1/5]"
            middle_scores+=("1")
        else
            echo -e "${RED}Failed:${NC} $COUNT instructions (≥ 1500) [0/5]"
            middle_scores+=("0")
        fi
    else
        echo -e "${RED}Sorting verification failed: $RESULT${NC}"
        middle_scores+=("0")
    fi
    
    echo -e "Execution time: ${ELAPSED}s"
done

# Calculate average score
sum=0
for score in "${middle_scores[@]}"; do
    sum=$((sum + score))
done
avg=$(echo "scale=1; $sum / ${#middle_scores[@]}" | bc)

echo -e "\n${CYAN}Middle Version Summary${NC}"
echo -e "Test runs: ${#middle_scores[@]}"
echo -e "Scores: ${middle_scores[*]}"
echo -e "Average score: $avg/5"

# ============= ADVANCED VERSION (500 RANDOM VALUES) =============
echo -e "\n${PURPLE}============== ADVANCED VERSION (500 RANDOM VALUES) ==============${NC}"

advanced_scores=()

# Run 1 test with 500 random numbers (fewer to save time)
echo -e "${YELLOW}This may take some time...${NC}"
for i in {1..1}; do
    echo -e "\n${CYAN}Test run $i for 500 random numbers${NC}"
    
    # Generate random array (reducing the range for speed)
    ARG=$(generate_unique_random_array 500 -1000 1000)
    
    # Measure timing
    START_TIME=$(date +%s.%N)
    
    # Save instructions to a file
    INSTRUCTIONS_FILE="$TEMP_DIR/instructions_500_$i.txt"
    ./push_swap $ARG > "$INSTRUCTIONS_FILE"
    
    # Count instructions
    COUNT=$(wc -l < "$INSTRUCTIONS_FILE" | tr -d ' ')
    
    # Measure end time
    END_TIME=$(date +%s.%N)
    ELAPSED=$(echo "$END_TIME - $START_TIME" | bc)
    
    # Verify sorting
    RESULT=$(cat "$INSTRUCTIONS_FILE" | $CHECKER $ARG)
    
    # Print test results
    if [ "$RESULT" = "OK" ]; then
        echo -e "${GREEN}Sorting verification: OK${NC}"
        
        # Score based on instruction count
        if [ $COUNT -lt 5500 ]; then
            echo -e "${GREEN}Excellent:${NC} $COUNT instructions (< 5500) [5/5]"
            advanced_scores+=("5")
        elif [ $COUNT -lt 7000 ]; then
            echo -e "${GREEN}Great:${NC} $COUNT instructions (< 7000) [4/5]"
            advanced_scores+=("4")
        elif [ $COUNT -lt 8500 ]; then
            echo -e "${YELLOW}Good:${NC} $COUNT instructions (< 8500) [3/5]"
            advanced_scores+=("3")
        elif [ $COUNT -lt 10000 ]; then
            echo -e "${YELLOW}Satisfactory:${NC} $COUNT instructions (< 10000) [2/5]"
            advanced_scores+=("2")
        elif [ $COUNT -lt 11500 ]; then
            echo -e "${RED}Poor:${NC} $COUNT instructions (< 11500) [1/5]"
            advanced_scores+=("1")
        else
            echo -e "${RED}Failed:${NC} $COUNT instructions (≥ 11500) [0/5]"
            advanced_scores+=("0")
        fi
    else
        echo -e "${RED}Sorting verification failed: $RESULT${NC}"
        advanced_scores+=("0")
    fi
    
    echo -e "Execution time: ${ELAPSED}s"
done

# Calculate average score
sum=0
for score in "${advanced_scores[@]}"; do
    sum=$((sum + score))
done
avg=$(echo "scale=1; $sum / ${#advanced_scores[@]}" | bc)

echo -e "\n${CYAN}Advanced Version Summary${NC}"
echo -e "Test runs: ${#advanced_scores[@]}"
echo -e "Scores: ${advanced_scores[*]}"
echo -e "Average score: $avg/5"

# ============= BONUS: CHECKER PROGRAM =============
if [ -f "./checker" ]; then
    echo -e "\n${PURPLE}============== BONUS: CHECKER PROGRAM ==============${NC}"
    
    bonus_tests=0
    bonus_passes=0
    
    # Error management tests for checker
    echo -e "\n${CYAN}Checker Error Management:${NC}"
    
    # Test with non-numeric parameter
    echo -e "Testing with non-numeric parameter..."
    result=$(./checker 42 abc 2>&1)
    expected="Error"
    if test_result "$(echo $result | grep -q "$expected"; echo $?)" "Non-numeric parameter: $result"; then
        ((bonus_passes++))
    fi
    ((bonus_tests++))
    
    # Test with duplicate parameter
    echo -e "Testing with duplicate parameter..."
    result=$(./checker 1 2 3 2 4 2>&1)
    expected="Error"
    if test_result "$(echo $result | grep -q "$expected"; echo $?)" "Duplicate parameter: $result"; then
        ((bonus_passes++))
    fi
    ((bonus_tests++))
    
    # Test with parameter > MAXINT
    echo -e "Testing with parameter > MAXINT..."
    result=$(./checker 2147483648 2>&1)
    expected="Error"
    if test_result "$(echo $result | grep -q "$expected"; echo $?)" "Parameter > MAXINT: $result"; then
        ((bonus_passes++))
    fi
    ((bonus_tests++))
    
    # Test with invalid instructions
    echo -e "\n${CYAN}Checker Invalid Instructions:${NC}"
    
    # Test with invalid instruction
    echo -e "Testing with invalid instruction..."
    result=$(echo "abc" | ./checker 0 1 2 2>&1)
    expected="Error"
    if test_result "$(echo $result | grep -q "$expected"; echo $?)" "Invalid instruction: $result"; then
        ((bonus_passes++))
    fi
    ((bonus_tests++))
    
    # Test with instruction with spaces
    echo -e "Testing with instruction with spaces..."
    result=$(echo " sa" | ./checker 0 1 2 2>&1)
    expected="Error"
    if test_result "$(echo $result | grep -q "$expected"; echo $?)" "Instruction with spaces: $result"; then
        ((bonus_passes++))
    fi
    ((bonus_tests++))
    
    # Test KO result
    echo -e "\n${CYAN}Checker KO Tests:${NC}"
    
    # Test with instructions that don't sort
    echo -e "Testing with instructions that don't sort the list..."
    result=$(echo -e "sa\npb\nrrr" | ./checker 0 9 1 8 2 7 3 6 4 5 2>&1)
    expected="KO"
    if test_result "$(echo $result | grep -q "$expected"; echo $?)" "Instructions that don't sort: $result"; then
        ((bonus_passes++))
    fi
    ((bonus_tests++))
    
    # Test OK result
    echo -e "\n${CYAN}Checker OK Tests:${NC}"
    
    # Test with already sorted list
    echo -e "Testing with already sorted list..."
    result=$(echo "" | ./checker 0 1 2 2>&1)
    expected="OK"
    if test_result "$(echo $result | grep -q "$expected"; echo $?)" "Already sorted list: $result"; then
        ((bonus_passes++))
    fi
    ((bonus_tests++))
    
    # Test with instructions that sort
    echo -e "Testing with instructions that sort the list..."
    result=$(echo -e "pb\nra\npb\nra\nsa\nra\npa\npa" | ./checker 0 9 1 8 2 2>&1)
    expected="OK"
    if test_result "$(echo $result | grep -q "$expected"; echo $?)" "Instructions that sort: $result"; then
        ((bonus_passes++))
    fi
    ((bonus_tests++))
    
    # Print bonus test summary
    echo -e "\n${CYAN}Bonus Test Summary: $bonus_passes/$bonus_tests tests passed${NC}"
    if [ $bonus_passes -eq $bonus_tests ]; then
        echo -e "${GREEN}All bonus tests passed!${NC}"
    else
        echo -e "${RED}Some bonus tests failed!${NC}"
    fi
fi

# ============= OVERALL SUMMARY =============
echo -e "\n${PURPLE}============== OVERALL SUMMARY ==============${NC}"
echo -e "${CYAN}Error Management:${NC} $error_passes/$error_tests tests passed"
echo -e "${CYAN}Identity Tests:${NC} $identity_passes/$identity_tests tests passed"
echo -e "${CYAN}Simple 3-Number Tests:${NC} $simple3_passes/$simple3_tests tests passed"
echo -e "${CYAN}Simple 5-Number Tests:${NC} $simple5_passes/$simple5_tests tests passed"
echo -e "${CYAN}Middle Version (100):${NC} Average score $avg/5"
echo -e "${CYAN}Advanced Version (500):${NC} Average score $avg/5"

if [ -f "./checker" ]; then
    echo -e "${CYAN}Bonus Tests:${NC} $bonus_passes/$bonus_tests tests passed"
fi

echo -e "\n${BLUE}============== TESTS COMPLETED ==============${NC}"

