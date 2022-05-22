#include <fstream>
#include <functional>
#include <iostream>
#include <iterator>
#include <numeric>
#include <stdio.h>
#include <vector>

#include "funcs.h"


int main()
{
    /************ПО ТОЧНОМУ РАСПРЕДЕЛЕНИЮ************/

    std::vector<int> tuples;
    gen(tuples);

    vector<int> temp = tuples;
    vector<int> ksi;

    ksi.reserve(tuples.size() / LEN);

    vector <int>::iterator it1 = temp.begin();
    int ksi_count = calc_triads(it1, LEN);
    ksi.push_back(ksi_count);


    for (unsigned int q = 0; q < (tuples.size() / LEN - 1); q++) {
        advance(it1, LEN);
        ksi_count = calc_triads(it1, LEN);
        ksi.push_back(ksi_count);
    }

    int sum_of_elems = 0;
    sum_of_elems = accumulate(ksi.begin(), ksi.end(), 0);
    cout << "SUM: " << sum_of_elems << endl;

    std::ofstream outFile("ksi_values.txt");
    for (const unsigned int& elm : ksi) outFile << elm << " ";

    /************МЕТОД МОНТЕ-КАРЛО************/

    // int sum_rand = 0;
    std::vector<int> sum_mn;

    std::vector<int> rand_seq;
    for (int n = 0; n < 100000; n++) {
        random_seq(rand_seq);
        sum_mn.push_back(calc_triads(rand_seq, NRAND));
    }
    cout << accumulate(sum_mn.begin(), sum_mn.end(), 0)/ sum_mn.size() << endl;
    cout << endl;

    std::ofstream outFileRand("ksi_values_rand.txt");
    for (const unsigned int& elm_rand : sum_mn) outFileRand << elm_rand << " ";

    return 0;
}
