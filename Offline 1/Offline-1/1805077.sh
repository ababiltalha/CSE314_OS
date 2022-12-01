#!/bin/bash

# default values for score and no of students

max_score=100
max_student_id=5

# checking parameters provided and assigning

[[ $# -gt 2 ]] && {
    echo "Invalid number of arguments"
    exit 1
} || {
    [[ $# -eq 2 ]] && {
        max_score=$1
        [[ $2 =~ [0-9] ]] || {
            echo "Invalid max student id"
            exit 1
        }
        max_student_id=$2
    } || {
        [[ $# -eq 1 ]] && {
            max_score=$1
        }
    }
}

# echo $# $max_score $max_student_id

touch temp.txt
touch trial.csv
echo "student_id,score" > trial.csv
max_student_id=$(( 1805120 + max_student_id ))
# echo $max_student_id

# for loop for checking the outputs and genereating marks

for student_id in $(seq 1805121 $max_student_id)
do
    # echo $student_id
    [[ -d Submissions/"$student_id" ]] && [[ -f Submissions/"$student_id"/"$student_id".sh ]] && {
        [[ -x Submissions/"$student_id"/"$student_id".sh ]] || {
            chmod a+x Submissions/"$student_id"/"$student_id".sh
        }
        bash ./Submissions/"$student_id"/"$student_id".sh > out"$student_id".txt
        diff --ignore-all-space out"$student_id".txt AcceptedOutput.txt > temp.txt
        echo "$student_id,$(( $max_score - 5*( $( grep -c "^[<>]" temp.txt ) ) ))" >> trial.csv
        rm out"$student_id".txt
    } || {
        echo "Submission format not followed"
        echo "$student_id,0" >> trial.csv
    }
done


for current_student_id in $(seq 1805121 $max_student_id)
do
    [[ -d Submissions/"$current_student_id" ]] && [[ -f Submissions/"$current_student_id"/"$current_student_id".sh ]] && {
        for student_id in $(seq 1805121 $max_student_id)
        do
            [[ $current_student_id -ne $student_id ]] && [[ -d Submissions/"$student_id" ]] && [[ -f Submissions/"$student_id"/"$student_id".sh ]] && {
            [[ 0 -eq $( diff --ignore-all-space Submissions/"$current_student_id"/"$current_student_id".sh Submissions/"$student_id"/"$student_id".sh | grep -c "^[<>]" ) ]] && {
                grep --only-matching "$current_student_id" trial.csv | sed 
            }
        }
        done
    }
done

[[ -e temp.txt ]] && {
    rm temp.txt
}



