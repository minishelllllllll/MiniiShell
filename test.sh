#!/bin/bash

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

# Test counters
TESTS_RUN=0
TESTS_PASSED=0

# Function to run a test
run_test() {
    local test_name="$1"
    local command="$2"
    local expected_output="$3"
    
    echo -e "${YELLOW}Running test: $test_name${NC}"
    
    # Run the command and capture output
    actual_output=$(echo "$command" | ./minishell 2>&1)
    
    # Compare outputs
    if [ "$actual_output" = "$expected_output" ]; then
        echo -e "${GREEN}✓ PASS${NC}"
        ((TESTS_PASSED++))
    else
        echo -e "${RED}✗ FAIL${NC}"
        echo "Expected: '$expected_output'"
        echo "Actual:   '$actual_output'"
    fi
    
    ((TESTS_RUN++))
    echo ""
}

# Check if minishell binary exists
if [ ! -f "./minishell" ]; then
    echo -e "${RED}Error: minishell binary not found${NC}"
    exit 1
fi

echo "Starting minishell tests..."
echo "=========================="

# Test 1: Simple echo command
run_test "Echo test" "echo hello" "hello"

# Summary
echo "=========================="
echo "Tests run: $TESTS_RUN"
echo -e "Tests passed: ${GREEN}$TESTS_PASSED${NC}"
echo -e "Tests failed: ${RED}$((TESTS_RUN - TESTS_PASSED))${NC}"

if [ $TESTS_PASSED -eq $TESTS_RUN ]; then
    echo -e "${GREEN}All tests passed!${NC}"
    exit 0
else
    echo -e "${RED}Some tests failed!${NC}"
    exit 1
fi
