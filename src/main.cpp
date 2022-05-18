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

    // int sum_rand = 0;
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

    std::vector<int> tuple(1);
    generate_tuples(tuple);

    int ksi_count = 0;
    vector<int> temp = tuple;
    vector<int> ksi;
    //show_vector(temp);

    ksi.reserve(tuple.size() / len);

    vector <int>::iterator it1 = temp.begin();
    ksi_count = calc_triads(it1);
    ksi.push_back(ksi_count);


    for (unsigned int q = 0; q < (tuple.size() / len - 1); q++) {
        advance(it1, len);
        ksi_count = calc_triads(it1);
        ksi.push_back(ksi_count);
    }
    int sum_of_elems = 0;
    sum_of_elems = accumulate(ksi.begin(), ksi.end(), 0);
    cout << "SUM: " << sum_of_elems << endl;

    std::ofstream outFile("ksi_values.txt");
    for (const unsigned int& elm : ksi) outFile << elm << " ";


    return 0;
}
