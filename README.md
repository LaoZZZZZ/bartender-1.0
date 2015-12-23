# bartender-1.0

# What's bartender?

Bartender is a c++ tool that is designed to process random barcode data. It currently has two functionalities. 
1. It could call out true barcodes and their true population size.
2. Find the trajectory for multiple time points(Coming out soon).

# Installation:
 Bartender requires that the gcc compler should be at least be gcc4-7 version. Installation is simple.
 1. make all
 2. sudo make install
 To uninstall:
 1. make clean;
 2. sudo make uninstall

# Input:
 Currently it accepts two different input formats. 
  1. The raw barcode text file. The file should only have one column, which is the raw barcode. 
  2. The raw count table csv file. The file has two columns. The first columns is the barcode sequence, the second column is the frequency of the corresponding barcode. This format is used for the case that the PCR effects has been removed.

The barcode in both input formats should be a stretch of DNA sequence(i.e.ATCTACTAC). It could contain some preceeding sequence or succeedings. 

#Output:
Bartender will output three files. 

## a. Cluster file.
   
This file contains general information of each cluster. It at least has four columns.
  1. Cluster.ID: the unique ID of the cluster
  2. Center: the center of this cluster. Typically the center will be viewed as the true barcode in the downstream analysis.
  3. Cluster.Score: the score measures the quality of the cluster. The lower the score is, the higher the cluster quality is. The score is calculated based on the entropy of binary variable using the Position Weight Matrix(PWM). Here is a brief explanation. Each cluster will have a PWM, which have the frequency of each nucleotide at each position. Based on the PWM, pick up the majority base pair and calculate its percentage(P). then the entropy value of each position will -Plog2(P) - (1 - P)log2(1-P) . The score is the maximum value of entropy values among all positions.
  4. The remaining columns are the cluster size at each time point. For single time point processing, the fourth column is the size of the cluster.

## b.Quality file.
This file keeps the PWM of each cluster. Check the files in the example for detail

## c.Barcode file.

This file is used to keep track the assignment of each raw barcode with respect to the clusters. It has three columns
  1. Line.Number: the line number in the raw input file.
  2. Barcode.Sequence: the extracted barcode from the that line. This barcode only contains base pairs in all random positions and all spacers are removed. So it should be different from the original barcode unless the input barcode already have spacers removed.
  3. Cluster.ID: the cluster id which this barcode belongs to.
