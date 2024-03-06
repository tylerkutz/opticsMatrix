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
	double GetHoleTheta(int, double);
	inline double GetHolePhi(int holeid) {return sieveMap[holeid].Phi;}
	inline double GetHoleLocalPhi(int holeid) {return sieveMap[holeid].LocalPhi;}

private:

	double sieve_z;

	std::map<int, SieveHole> sieveMap;
	std::vector<double> localPhiShifts;
	void LoadSieveHoles(TString);

};

#endif
