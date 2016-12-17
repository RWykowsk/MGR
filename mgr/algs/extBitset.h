#ifndef _H_EXTBITSET
#define _H_EXTBITSET	1

#include <sys/types.h>
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <cstdlib>

typedef unsigned int uint;
typedef unsigned int extBitset;

using namespace std;

#define extBitsetINSERT(bitset,element) (bitset = (1 << (element-1)))
#define extBitsetREMOVE(bitset,element) (bitset &= ~(1 << (element-1)))
#define extBitsetUNION(a,b)		(a |= b)
#define extBitsetINTERSECTION(a,b)	(a &= b)
#define extBitsetMINUS(a,b)		(a &= ~b)
#define extBitsetINSERTALL(a,size)	(a = ~(~0 << size))
#define extBitsetCLEAR(a)		(a = 0)
#define extBitsetSETEQUAL(a,b)		(a = b)
#define extBitsetEXISTS(a,element)	(a & (1 << (element-1)))
#define extBitsetISSUPERSET(a,b)	((a & b) != a)
#define extBitsetISSUBSET(a,b)		((a & b) == a) // a is a subset of b


int extBitsetGETNEXT(uint bitset, int position);
int extBitsetPREFIX(uint a, uint b);

void extBitsetPRINT(uint bitset);
void extBitsetPRINTTOFILE(uint bitset, ofstream &outfile);


#endif
