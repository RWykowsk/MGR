/*
 * ApprCovAllRecords.h
 *
 *  Created on: Jun 13, 2017
 *      Author: wyq
 */

#ifndef APPRCOVALLRECORDS_H_
#define APPRCOVALLRECORDS_H_

#include "ApprCovAllGroupsNumber.h"

class ApprCovAllRecords: public ApprCovAllGroupsNumber {
public:
	ApprCovAllRecords(int N,double alfa,double beta, double groupNoReq, string outputFile);
	virtual ~ApprCovAllRecords();
protected:
	virtual bool holds(vector<vector<int>*> *C);
	string outputFile;
};

#endif /* APPRCOVALLRECORDS_H_ */
