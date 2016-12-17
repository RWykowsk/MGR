/*
 * SuperFun.cpp
 *
 *  Created on: 13.11.2016
 *      Author: WYQ
 */

#include "SuperFun.h"

SuperFun::SuperFun()
{
	// TODO Auto-generated constructor stub

}

SuperFun::~SuperFun()
{
	// TODO Auto-generated destructor stub
}

bool SuperFun::superHolds(vector<vector<int> *> &C)
{
	if (C.size() == 0)
		return true;
	return false;
}

virtual void SuperFun::candidatesFurtherProcessing(vector<Candidate*> tmp,
		const ofstream& output,
		vector<Candidate*>& Rk)
{
	for (int k = 2; tmp.size() > 0; k++)
	{
		output << tmp.size() << '\t';
		for (int z = 0; z < tmp.size(); z++)
			if (superHolds(tmp.at(z)->groups))
			{
				Rk.push_back(tmp.at(z));
				tmp.erase(tmp.begin() + z);
				z--;
			}
		initializeStatistics();
		vector<Candidate*> tmp2;
		funGen(tmp, k, tmp2);
		//        output << "Liczba wszystkich wytworzonych podzialow "<<No_divisions<<endl;
		//        output << "Liczba wytworzonych podzialow po czyszczeniu kandydatów(pruning) "<<No_divisions2<<endl;
		//        output << "Suma wszystkich grup po czyszczeniu kandydatów(pruning) "<<sum_groups<<endl;
		//        double avg_groups=double(sum_groups)/No_divisions2;
		//        output << "Srednia liczba grup po czyszczeniu kandydatów(pruning) "<<avg_groups<<endl;
		//        output << "Suma wszystkich rekordow po czyszczeniu kandydatów(pruning) "<<sum_records<<endl;
		//        double avg_records=double(sum_records)/No_divisions2;
		//        output << "Srednia liczba rekordow po czyszczeniu kandydatów(pruning) "<<avg_records<<endl;
		printStatistics(output);
		tmp = tmp2;
	}
}

virtual void SuperFun::doDecisionProduct(Candidate* X,
		Candidate* Y,
		Candidate** Cand)
{
	DecisionProduct(X->groups, Y->groups, *Cand);
}

virtual void SuperFun::funGen(vector<Candidate *> &Ck,
		int k,
		vector<Candidate *> &output)
{
	for (unsigned int i = 0; i < Ck.size(); i++)
		for (unsigned int j = i + 1; j < Ck.size(); j++)
		{
			bool ok_to_merge = false;
			int prefix;
			prefix = extBitsetPREFIX(Ck.at(i)->Cand_id, Ck.at(j)->Cand_id);
			if (prefix + 1 == k)
				ok_to_merge = true;
			if (ok_to_merge)
			{
				extBitset Cand_id = Ck.at(i)->Cand_id;
				extBitsetUNION(Cand_id, Ck.at(j)->Cand_id);
				Candidate *X, *Y;
				InitializeParenthood(Ck.at(i), Ck.at(j), X, Y, k);
				bool cand_validate = true;
				Candidate *E;
				int pos;
				pos = extBitsetGETNEXT(Cand_id, 0);
				extBitset cand_validator;
				while (pos > 0)
				{ //petla do tworzenia sprawdzianow
					cand_validator = Cand_id;
					extBitsetREMOVE(cand_validator, pos);
					if ((cand_validator == Ck.at(i)->Cand_id)
							|| (cand_validator == Ck.at(j)->Cand_id)) //jezeli jest równy ktoremus ojcu
					{
						pos = extBitsetGETNEXT(Cand_id, pos);
						continue; //to przejdz do nastepnego sprawdzianu, m++
					}
					for (unsigned int o = 0; o < Ck.size(); o++)
					{ //sprawdzenie czy sprawdzian spelnia warunki
						cand_validate = false;
						if (cand_validator == Ck.at(o)->Cand_id)
						{ //sprawdz czy istnieje podzbior
							cand_validate = true;
							E = Ck.at(o);
							break;
						}
					}
					if (cand_validate == false)
						break;
					else
						UpdateParenthood(E, X, Y, k);
					pos = extBitsetGETNEXT(Cand_id, pos);
				}

				if (cand_validate)
				{
					Candidate *Cand = new Candidate;
					doDecisionProduct(X, Y, &Cand);
					No_divisions++;
					sum_groups_before = sum_groups_before + Cand->GroupsNo;
					sum_records_before = sum_records_before + Cand->RecordsNo;
					Cand->Cand_id = Cand_id;
					if ((Cand->RecordsNo != X->RecordsNo)
							|| (Cand->GroupsNo != X->GroupsNo))
					{
						output.push_back(Cand);
						No_divisions2++;
						sum_groups = sum_groups + Cand->GroupsNo;
						sum_records = sum_records + Cand->RecordsNo;
					}
					else
						delete Cand;

				}
			}

		}

}

