/*
 * ApprCovAllGroups.h
 *
 *  Created on: May 24, 2017
 *      Author: wyq
 */

#ifndef APPRCOVALLGROUPS_H_
#define APPRCOVALLGROUPS_H_

#include "ApprCov.h"

class ApprCovAllGroups : public ApprCov {
public:
	ApprCovAllGroups(int N,double alfa,double beta);
	virtual ~ApprCovAllGroups();
protected:
	virtual void initialDeltaProcessing(std::vector<vector<int> *>* A);
	virtual bool holds(vector<vector<int>*> *C);
	vector<bool> *allGroupsOK;
};

#endif /* APPRCOVALLGROUPS_H_ */
