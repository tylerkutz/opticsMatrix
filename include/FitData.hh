#ifndef FITDATA_HH
#define FITDATA_HH

#include "TFile.h"
#include "TTree.h"

class FitData{

public:

	FitData(TTree*);
	~FitData();

	void SetMatrixFitter();

private:
	TTree* fTree;
	void AddPrimeVariables();
	void ProcessEvents();

};

#endif
