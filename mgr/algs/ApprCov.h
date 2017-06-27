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
	ApprCov(int N, double alfa,double beta);
	virtual ~ApprCov();
protected:
	virtual void initialDeltaProcessing(std::vector<vector<int> *>* A);
	virtual bool holds(vector<vector<int>*> *C);
	vector<int> *decCardinalities;
	vector<int> *decCounters;
	vector<double> *coverages;
	double alfa;
	double beta;
private:


};

#endif /* APPRCOV_H_ */
