#!/bin/bash

echo "Type the book's filename: "

#read bookfile
bookfile="wuthering-heights.txt"

book="${bookfile%.*}" 

echo "Running unix for poets exercises on $bookfile"

# COUNTING EXERCISE 1: WORD COUNT
tr -sc 'A-Za-z' '\012' < $bookfile | sort | uniq -c > wordcount-$book\.hist

# COUNTING EXERCISE 2: VOWEL COUNT
tr -sc 'A-Z' 'a-z' < $bookfile | tr -sc 'AEIOU' '\012' | sort | uniq -c > vowelcount-$book\.hist

# COUNTING EXERCISE 3: CONSONANT COUNT
tr -sc 'A-Z' 'a-z' < $bookfile | tr -sc 'BCDFGHJKLMNPQRSTWVXYZ' '\012' | sort | uniq -c > consonantcount-$book\.hist

# SORT EXERCISE 1: 
