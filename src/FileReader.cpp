#include <zlib.h>
#include <stdio.h>
#include<iostream>
#include <time.h>
#include "BloomFilter.hpp"
#include <vector>
#include <string>
#include "RollingHashIterator.h"
#include "kseq.h"
using namespace std;
// STEP 1: declare the type of file handler and the read() function
KSEQ_INIT(gzFile, gzread)

int main(int argc, char *argv[])
{
    gzFile fp;
    kseq_t *seq;
    int l;
    if (argc == 1) {
        fprintf(stderr, "Usage: %s <in.seq>\n", argv[0]);
        return 1;
    }

    time_t start = time(NULL);

    BloomFilter bloom(1000, 4, 5);

    fp = gzopen(argv[1], "r"); // STEP 2: open the file handler
    seq = kseq_init(fp); // STEP 3: initialize seq
    while ((l = kseq_read(seq)) >= 0) { // STEP 4: read sequence
    	printf("seq: %s\n", seq->seq.s);
		RollingHashIterator itr(seq->seq.s, 4, 5);
		while (itr != itr.end()) {
			bloom.insert(*itr);
			cout << itr.kmer() << endl;
			itr++;
		}

    }
    kseq_destroy(seq); // STEP 5: destroy seq
    gzclose(fp); // STEP 6: close the file handler

    time_t end = time(NULL);
    std::cout<<"Execution Time: "<< (double)(end-start)<<" Seconds"<<std::endl;
    cout << bloom.contains("AATGG")<<endl;
    return 0;
}
