//
//  qualitytabledumper.cpp
//  barcode_project
//
//  Created by luzhao on 12/21/15.
//  Copyright © 2015 luzhao. All rights reserved.
//

#include "qualitytabledumper.hpp"

#include <sstream>
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
                this->_out << pwm[pos++][bp];
            }
            while (pos < _max_barcode_length) {
                this->_out << 0U;
                ++pos;
            }
            this->_out << '\n';
        }
    }
}