void SuperFun::InitializeParenthood(Candidate *A,
		Candidate *B,
		Candidate *&X,
		Candidate *&Y,
		int k)
{
	if (k == 1)
	{
		A->RecordsNo = CountRecords(A);
		B->RecordsNo = CountRecords(B);
	}
	if ((A->RecordsNo < B->RecordsNo)
			|| ((A->RecordsNo == B->RecordsNo) && (A->GroupsNo > B->GroupsNo)))
	{
		X = A;
		Y = B;
	}
	else
	{
		X = B;
		Y = A;
	}
}

int SuperFun::CountRecords(Candidate *C)
{
	int records = 0;
	for (unsigned int z = 0; z < C->groups.size(); z++) //wszystkie grupy
		for (unsigned int a = 0; a < C->groups.at(z)->size(); a++) //wszystkie elementy z grupy
			records++;
	return records;
}

void SuperFun::UpdateParenthood(Candidate *E,
		Candidate *&X,
		Candidate *&Y,
		int k)
{
	if (k == 1)
		E->RecordsNo = CountRecords(E);
	if (X->RecordsNo < Y->RecordsNo)
	{
		if (E->RecordsNo < X->RecordsNo)
		{
			Y = X;
			X = E;
		}
		else if (E->RecordsNo == X->RecordsNo)
		{
			if (E->GroupsNo > X->GroupsNo)
			{
				Y = X;
				X = E;
			}
			else
				Y = E;
		}
		else if (E->RecordsNo < Y->RecordsNo)
			Y = E;
		else if (E->RecordsNo == Y->RecordsNo)
		{
			if (E->GroupsNo > Y->GroupsNo)
			{
				Y = E;
			}
		}

	}
	else if (E->RecordsNo < X->RecordsNo)
		X = E;
	else if (E->RecordsNo == X->RecordsNo)
	{
		if (E->GroupsNo > X->GroupsNo)
		{
			X = E;
		}
		else if (E->GroupsNo > Y->GroupsNo)
			Y = E;
	}

}

void SuperFun::DecisionProduct(
		vector<vector<int> *> &A,
		vector<vector<int> *> &B,
		Candidate *&C)
{
	vector<vector<int> > S;
	C->groups.clear();
	C->GroupsNo = 0;
	C->RecordsNo = 0;
	S.resize(dataRowsNumber);
	partitionArrayRepresentation(B);
	set<int> BGroupIds; //set, bo groupsID moze sie powtarzac, a my nie chcemy
	for (unsigned int i = 0; i < A.size(); i++)
	{ //petla obslugujaca kazda grupe A
		BGroupIds.clear();
		int j;
		for (unsigned int k = 0; k < A.at(i)->size(); k++)
		{ //petla obslugujaca kazdy element z grupy z A
			j = T.at(A.at(i)->at(k)); // A.at(i).at(k) - oid
			if (j != -1)
			{
				S.at(j).push_back(A.at(i)->at(k)); //S[j]
				BGroupIds.insert(j);
			}
		}
		set<int>::iterator it;
		for (it = BGroupIds.begin(); it != BGroupIds.end(); ++it)
		{
			if (IsGroupContainedInAnyDecisionClass(S.at(*it)) == false)
			{
				//C->groups.push_back(new vector<int *>());
				C->groups.push_back(new vector<int>(S.at(*it)));
//                for (unsigned int x = 0; x < S.at(*it).size(); x++) {//insertowanie S[j] do C
//                    C->groups.back()->push_back(new int(S.at(*it).at(x)));
				C->RecordsNo = C->RecordsNo + S.at(*it).size();
//                }
				C->GroupsNo++;
			}

		}
		S.clear();
		S.resize(dataRowsNumber);
	}
	clearStrippedPartitionArrayRepresentation(B);
}

bool SuperFun::IsGroupContainedInAnyDecisionClass(vector<int> &S)
{
	if (S.size() > 1)
	{
		int oid = S.at(0);
		int firstGroup = delta.at(oid);
		if (firstGroup == -1)
			return false;
		for (unsigned int k = 1; k < S.size(); k++)
		{ //petla obslugujaca kazdy element z grupy z S
			oid = S.at(k);
			int nextGroup = delta.at(oid);
			if (firstGroup != nextGroup)
				return false;
		}
	}

	return true;
}

