#!/bin/bash
touch test_with_FIX.txt
rm test_with_FIX.txt
status=$?
if [ -f test_with_FIX.txt ] || ((status != 0)); then
	echo "TEST rm without wrapper and with FIX failed"
	exit $status
else
	echo "OK"
fi;

touch test_without_FI_X.txt
rm test_without_FI_X.txt
status=$?
if [ -f test_without_FI_X.txt ] || ((status != 0)); then
	echo "TEST rm without wrapper and without FIX failed"
	exit $status
else
	echo "OK"
fi;

touch test_with_FIX.txt
LD_PRELOAD=`pwd`/.libs/libwrapper.so rm test_with_FIX.txt
status=$?
if [ ! -f test_with_FIX.txt ] || ((status == 0)); then
	echo "TEST rm with wrapper and with FIX failed"
	exit $status
else
	echo "OK"
fi;

touch test_without_FI_X.txt
LD_PRELOAD=`pwd`/.libs/libwrapper.so rm test_without_FI_X.txt
status=$?
if [ -f test_without_FI_X.txt ] || ((status != 0)); then
	echo "TEST rm with wrapper and without FIX failed"
	exit $status
else
	echo "OK"
fi;
