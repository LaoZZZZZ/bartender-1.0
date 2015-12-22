//
//  barcodeeditor.cpp
//  barcode_project
//
//  Created by luzhao on 12/17/15.
//  Copyright © 2015 luzhao. All rights reserved.
//

#include "barcodeeditor.hpp"
#include "kmer_freq.h"
#include "typdefine.h"

#include <memory>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;
namespace barcodeSpace {
    void BarcodeEditor::editBarcodes(const std::vector<std::pair<std::string, freq> > &barcode_list) {
        reset(_seed_length);
        size_t max_barcode_length = 0;
        // Assign each barcode to a seed seletor by its length.
        unordered_map<size_t, std::shared_ptr<SeedSelector>> seed_selectors;
        for (const auto& barcode : barcode_list) {
            size_t len = barcode.first.length();
            if (seed_selectors.find(len) ==
                seed_selectors.end()) {
                seed_selectors[len].reset(new SeedSelector(_seed_length,len));
            }
            seed_selectors[len]->addBarcode(barcode);
            max_barcode_length = max(max_barcode_length, barcode.first.length());
        }
        
        // Find corresponding seed length for each barcode length;
        vector<size_t> barcode_2_seed_length(max_barcode_length + 1, 0);
        for (const auto& seed_selector : seed_selectors) {
            const vector<pair<int, int>> seed_position = seed_selector.second->getSeedsPositions();
            size_t seed_length_temp = 0;
            for (const auto& seed_span : seed_position) {
                seed_length_temp += seed_span.second;
            }
            barcode_2_seed_length[seed_selector.first] = seed_length_temp;
        }
        // Extract the seed part from each barcode.
        // and Update the connections between edited barcode with the original barcode
        for (size_t index = 0; index < barcode_list.size(); ++index) {
            size_t barcode_length = barcode_list[index].first.length();

            kmers_freq temp = extractSeed(seed_selectors[barcode_length]->getSeedsPositions(), barcode_list[index]);

            if (_barcode_tables[barcode_2_seed_length[barcode_length]].find(temp._key) ==
                _barcode_tables[barcode_2_seed_length[barcode_length]].end()) {
                _barcode_tables[barcode_2_seed_length[barcode_length]][temp._key] = temp._freq;
                _barcode_2_sequence[barcode_2_seed_length[barcode_length]][temp._key]=
                {RawDataInfo(barcode_list[index].first, index)};

            } else {
                _barcode_tables[barcode_2_seed_length[barcode_length]][temp._key] += temp._freq;
                _barcode_2_sequence[barcode_2_seed_length[barcode_length]][temp._key].push_back(RawDataInfo(barcode_list[index].first, index));
            }
            
            
        }
    }
    
    kmers_freq BarcodeEditor::extractSeed(const std::vector<std::pair<int, int>>& seed_span,
                                          const std::pair<string, freq>& barcode) {
        kmer result;
        for (const auto& span : seed_span) {
            for (int i = 0; i < span.second; ++i) {
                result |= _dict->asc2dna(barcode.first[span.first + i]);
                result <<= 2;
            }
        }
        result >>= 2;
        return kmers_freq(result, barcode.second);
    }

}   // namespace barcodeSpace