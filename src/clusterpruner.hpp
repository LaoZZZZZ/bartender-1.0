//
//  clusterpruner.hpp
//  barcode_project
//
//  Created by luzhao on 1/16/16.
//  Copyright © 2016 luzhao. All rights reserved.
//

#ifndef clusterpruner_hpp
#define clusterpruner_hpp

#include "centerrecalibrator.h"
#include "cluster.h"
#include "idgenerator.h"


#include <list>
#include <memory>
#include <vector>

namespace barcodeSpace {
    // This class is designed to prune the cluster list generated by the clusterpipeline class.
    // 1. Split clusters if the cluster is potentially consisted of multiple distinct barcodes.
    // 2. Reassign low frequency barcode to the splited cluster.
    // 3. Merge clusters who share the same center.
    // 4. Filter out those clusters whose size is below the cutoff.
    class ClusterPruner {
    public:
        ClusterPruner(double entropy_threshold, // Entropy thresholds that define mixture positions
                      size_t maximum_centers,   // The maximum centers to be detected.
                      double p_value, // used for test if the base pair is potential mixture.
                      double percentage_threshold,// The percentage that the bp is viewed as potential center
                      size_t cutoff); // Only cluster with size no less than this cutoff will be kept.
        const std::list<std::shared_ptr<cluster>>& prunedClusters()const { return _clusters;}
        void prune(const std::list<std::shared_ptr<cluster>>& clusters);
    private:
        std::shared_ptr<CenterRecalibrator> _recalibrator; // center recalibrator
        size_t  _cutoff;
        std::list<std::shared_ptr<cluster>> _clusters;
    };
}   // namespace barcodeSpace

#endif /* clusterpruner_hpp */
