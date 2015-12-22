//
//  qualitytabledumper.hpp
//  barcode_project
//
//  Created by luzhao on 12/21/15.
//  Copyright © 2015 luzhao. All rights reserved.
//

#ifndef qualitytabledumper_hpp
#define qualitytabledumper_hpp

#include "kmers_dictionary.h"
#include "minicsv.h"


#include <array>
#include <vector>

namespace barcodeSpace {
    
    // This class could dump position weight matrix to file.
    class QualityTableDumper  {
    public:
        QualityTableDumper(const std::string& filename, size_t max_length_barcode) :
        _out(filename.c_str()), _max_barcode_length(max_length_barcode) {
            _out.set_delimiter(',', " ");
            _dict = kmersDictionary::getAutoInstance();
            generateHeader();
            writeHeader();
            
        }
        void WritePWM(int cluster_id, const std::vector<std::array<int, 4>>& pwm);
        ~QualityTableDumper() {
            this->_out.close();
        }
    private:
        void generateHeader();
        void writeHeader() {
            for (const auto& h : _header) {
                this->_out << h;
            }
            this->_out << '\n';
        }
        csv::ofstream _out;
        std::vector<std::string>    _header;
        std::shared_ptr<kmersDictionary> _dict;
        size_t _max_barcode_length;
    };
}   // namespace barcodeSpace

#endif /* qualitytabledumper_hpp */
