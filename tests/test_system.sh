#!/bin/bash

ar_dir="/dev/shm/AR_CL_Project_TMP_directory"
test_generator="gtg"
test_generator_src="gragen.cpp"

rm -rf $ar_dir

mkdir -p $ar_dir

echo "Created dir $ar_dir."

cp ./tests/$test_generator_src $ar_dir/

cd $ar_dir

clang++ -Wall -o $test_generator $test_generator_src -O2

echo "Compiled $test_generator."

mkdir -p tests

# Generating small test cases
mkdir -p tests/small
for (( test_case_num = 1; test_case_num <= 50; test_case_num++ )) do

	test_name="$test_case_num.in"
	./$test_generator 10 > tests/small/$test_name

	echo "Generation test number $test_case_num is done."

done

# Generating middle test cases
mkdir -p tests/middle
for (( test_case_num = 1; test_case_num <= 50; test_case_num++ )) do

	test_name="$test_case_num.in"
	./$test_generator 1000 > tests/middle/$test_name

	echo "Generation test number $test_case_num is done."

done

# Generating big test cases
mkdir -p tests/big
for (( test_case_num = 1; test_case_num <= 50; test_case_num++ )) do

	test_name="$test_case_num.in"
	./$test_generator 100000 > tests/big/$test_name

	echo "Generation test number $test_case_num is done."

done
