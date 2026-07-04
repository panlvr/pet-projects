#!/bin/bash

SUCCESS=0
FAIL=0
COUNTER=0

SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
PROJECT_DIR="$(dirname "$SCRIPT_DIR")"

TEST_FILE_1="$SCRIPT_DIR/test_files/sample.txt"
TEST_FILE_2="$SCRIPT_DIR/test_files/mixed.txt"

run_test() {
    FLAGS="$1"
    FILES="$2"

    (( COUNTER++ ))

    "$PROJECT_DIR/s21_cat" $FLAGS $FILES > "$SCRIPT_DIR/s21_cat_output.txt" 2>&1
    cat $FLAGS $FILES > "$SCRIPT_DIR/real_cat_output.txt" 2>&1

    if diff -q "$SCRIPT_DIR/s21_cat_output.txt" "$SCRIPT_DIR/real_cat_output.txt" > /dev/null
    then
        echo "SUCCESS: cat $FLAGS $FILES"
        (( SUCCESS++ ))
    else
        echo "FAIL: cat $FLAGS $FILES"
        echo "----------- YOUR OUTPUT -----------"
        cat "$SCRIPT_DIR/s21_cat_output.txt"
        echo "----------- REAL CAT -------------"
        cat "$SCRIPT_DIR/real_cat_output.txt"
        echo "----------------------------------"
        (( FAIL++ ))
    fi

    rm -f "$SCRIPT_DIR/s21_cat_output.txt" "$SCRIPT_DIR/real_cat_output.txt"
}

# BASIC
run_test "" "$TEST_FILE_1"
run_test "" "$TEST_FILE_2"

# SINGLE FLAGS
run_test "-b" "$TEST_FILE_2"
run_test "-e" "$TEST_FILE_2"
run_test "-n" "$TEST_FILE_2"
run_test "-s" "$TEST_FILE_2"
run_test "-t" "$TEST_FILE_2"
run_test "-v" "$TEST_FILE_2"

# GNU LONG OPTIONS
run_test "--number" "$TEST_FILE_1"
run_test "--number-nonblank" "$TEST_FILE_2"
run_test "--show-ends" "$TEST_FILE_2"
run_test "--show-tabs" "$TEST_FILE_2"
run_test "--show-nonprinting" "$TEST_FILE_2"
run_test "--squeeze-blank" "$TEST_FILE_2"

# COMBINED FLAGS
run_test "-be" "$TEST_FILE_2"
run_test "-bn" "$TEST_FILE_2"
run_test "-et" "$TEST_FILE_2"
run_test "-sv" "$TEST_FILE_2"
run_test "-bensvt" "$TEST_FILE_2"

# MIXED SHORT/LONG OPTIONS
run_test "-n --show-ends" "$TEST_FILE_1"
run_test "--number-nonblank -T" "$TEST_FILE_2"
run_test "--show-nonprinting --show-tabs" "$TEST_FILE_2"


# MULTIPLE FILES
run_test "-n" "$TEST_FILE_1 $TEST_FILE_2"
run_test "-s" "$TEST_FILE_1 $TEST_FILE_2"

# INVALID FLAG
(( COUNTER++ ))

"$PROJECT_DIR/s21_cat" -Q "$TEST_FILE_1" > /dev/null 2>&1

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