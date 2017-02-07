/*
 * BasicAlg.cpp
 *
 *  Created on: 29.10.2016
 *      Author: WYQ
 */

#include "BasicAlg.h"

BasicAlg::BasicAlg(int N)
{
	this->rNo = N;
	this->dataRowsNumber = N;
}

BasicAlg::~BasicAlg()
{
	// TODO Auto-generated destructor stub
}

void BasicAlg::partitionArrayRepresentation(vector<vector<int> *> *A)
{
	for (unsigned int i = 0; i < A->size(); i++)
	{
		for (unsigned int j = 0; j < A->at(i)->size(); j++)
		{
			T.at(A->at(i)->at(j)) = i;
		}
	}
}

void BasicAlg::deltaPartitionArrayRepresentation(vector<vector<int> *> *A)
{
	for (unsigned int i = 0; i < A->size(); i++)
	{
		for (unsigned int j = 0; j < A->at(i)->size(); j++)
		{
			delta.at(A->at(i)->at(j)) = i;
		}
	}
}

void BasicAlg::doBeforeProduct(Candidate *Ck)
{
	groups = new vector<vector<int>*>();
}

void BasicAlg::product(vector<vector<int> *> *A, vector<vector<int> *> *B)
{
	vector<vector<int> > S;
	S.resize(dataRowsNumber);
	GroupsNo = 0;
	partitionArrayRepresentation(A);
	set<int> AGroupIds; //set, bo groupsID moze sie powtarzac, a my nie chcemy
	for (unsigned int i = 0; i < B->size(); i++)
	{ //petla obslugujaca kazda grupe B
		AGroupIds.clear();
		int j;
		for (unsigned int k = 0; k < B->at(i)->size(); k++)
		{ //petla obslugujaca kazdy element z grupy z B
			j = T.at(B->at(i)->at(k)); // B.at(i).at(k) - oid
			S.at(j).push_back(B->at(i)->at(k)); //S[j]
			AGroupIds.insert(j);
		}
		set<int>::iterator it;
		for (it = AGroupIds.begin(); it != AGroupIds.end(); ++it)
		{
			groups->push_back(new vector<int>(S.at(*it)));
//            C.push_back(new vector <int>());
//            for (unsigned int x = 0; x < S.at(*it).size(); x++) {//insertowanie S[j] do C
//                C.back()->push_back(S.at(*it).at(x));
//            }
			GroupsNo++;
		}
		S.clear();
		S.resize(dataRowsNumber);
	}
}

bool BasicAlg::holds(vector<vector<int> *> *C)
{
	for (unsigned int i = 0; i < C->size(); i++)
	{ //petla obslugujaca kazda grupe z C
		int oid = C->at(i)->at(0);
		int firstGroup = delta.at(oid);
		for (unsigned int k = 1; k < C->at(i)->size(); k++)
		{ //petla obslugujaca kazdy element z grupy z C
			oid = C->at(i)->at(k);
			int nextGroup = delta.at(oid);
			if (firstGroup != nextGroup)
				return false;
		}
	}
	return true;
}

void BasicAlg::addCandidate(extBitset Cand_id,
		vector<vector<int> *>* groups,
		vector<Candidate*>& output)
{
	//cout<<"bla2"<<endl;
	output.push_back(new Candidate);
	output.back()->Cand_id = Cand_id;
	//output->back()->Cand_id = new vector <int> (Cand_id);
	output.back()->GroupsNo = GroupsNo; // i ostatni id z drugiego dziecka
	output.back()->groups = groups;
	No_divisions2++;
	sum_groups = sum_groups + GroupsNo;
	sum_records = sum_records + dataRowsNumber;
}

