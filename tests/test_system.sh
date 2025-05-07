#!/bin/bash

ar_dir="/dev/shm/AR_CL_Project_TMP_directory"
test_generator="gtg"
test_generator_src="gragen.cpp"

rm -rf $ar_dir

mkdir -p $ar_dir

echo "Created dir $ar_dir."

cp $test_generator_src $ar_dir/

cd $ar_dir

clang++ -Wall -o $test_generator $test_generator_src -O2

echo "Compiled $test_generator."

mkdir -p tests

for (( test_case_num = 1; test_case_num <= 3; test_case_num++ )) do

	test_name="test_$test_case_num.in"
	./$test_generator > tests/$test_name

	echo "Generation test number $test_case_num is done."

done

