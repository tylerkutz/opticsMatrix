#ifndef INPUTDATA_HH
#define INPUTDATA_HH

class TFile;
class TTree;
class TTreeReader;
class SieveMap;
class MatrixFitter;

#include <vector>

#include "TTreeReaderValue.h"

class InputDataManager{

public:

	InputDataManager(TString, TString);
	~InputDataManager();

	inline TTree* GetTree() { return fTree;}	

	void SetRemollBranchNames();
	void SetJapanBranchNames();
	
	inline void SetSieveMap(SieveMap* sm) {fSieveMap = sm;}
	inline void SetMatrixFitter(MatrixFitter* mf) {fMFitter = mf;}

	void SetTreeReader(); 

	void ProcessEvents();

private:

	TFile* fFile;
	TTree* fTree;
	TTreeReader* fReader;

	SieveMap* fSieveMap;
	MatrixFitter* fMFitter;

	void GenerateTrainingIndex(double);
	std::vector<int> trainingIndex;

	// Input values
	double gemR;
	double gemPhi;
	double gemX;
	double gemY;
	double gemPx;
	double gemPy;
	double gemPz;
	int holeID;
	// Calculated values
	double gemRp;
	double gemPhip;

	TTreeReaderValue<double>* gemR_val;
	TTreeReaderValue<double>* gemPhi_val;
	TTreeReaderValue<double>* gemX_val;
	TTreeReaderValue<double>* gemY_val;
	TTreeReaderValue<double>* gemPx_val;
	TTreeReaderValue<double>* gemPy_val;
	TTreeReaderValue<double>* gemPz_val;
	TTreeReaderValue<int>* holeID_val;

	void GetValues();

	TString gemR_branch = "";
	TString gemPhi_branch = "";
	TString gemX_branch = "";
	TString gemY_branch = "";
	TString gemPx_branch = "";
	TString gemPy_branch = "";
	TString gemPz_branch = "";

};

#endif
