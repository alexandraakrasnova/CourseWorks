#ifndef PROJECT_INCLUDE_FUNCS_H_
#define PROJECT_INCLUDE_FUNCS_H_

#define NRAND    50
#define VALRAND  3
#define LEN		10
#define ELEM	3

#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <sstream>  // ?????????????
#include <iomanip> // ?????????????

using namespace std;

struct triad
{
	int a, b, c;
	triad(int x, int y, int z) :a(x), b(y), c(z) {}
};

void show_vector(const std::vector<int>& a);
void show_tuples(const std::vector<triad>& v);
// void random_seq(std::vector<int>& rand_seq);
int calc_triads(const std::vector<int>& rand_seq, int length);
int calc_triads(vector <int>::iterator& beg, int length);
void gen(std::vector<int>& tuples);

#endif  // PROJECT_INCLUDE_FUNCS_H_
