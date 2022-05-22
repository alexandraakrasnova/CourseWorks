#include <fstream>
#include <functional>
#include <iostream>
#include <iterator>
#include <numeric>
#include <stdio.h>
#include <vector>

#include "funcs.h"
#include "mersenne_twister.h"

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

    CRandomMersenne r(42);
    for (int n = 0; n < 100000; n++) {
        for (int i = 0; i < NRAND; i++) {
            rand_seq.push_back(r.IRandom(0, VALRAND));
        }
    }

    vector<int> temp_rand = rand_seq;
    vector<int> ksi_rand;
    ksi_rand.reserve(rand_seq.size() / NRAND);

    vector <int>::iterator it_rand = temp_rand.begin();
    int ksi_count_rand = calc_triads(it_rand, NRAND);
    ksi_rand.push_back(ksi_count);


    for (unsigned int q = 0; q < (rand_seq.size() / NRAND - 1); q++) {
        advance(it_rand, NRAND);
        ksi_count_rand = calc_triads(it_rand, NRAND);
        ksi_rand.push_back(ksi_count_rand);
    }

    std::ofstream outFileRand("ksi_values_rand.txt");
    for (const unsigned int& elm_rand : ksi_rand) outFileRand << elm_rand << " ";


    /************ГЕНЕРАТОР ЧИСЕЛ************/
    //int min = 0;
    //int max = 10;

    //CRandomMersenne r(454);
    //cout << r.IRandom(min, max) << endl;

    //std::vector<int> rand_seq_test;
    //for (int y = 0; y < 3; y++) {
    //    for (int i = 0; i < NRAND; i++) {
    //        rand_seq_test.push_back(r.IRandom(0, VALRAND));
    //    }
    //    show_vector(rand_seq_test);
    //    std::cout << "ooo";
    //}
    

    return 0;
}
