CC	= g++
CFLAGS	= -fPIC -w -O3 -std=c++11  -I${BOOST_INSTALL_DIR}/include
LDFLAGS	= -L${BOOST_INSTALL_DIR}/lib -lboost_regex -lboost_iostreams 

SINGLE	= bartender_single
EXTRACTOR = bartender_extractor
#COMBINER = bartender_combiner
SINGLEWRAPPER	= bartender_single_com
EXTRACTORWRAPPER	= bartender_extractor_com
INSTALLDIR	= /usr/local/bin

# command

RM	=rm
CP	=cp
CD	=cd
MV	=mv

	
BARTENDERSINGLESOURCES	= ./src/barcodeeditor.cpp ./src/barcodemutationgenerator.cpp ./src/barcodetabledumper.cpp ./src/centerclustermapper.cpp ./src/centerhistogramgenerator.cpp ./src/centerrecalibrator.cpp ./src/cluster.cpp ./src/clusteralgorithm.cpp ./src/clustercenterlinkgenerator.cpp ./src/clusteringwithtest.cpp ./src/clustermergerpooltester.cpp ./src/clustermergertester.cpp ./src/clustermergerunpooltester.cpp ./src/clusteroutput.cpp ./src/clusterpipeline.cpp ./src/clustersplitter.cpp ./src/clustertabledumper.cpp ./src/csvreader.cpp ./src/dictatorcenter.cpp ./src/dictatorcluster.cpp ./src/distanceselector.cpp ./src/errorrateestimator.cpp ./src/hypothesistester.cpp ./src/idgenerator.cpp ./src/kmer_freq.cpp ./src/kmerdecoder.cpp ./src/kmers_bitwisetransform.cpp ./src/kmers_dictionary.cpp ./src/bartender_single.cpp ./src/meansequentialestimator.cpp ./src/mergebycenters.cpp ./src/mixturebptester.cpp ./src/proportionpooltest.cpp ./src/proportiontest.cpp ./src/qualitytabledumper.cpp ./src/rawbarcodeprocessor.cpp ./src/rawdatainfo.cpp ./src/seedselector.cpp ./src/sequence.cpp ./src/util.cpp ./src/errorintroducer.cpp ./src/centerclustermapperiterator.cpp ./src/clustermergeronesampletester.cpp ./src/oneproportiontest.cpp ./src/clusterpruner.cpp
BARTENDERSINGLEOBJECTS=$(BARTENDERSINGLESOURCES:.cpp=.o)

BARTENDEREXTRACTORSOURCES	= ./src/kmerdecoder.cpp ./src/kmers_bitwisetransform.cpp ./src/kmers_dictionary.cpp ./src/sequence.cpp ./src/util.cpp ./src/singlereadsprocessor.cpp ./src/bartender_extractor.cpp ./src/barcodeextractor.cpp ./src/pattern.cpp ./src/fastapattern.cpp ./src/fastqpattern.cpp 
BARTENDEREXTRACTOROBJECTS=$(BARTENDEREXTRACTORSOURCES:.cpp=.o)
all: $(BARTENDERSINGLESOURCES) $(SINGLE) $(EXTRACTOR)
install:
	
	$(CP) $(SINGLE)	$(INSTALLDIR)/ 
	$(CP) $(EXTRACTOR)	$(INSTALLDIR)/ 
#	$(CP) $(COMBINER) $(INSTALLDIR)/
	$(CP) $(SINGLEWRAPPER) $(INSTALLDIR)/
	$(CP) $(EXTRACTORWRAPPER) $(INSTALLDIR)/
uninstall:
	$(RM) -r $(INSTALLDIR)/$(SINGLE)
	$(RM) -r $(INSTALLDIR)/$(EXTRACTOR)
	$(RM) -r $(INSTALLDIR)/$(SINGLEWRAPPER)
	$(RM) -r $(INSTALLDIR)/$(EXTRACTORWRAPPER)
clean:
	$(RM) $(BARTENDERSINGLEOBJECTS)
	$(RM) $(BARTENDEREXTRACTOROBJECTS)
	$(RM) $(SINGLE)
	$(RM) $(EXTRACTOR)
$(SINGLE): $(BARTENDERSINGLEOBJECTS) 
	$(CC) $(BARTENDERSINGLEOBJECTS) -o $@ 
$(EXTRACTOR): $(BARTENDEREXTRACTOROBJECTS) 
	$(CC) $(BARTENDEREXTRACTOROBJECTS) -o $@ $(LDFLAGS) 
.cpp.o:
	$(CC)  -c $(CFLAGS) $< -o $@

