#!/bin/bash

echo "Type the book's filename (with extension): "

#read bookfile
bookfile="wuthering-heights.txt"

book="${bookfile%.*}" 

echo "Running unix for poets exercises on $bookfile"

# COUNTING EXERCISE 1: WORD COUNT
tr -sc 'A-Za-z' '\012' < $bookfile > $book\.words 

sort $book\.words | uniq -c > wordcount-$book\.hist

# COUNTING EXERCISE 2: VOWEL COUNT
tr -sc 'A-Z' 'a-z' < $bookfile > $book\.wordscase

tr -sc 'AEIOU' '\012' < $book\.wordscase | sort | uniq -c > vowelcount-$book\.hist

# COUNTING EXERCISE 3: CONSONANT COUNT
tr -sc 'BCDFGHJKLMNPQRSTWVXYZ' '\012' < $book\.wordscase | sort | uniq -c > consonantcount-$book\.hist

# SORT EXERCISE 1: SORT BY FREQUENCY
sort $book\.words | uniq -c | sort -nr > freqsort-$book\.hist

# SORT EXERCISE 2: SORT BY FOLDING CASE
sort $book\.words |  uniq -c | sort -f > foldingsort-$book\.hist

# SORT EXERCISE 3: SORT BY RHYMING ORDER
sort $book\.words | rev | sort | rev | uniq -c > rhymingsort-$book\.hist

# COUNT BIGRAMs EXERCISE
tail -n +2 $book\.words > $book\.nextwords
paste $book\.words $book\.nextwords | sort | uniq -c > $book\.bigrams

# COUNT TRIGRAMs EXERCISE
tail -n +3 $book\.words > $book\.nextwordst
paste $book\.words $book\.nextwords $book\.nextwordst | sort | uniq -c > $book\.trigrams 

# GREP EXERCISE 1

# GREP EXERCISE 2

# GREP EXERCISE 3 

# GREP EXERCISE 4 

# GREP EXERCISE 5 

# GREP EXERCISE 6 

# GREP EXERCISE 7

# SED EXERCISE 1

# SED EXERCISE 2

# SED EXERCISE 3 

# AWK EXERCISE 8.1

# AWK EXERCISE 8.2 - 1 

# AWK EXERCISE 8.2 - 2 

# AWK EXERCISE 8.3

# AWK EXERCISE 8.4 - 1

# AWK EXERCISE 8.4 - 2

# AWK EXERCISE 8.5

# AWK EXERCISE 8.6

# ARRAY EXERCISE 8.9 - 1

# ARRAY EXERCISE 8.9 - 2

# ARRAY EXERCISE 8.9 - 3

# ARRAY EXERCISE 8.9 - 4

# CONCORDANCE EXERCISE 11