bool BasicAlg::validateCandidate(extBitset Cand_id,
		vector<vector<int> *>* groups,
		vector<Candidate*>& Ck,
		vector<Candidate*>& output)
{
	bool cand_validate = false;
	int pos;
	pos = extBitsetGETNEXT(Cand_id, 0);
	extBitset cand_validator;
	while (pos > 0)
	{
		//petla do tworzenia sprawdzianow
		cand_validator = Cand_id;
		extBitsetREMOVE(cand_validator, pos);
		for (unsigned int o = 0; o < Ck.size(); o++)
		{
			//sprawdzenie czy sprawdzian spelnia warunki
			cand_validate = false;
			if (cand_validator == Ck.at(o)->Cand_id)
			{
				//sprawdz czy istnieje podzbior
				cand_validate = true;
				if (GroupsNo == Ck.at(o)->GroupsNo) //sprawdz czy podzbior ma tyle samo grup
				{
					cand_validate = false;
				}
				break;
			}
		}
		if (cand_validate == false)
		{
			//jezeli nie spelnia to nie sprawdzaj dalszych sprawdzianow
			break;
		}
		pos = extBitsetGETNEXT(Cand_id, pos);
	}
	if (cand_validate == true)
	{
		addCandidate(Cand_id, groups, output);
	}
	return cand_validate;
}

void BasicAlg::mergeCandidates(unsigned int i,
		unsigned int j,
		vector<Candidate*>& Ck,
		vector<Candidate*>& output)
{
	extBitset Cand_id = Ck.at(i)->Cand_id;
	extBitsetUNION(Cand_id, Ck.at(j)->Cand_id);
	doBeforeProduct(Ck.at(j));
	product(Ck.at(i)->groups, Ck.at(j)->groups);
	No_divisions++;
	sum_groups_before = sum_groups_before + GroupsNo;
	sum_records_before = sum_records_before + rNo;
	bool cand_validate = validateCandidate(Cand_id, groups, Ck, output);
}

void BasicAlg::funGen(vector<Candidate *> &Ck,
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
				mergeCandidates(i, j, Ck, output);
			}

		}

}

void BasicAlg::prepareCandidate(vector<Candidate*>& C1)
{
	for (unsigned int z = 0; z < C1.size(); z++)
		C1.at(z)->GroupsNo = C1.at(z)->groups->size();
}

void BasicAlg::removeDecisionColumn(int d_column, vector<Candidate*>& C1)
{
	for (unsigned int z = 0; z < C1.at(d_column - 1)->groups->size(); z++)
	{
		//atrybut ostatni(decyzja) wszystkie grupy -usuwanie
		//        for (unsigned int a = 0; a < C1.at(d_column - 1)->groups.at(z)->size(); a++) {//wszystkie elementy z grupy
		//            delete C1.at(d_column - 1)->groups.at(z)->at(a);
		//        }
		delete C1.at(d_column - 1)->groups->at(z);
	}
	delete C1.at(d_column - 1);
	C1.erase(C1.begin() + d_column - 1);
}

void BasicAlg::initializeStatistics()
{
	No_divisions = 0;
	No_divisions2 = 0;
	sum_groups = 0;
	sum_records = 0;
	sum_groups_before = 0;
	sum_records_before = 0;
}

void BasicAlg::printHeaders(ofstream& output)
{
	output << "Liczba kandydatow o dlugosci : " << '\t';
	output << "Liczba wszystkich wytworzonych podzialow " << '\t';
	output << "Suma wszystkich grup " << '\t';
	output << "Srednia liczba grup " << '\t';
	output << "Suma wszystkich rekordow " << '\t';
	output << "Srednia liczba rekordow " << '\t';
	output
			<< "Liczba wytworzonych podzialow po czyszczeniu kandydatów(pruning) "
			<< '\t';
	output << "Suma wszystkich grup po czyszczeniu kandydatów(pruning) "
			<< '\t';
	output << "Srednia liczba grup po czyszczeniu kandydatów(pruning) "
			<< '\t';
	output << "Suma wszystkich rekordow po czyszczeniu kandydatów(pruning) "
			<< '\t';
	output << "Srednia liczba rekordow po czyszczeniu kandydatów(pruning) "
			<< '\n';
}

