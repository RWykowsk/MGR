
#include <algorithm>
#include "fileUtils.h"

void create_modified_file(ifstream *input_file, int decision_column, int decision_type, string output_file_name,
                          int number_of_transactions) {

/*    ofstream outfile("output.txt");
    vector<vector<dictionary> > dict;
    vector<vector<int>> data;
    vector<int> row;
    string str;
    int id_row = 0;//ktory wiersz(transakcja) w pliku
    if (getline(*input_file, str)) {
        istringstream line(str);// cały wiersz pliku
        istringstream tmp(str);//to samo
        //policz ile kolumn potem przeczytaj
        int column_number_total = 0;
        while (line) {
            string s;
            if (!getline(line, s, ',')) break;//wez do przecinka z ss
            column_number_total++;
        }
        cout << column_number_total << endl;
        dict.resize(column_number_total);

        while (tmp) {
            string s;
            data.push_back(row);
            if (!getline(tmp, s, ',')) break;
            dict.at(0).push_back(dictionary(s, 0));
            data.at(0).push_back(id_row);
        }
    }


    int transaction_counter = 2;
    while (*input_file && transaction_counter <= number_of_transactions) {
        id_row++;
        string s;
        if (!getline(*input_file, s)) break;
        istringstream ss(s);
        int column_number = 0;
        data.push_back(row);
        while (ss) {
            string s;
            if (!getline(ss, s, ',')) break;
            bool is_in_dict = false;
            for (unsigned int z = 0; z < dict.at(column_number).size(); z++) {
                if (s == dict.at(column_number).at(
                        z).word) {//jezeli jest juz w slowniku, to dodaj do grupy o id ze slownika element(id_wiersza)
                    is_in_dict = true;
                    data.back().push_back(dict.at(column_number).at(z).id);
                    //outfile << dict.at(column_number).at(z).id << " ";
                    break;
                }

            }
            if (!is_in_dict) {//dodaj do slownika, dodaj nowa grupe i jej element(id wiersza)
                int dict_id = dict.at(column_number).size();
                dict.at(column_number).push_back(dictionary(s, dict_id));
                data.back().push_back(dict.at(column_number).at(dict_id).id);
                //outfile << dict.at(column_number).at(dict_id).id << " ";
            }


            column_number++;
        }
        transaction_counter++;
    }

    //komparator - porównuje dwa wektory
    auto cmp = [](vector<int> const &a, vector<int> const &b) {
        for (int c = 0; c < a.size(); c++) {
            if (a.at(c) > b.at(c))
                return false;
            else if (a.at(c) < b.at(c))
                return true;
        }
        return true;
    };


    sort(data.begin(), data.end(), cmp);


    for (unsigned int i = 0; i < data.size(); i++) {
        for (unsigned int j = 0; j < data.at(i).size(); j++) {
            cout << data.at(i).at(j) << " ";
        }
        cout << endl;
    }



    //komparator - porównuje dwa wektory
    auto cmp_decision = [](vector<int> const &a, vector<int> const &b) {
        for (int c = 0; c < a.size(); c++) {
            if (c != decision_column) {
                if (a.at(c) != b.at(c))
                    return false;
            }
        }
        return true;
    };

    vector<pair<int, int>> generalizeDec;
    for (int i = 0; i < data.size(); i++) {
        if (i + 1 < data.size()) {
            if (!cmp_decision(data.at(i), data.at(i + 1))) {
                switch (decision_type) {
                    case 2:
                        data.at(i).at(decision_column) = dict.at(decision_column).back().id + 1;
                        data.at(i + 1).at(decision_column) = dict.at(decision_column).back().id + 1;
                        break;
                    case 3:
                        if (generalizeDec.size() == 0)
                            data.at(i).at(decision_column) = pow(2, dict.at(decision_column).back().id);
                        else {
                            int tab[dict.at(decision_column).back().id];
                            for (int c = 0; c < generalizeDec.size(); c++) {
                                if (tab[c] == 0)
                                    tab[c] = 1;
                            }
                            int sum = 0;
                            for (int c = 0; c < generalizeDec.size(); c++) {
                                if (tab[c] == 1)
                                    sum += tab[i] * pow(2, c);
                            }
                            for (int c = 0; c < generalizeDec.size(); c++) {
                                data.at(generalizeDec.at(c).first).at(decision_column) = sum;
                            }
                        }
                        break;
                    case 4:
                        //TODO
                        break;
                    default:
                        break;
                }
            }
            else if (decision_type == 3) {
                generalizeDec.push_back(make_pair(i, data.at(i).at(decision_column)));
            }
        }
    }
    outfile.close();*/


    (*input_file).close();

}

