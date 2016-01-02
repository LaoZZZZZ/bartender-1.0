#include <iostream>
#include <cassert>
#include <memory>
#include "../patternparser.h"
#include "../fastqpattern.h"
#include "../fastapattern.h"
#include "../sequence.h"
using std::string;
using std::endl;
using std::cout;
using std::unique_ptr;
using barcodeSpace::fastqPattern;
using barcodeSpace::fastaPattern;
using barcodeSpace::patternParser;
using barcodeSpace::Sequence; 
int main(void) {
    std::string fastafile = "./reads/e_coli_10000snp.fa";
    std::unique_ptr<patternParser> parser(new fastaPattern(fastafile));
    bool done = false, success = false;
    Sequence read;
    int count = 0;
    int line = 1;
    while (!done) {
        read.clear();
	assert(line == parser->CurrentLine());
	parser->parse(read, success, done);
        assert(success);
        ++count;
	line += 2;
    }   
    cout << "Total number reads: " << count <<endl;
    // This file contains 10000 reads.
    assert(10000 == count);

    ///////////////////////////Test fastqPattern//////////////////////////////////////
    
    std::string fastqfile = "./reads/1000_reorder.fq";
    parser.reset(new fastqPattern(fastqfile));
    done = false;
    success = false;
    count = 0;
    line = 1;
    while (!done) {
	read.clear();
	assert(line == parser->CurrentLine());
	parser->parse(read, success, done);
        ++count; 
	line += 4;
        assert(success || read.empty());
    } 
    // The file contains 1000 reads.
    assert(count == 1000);
    
    return 0;
}
