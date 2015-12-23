//
//  barcodetabledumper.cpp
//  barcode_project
//
//  Created by luzhao on 12/21/15.
//  Copyright © 2015 luzhao. All rights reserved.
//

#include "barcodetabledumper.hpp"
#include "rawdatainfo.hpp"

#include <string>
using namespace std;
using namespace csv;
namespace barcodeSpace {
    void BarcodeTableDumper::writeBarcodeLine(int cluster_id, const RawDataInfo& data_info) {
        this->_out << to_string(data_info._lineNumber) << data_info._rawdata << to_string(cluster_id) << '\n';
    }
    void BarcodeTableDumper::writeHeader() {
        for (const auto& h : _header) {
            this->_out << h;
        }
        this->_out << '\n';
    }
 
}
