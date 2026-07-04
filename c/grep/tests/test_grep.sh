#!/bin/bash

SUCCESS=0
FAIL=0
COUNTER=0

SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
PROJECT_DIR="$(dirname "$SCRIPT_DIR")"

TEST_FILE_1="$SCRIPT_DIR/test_files/sample.txt"
TEST_FILE_2="$SCRIPT_DIR/test_files/mixed.txt"
TEST_FILE_3="$SCRIPT_DIR/test_files/poem.txt"
TEST_FILE_4="$SCRIPT_DIR/test_files/server.log"

run_test() {
    FLAGS="$1"
    PATTERN="$2"
    FILES="$3"

    (( COUNTER++ ))

    "$PROJECT_DIR/s21_grep" $FLAGS "$PATTERN" $FILES > "$SCRIPT_DIR/s21_grep_output.txt" 2>&1
    grep $FLAGS "$PATTERN" $FILES > "$SCRIPT_DIR/real_grep_output.txt" 2>&1

    if diff -q "$SCRIPT_DIR/s21_grep_output.txt" "$SCRIPT_DIR/real_grep_output.txt" > /dev/null
    then
        echo "SUCCESS: grep $FLAGS '$PATTERN' $FILES"
        (( SUCCESS++ ))
    else
        echo "FAIL: grep $FLAGS '$PATTERN' $FILES"
        echo "----------- YOUR OUTPUT -----------"
        cat "$SCRIPT_DIR/s21_grep_output.txt"
        echo "----------- REAL GREP ------------"
        cat "$SCRIPT_DIR/real_grep_output.txt"
        echo "----------------------------------"
        (( FAIL++ ))
    fi

    rm -f "$SCRIPT_DIR/s21_grep_output.txt" "$SCRIPT_DIR/real_grep_output.txt"
}

# BASIC
run_test "" "apple" "$TEST_FILE_2"
run_test "" "banana" "$TEST_FILE_2"
run_test "" "ERROR" "$TEST_FILE_4"
run_test "" "silence" "$TEST_FILE_3"

# -i
run_test "-i" "apple" "$TEST_FILE_2"
run_test "-i" "APPLE" "$TEST_FILE_2"
run_test "-i" "error" "$TEST_FILE_4"

# -v
run_test "-v" "apple" "$TEST_FILE_2"
run_test "-v" "INFO" "$TEST_FILE_4"

# -c
run_test "-c" "apple" "$TEST_FILE_2"
run_test "-c" "ERROR" "$TEST_FILE_4"

# -l
run_test "-l" "apple" "$TEST_FILE_1 $TEST_FILE_2"
run_test "-l" "ERROR" "$TEST_FILE_3 $TEST_FILE_4"

# -n
run_test "-n" "apple" "$TEST_FILE_2"
run_test "-n" "wave" "$TEST_FILE_3"

# -e
run_test "-e" "apple" "$TEST_FILE_2"
run_test "-e" "ERROR" "$TEST_FILE_4"

# MULTIPLE FLAGS
run_test "-iv" "apple" "$TEST_FILE_2"
run_test "-in" "apple" "$TEST_FILE_2"
run_test "-cv" "apple" "$TEST_FILE_2"
run_test "-lv" "ERROR" "$TEST_FILE_4"
run_test "-ivn" "error" "$TEST_FILE_4"
run_test "-nvc" "INFO" "$TEST_FILE_4"

# MULTIPLE FILES
run_test "-n" "apple" "$TEST_FILE_1 $TEST_FILE_2"
run_test "-c" "ERROR" "$TEST_FILE_3 $TEST_FILE_4"
run_test "-l" "silence" "$TEST_FILE_1 $TEST_FILE_3"

# REGEX TESTS
run_test "" "app.*" "$TEST_FILE_2"
run_test "" "^First" "$TEST_FILE_2"
run_test "" "line$" "$TEST_FILE_2"
run_test "" "^\\[ERROR\\]" "$TEST_FILE_4"
run_test "" ".*memory.*" "$TEST_FILE_4"
run_test "" "^[A-Z].*" "$TEST_FILE_3"

# MULTIPLE -e
(( COUNTER++ ))

"$PROJECT_DIR/s21_grep" -e apple -e banana "$TEST_FILE_1" > "$SCRIPT_DIR/s21_grep_output.txt" 2>&1
grep -e apple -e banana "$TEST_FILE_1" > "$SCRIPT_DIR/real_grep_output.txt" 2>&1

if diff -q "$SCRIPT_DIR/s21_grep_output.txt" "$SCRIPT_DIR/real_grep_output.txt" > /dev/null
then
    echo "SUCCESS: multiple -e"
    (( SUCCESS++ ))
else
    echo "FAIL: multiple -e"
    echo "----------- YOUR OUTPUT -----------"
    cat "$SCRIPT_DIR/s21_grep_output.txt"
    echo "----------- REAL GREP ------------"
    cat "$SCRIPT_DIR/real_grep_output.txt"
    echo "----------------------------------"
    (( FAIL++ ))
fi

rm -f "$SCRIPT_DIR/s21_grep_output.txt" "$SCRIPT_DIR/real_grep_output.txt"

# INVALID FLAG
(( COUNTER++ ))

"$PROJECT_DIR/s21_grep" -Q apple "$TEST_FILE_1" > /dev/null 2>&1

if [ $? -ne 0 ]
then
    echo "SUCCESS: invalid flag"
    (( SUCCESS++ ))
else
    echo "FAIL: invalid flag"
    (( FAIL++ ))
fi

echo ""
echo "TOTAL: $COUNTER"
echo "SUCCESS: $SUCCESS"
echo "FAIL: $FAIL"