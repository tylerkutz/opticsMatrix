#include <iostream>
#include <fstream>

#include "DataManager.hh"

using namespace std;

DataManager::DataManager(TString inFileName) {

	fInFile = new TFile(inFileName);
	fInTree = (TTree*)fInFile->Get("newT"); 

}

DataManager::~DataManager() {
}

int DataManager::GetNumEvents() {

	if(fInTree) {
		return fInTree->GetEntries();		
	}	

	return -1;

}



