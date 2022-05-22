#include <iostream>
#include <vector>
#include <functional>
#include <random>
#include "funcs.h"

using namespace std;

void show_vector(const vector<int>& a)
{
    for (auto it = a.begin(); it != a.end(); ++it)
        cout << *it << ' ';
    cout << endl;
}

void show_tuples(const vector<triad>& v)
{
    for (unsigned int i = 0; i < v.size(); i++)
        cout << v[i].a << ' ' << v[i].b << ' ' << v[i].c << endl;
}

void random_seq(vector<int>& rand_seq) {
    rand_seq.resize(0);
    rand_seq.reserve(NRAND);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, VALRAND-1);
    for (int i = 0; i < NRAND; i++) {
        rand_seq.push_back(dis(gen));
    }
    //show_vector(rand_seq);
    return;
}

int calc_triads(const vector<int>& rand_seq, int length) {
    int sum = 0;
    for (int j = 0; j < length - 2; j++) {
        if ((rand_seq[j] < rand_seq[j + 1]) && (rand_seq[j + 2] < rand_seq[j + 1])) {
            ++sum;
        }
    }
    //cout << sum << endl;
    //for (int j = 0; j < N - 1; j++) {
    //    if ((rand_seq[j] < rand_seq[j + 1]) && (rand_seq[j + 2] < rand_seq[j + 1])) {
    //        triad tuple(rand_seq[j], rand_seq[j + 1], rand_seq[j + 2]);
    //        v.push_back(tuple);
    //    }
    //}
    
    return sum;
}

int calc_triads(vector <int>::iterator& it1, int length) {
    int sum = 0;
    for (int i = 0; i < length - 2; i++) {
        if ((*(it1 + i) < *(it1 + i + 1)) && (*(it1 + i + 1) > *(it1 + i + 2))) {
            ++sum;
        }
    }
    return sum;
}

//void generate_tuples(vector<int>& tuples) {
//    int k;
//    tuples.reserve(LEN);
//    while (1) {
//            for (int i = 0; i < LEN; i++) {
//                // cout << tuples[i] << ' ';
//                tuples.push_back(tuples[i]);
//            }
//            for (k = LEN - 1; k >= 0 && tuples[k] == ELEM - 1; k--) {
//                tuples[k] = 0;
//            }
//            if (k == -1) {
//                break;
//            }
//            else {
//                ++tuples[k];
//            }
//                  
//    }
//    tuples.erase(tuples.begin());
//    //show_vector(tuples);
//    return;
//}


void gen(std::vector<int>& tuples) {
    tuples.reserve(LEN);
    std::vector<int> temp(LEN);
    std::function<void(int pos)> Rec = [&](auto pos) {
        if (pos >= LEN) {
            for (auto el : temp) {
                tuples.push_back(el);
                //std::cout << el << " ";
            }
            //std::cout << std::endl;
            return;
        }
        for (size_t i = 0; i < ELEM; ++i) {
            temp[pos] = i;
            Rec(pos + 1);
        }
    };
    Rec(0);
    // show_vector(tuples);
    return;
}
