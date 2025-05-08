#!/bin/bash

cmake --build build

ar_dir="/dev/shm/AR_CL_Project_TMP_directory"
project_dir=$(pwd)

required=("gragen" "check_equivalence" "dijkstra")

testing_dirs=(0)
test_case_count="0"

function run_tests {

	for dir in ${testing_dirs[@]}; do
		for (( test_case_num = 1; test_case_num <= $(($test_case_count)); test_case_num++ )) do
			test_name="$ar_dir/tests/$dir/test_$test_case_num.in"
			$1 < $test_name > $ar_dir/results/$dir/$2_$test_case_num.out
		done
	done

}

function generate_tests {

	rm -rf $ar_dir

	mkdir -p $ar_dir
	mkdir -p $ar_dir/tests
	mkdir -p $ar_dir/results

	for file in ${required[@]}; do
		clang++ -Wall -o $ar_dir/$file ./tests/$file.cpp -O2
	done

	for dir in ${testing_dirs[@]}; do
		mkdir $ar_dir/tests/$dir
		mkdir $ar_dir/results/$dir
		for (( test_case_num = 1; test_case_num <= $(($test_case_count)); test_case_num++ )) do
			test_name="$ar_dir/tests/$dir/test_$test_case_num.in"
			$ar_dir/gragen $test_case_num $dir > $test_name
			echo "Generation test $test_case_num with $dir vertexes is done."
		done
	done

	du -sh $ar_dir/tests

}

if [ $# -gt 1 ]; then
	test_case_count=$1
	testing_dirs=($2)
	generate_tests
	echo "$1 $2" > $ar_dir/cache
else 
	read test_case_count testing_dirs < $ar_dir/cache
fi

echo -n "GPU "; { time run_tests "./build/app" "gpu"; } 2>&1 | grep real
echo -n "CPU "; { time run_tests "$ar_dir/dijkstra" "cpu"; } 2>&1 | grep real

for dir in ${testing_dirs[@]}; do
	for (( test_case_num = 1; test_case_num <= $(($test_case_count)); test_case_num++ )) do
		echo -ne "$test_case_num\t" 
		$ar_dir/check_equivalence $ar_dir/results/$dir/gpu_$test_case_num.out $ar_dir/results/$dir/cpu_$test_case_num.out
	done
done

exit 0