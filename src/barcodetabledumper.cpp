//
//  barcodetabledumper.cpp
//  barcode_project
//
//  Created by luzhao on 12/21/15.
//  Copyright © 2015 luzhao. All rights reserved.
//

#include "barcodetabledumper.hpp"
#include "rawdatainfo.hpp"

namespace barcodeSpace {
    void BarcodeTableDumper::writeBarcodeLine(int cluster_id, const RawDataInfo& data_info) {
        this->_out << data_info._lineNumber << data_info._rawdata << cluster_id << '\n';
    }

}
