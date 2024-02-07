#ifndef DATA_HH
#define DATA_HH

#include "TFile.h"
#include "TTree.h"

class DataManager{

public:

	DataManager(TString);
	~DataManager();

	int GetNumEvents();

private:

	TFile* fInFile = NULL;
	TTree* fInTree = NULL;


};

#endif
