/*
 * ApprCov.h
 *
 *  Created on: 06.03.2017
 *      Author: wyq
 */

#ifndef APPRCOV_H_
#define APPRCOV_H_

#include "BasicAlg.h"

class ApprCov: public BasicAlg {
public:
public:
	//ApprCov(int N);
	ApprCov(int N, double alfa);
	virtual ~ApprCov();
protected:
	virtual void initialDeltaProcessing(std::vector<vector<int> *>* A);
	virtual bool holds(vector<vector<int>*> *C);
private:
	vector<int> *decCardinalities;
	vector<int> *decCounters;
	vector<double> *coverages;
	double alfa;

};

#endif /* APPRCOV_H_ */
