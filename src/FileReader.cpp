#include <zlib.h>
#include <stdio.h>
#include<iostream>
#include <time.h>
#include "BloomFilter.hpp"
#include <vector>
#include <map>
#include <set>
#include <string>
#include "RollingHashIterator.h"
#include "kseq.h"

using namespace std;
// STEP 1: declare the type of file handler and the read() function
KSEQ_INIT(gzFile, gzread)

int main(int argc, char *argv[])
{
	map<string, uint64_t> map;
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
		RollingHashIterator itr(seq->seq.s, 4, 5);
		while (itr != itr.end()) {
			if(bloom.contains(*itr)) {
				if(map.find(itr.kmer()) == map.end()) {
					map.insert(make_pair(itr.kmer(),1));
				} else {
					map[itr.kmer()]++;
				}
			} else {
				bloom.insert(*itr);
				map.insert(make_pair(itr.kmer(),1));
			}

			itr++;
		}

    }

    for(std::map<string, uint64_t>::iterator it=map.begin(); it!= map.end(); ++it) {
    	std::cout << it->first << " => " << it->second << '\n';
    }
    std::vector<pair<std::string, uint64_t>> keys;

    typedef std::map<string, uint64_t>::iterator iter;
    iter it = map.begin();
    iter end2 = map.end();

    uint64_t maxValue = it->second;
    string maxKey = it->first;

    for( ; it != end2; ++it) {
        if(it->second > maxValue) {
        	maxValue = it->second;
        	maxKey = it->first;
        }
    }
    keys.push_back(std::make_pair(maxKey,maxValue));

    for (auto i = keys.begin(); i != keys.end(); ++i)
        std::cout << i->first << "->" << i->second << endl;

    kseq_destroy(seq); // STEP 5: destroy seq
    gzclose(fp); // STEP 6: close the file handler

    time_t end = time(NULL);
    std::cout<<"Execution Time: "<< (double)(end-start)<<" Seconds"<<std::endl;
    return 0;
}
