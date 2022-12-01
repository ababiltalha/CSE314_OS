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
        [[ $1 =~ ^[0-9] ]] && {
            max_score=$1
        } || {
            echo "Invalid max score"
            exit 1
        }
        [[ $2 =~ ^[1-9] ]] && {
            max_student_id=$2
        } || {
            echo "Invalid max student id"
            exit 1
        }
        
    } || {
        [[ $# -eq 1 ]] && {
            [[ $1 =~ ^[0-9] ]] && {
                max_score=$1
            } || {
                echo "Invalid max score"
                exit 1
            }
        }
    }
}

# necessary temp files

touch temp.txt
touch output.csv
echo "student_id,score" > output.csv
max_student_id=$(( 1805120 + max_student_id ))

# for loop for checking the outputs and genereating marks

for student_id in $(seq 1805121 $max_student_id)
do
    [[ -d Submissions/"$student_id" ]] && [[ -f Submissions/"$student_id"/"$student_id".sh ]] && {
        [[ -x Submissions/"$student_id"/"$student_id".sh ]] || {
            chmod a+x Submissions/"$student_id"/"$student_id".sh
        }
        bash ./Submissions/"$student_id"/"$student_id".sh > out"$student_id".txt
        diff --ignore-all-space out"$student_id".txt AcceptedOutput.txt > temp.txt
        marks=$(( $max_score - 5*( $( grep -c "^[<>]" temp.txt ) ) ))
        (( $marks < 0 )) && marks=0
        echo "$student_id,$marks" >> output.csv
        rm out"$student_id".txt
    } || {
        echo "Submission format not followed by $student_id"
        echo "$student_id,0" >> output.csv
    }
done

# copy checker loop(s)

for current_student_id in $(seq 1805121 $max_student_id)
do
    [[ -d Submissions/"$current_student_id" ]] && [[ -f Submissions/"$current_student_id"/"$current_student_id".sh ]] && {
        for student_id in $(seq 1805121 $max_student_id)
        do
            [[ $current_student_id -ne $student_id ]] && [[ -d Submissions/"$student_id" ]] && [[ -f Submissions/"$student_id"/"$student_id".sh ]] && {
            [[ 0 -eq $( diff --ignore-all-space Submissions/"$current_student_id"/"$current_student_id".sh Submissions/"$student_id"/"$student_id".sh | grep -c "^[<>]" ) ]] && {
                # grep "^$current_student_id," output.csv
                sed -i "s/^$current_student_id,/$current_student_id,-/g" output.csv
            }
        }
        done
    }
done

# deletion of remaining temp files

[[ -e temp.txt ]] && {
    rm temp.txt
}



