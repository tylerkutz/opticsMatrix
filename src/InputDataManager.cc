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
#include "TH1F.h"
#include "TROOT.h"
#include "TLine.h"
#include "TPad.h"
#include "TCanvas.h"
#include "TStyle.h"

using namespace std;

InputDataManager::InputDataManager(TString inFileName, TString inTreeName) {

	fFile = new TFile(inFileName);
	fTree = (TTree*)fFile->Get(inTreeName);	
	
	GenerateTrainingIndex(0.5);

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
	holeID_branch	= "hole_id";	

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
	holeID_val 	= new TTreeReaderValue<int>(*fReader, holeID_branch);

}

void InputDataManager::ProcessEvents() {

	int ev = 0;

	SetTreeReader();
	while(fReader->Next()) {
	
		GetValues();

		if(gemPhi < 0.) gemPhi+=2.*M_PI;
		
		gemRp 	= (gemX*gemPx + gemY*gemPy) / (gemR*gemPz);
		gemPhip	= (gemX*gemPy - gemY*gemPx) / (gemR*gemPz);

		if(gemR > radCutMaxR[holeID]) continue;

		double sievePhi = fSieveMap->GetHolePhi(holeID);
		if(sievePhi < 0) sievePhi+=2.*M_PI;
		double sieveTheta = fSieveMap->GetHoleTheta(holeID);

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


void InputDataManager::GetRadiativeTailCut() {

	vector<int> holeIDs = fSieveMap->GetListOfHoleIDs();

	TH1F* rad1 = new TH1F("rad1", "", 100, 650, 1150); 

	gROOT->SetBatch(kTRUE);
	TCanvas* c1 = new TCanvas("c1", "", 700, 500);
	gStyle->SetOptStat(0);

	TLine* lrmax = new TLine(0.,0.,1.,1.);
	lrmax->SetLineColor(2);

	for(const int& holeid : holeIDs) {
		
		fTree->Draw(gemR_branch + ">>rad1", Form("hole_id==%i", holeid), "GOFF");

		double holeCenter = rad1->GetBinCenter(rad1->GetMaximumBin());

		double rMin = holeCenter - 50.;
		double rMax = holeCenter + 50.;

		TH1F* rad2 = new TH1F("rad2", "", 100, rMin, rMax);
		rad2->GetXaxis()->SetTitle("r (mm)");
		rad2->SetTitle(Form("Hole %i", holeid));

		fTree->Draw(gemR_branch + ">>rad2", Form("hole_id==%i", holeid), "GOFF");

		double rMean = rad2->GetMean();
		double rRMS = rad2->GetRMS();

		radCutMaxR[holeid] = rMean + 2.*rRMS;

		rad2->Draw();
		c1->Update();
		lrmax->SetX1(radCutMaxR[holeid]);
	       	lrmax->SetY1(0.);
		lrmax->SetX2(radCutMaxR[holeid]);
		lrmax->SetY2(gPad->GetUymax());
		lrmax->Draw("SAME");
		c1->SaveAs(Form("rad_cut_hole_%i.pdf",holeid));			

		rad2->Delete();

	}

}