void BasicAlg::search4FunctionalDependencies(vector<Candidate*>* tmp,
		vector<Candidate*>& Rk)
{
	//        output << "Identyfikatory minimalnych zaleznosci funkcyjnych " << endl;
	for (unsigned int z = 0; z < tmp->size(); z++)
		if (holds(tmp->at(z)->groups))
		{
			Rk.push_back(tmp->at(z));
			//                extBitsetPRINTTOFILE(tmp.at(z)->Cand_id, output);
			//                output<<"\n";
			tmp->erase(tmp->begin() + z);
			z--;
		}
}

void BasicAlg::printStatistics(ofstream& output)
{
	//        output << "Liczba wszystkich wytworzonych podzialow "<<No_divisions<<endl;
	//        output << "Liczba wytworzonych podzialow po czyszczeniu kandydatów(pruning) "<<No_divisions2<<endl;
	//        output << "Suma wszystkich grup po czyszczeniu kandydatów(pruning) "<<sum_groups<<endl;
	//        double avg_groups=double(sum_groups)/No_divisions2;
	//        output << "Srednia liczba grup po czyszczeniu kandydatów(pruning) "<<avg_groups<<endl;
	//        output << "Suma wszystkich rekordow po czyszczeniu kandydatów(pruning) "<<sum_records<<endl;
	//        double avg_records=double(sum_records)/No_divisions2;
	//        output << "Srednia liczba rekordow po czyszczeniu kandydatów(pruning) "<<avg_records<<endl;
	output << No_divisions << '\t';
	output << sum_groups_before << '\t';
	double avg_groups_before = double(sum_groups_before) / No_divisions2;
	output << avg_groups_before << '\t';
	output << sum_records_before << '\t';
	double avg_records_before = double(sum_records_before) / No_divisions2;
	output << avg_records_before << '\t';
	output << No_divisions2 << '\t';
	output << sum_groups << '\t';
	double avg_groups = double(sum_groups) / No_divisions2;
	output << avg_groups << '\t';
	output << sum_records << '\t';
	double avg_records = double(sum_records) / No_divisions2;
	output << avg_records << '\n';
}

void BasicAlg::candidatesInitialProcessing(ofstream& output,
		vector<Candidate*>* tmp,
		vector<Candidate*>& Rk)
{
	output << tmp->size() << '\t';
	search4FunctionalDependencies(&*tmp, Rk);
	initializeStatistics();
	vector<Candidate*> tmp2;
	funGen(*tmp, 1, tmp2);
	printStatistics(output);
	*tmp = tmp2;
}

void BasicAlg::candidatesFurtherProcessing(vector<Candidate*> tmp,
		ofstream& output,
		vector<Candidate*>& Rk)
{
	for (int k = 2; tmp.size() > 0; k++)
	{
		output << tmp.size() << '\t';
		//        output << "Identyfikatory minimalnych zaleznosci funkcyjnych " << endl;
		search4FunctionalDependencies(&tmp, Rk);
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
		//tmp = std::move(tmp2);
		tmp = move(tmp2);
	}
}

void BasicAlg::processData(vector<Candidate *> &C1,
		int id_row,
		vector<Candidate *> &Rk,
		int d_column,
		string output_file)
{
	clock_t start, end;
	start = clock();
	T.resize(id_row);
	delta.resize(id_row);
	prepareCandidate(C1);
	deltaPartitionArrayRepresentation(C1.at(d_column - 1)->groups);
	removeDecisionColumn(d_column, C1);
	vector<Candidate *> tmp;
	tmp = C1;
	ofstream output(output_file.c_str());
	printHeaders(output);

	candidatesInitialProcessing(output, &tmp, Rk);
	candidatesFurtherProcessing(tmp, output, Rk);
	output.close();

}
