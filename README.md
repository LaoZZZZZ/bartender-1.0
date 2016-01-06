# bartender-1.0

# What's bartender?

Bartender is a c++ tool that is designed to process random barcode data. Bartender is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY.

It currently has two functionalities. 

1. Extracts the barcode from the original reads
2. It can call out true barcodes and their population size.


It will be able to handle multiple time points and estimate the trajectory in the next version.

# Installation
 Bartender requires boost library and gcc compiler which should be no older than gcc47. Installation is simple.
 1. make all
 2. sudo make install

The default install directory is /usr/local/bin and is hard coded in the make file. If you want to change the install directory, you need to make a small change to the Makefile.

# Components
##Extraction
###Input
This components takes a reads file and outputs the extracted barcode. Current it only supports single-end reads. The following are the input parameters.

-f: the input reads file(required). Only supports FASTQ and FASTA.

-o: the output prefix(required). The output filename will be output prefix + "_barcode.txt"

-q: the quality threshold(optional). Only those barcode that has average quality no less than this threshold will be kept. This threshold is the corresponding ascii value. Different formats might have different ranges, please check relevant reference to determine the value. The default value is 0. That is it will accept all valid barcode.

 
-m: the total number of mismatches allowed in the preceeding and suceeding sequence(optional). Default value is 2. The mismatches will be evenly distributed to two parts.

-p: the barcode pattern(required). The general pattern looks like XXXX[min-max]XXXXX[min-max]XXXXX. XXXX part are those fixed DNA sequence, ie. preceeding sequence, spacers and succeeding sequence. [min-max] specified the range of number of random base pairs between two fix parts. Both min and max are integers. The pattern should obey the following rules:
 1. It could only have DNA sequence, numerical value, brackets and '-'
 2. The DNA sequence before the first bracket is viewed as the proceeding sequence.
 3. The DNA sequence after the last bracket is viewed as the succeeding sequence.
 5. The range specified by the numeric values within each pair of brackets specifies the possible number of random positions for that part. i.e [2-3] means this random part at least has 2 base pair and 3 base pairs at most. [3] means this part has 3 base pair. 
 6. The pattern must start with fixed sequence and end with fixed sequence. In another word, the current version only supports the barcode that has non-empty wrapping sequence on both ends.
 7. The maximum length of preceeding and succeeding sequence is 5.
 
Here are some valid examples. 

TACCT[10]ATAA: Preceeding sequence is TACCT followed by a random part having 10 base pairs. The succeeding sequence is ATAA.

TTAC[3]AA[4-5]CCT: The preceeding sequence is TTAC. First random part has 3 base pairs followed by a spacers,which is AA. The second random parts could possibly has 4 or 5 base pairs. The succeeding sequence is CCT.

###Output
One output file will be generated. It has two columns. The first column is the extracted barcode(Only random parts are kept). The second column is the original line number in the reads file.


##Clustering
# Input:
 Currently it accepts two different input formats(See the file under the example folder). 
  1. The raw barcode text file. The file should only have one column, which is the raw barcode. 
  2. The raw count table csv file. The file has two columns. The first column is the barcode sequence, the second column is the frequency of the corresponding barcode. This format is used for the case that the PCR effect has been removed.

The barcode in both input formats should be a stretch of DNA sequence(i.e.ATCTACTAC). It could contain a COMMON preceeding or succeeding sequence. In another word, the differences among the raw barcodes should come from the barcode region not from the extra preceeding or succeeding sequence.

# Usage

The command name is bartender_single_com, which is a python file. Use "bartender_single_com -h" for help. There are only 3 options and is very easy to use(See bartender_test.sh file under the example).

# Output:
Bartender outputs three files. 

## a. Cluster file.
   
This file contains general information of each cluster. It has at least four columns.
  1. Cluster.ID: the unique ID of the cluster.
  2. Center: the center of this cluster. The center is the representative sequence of all original barcodes that belong to this cluster. Typically the center will be viewed as the true barcode in the downstream analysis.
  3. Cluster.Score: the score measures the quality of the cluster. The lower the score is, the higher the cluster quality is. The score is calculated based on the entropy of binary variable using the Position Weight Matrix(PWM). Here is a brief explanation. Each cluster will have a PWM, which has the frequency of each nucleotide at each position. Based on the PWM, pick up the majority nucleotide and calculate its percentage(P). then the entropy value of each position is -P*log2(P) - (1 - P)*log2(1-P) . The score is the maximum value of entropy values among all positions.
  4. The remaining columns are the cluster size at each time point. For single time point processing, the fourth column is the size of the cluster.

## b.Quality file.

This file keeps the PWM of each cluster. Check the files in the example folder for detail.

## c.Barcode file.

This file is used to keep track the assignment of each raw barcode with respect to the cluster. It has three columns.
  1. Line.Number: the line number in the raw input file.
  2. Barcode.Sequence: the extracted barcode from the that line. This barcode only contains base pairs in all random positions and all spacers are removed. So it should be different from the original barcode unless the input barcode already has spacers removed.
  3. Cluster.ID: the cluster id which this barcode belongs to.
