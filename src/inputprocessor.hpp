//
//  inputprocessor.hpp
//  barcode_project
//
//  Created by luzhao on 12/16/15.
//  Copyright © 2015 luzhao. All rights reserved.
//

#ifndef inputprocessor_hpp
#define inputprocessor_hpp

#include "typdefine.h"

#include <list>
#include <string>
#include <vector>
#include <unordered_map>

// Processing the raw input file.
// Three different file formats:
// 1. Fastq file.
// 2. Raw barcode list.
// 3. Barcode frequent table.
namespace barcodeSpace {
class InputProcessor {
public:
    InputProcessor() {_original_sequence.clear();}
    void process() {parseFile();}
    const std::vector<std::pair<std::string, freq>>& BarcodeList() const {return _original_sequence;}
protected:
    std::vector<std::pair<std::string, freq>>    _original_sequence;
private:
    virtual void parseFile() = 0;
};
}   // namespace barcodeSpace
#endif /* inputprocessor_hpp */
