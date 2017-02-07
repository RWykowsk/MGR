/*
 * SuperFunBA.h
 *
 *  Created on: 13.11.2016
 *      Author: WYQ
 */

#ifndef SUPERFUNBA_H_
#define SUPERFUNBA_H_

#include "SuperFun.h"

class SuperFunBA: public SuperFun
{
public:
	SuperFunBA(int N);
protected:
	virtual void doDecisionProduct(Candidate* X,
			Candidate* Y,
			Candidate** Cand);
};

#endif /* SUPERFUNBA_H_ */
