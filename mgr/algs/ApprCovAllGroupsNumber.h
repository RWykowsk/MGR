/*
 * ApprCovAllGroupsNumber.h
 *
 *  Created on: Jun 7, 2017
 *      Author: wyq
 */

#ifndef APPRCOVALLGROUPSNUMBER_H_
#define APPRCOVALLGROUPSNUMBER_H_

#include "ApprCov.h"

class ApprCovAllGroupsNumber : public ApprCov {
public:
	ApprCovAllGroupsNumber(int N,double alfa,double beta, double groupNoReq);
	virtual ~ApprCovAllGroupsNumber();
protected:
	virtual void initialDeltaProcessing(std::vector<vector<int> *>* A);
	virtual bool holds(vector<vector<int>*> *C);
	vector<int> *groupsOKCounter;
	double groupNoReq;
};

#endif /* APPRCOVALLGROUPSNUMBER_H_ */
