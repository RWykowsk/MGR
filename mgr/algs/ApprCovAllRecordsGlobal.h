/*
 * ApprCovAllRecordsGlobal.h
 *
 *  Created on: Jun 13, 2017
 *      Author: wyq
 */

#ifndef APPRCOVALLRECORDSGLOBAL_H_
#define APPRCOVALLRECORDSGLOBAL_H_

#include "ApprCovAllRecords.h"

class ApprCovAllRecordsGlobal: public ApprCovAllRecords {
public:
	ApprCovAllRecordsGlobal(int N,double alfa,double beta, double groupNoReq, string outputFile);
	virtual ~ApprCovAllRecordsGlobal();
protected:
	virtual bool holds(vector<vector<int>*> *C);
};

#endif /* APPRCOVALLRECORDSGLOBAL_H_ */
