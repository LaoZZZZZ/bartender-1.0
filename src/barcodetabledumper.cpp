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
namespace barcodeSpace {
    void BarcodeTableDumper::writeBarcodeLine(int cluster_id, const RawDataInfo& data_info) {
        _cash[0] = to_string(data_info._lineNumber);
        _cash[1] = data_info._rawdata;
        _cash[2] = to_string(cluster_id);
        _out.Write(_cash);
    }
 
}
