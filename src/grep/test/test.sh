#!/bin/bash

COUNT_SUCCESS=0
COUNT_FAIL=0
COMP_RES=""
TEST="test/test.txt"

for flag in -e -i -v -c -l -n
do
    for str in 'is' 'IS' 'abcd' ''
    do
        echo TEST with flag="$flag" and str="$str" file="$TEST"
        ./test_grep "$flag" "$str" "$TEST" > my_grep.txt
        grep "$flag" "$str" "$TEST" > grep.txt
        COMP_RES="$(diff -s my_grep.txt grep.txt)"
        if [ "$COMP_RES" == "Files my_grep.txt and grep.txt are identical" ]
            then
                (( COUNT_SUCCESS++ ))
                echo "SUCCESS"
            else
                (( COUNT_FAIL++ ))
                echo "FAIL"
            fi
                rm my_grep.txt grep.txt
    done
done

for flag in -e -i -v -c -l -n
do
    for str in 'is' 'IS' 'abcd' ''
    do
        echo TEST with flag="$flag" and str="$str" file="$TEST" "$TEST"
        ./test_grep "$flag" "$str" "$TEST" "$TEST" > my_grep.txt
        grep "$flag" "$str" "$TEST" "$TEST" > grep.txt
        COMP_RES="$(diff -s my_grep.txt grep.txt)"
        if [ "$COMP_RES" == "Files my_grep.txt and grep.txt are identical" ]
            then
                (( COUNT_SUCCESS++ ))
                echo "SUCCESS"
            else
                (( COUNT_FAIL++ ))
                echo "FAIL"
            fi
                rm my_grep.txt grep.txt
    done
done

for str in 'is' 'IS' 'abcd' ''
do
    echo TEST with str="$str" file="$TEST"
    ./test_grep "$str" "$TEST" > my_grep.txt
    grep "$str" "$TEST" > grep.txt
    COMP_RES="$(diff -s my_grep.txt grep.txt)"
    if [ "$COMP_RES" == "Files my_grep.txt and grep.txt are identical" ]
        then
            (( COUNT_SUCCESS++ ))
            echo "SUCCESS"
        else
            (( COUNT_FAIL++ ))
            echo "FAIL"
        fi
            rm my_grep.txt grep.txt
done
    
for str in 'is' 'IS' 'abcd' ''
do
    echo TEST with str="$str" file="$TEST" "$TEST"
    ./test_grep "$str" "$TEST" "$TEST" > my_grep.txt
    grep "$str" "$TEST" "$TEST" > grep.txt
    COMP_RES="$(diff -s my_grep.txt grep.txt)"
    if [ "$COMP_RES" == "Files my_grep.txt and grep.txt are identical" ]
        then
            (( COUNT_SUCCESS++ ))
            echo "SUCCESS"
        else
            (( COUNT_FAIL++ ))
            echo "FAIL"
        fi
            rm my_grep.txt grep.txt
done
    
echo "SUCCESS: $COUNT_SUCCESS"
echo "FAIL: $COUNT_FAIL"
