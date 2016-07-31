# kmer-counting

Aim of this task is to count the frequencies of k-mers for a given FASTQ file and report to top X count of these that is determined by the user. k is also determined by the user. For this purpose I have used several libraries. These are;

1 - kseq.h
I have used this library to read FASTQ files efficiently. 

2 - BloomFilter
I have used this library to look for existince of k-mers more efficiently. While iterating all the k-mers one by one Bloom Filter is used to check existence. 

3 - Rolling Iterator
Rolling iterator simply hashes the k-mers while iterating over the k-mers. For sake of simplicity I have assigned 4 to hash function number.

I make use of several articles particularly the following one. 
http://bmcbioinformatics.biomedcentral.com/articles/10.1186/1471-2105-12-333



