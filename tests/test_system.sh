#!/bin/bash

ar_dir="/dev/shm/AR_CL_Project_TMP_directory"
test_generator="gtg"
test_generator_src="gragen.cpp"
project_dir=$(pwd)
testing_dirs=(100000)
test_case_count="2"

function run_tests {

	echo ""
	for dir in ${testing_dirs[@]}; do
		for (( test_case_num = 1; test_case_num <= $(($test_case_count)); test_case_num++ )) do
			test_name="$ar_dir/tests/$dir/test_$test_case_num.in"
			echo -n "$2 "
			./$1 < $test_name > $ar_dir/results/$dir/$2_$test_case_num.out
		done
	done

}

function generate_tests {

	rm -rf $ar_dir

	mkdir -p $ar_dir
	mkdir -p $ar_dir/tests
	mkdir -p $ar_dir/results

	cp ./tests/$test_generator_src $ar_dir/

	clang++ -Wall -o $ar_dir/$test_generator $ar_dir/$test_generator_src -O2

	for dir in ${testing_dirs[@]}; do
		mkdir $ar_dir/tests/$dir
		mkdir $ar_dir/results/$dir
		for (( test_case_num = 1; test_case_num <= $(($test_case_count)); test_case_num++ )) do
			test_name="$ar_dir/tests/$dir/test_$test_case_num.in"
			$ar_dir/$test_generator $test_case_num $dir > $test_name
			echo "Generation test $test_case_num with $dir vertexes is done."
		done
	done

}

if [ $# -gt 1 ]; then
	test_case_count=$1
	testing_dirs=($2)
	generate_tests
fi

{ time run_tests "/build/app" "gpu"; } 2>&1 | grep real
{ time run_tests "/misc/dijkstra" "cpu"; } 2>&1 | grep real

exit 0