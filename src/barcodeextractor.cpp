#include "barcodeextractor.h"
#include "util.h"
#include "sequence.h"


#include <algorithm>
#include <boost/regex.hpp>
#include <string>
using std::string;
namespace barcodeSpace {

bool BarcodeExtractor::ExtractBarcode(Sequence &read) const {
    int position = isMatched(read.fowardSeq(), read.quality());
    return position != -1;
}
Sequence BarcodeExtractor::ExtractBarcode(const Sequence& read, bool& success)const {
    success = false;
    Sequence result(read.id(), read.fowardSeq().c_str(), read.quality());
    int pos = isMatched(result.fowardSeq(), result.quality());
    success = pos != -1;
    return result;
}

int BarcodeExtractor::isMatched(string& sequence,string& qual)const{
    boost::smatch result;
    if(boost::regex_search(sequence, result, _pattern) && !result.empty()){
        this->combinePieces(sequence,qual,result);
        return static_cast<int>(result.position());
    }

    reverseComplementInplace(sequence);
    //string rev_sequence = reverseComplement(sequence);
    std::reverse(qual.begin(),qual.end());
    if(boost::regex_search(sequence,result,_pattern) && !result.empty()){
        this->combinePieces(sequence,qual,result);
        return static_cast<int>(result.position());
    }
    return -1;
}
void BarcodeExtractor::combinePieces(string& sequence, string& qual, boost::smatch& result)const{
    assert(result.size() == 10);
    //sequence.clear();
    //cout<<sequence<<endl;
    string temp;
    string tempqual;
    //first barcode
    size_t start = result.position();
    temp += sequence.substr(start+4,result.position(3)-start-4);
    tempqual += qual.substr(start+4,result.position(3)-start-4);
    //second barcode
    start = result.position(3);
    temp += sequence.substr(start +2,result.position(5) - start - 2);
    //third barcode
    tempqual += qual.substr(start +2,result.position(5) - start - 2);

    start = result.position(5);
    temp += sequence.substr(start+2,result.position(7) - start -2);
    // last barcode
    tempqual += qual.substr(start+2,result.position(7) - start -2);

    start = result.position(7);
    temp += sequence.substr(start +2, result.position(9)-start -2);
    tempqual += qual.substr(start +2, result.position(9)-start -2);
    sequence.assign(temp);

    qual.assign(tempqual);
}
}   // namespace barcodeSpace
