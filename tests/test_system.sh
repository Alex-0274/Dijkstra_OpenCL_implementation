#!/bin/bash

clear

cmake --build build

ar_dir="/dev/shm/AR_CL_Project_TMP_directory"
project_dir=$(pwd)

required=("gragen" "check_equivalence" "dijkstra")

declare -a num_of_tests=()
declare -a vertex_count=()
declare -a average_edge_count=()

function run_tests {

	programm=$1
	type=$2
	num_of_tests_NOW_local=$3
	vertex_count_NOW_local=$4

	for (( test_case_num = 1; test_case_num <= $(($num_of_tests_NOW_local)); test_case_num++ )) do
		test_name="$ar_dir/tests/$vertex_count_NOW_local/test_$test_case_num.in"
		$programm < $test_name > $ar_dir/results/$vertex_count_NOW_local/$type_$test_case_num.out
	done

}

rm -rf $ar_dir

mkdir -p $ar_dir
mkdir -p $ar_dir/tests
mkdir -p $ar_dir/results

for file in ${required[@]}; do

	clang++ -Wall -o $ar_dir/$file ./tests/$file.cpp -O2

done

echo "Compilation is complete."

for ((i=3; i <= $#; i+=3)); do

	num_of_tests_NOW=$(($i - 2)); num_of_tests_NOW=("${!num_of_tests_NOW}")
	vertex_count_NOW=$(($i - 1)); vertex_count_NOW=("${!vertex_count_NOW}")
	average_edge_count_NOW=$i; average_edge_count_NOW=("${!average_edge_count_NOW}")

	mkdir $ar_dir/tests/$vertex_count_NOW
	mkdir $ar_dir/results/$vertex_count_NOW

	for (( test_case_num = 1; test_case_num <= $(($num_of_tests_NOW)); test_case_num++ )) do

		test_name="$ar_dir/tests/$vertex_count_NOW/test_$test_case_num.in"
		
		$ar_dir/gragen $test_case_num $vertex_count_NOW $average_edge_count_NOW > $test_name

		echo "Generation test $test_case_num in test case ($num_of_tests_NOW, $vertex_count_NOW, $average_edge_count_NOW) is done."

	done

done

echo

du -sh $ar_dir/tests

clear

for ((i=3; i <= $#; i+=3)); do

	num_of_tests_NOW=$(($i - 2)); num_of_tests_NOW=("${!num_of_tests_NOW}")
	vertex_count_NOW=$(($i - 1)); vertex_count_NOW=("${!vertex_count_NOW}")
	average_edge_count_NOW=$i; average_edge_count_NOW=("${!average_edge_count_NOW}")

	echo
	
	echo -ne "\033[1;34mGPU on test case ($num_of_tests_NOW, $vertex_count_NOW, $average_edge_count_NOW) \033[1;33m";
	{ time run_tests "./build/app" "gpu" $num_of_tests_NOW $vertex_count_NOW; } 2>&1 | grep real
	
	echo -ne "\033[1;34mCPU on test case ($num_of_tests_NOW, $vertex_count_NOW, $average_edge_count_NOW) \033[1;33m";
	{ time run_tests "$ar_dir/dijkstra" "cpu" $num_of_tests_NOW $vertex_count_NOW; } 2>&1 | grep real
	
done

echo -e "\033[0m"

rm -rf $ar_dir

exit 0