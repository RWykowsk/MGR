

#ifndef MED_PROJEKT_FILEUTILS_H
#define MED_PROJEKT_FILEUTILS_H

#include <vector>
#include <string>
#include "functions.h"

void create_modified_file(ifstream *input_file, int decision_column, int decision_type, string output_file_name, int number_of_transactions);

int read_from_modified_file(string filename, vector<Candidate *> &C1, int number_of_transactions);

void save_to_outputfile(vector<Candidate *> Rk, int a_type, int number_of_transactions,
                        string input_file, double diffFilePrepare, double diffAlg, double diffAll);
string create_file_name(int a_type, int number_of_transactions,
                      string input_file);


#endif //MED_PROJEKT_FILEUTILS_H
