//
//  clustertabledumper.cpp
//  barcode_project
//
//  Created by luzhao on 12/21/15.
//  Copyright © 2015 luzhao. All rights reserved.
//

#include "clustertabledumper.hpp"
#include "split_util.h"

#include <algorithm>
namespace barcodeSpace {
    
    void ClusterTableDumper::Write(const ClusterTableElement& line) {
        if (_header.empty()) {
            generateHeader(line.time_points.size());
            writeHeader();
        }
        this->_out << line.cluster_id << line.center << line.cluster_score;
        
        for (const auto& tsize : line.time_points) {
            this->_out << tsize;
        }
        this->_out << '\n';
    }
    
    void ClusterTableDumper::generateHeader(size_t num_time_points) {
        _header.push_back("Cluster.ID");
        _header.push_back("Center");
        _header.push_back("Cluster.Score");
        
        std::stringstream buffer;
        for(size_t time_point = 1; time_point <= num_time_points; ++time_point) {
            buffer << "time_point_" << time_point;
            _header.push_back(buffer.str());
            buffer.str("");
        }
        
    }
    
    double ClusterTableDumper::maxEntropy(const std::vector<std::array<int, 4>>& frequency_table) {
        double score(0);
        for (const auto& bp_freq : frequency_table) {
            score = fmax(score, Entropy(bp_freq));
        }
        return score;
    }
}   // namespace barcodeSpace