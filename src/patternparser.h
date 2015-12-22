/*
 * Copyright 2014, Lu Zhao <luzhao1986@gmail.com>
 *
 * This file is part of suffix matching project.
 */
#ifndef PATTERNPARSER_H
#define PATTERNPARSER_H

#include <memory>
#include <string>
#include <fstream>
#include <algorithm>
#include "filebuf.h"
#include "sequence.h"
using std::shared_ptr;
using std::unique_ptr;
using std::string;
using std::ifstream;
using std::reverse;
namespace barcodeSpace{
/**
  * A general pattern that parses the sequence file.
  * Its subclass is designed to handle a specific file format,like fastq,fasta..
*/
class patternParser
{
public:
    patternParser(const string& file):
        _file(file),_nakeHandler(NULL){
        _nakeHandler = fopen(this->_file.c_str(),"r");
        if(!(_nakeHandler)){
            throw runtime_error(string("can not open file ") + _file);
        }
        fb_.reset(new FileBuf(this->_nakeHandler));
    }
    void parse(Sequence& r,bool& success,bool& done){
        this->parseImp(r,success,done);
        /*
        int start = this->extractBarcode(sequence,qual);
        if(start >=0){
            r->fowardSeq().installChars(sequence.c_str(),sequence.length());
            r->quality().install(qual.c_str(),qual.length());
            read.reset(r);
            success = true;
        }
        else{
            success = false;
        }
        done = this->fb_->eof();
        */
    }
    void reset(){
        fclose(this->_nakeHandler);
        this->fb_.reset();
        _nakeHandler = fopen(this->_file.c_str(),"r");
        if(!(_nakeHandler)){
            throw runtime_error(string("can not open file ") + _file);
        }
        fb_.reset(new FileBuf(this->_nakeHandler));
    }
    virtual ~patternParser(){
        fclose(this->_nakeHandler);
    }
private:
    virtual void parseImp(Sequence&,bool&,bool&) = 0;
    patternParser(const patternParser&);
    patternParser& operator=(const patternParser&);
protected:
    std::unique_ptr<FileBuf>                fb_;
private:
    string                                  _file;
    FILE*                                   _nakeHandler;
};
}
#endif // PATTERNPARSER_H
