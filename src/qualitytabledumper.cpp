//
//  qualitytabledumper.cpp
//  barcode_project
//
//  Created by luzhao on 12/21/15.
//  Copyright © 2015 luzhao. All rights reserved.
//

#include "qualitytabledumper.hpp"
#include "minicsv.h"

#include <sstream>
#include <string>

using namespace std;
using namespace csv;
namespace barcodeSpace {
    void QualityTableDumper::generateHeader() {
        _header.push_back("Cluster.ID");
        _header.push_back("Base");
        std::stringstream buffer;
        for(size_t pos = 1; pos <= _max_barcode_length; ++pos) {
            buffer << "position_" << pos;
            _header.push_back(buffer.str());
            buffer.str("");
        }
    }
    void QualityTableDumper::WritePWM(int cluster_id, const std::vector<std::array<int, 4>>& pwm) {

        for (int bp = 0; bp < 4; ++bp) {
            this->_out << cluster_id << std::string(1, _dict->dna2asc(bp));
            size_t pos = 0;
            while (pos < pwm.size()) {
                this->_out << to_string(pwm[pos++][bp]);
            }
            while (pos < _max_barcode_length) {
                this->_out << "0";
                ++pos;
            }
            this->_out << '\n';
        }
    }
    void QualityTableDumper::writeHeader() {
        for (const auto& h : _header) {
            this->_out << h;
        }
        this->_out << '\n';
    }
 
}
