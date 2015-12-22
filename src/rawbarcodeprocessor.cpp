//
//  rawbarcodeprocessor.cpp
//  barcode_project
//
//  Created by luzhao on 12/14/15.
//  Copyright © 2015 luzhao. All rights reserved.
//

#include "rawbarcodeprocessor.hpp"
#include "csvreader.h"
#include "seedselector.hpp"

#include <cassert>
#include <list>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;
namespace barcodeSpace {
    RawBarcodeProcessor::RawBarcodeProcessor(const std::string& filenames, bool header) :  InputProcessor(){
        CSVReader* csv_reader_ptr = new CSVReader(filenames, header);
        assert(csv_reader_ptr);
        _csv_reader.reset(csv_reader_ptr);
    }
    
    void RawBarcodeProcessor::parseFile() {
        vector<string> row;
        while (_csv_reader->nextRow(&row)) {
            assert(row.size() == 1);
            _original_sequence.push_back({row[0], 1U});
            row.clear();
        }
    }

    
}