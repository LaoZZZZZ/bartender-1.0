CC	= g++
CFLAGS	= -std=c++11 -fPIC -w -O3
LDFLAGS	= 

SINGLE	= bartender_single
#COMBINER = bartender_combiner
WRAPPER	= bartender_single_com
INSTALLDIR	= /usr/local/bin/

# command

RM	=rm
CP	=cp
CD	=cd
MV	=mv

	
BARTENDERSINGLESOURCES	= ./src/barcodeeditor.cpp ./src/barcodemutationgenerator.cpp ./src/barcodetabledumper.cpp ./src/centerclustermapper.cpp ./src/centerhistogramgenerator.cpp ./src/centerrecalibrator.cpp ./src/cluster.cpp ./src/clusteralgorithm.cpp ./src/clustercenterlinkgenerator.cpp ./src/clusteringwithtest.cpp ./src/clustermergerpooltester.cpp ./src/clustermergertester.cpp ./src/clustermergerunpooltester.cpp ./src/clusteroutput.cpp ./src/clusterpipeline.cpp ./src/clustersplitter.cpp ./src/clustertabledumper.cpp ./src/countbarcodeprocessor.cpp ./src/csvreader.cpp ./src/dictatorcenter.cpp ./src/dictatorcluster.cpp ./src/distanceselector.cpp ./src/errorrateestimator.cpp ./src/hypothesistester.cpp ./src/idgenerator.cpp ./src/kmer_freq.cpp ./src/kmerdecoder.cpp ./src/kmers_bitwisetransform.cpp ./src/kmers_dictionary.cpp ./src/bartender_single.cpp ./src/meansequentialestimator.cpp ./src/mergebycenters.cpp ./src/mixturebptester.cpp ./src/proportionpooltest.cpp ./src/proportiontest.cpp ./src/qualitytabledumper.cpp ./src/rawbarcodeprocessor.cpp ./src/rawdatainfo.cpp ./src/seedselector.cpp ./src/sequence.cpp ./src/util.cpp ./src/errorintroducer.cpp ./src/centerclustermapperiterator.cpp

BARTENDERSINGLEOBJECTS=$(BARTENDERSINGLESOURCES:.cpp=.o)
all: $(BARTENDERSINGLESOURCES) $(SINGLE) 
install:
	
	#$(LN) $(WRAPPER).py $(WRAPPER)
	$(CP) $(SINGLE)	$(INSTALLDIR) 
#	$(CP) $(COMBINER) $(INSTALLDIR)
	$(CP) $(WRAPPER) $(INSTALLDIR)
	$(CP) $(WRAPPER).py $(INSTALLDIR)
uninstall:
	$(RM) -r $(INSTALLDIR)/$(PROG)
	$(RM) -r $(INSTALLDIR)/$(WRAPPER)
clean:
	$(RM) $(BARTENDERSINGLEOBJECTS)
	$(RM) $(SINGLE)
$(SINGLE): $(BARTENDERSINGLEOBJECTS) 
	$(CC) $(BARTENDERSINGLEOBJECTS) -o $@ $(LDFLAGS) 
.cpp.o:
	$(CC)  -c $(CFLAGS) $< -o $@

