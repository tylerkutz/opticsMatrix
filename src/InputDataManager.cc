#include <iostream>
#include <fstream>
#include <algorithm>
#include <random>

#include "InputDataManager.hh"
#include "SieveMap.hh"
#include "MatrixFitter.hh"

#include "TFile.h"
#include "TTree.h"
#include "TTreeReader.h"

using namespace std;

InputDataManager::InputDataManager(TString inFileName, TString inTreeName) {

	fFile = new TFile(inFileName);
	fTree = (TTree*)fFile->Get(inTreeName);	
	
	GenerateTrainingIndex(0.6);
	

}

InputDataManager::~InputDataManager() {
}

void InputDataManager::SetRemollBranchNames() {

	gemR_branch 	= "gem1_r";
	gemPhi_branch 	= "gem1_ph";
	gemX_branch 	= "gem1_x";
	gemY_branch 	= "gem1_y";
	gemPx_branch 	= "gem1_px";
	gemPy_branch 	= "gem1_py";
	gemPz_branch 	= "gem1_pz";
	
	SetTreeReader();

}

void InputDataManager::SetJapanBranchNames() {
}

void InputDataManager::SetTreeReader() {
	
	if(gemR_branch=="") {
		cout << "You have not set the input branch names!" << endl;
		exit(-1);
	}

	fReader = new TTreeReader(fTree);

	gemR_val 	= new TTreeReaderValue<double>(*fReader, gemR_branch);
	gemPhi_val 	= new TTreeReaderValue<double>(*fReader, gemPhi_branch);
	gemX_val 	= new TTreeReaderValue<double>(*fReader, gemX_branch);
	gemY_val 	= new TTreeReaderValue<double>(*fReader, gemY_branch);
	gemPx_val 	= new TTreeReaderValue<double>(*fReader, gemPx_branch);
	gemPy_val 	= new TTreeReaderValue<double>(*fReader, gemPy_branch);
	gemPz_val 	= new TTreeReaderValue<double>(*fReader, gemPz_branch);
	holeID_val 	= new TTreeReaderValue<int>(*fReader, "hole_id");

}

void InputDataManager::ProcessEvents() {

	int ev = 0;

	while(fReader->Next()) {
	
		GetValues();

		gemRp 	= (gemX*gemPx + gemY*gemPy) / (gemR*gemPz);
		gemPhip	= (gemX*gemPy - gemY*gemPx) / (gemR*gemPz);

		double sievePhi = fSieveMap->GetHolePhi(holeID);
		double sieveTheta = fSieveMap->GetHoleTheta(holeID, 600.);

		double X[4] = {gemR, gemRp, gemPhi, gemPhip};
		double D[] = {sieveTheta, sievePhi};
		double E = 0.;

		if(trainingIndex[ev] == 1) {
			fMFitter->AddTrain(X, D, E);
		} else {
			fMFitter->AddTest(X, D, E);
		}

		ev++;	
	}
/*
	double* varMin = new double[4];
	double* varMax = new double[4];
	for(int i = 0; i < 4; i++) {
		varMin[i] = (*fMFitter->fFit->GetMinVariables())(i);
		varMax[i] = (*fMFitter->fFit->GetMaxVariables())(i);
	}

	fReader->Restart();
	ev = 0;
	while(fReader->Next()) {

		GetValues();
		
		gemRp 	= (gemX*gemPx + gemY*gemPy) / (gemR*gemPz);
		gemPhip	= (gemX*gemPy - gemY*gemPx) / (gemR*gemPz);

		double sievePhi = fSieveMap->GetHolePhi(holeID);
		double sieveTheta = fSieveMap->GetHoleTheta(holeID);

		double X[4] = {gemR, gemRp, gemPhi, gemPhip};
		double D = sieveTheta;
		double E = 0.;

		bool outOfRange = false;
		for(int iv = 0; iv < 4; iv++) {
			if(X[i] < varMin[i] || X[i] > varMax[i]) outOfRange = true;
		}

		if(outOfRange || ) continue;

	}
*/
}

void InputDataManager::GetValues() {

	gemR = **gemR_val;
	gemPhi = **gemPhi_val;
	gemX = **gemX_val;
	gemY = **gemY_val;
	gemPx = **gemPx_val;
	gemPy = **gemPy_val;
	gemPz = **gemPz_val;
	holeID = **holeID_val;

}

void InputDataManager::GenerateTrainingIndex(double trainingFraction) {

	int n_train = fTree->GetEntries() * trainingFraction;
	for(int i = 0; i < fTree->GetEntries(); i++) {
		if(i < n_train) {
			trainingIndex.push_back(1);
		} else {
			trainingIndex.push_back(0);
		}
	}	

	auto rd = std::random_device {}; 
	auto rng = std::default_random_engine { rd() };
	std::shuffle(std::begin(trainingIndex), std::end(trainingIndex), rng);

}

















