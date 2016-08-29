from __future__ import division
import nltk
from nltk.book import *

# CMP527: LABORATORIO 2 do NLTK
# ALUNO: PAULO RENATO LANZARIN
# MATRICULA: 228818

# EX 1
print "List of words on text 5 that starts with 'b': ", sorted([w for w in set(text5) if w.startswith('b')])

# EX 2
print "Ranges exercise: ", range(10), range(10, 20), range(20, 10, -2)

# EX 3
print "Sunset phrase: ", text9[621:644]

# EX4
vocab = []
sentences = [sent1, sent2, sent3, sent4, sent5, sent6, sent7, sent8] 
for s in sentences:
    vocab = vocab + sorted(set([word.lower() for word in s if word.isalpha()]))

print "Vocabulary of sentences: ", vocab

# EX5
print len(sorted(set([w.lower() for w in text1]))), len(sorted(([w.lower() for w in set(text1)])))
print "EX5: first one computes all tokens discerning case, whilst the second one computes every token before they're put to same case. Hence, the second one has more tokens"

# EX6
print "EX6: isupper() will include all words that are uppercase, while not islower() will inclue all alphabetic non-uppercase words and non-alphabetic sequences"

# EX7
print "EX7: ", text2[len(text2)-2:]

# EX8
fltf = FreqDist([w for w in text5 if len(w) == 5])
print "EX8: ", fltf.keys() 

# EX9
print "EX9: "
for w in text6:
    if(w.isupper()):
        print w

# EX10
ex10 = []
for w in text6:
    if(w.endswith('ize') or ('z' in w) or ('pt' in w) or w.istitle()):
        ex10 += w

# EX11
sent = ['she', 'sells', 'sea', 'shells', 'by','the', 'sea', 'shore'] 
print "EX11: all words beginning with sh: ", sorted(set([word.lower() for word in sent if word.startswith('sh')]))
print "EX11: all words bigger than 4: ", sorted(set([word.lower() for word in sent if len(word) > 4]))

# EX12
# sums the total number of characters in text1
print "EX12: average number of characters per word on text1 : ", sum([len(w) for w in text1]) / len(text1)

# EX13
def vocab_size(text):
    return len(set([word.lower() for word in text if word.isalpha()]))

# EX14
def percent(inword, text):
    for word in text:
        if word == inword:
            total += 1
    return (total/len(text)) * 100

# EX15
print "EX15: Set comparison enables us to determine if all the elements are equal or if they are a super or subset of another set"
