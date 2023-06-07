#!/bin/bash

output_dir="minishell_output"
expected_dir="expected_output"
test_dir="test_results"
valgrind_dir="valgrind_output"

mkdir -p "$output_dir"
mkdir -p "$test_dir"
mkdir -p "$valgrind_dir"

counter=1

while IFS= read -r string; do
    echo "Executing minishell with input: $string"
    output=$(echo "$string" | /nfs/homes/lbaumann/projects/minishell/minishell)
    echo "$output" | tail -n +2 > "$output_dir/$counter"
    echo "Execution complete for: $string"
    echo
    ((counter++))
done < test_strings

counter=1

while IFS= read -r _; do
    echo "Comparing output file $counter"
    diff "$output_dir/$counter_out" "$expected_dir/$counter" > "$test_dir/$counter"
    echo "Comparison complete for file $counter"
    echo
    ((counter++))
done < test_strings

counter=1

while IFS= read -r string; do
    echo "Executing minishell with valgrind for input: $string"
    valgrind_output=$(echo "$string" | valgrind --leak-check=full --log-file="$valgrind_dir/$counter" /nfs/homes/lbaumann/projects/minishell/minishell)
    echo "Execution complete with valgrind for: $string"
    echo
    ((counter++))
done < test_strings
