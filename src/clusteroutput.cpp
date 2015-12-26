#include "clusteroutput.h"
#include "cluster.h"
#include "clustertabledumper.hpp"
#include "qualitytabledumper.hpp"
#include "barcodetabledumper.hpp"

#include <array>
#include <cassert>
#include <list>
#include <memory>
#include <sstream>
#include <string>


using std::list;
using std::string;
using std::shared_ptr;
using std::array;

namespace barcodeSpace {

ClusterOutput::ClusterOutput(const string& prefix):_filename_prefix(prefix)
{
}

void ClusterOutput::WriteToFile(const std::list<std::shared_ptr<cluster>>& clusters,
                                const std::vector<barcode2Sequence>& raw_data_info) {
    if (clusters.empty())
        return;
    size_t max_length(0);
    // Get the maximum length of barcode
    for (size_t i = 1; i < raw_data_info.size(); ++i) {
        if (!raw_data_info[i].empty()) {
            max_length = i;
        }
    }
    size_t num_time_points = clusters.front()->columns().size();
    ClusterTableDumper cluster_dumper(_filename_prefix + "_cluster.csv", num_time_points);
    
    QualityTableDumper quality_dumper(_filename_prefix + "_quality.csv", max_length);
    BarcodeTableDumper barcode_link_dumper(_filename_prefix + "_barcode.csv");
    
    for (const auto& c : clusters) {
        cluster_dumper.WriteCluster(c);
        quality_dumper.WritePWM(c->ClusterID(), c->bpFrequency());
        for (const auto& edited_barcode : c->barcodes()) {
            const std::list<RawDataInfo>& barcodes = raw_data_info[c->center()->klen()].at(edited_barcode._key);
            for (const auto& raw_info : barcodes) {
                barcode_link_dumper.writeBarcodeLine(c->ClusterID(), raw_info);
            }
        }
        
            
    }
}
}   //namespace barcodeSpace
