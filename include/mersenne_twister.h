#pragma once

#ifndef PROJECT_INCLUDE_MERSENNE_TWISTER_H_
#define PROJECT_INCLUDE_MERSENNE_TWISTER_H_

class CRandomMersenne {
	//constants for MT19937:
#define MERS_N	 624
#define MERS_M	 397
#define MERS_R   31
#define MERS_U	 11
#define MERS_S	 7
#define MERS_T	 15
#define MERS_L	 18
#define MERS_A	 0x9908B0DF
#define MERS_B	 0x9D2C5680
#define MERS_C	 0xEFC60000

public:
	CRandomMersenne(unsigned long seed) {							// constructor
		RandomInit(seed);
	}
	void RandomInit(unsigned long seed);							// re-seed
	int IRandom(int min, int max);									// output random integer
	// void RandomInitByArray(unsigned long seeds[], int length); // seed by more than 32 bits
	double Random();												// output random float
	unsigned long BRandom();										// output random bits
private:
	unsigned long mt[MERS_N];										// state vector (array to store the state of the generator)
	int mti;														// index into mt
	enum TArch { LITTLEENDIAN, BIGENDIAN, NONIEEE };
	TArch Architecture;												// conversion to float depends on computer architecture
};

void CRandomMersenne::RandomInit(unsigned long seed) {
	// re-seed generator
	mt[0] = seed;
	for (mti = 1; mti < MERS_N; mti++) {
		mt[mti] = (1812433253UL * (mt[mti - 1] ^ (mt[mti - 1] >> 30)) + mti);
	}
	// detect computer architecture
	union { double f; unsigned long i[2]; } convert;
	convert.f = 1.0;
	// Note: Old versions of the Gnu g++ compiler may make an error here,
	// compile with the option	-fenum-int-equiv	to fix the problem
	if (convert.i[1] == 0x3FF00000)
		Architecture = LITTLEENDIAN;
	else if (convert.i[0] == 0x3FF00000)
		Architecture = BIGENDIAN;
	else
		Architecture = NONIEEE;
}

//
//void CRandomMersenne::RandomInitByArray(unsigned long seeds[], int length) {
//	// seed by more than 32 bits
//	int i, j, k;
//	RandomInit(19650218UL);
//	if (length <= 0) return;
//	i = 1;	j = 0;
//	k = (MERS_N > length ? MERS_N : length);
//	for (; k; k--) {
//		mt[i] = (mt[i] ^ ((mt[i - 1] ^ (mt[i - 1] >> 30)) * 1664525UL)) + seeds[j] + j;
//		i++; j++;
//		if (i >= MERS_N) { mt[0] = mt[MERS_N - 1]; i = 1; }
//		if (j >= length) j = 0;
//	}
//	for (k = MERS_N - 1; k; k--) {
//		mt[i] = (mt[i] ^ ((mt[i - 1] ^ (mt[i - 1] >> 30)) * 1566083941UL)) - i;
//		if (++i >= MERS_N) { mt[0] = mt[MERS_N - 1]; i = 1; }
//	}
//	mt[0] = 0x80000000UL; // MSB is 1; assuring non-zero initial array
//}

unsigned long CRandomMersenne::BRandom() {
	// generate 32 random bits
	unsigned long y;

	if (mti >= MERS_N) {
		// generate MERS_N words at one time
		const unsigned long LOWER_MASK = (1LU << MERS_R) - 1; // lower MERS_R bits
		const unsigned long UPPER_MASK = -1L << MERS_R;		// upper (32 - MERS_R) bits
		static const unsigned long mag01[2] = { 0, MERS_A };

		int kk;
		for (kk = 0; kk < MERS_N - MERS_M; kk++) {
			y = (mt[kk] & UPPER_MASK) | (mt[kk + 1] & LOWER_MASK);
			mt[kk] = mt[kk + MERS_M] ^ (y >> 1) ^ mag01[y & 1];
		}

		for (; kk < MERS_N - 1; kk++) {
			y = (mt[kk] & UPPER_MASK) | (mt[kk + 1] & LOWER_MASK);
			mt[kk] = mt[kk + (MERS_M - MERS_N)] ^ (y >> 1) ^ mag01[y & 1];
		}

		y = (mt[MERS_N - 1] & UPPER_MASK) | (mt[0] & LOWER_MASK);
		mt[MERS_N - 1] = mt[MERS_M - 1] ^ (y >> 1) ^ mag01[y & 1];
		mti = 0;
	}

	y = mt[mti++];

	// Tempering (May be omitted):
	y ^= y >> MERS_U;
	y ^= (y << MERS_S) & MERS_B;
	y ^= (y << MERS_T) & MERS_C;
	y ^= y >> MERS_L;
	return y;
}

double CRandomMersenne::Random() {
	// output random float number in the interval 0 <= x < 1
	union { double f; unsigned long i[2]; } convert;
	unsigned long r = BRandom(); // get 32 random bits
	switch (Architecture) {
	case LITTLEENDIAN:
		convert.i[0] = r << 20;
		convert.i[1] = (r >> 12) | 0x3FF00000;
		return convert.f - 1.0;
	case BIGENDIAN:
		convert.i[1] = r << 20;
		convert.i[0] = (r >> 12) | 0x3FF00000;
		return convert.f - 1.0;
	case NONIEEE:
	default:
		;
	}
	// This somewhat slower method works for all architectures, including
	// non-IEEE floating point representation:
	return (double)r * (1. / ((double)(unsigned long)(-1L) + 1.));
}

int CRandomMersenne::IRandom(int min, int max) {
	// output random integer in the interval min <= x <= max
	static int r;
	r = int((max - min + 1) * Random()) + min; // multiply interval with random and truncate
	if (r > max) r = max;
	if (max < min) return 0x80000000;
	return r;
}

#endif  // PROJECT_INCLUDE_MERSENNE_TWISTER_H_
