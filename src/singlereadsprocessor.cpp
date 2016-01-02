//
//  singlereadsprocessor.cpp
//  barcode_project
//
//  Created by luzhao on 1/1/16.
//  Copyright © 2016 luzhao. All rights reserved.
//

#include "singlereadsprocessor.hpp"

#include "pattern.h"
#include "sequence.h"
#include "util.h"

#include <string>

namespace barcodeSpace {
    SingleReadsProcessor::SingleReadsProcessor(const std::string& reads_file_name,
                                               std::shared_ptr<BarcodeExtractor> extractor,
                                               file_format format,
                                               const std::string& output,
                                               double qual_thres) :
                            _extractor(extractor), _formats(format), _outprefix(output),
                            _barcode_dumper(output + "_barcode.txt", false),
                            _line_num_dumper(output + "_line.txt", false),
                            _total_reads(0), _total_barcodes(0),
                            _total_valid_barcodes(0), _quality_threshold(qual_thres){
                                _pattern_handler.reset(CreatePatternParser(reads_file_name, format));
    }
    
    void SingleReadsProcessor::extract() {
        bool done = false;
        bool success = false;
        Sequence read;
        while(!done) {
            read.clear();
            _pattern_handler->parse(read, success, done);
            size_t line = _pattern_handler->CurrentLine();
            // If get a read successfully, then extract the barcode from the read.
            if (success) {
                success = _extractor->ExtractBarcode(read);
                
                // If extracted a barcode from the read successfully,
                if (success) {
                    // The average quality is above the threshold.
                    if (qualityCheck(read.quality(), _quality_threshold)) {
                        _barcode_dumper.writeString(read.fowardSeq() + '\n');
                        _line_num_dumper.writeString(std::to_string(line) + '\n');
                        ++_total_valid_barcodes;
                    }
                    // Keep tract all barcodes.
                    ++_total_barcodes;
                }
                ++_total_reads;
                
            }
        }

    }
}   // namespace barcodeSpace