int read_from_modified_file(string filename, vector<Candidate *> &C1, int number_of_transactions) {
    ifstream infile(filename.c_str());
    ofstream outfile("output.txt");
    vector<vector<dictionary> > dict;
    string str;
    int id_row = 0;//ktory wiersz(transakcja) w pliku
    if (getline(infile, str)) {
        istringstream row(str);// cały wiersz pliku
        istringstream tmp(str);//to samo
        //policz ile kolumn potem przeczytaj
        int column_number_total = 0;
        while (row) {
            string s;
            if (!getline(row, s, ',')) break;//wez do przecinka z ss
            column_number_total++;
        }
        //cout << column_number_total << endl;
        dict.resize(column_number_total);

        for (int z = 0; z < column_number_total; z++) {
            C1.push_back(new Candidate);
            extBitsetINSERT(C1.at(z)->Cand_id ,z+1);
            //C1.at(z)->Cand_id.push_back(z);
        }
        int column_number = 0;
        while (tmp) {
            string s;
            if (!getline(tmp, s, ',')) break;
            dict.at(column_number).push_back(dictionary(s, 0));
            C1.at(column_number)->groups.push_back(new vector<int>());
            //int *id =new int(id_row);
            //id=id_row;
            C1.at(column_number)->groups.at(0)->push_back(id_row);
            outfile << "0 ";
            //int *a=C1.at(column_number)->groups.at(0)->at(0);
            //cout<<*a<<"\t"<<a<<endl;
            column_number++;
        }
        outfile << "\n";
    }


    int transaction_counter = 2;
    while (infile && transaction_counter <= number_of_transactions) {
        id_row++;
        string s;
        if (!getline(infile, s)) break;
        istringstream ss(s);
        int column_number = 0;
        while (ss) {
            string s;
            if (!getline(ss, s, ',')) break;
            bool is_in_dict = false;
            for (unsigned int z = 0; z < dict.at(column_number).size(); z++) {
                if (s == dict.at(column_number).at(
                        z).word) {//jezeli jest juz w slowniku, to dodaj do grupy o id ze slownika element(id_wiersza)
                    is_in_dict = true;
                    C1.at(column_number)->groups.at(dict.at(column_number).at(z).id)->push_back(id_row);
                    outfile << dict.at(column_number).at(z).id << " ";
                    break;
                }

            }
            if (!is_in_dict) {//dodaj do slownika, dodaj nowa grupe i jej element(id wiersza)
                int dict_id = dict.at(column_number).size();
                dict.at(column_number).push_back(dictionary(s, dict_id));
                C1.at(column_number)->groups.push_back(new vector<int>());
                C1.at(column_number)->groups.at(dict.at(column_number).at(dict_id).id)->push_back(id_row);
                outfile << dict.at(column_number).at(dict_id).id << " ";
            }


            column_number++;
        }
        outfile << "\n";
        transaction_counter++;


    }
    outfile.close();
    infile.close();

    return id_row;//number of transactions
}

void save_to_outputfile(vector<Candidate *> Rk, int a_type, int number_of_transactions, string input_file,
                        double diffFilePrepare, double diffAlg, double diffAll) {
    string filename = "results";
    string a_name;
    ostringstream temp_records;
    temp_records << number_of_transactions;
    string records = temp_records.str();
    for (unsigned int i = 0; i < input_file.size(); i++) {
        if (input_file[i] == '.') {
            filename.append("_");
            filename.append(input_file.begin(), input_file.begin() + i);
            filename.append("_");
        }
    }
    filename.append(records);
    filename.append("_");
    switch (a_type) {

        case 4:
            a_name = "SuperFunBA";
            break;
        case 3:
            a_name = "SuperFunAB";
            break;

        case 2:
            a_name = "Stripped";
            break;
        case 1:
            a_name = "Basic";
            break;
        default:
            a_name = "Error";;
            break;
    }
    filename.append(a_name);
    filename.append(".txt");
    ofstream output(filename.c_str());
    output << "Liczba minimalnych zaleznosci funkcyjnych " << Rk.size() << endl;
    output << "Identyfikatory minimalnych zaleznosci funkcyjnych " << endl;
    for (unsigned int i = 0; i < Rk.size(); i++) {
//        for (unsigned int j = 0; j < Rk.at(i)->Cand_id.size(); j++) {
//            output << Rk.at(i)->Cand_id.at(j) << " ";
                //output<<Rk.at(i)->Cand_id;
                extBitsetPRINTTOFILE(Rk.at(i)->Cand_id, output);
//        }
        output << "\n";
    }
    output << endl;
    output << "Czas przetwarzania pliku: " << diffFilePrepare << endl;
    output << "Czas wykonywania algorytmu: " << diffAlg << endl;
    output << "Czas wykonywania całego programu: " << diffAll << endl;
    output.close();
}



string create_file_name(int a_type, int number_of_transactions, string input_file)
{
    string filename = "results";
    string a_name;
    ostringstream temp_records;
    temp_records << number_of_transactions;
    string records = temp_records.str();
    for (unsigned int i = 0; i < input_file.size(); i++) {
        if (input_file[i] == '.') {
            filename.append("_");
            filename.append(input_file.begin(), input_file.begin() + i);
            filename.append("_");
        }
    }
    filename.append(records);
    filename.append("_");
    switch (a_type) {

        case 4:
            a_name = "SuperFunBA";
            break;
        case 3:
            a_name = "SuperFunAB";
            break;

        case 2:
            a_name = "Stripped";
            break;
        case 1:
            a_name = "Basic";
            break;
        default:
            a_name = "Error";;
            break;
    }
    filename.append(a_name);
    filename.append("_statistics.txt");
    return filename;
}
