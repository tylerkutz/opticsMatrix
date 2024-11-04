#ifndef SIEVE_HH
#define SIEVE_HH

#include <map>

#include "TString.h"

struct SieveHole{
	double R, Theta, Phi, LocalPhi;	
};

class SieveMap{

public:

	SieveMap(TString);
	~SieveMap();

	inline double GetHoleR(int holeid) {return sieveMap[holeid].R;}
	double GetHoleTheta(int);
	inline double GetHolePhi(int holeid) {return sieveMap[holeid].Phi;}
	inline double GetHoleLocalPhi(int holeid) {return sieveMap[holeid].LocalPhi;}
	inline std::vector<int> GetListOfHoleIDs() {return listOfHoleIDs;}
	inline void SetFoilZ(double fz) {foil_z = fz;}

private:

	double sieve_z;
	double foil_z;

	std::map<int, SieveHole> sieveMap;
	std::vector<double> localPhiShifts;
	std::vector<int> listOfHoleIDs;
	void LoadSieveHoles(TString);


};

#endif
