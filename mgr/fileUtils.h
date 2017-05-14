

#ifndef MED_PROJEKT_FILEUTILS_H
#define MED_PROJEKT_FILEUTILS_H

#include <vector>
#include <string>
#include "algs/BasicAlg.h"

using namespace std;
struct dictionary
{
	string word;
	int id;
	dictionary(string a, int b)
	{
		word = a;
		id = b;
	}
};

void create_modified_file(ifstream *input_file, int decision_column, int decision_type, string output_file_name, int number_of_transactions);

int read_from_modified_file(string filename, vector<Candidate *> &C1, int number_of_transactions);

void save_to_outputfile(vector<Candidate *> Rk, int a_type, int number_of_transactions,
                        string input_file, double diffFilePrepare, double diffAlg, double diffAll,double alfa);
string create_file_name(int a_type, int number_of_transactions,
                      string input_file);


#endif //MED_PROJEKT_FILEUTILS_H
