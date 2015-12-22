#include <iostream>
#include <cassert>
#include <memory>
#include <boost/regex.hpp>
#include "../barcodeextractor.h"
#include "../util.h"
using std::string;
using std::vector;
using std::endl;
using std::cout;
using std::unique_ptr;
using barcodeSpace::BarcodeExtractor;
using barcodeSpace::Sequence; 
using boost::regex;
using barcodeSpace::reverseComplement;
int main(void) {

    boost::regex pattern("(.ACC|T.CC|TA.C|TAC.)(A|T|C|G|N){4,7}(AA)(A|T|C|G|N){4,7}(AA)(A|T|C|G|N){4,7}(TT)(A|T|C|G|N){4,7}(.TAA|A.AA|AT.A|ATA.)",boost::regex::ECMAScript);
    string seq("TGCTGAACGCCCTCTTACGGATATTCGCGATGAGTATCATTACCCCAAAAAGAAAGGTATTAAGGATGAGTGTTCAAGATTGCTGGAGGCCTCCACTA");
    //string seq("CGACGATGTTTAATATGGACTAAAGGAGGCTTTTGTCGACGGATCCGATATCGGTACCACATAAACAATAAAGTCTATTATGNAATNACTTCGNAT");
    string qual("@@@@@FFFFDHFHFDHIJIIGGHIJJJIIJJIGDHDGCHIIJGI@HIIBA<EEFFAAB@BBBDDDDDDCCCD:>A:ACCA:>CCCCCDD#+22#++8?");
    Sequence read("read1", seq.c_str(), qual);
    BarcodeExtractor extractor(pattern);
    Sequence read_cp(read.id(), seq, qual);    
    extractor.ExtractBarcode(read_cp);
    //cout << extractor.ExtractBarcode(read_cp) << endl;
    //cout << read_cp.fowardSeq() << '\t' <<  read_cp.quality() <<endl; 
    bool success = false;
    Sequence barcode = extractor.ExtractBarcode(read, success); 
    //cout << success << '\t' << barcode.fowardSeq() << '\t' << barcode.quality() <<endl;
    /*
    std::string fastafile = "/home/laozzzzz/barcode_project/reads/e_coli_10000snp.fa";
    std::unique_ptr<patternParser> parser(new fastaPattern(fastafile));
    bool done = false, success = false;
    Sequence read;
    parser->parse(read, success, done);
    assert(success);
    assert(!done);
    cout << read.fowardSeq() << '\t' << read.quality() << endl;       
    int count = 1;
    while (!done) {
        read.clear();
	parser->parse(read, success, done);
        assert(success);
        ++count;
    }   
    cout << "Total number reads: " << count <<endl;
    // This file contains 10000 reads.
    assert(10000 == count);

    ///////////////////////////Test fastqPattern//////////////////////////////////////
    
    std::string fastqfile = "/home/laozzzzz/barcode_project/reads/1000_reorder.fq";
    parser.reset(new fastqPattern(fastqfile));
    done = false;
    success = false;
    count = 0;
    while (!done) {
	read.clear();
	parser->parse(read, success, done);
        ++count; 
        assert(success || read.empty());
    } 
    // The file contains 1000 reads.
    assert(count == 1000);
    */ 
    return 0;
}


