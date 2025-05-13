#!/bin/bash

ar_dir="/dev/shm/AR_CL_Project_TMP_directory"
gragen="gtg"
gragen_src="gragen.cpp"
check_equivalence="chequ"
check_equivalence_src="check_equivalence.cpp"
project_dir=$(pwd)

required=("gragen" "check_equivalence" "dijkstra")

declare -a testing_dirs=()
declare -A num_of_tests=()

function run_tests {

	for (( test_case_num = 1; test_case_num <= $((${num_of_tests[$3]})); test_case_num++ )) do
		test_name="$ar_dir/tests/$3/test_$test_case_num.in"
		$1 < $test_name > $ar_dir/results/$3/$2_$test_case_num.out
	done

}

function generate_tests {

	rm -rf $ar_dir

	mkdir -p $ar_dir
	mkdir -p $ar_dir/tests
	mkdir -p $ar_dir/results

	cp ./tests/$gragen_src $ar_dir/
	cp ./tests/$check_equivalence_src $ar_dir/

	clang++ -Wall -o $ar_dir/$gragen $ar_dir/$gragen_src -O2
	clang++ -Wall -o $ar_dir/$check_equivalence $ar_dir/$check_equivalence_src -O2

	for dir in ${testing_dirs[@]}; do
		mkdir $ar_dir/tests/$dir
		mkdir $ar_dir/results/$dir
		for (( test_case_num = 1; test_case_num <= $((${num_of_tests[$dir]})); test_case_num++ )) do
			test_name="$ar_dir/tests/$dir/test_$test_case_num.in"
			$ar_dir/$gragen $test_case_num $dir > $test_name
			echo "Generation test $test_case_num with $dir vertexes is done."
		done
	done

	echo

	du -sh $ar_dir/tests

}

for ((i=2; i <= $#; i+=2)); do
	prev=$(($i - 1))
	now=$i
	testing_dirs+=("${!now}")
	num_of_tests["${!now}"]="${!prev}"
done

generate_tests

for dir in ${testing_dirs[@]}; do
	echo
	echo -ne "\033[1;34mGPU on test case with $dir vertexes \033[1;33m"; { time run_tests "./build/app" "gpu" $dir; } 2>&1 | grep real
	echo -ne "\033[1;34mCPU on test case with $dir vertexes \033[1;33m"; { time run_tests "$ar_dir/dijkstra" "cpu" $dir; } 2>&1 | grep real
done

echo -e "\033[0m"

for dir in ${testing_dirs[@]}; do
	for (( test_case_num = 1; test_case_num <= $((${num_of_tests[$dir]})); test_case_num++ )) do
		echo -ne "$dir\t\t$test_case_num\t" 
		$ar_dir/check_equivalence $ar_dir/results/$dir/gpu_$test_case_num.out $ar_dir/results/$dir/cpu_$test_case_num.out
	done
done

exit 0