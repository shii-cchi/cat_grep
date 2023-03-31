#!/bin/bash

COUNT_SUCCESS=0
COUNT_FAIL=0
COMP_RES=""

for flag in -b -e -n -s -t #GNU: -E -T --number --squeeze-blank
do
    for TEST in test/test.txt test/test2.txt test/test3.txt
    do
        echo TEST with flag="$flag" file="$TEST"
        ./test_cat "$flag" "$TEST" > my_cat.txt
        cat "$flag" "$TEST" > cat.txt
        COMP_RES="$(diff -s my_cat.txt cat.txt)"
        if [ "$COMP_RES" == "Files my_cat.txt and cat.txt are identical" ]
            then
                ((COUNT_SUCCESS++))
                echo "SUCCESS"
            else
                ((COUNT_FAIL++))
                echo "FAIL"
            fi
                rm my_cat.txt cat.txt
    done
done

for flag in -b -e -n -s -t #GNU: -E -T --number --squeeze-blank
do
    TEST1="test/test.txt"
    TEST2="test/test2.txt"
    echo TEST with flag="$flag" file="$TEST1" "$TEST2"
    ./test_cat "$flag" "$TEST1" "$TEST2" > my_cat.txt
    cat "$flag" "$TEST1" "$TEST2" > cat.txt
    COMP_RES="$(diff -s my_cat.txt cat.txt)"
    if [ "$COMP_RES" == "Files my_cat.txt and cat.txt are identical" ]
        then
            ((COUNT_SUCCESS++))
            echo "SUCCESS"
        else
            ((COUNT_FAIL++))
            echo "FAIL"
        fi
            rm my_cat.txt cat.txt
done

for TEST in "test/test.txt" "test/test2.txt" "test/test3.txt"
do
    echo TEST file="$TEST"
    ./test_cat "$TEST" > my_cat.txt
    cat "$TEST" > cat.txt
    COMP_RES="$(diff -s my_cat.txt cat.txt)"
    if [ "$COMP_RES" == "Files my_cat.txt and cat.txt are identical" ]
        then
            ((COUNT_SUCCESS++))
            echo "SUCCESS"
        else
            ((COUNT_FAIL++))
            echo "FAIL"
        fi
            rm my_cat.txt cat.txt
done

TEST1="test/test.txt"
TEST2="test/test2.txt"
echo TEST file="$TEST1" "$TEST2"
./test_cat "$TEST1" "$TEST2" > my_cat.txt
cat "$TEST1" "$TEST2" > cat.txt
COMP_RES="$(diff -s my_cat.txt cat.txt)"
if [ "$COMP_RES" == "Files my_cat.txt and cat.txt are identical" ]
    then
        ((COUNT_SUCCESS++))
        echo "SUCCESS"
    else
        ((COUNT_FAIL++))
        echo "FAIL"
    fi
        rm my_cat.txt cat.txt
     
echo "SUCCESS: $COUNT_SUCCESS"
echo "FAIL: $COUNT_FAIL"
