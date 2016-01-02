#ifndef BARCODEEXTRACTOR_H
#define BARCODEEXTRACTOR_H
#include <string>
#include <boost/regex.hpp>
#include "sequence.h"

namespace barcodeSpace{
class BarcodeExtractor
{
public:
    BarcodeExtractor(const boost::regex& pattern,
                     const std::string& preceeding = "",
                     const std::string& suceeding = "",
		     size_t parts = 0)
                : _pattern(pattern), _error_rate(0),
                  _preceeding(preceeding), _suceeding(suceeding), _parts(parts){}
    // Extracts the barcode region from the read.
    // And change the read in place.
    bool ExtractBarcode(Sequence& read) const;
    // Extracts the barcode region from the given read,
    // return a new read that only contains the barcode region.
    Sequence ExtractBarcode(const Sequence& read, bool& success) const;
    double ErrorRate() const { return _error_rate;}
private:
    int isMatched(std::string& sequence, std::string& qual) const;

    int extractBarcode(std::string& seq, std::string& qual) const{
        return this->isMatched(seq, qual);
    }

    // TODO(lu): factor out this part from the source code into the
    // input specification. Since this only works for current barcode parttern.
    // Should come out with a smart way to remove the spacers.
    void combinePieces(std::string& sequence, std::string& qual, boost::smatch& result)const;

private:
    boost::regex    _pattern;
    double          _error_rate;
    std::string     _preceeding;
    std::string     _suceeding;
    size_t          _parts;
};
}   // namespace barcodeSpace
#endif // BARCODEEXTRACTOR_H
