//
//  barcodetabledumper.hpp
//  barcode_project
//
//  Created by luzhao on 12/21/15.
//  Copyright © 2015 luzhao. All rights reserved.
//

#ifndef barcodetabledumper_hpp
#define barcodetabledumper_hpp

#include "minicsv.h"
#include "rawdatainfo.hpp"

#include <list>
#include <string>
#include <vector>
namespace barcodeSpace {
    class BarcodeTableDumper {
    public:
        BarcodeTableDumper(const std::string& filename) : _out(filename.c_str()) {
            generateHeader();
            writeHeader();
        }
        void writeBarcodeLine(int cluster_id, const RawDataInfo& data_info);
        ~BarcodeTableDumper() {
            this->_out.close();
        }
    private:
        void generateHeader() {
            _header.push_back("Line.Number");
            _header.push_back("Barcode.Sequence");
            _header.push_back("Cluster.ID");
        }
        void writeHeader();

        csv::ofstream _out;
        std::vector<std::string> _header;
    };
}   // namespace barcodeSpace
#endif /* barcodetabledumper_hpp */
