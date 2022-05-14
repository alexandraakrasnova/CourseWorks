#include <iostream>
#include <stdio.h>
#include <vector>
#include <numeric>
#include <fstream>
#include <iterator>

#include "funcs.h"

int main()
{
    std::vector<int> rand_seq_1;
    random_seq(rand_seq_1);
    std::vector<int> rand_seq_2;
    random_seq(rand_seq_2);

    int sum_rand = 0;
    std::vector<int> sum_mn;

    std::vector<int> rand_seq;
    for (int n = 0; n < 100000; n++) {
        random_seq(rand_seq);
        sum_mn.push_back(calc_triads(rand_seq));
    }
    cout << accumulate(sum_mn.begin(), sum_mn.end(), 0)/ sum_mn.size() << endl;
    cout << endl;

    std::ofstream outFileRand("ksi_values_rand.txt");
    for (const unsigned int& elm_rand : sum_mn) outFileRand << elm_rand << " ";

    cout << calc_triads(rand_seq_1) << endl;
    cout << calc_triads(rand_seq_2) << endl;
    cout << endl;

    //cout << "TUPLES" << endl;

    std::vector<int> tuples(1);
    generate_tuples(tuples);


    //cout << tuples.size()/len << endl;
    int ksi_count = 0;
    vector<int> temp = tuples;
    vector<int> ksi;
    //show_vector(temp);

    ksi.reserve(tuples.size() / len);

    vector <int>::iterator it1 = temp.begin();
    //vector <int>::iterator it2 = temp.begin();
    //advance(it2, len - 1);
    //cout << "IT_1 : " << *it1 << " IT_2 : " << *it2 << endl;
    ksi_count = calc_triads(it1);
    //cout << ksi_count << endl;
    //advance(it1, len);
    ksi.push_back(ksi_count);


    for (int q = 0; q < (tuples.size() / len - 1); q++) {
        advance(it1, len);
        //it1 += len;
        //advance(it2, len);
        //cout << "IT_1_ : " << *it1 << " IT_2_ : " << *it2 << endl;
        //cout << "**" << *(it1 + 1) << endl;
        ksi_count = calc_triads(it1);
        //cout << ksi_count << endl;
        //advance(it1, len);
        ksi.push_back(ksi_count);
    }
    int sum_of_elems = 0;
    sum_of_elems = accumulate(ksi.begin(), ksi.end(), 0);
    cout << "SUM: " << sum_of_elems << endl;

    std::ofstream outFile("ksi_values.txt");
    for (const unsigned int& elm : ksi) outFile << elm << " ";


    return 0;
}
