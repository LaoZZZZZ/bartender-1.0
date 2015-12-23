//
//  clustertabledumper.hpp
//  barcode_project
//
//  Created by luzhao on 12/21/15.
//  Copyright © 2015 luzhao. All rights reserved.
//

#ifndef clustertabledumper_hpp
#define clustertabledumper_hpp

//#include "csvoutput.h"
#include "cluster.h"
#include "kmerdecoder.hpp"
#include "minicsv.h"
#include "typdefine.h"

#include <array>
#include <list>
#include <memory>
#include <string>
#include <vector>
#include <unordered_map>

namespace barcodeSpace {
    
    struct ClusterTableElement {
        
        int cluster_id;
        double cluster_score;
        std::string center;
        std::vector<freq>   time_points;
        
    };
    
    class ClusterTableDumper {
    public:
        ClusterTableDumper(const std::string& filename):
        _out(filename.c_str()) {
            _out.set_delimiter(',', " ");
        }
        
        void WriteCluster(const std::shared_ptr<cluster>& c) {
            ClusterTableElement elem;
            elem.cluster_id = c->ClusterID();
            elem.cluster_score = maxEntropy(c->bpFrequency());
            elem.center = decodeKmer(c->center()->center(), c->center()->klen());
            elem.time_points = c->columns();
            Write(elem);
        }
        ~ClusterTableDumper() {
            this->_out.close();
        }
    private:
        // Write a single line.
        void Write(const ClusterTableElement& line);
        // Generates the header correspondingly upon the first cluster.
        void generateHeader(size_t num_time_points);
        void writeHeader();
        std::string decodeKmer(const kmer& k, size_t klen) {
            if (kmer_decoders.find(klen) == kmer_decoders.end()) {
                kmer_decoders[klen].reset(new KmerDecoder(klen));
            }
            return kmer_decoders[klen]->DNASequence(k);
        }
        double maxEntropy(const std::vector<std::array<int, 4>>& frequency_table);
        std::vector<std::string>    _header;


        csv::ofstream _out;
        std::unordered_map<size_t, std::shared_ptr<KmerDecoder>> kmer_decoders;
    };
}   // namespace barcodeSpace

#endif /* clustertabledumper_hpp */
