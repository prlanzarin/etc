from __future__ import division
import nltk
from nltk.book import *

# CMP527: LABORATORIO 1 do NLTK
# ALUNO: PAULO RENATO LANZARIN
# MATRICULA: 228818

def lexical_diversity(text):
    return len(text) / len(set(text))

def percentage(count, total):
    return 100 * (count / total)

# EX 1
print "Exercise 1: ", 12 / (4 + 1)

# EX 2
# 26^100 hundred-letter possible strings
print "Number of hundred-letter strings (26**100): ", 26**100

# EX 3
# multiplication over lists replicates its contents x times
print "Exercise 3: ", ["Monty", "Python"] * 20, sent1*3

# EX4
print "Words on text2", len(text2)
print "Distinct words on text2", len(set(text2))

# EX5
print "Humor is more lexically diverse than romance"

# EX6
print "Exercise 6: generating dispersion plot for Elinor, Marianne, Edward and Willoughby"
text2.dispersion_plot(["Elinor", "Edward", "Marianne", "Willoughby"])
print "Female characters are far more proeminent (as they are the focal point of the book"
print "Pairs seems to be Elinor+Edward and Marianne+Willoughby, judging by similarity of text positions"

# EX7
print "Exercise 7, collocations on text5: ", text5.collocations()

# EX8
print "Exercise 8, sets and length: ", len(set(text4))
print "The purpose is to return the number of distinct tokens on text4."
print "First, nltk processes a set of words/tokens. They are distinct (set)."
print "Then, we get the length of the generated list of strings."

# EX9
#   1
my_string = "Then shall men and women come unto the place prepared for them."
print "Exercise 9.1: ", my_string

#   2
print "Exercise 9.2: ", my_string*2
print "Exercise 9.2: ", " ".join([my_string, my_string])

# EX10
my_sent = [ "the", "place", "prepared", "for", "them"]
ms_string = " ".join(my_sent)
print "Exercise 10: ", ms_string
print "Exercise 10: ", ms_string.split()

# EX11
ph1 = ["p1", "p2", "p3"]
ph4 = ["p4", "p5", "p6"]
print "Exercise 11: ", ph1 + ph4, " <==> ", ph4 + ph1
print "Exercise 11, len(p1 + p2) and len(p1) + len(p2):", len(ph1+ph4), len(ph1) + len(ph4)
# EX12
print "Exercise 12: ", "Monty Python"[6:12]
print "Exercise 12: ", ["Monty", "Python"][1]
print "The most relevant to NLP is the second one because it depicts an access"
print "to the second word of a list of words, which is the way phrases/text are commonly"
print "represented. The first one is a string and depicts the acess to letters 6-11"

# EX13
print "Exercise 13, acessing third letter of third word on sent1: ", sent1[2][2]
print "my_sent[4][2]: ", my_sent[4][2]

# EX14
idx1 = sent3.index("the")
idx2 = sent3[idx1+1:].index("the") + (idx1+1)
idx3 = sent3[idx2+1:].index("the") + (idx2+2)
print "Exercise 14, -the indexes on sent3: ", idx1, idx2, idx3 
