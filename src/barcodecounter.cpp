#include "barcodecounter.h"
#include <string>
#include "kmers_bitwisetransform.h"

using std::string;

namespace barcodeSpace{

BarcodeCounter::BarcodeCounter(size_t klen):_klen(klen)
{
    this->_trans = kmersBitwiseTransform::getInstance();
}
}
