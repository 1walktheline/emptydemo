
#ifndef TOOLS_H
#define TOOLS_H
#pragma once

#include <stdio.h> 
#include <iostream>
// #include "Config.h"
// #include "../util/TedKrovetzAesNiWrapperC.h"
#include <wmmintrin.h>
#include <emmintrin.h>
#include <smmintrin.h>
#include <vector>
#include <time.h>
// #include "secCompMultiParty.h"
// #include "main_gf_funcs.h"
#include <string>
#include <openssl/sha.h>
#include <math.h>
#include <sstream>
// #include "AESObject.h"
#include "connect.h"
#include "globals.h"

extern int partyNum;

// extern AESObject* aes_next;
// extern AESObject* aes_indep;

// extern smallType additionModPrime[PRIME_NUMBER][PRIME_NUMBER];
// extern smallType subtractModPrime[PRIME_NUMBER][PRIME_NUMBER];
// extern smallType multiplicationModPrime[PRIME_NUMBER][PRIME_NUMBER];

void emptyToolsInit();


void log_print(string str);
void error(string str);
string which_network(string network);

void print_myType(myType var, string message, string type);
void print_linear(myType var, string type);

void print_vector(RSSVectorMyType &var, string type, string pre_text, int print_nos);
void print_vector(RSSVectorSmallType &var, string type, string pre_text, int print_nos);

void matrixMultRSS(const RSSVectorMyType &a, const RSSVectorMyType &b, vector<myType> &temp3, 
					size_t rows, size_t common_dim, size_t columns,
				 	size_t transpose_a, size_t transpose_b);

myType dividePlain(myType a, int b);
void dividePlain(vector<myType> &vec, int divisor);

size_t nextParty(size_t party);
size_t prevParty(size_t party);


// inline smallType getMSB(myType a)
// {return ((smallType)((a >> (BIT_SIZE - 1)) & 1));}

// inline RSSSmallType addModPrime(RSSSmallType a, RSSSmallType b)
// {
// 	RSSSmallType ret;
// 	ret.first = additionModPrime[a.first][b.first];
// 	ret.second = additionModPrime[a.second][b.second]; 
// 	return ret;
// }

// inline smallType subModPrime(smallType a, smallType b)
// {return subtractModPrime[a][b];}

// inline RSSSmallType subConstModPrime(RSSSmallType a, const smallType r)
// {
// 	RSSSmallType ret = a;
// 	switch(partyNum)
// 	{
// 		case PARTY_A: ret.first = subtractModPrime[a.first][r];
// 					  break;       
// 		case PARTY_C: ret.second = subtractModPrime[a.second][r];
// 					  break;
// 	}		
// 	return ret;
// }

// inline RSSSmallType XORPublicModPrime(RSSSmallType a, bool r)
// {
// 	RSSSmallType ret;
// 	if (r == 0)
// 		ret = a;
// 	else
// 	{
// 		switch(partyNum)
// 		{
// 			case PARTY_A: ret.first = subtractModPrime[1][a.first];
// 						  ret.second = subtractModPrime[0][a.second];
// 						  break;       
// 			case PARTY_B: ret.first = subtractModPrime[0][a.first];
// 						  ret.second = subtractModPrime[0][a.second];
// 						  break;
// 			case PARTY_C: ret.first = subtractModPrime[0][a.first];
// 						  ret.second = subtractModPrime[1][a.second];
// 						  break;
// 		}
// 	}
// 	return ret;
// }

//单个数据本地的2p,3p wrap
inline smallType wrapAround(myType a, myType b, int32_t bw)
{return (a > ((1ULL << bw) - 1 - b)) & 1;}

inline smallType wrap3(myType a, myType b, myType c, int32_t bw)
{
	myType temp = a+b;
	if (wrapAround(a,b,bw))
		return 1 + wrapAround(temp, c, bw);
	else 
		return wrapAround(temp, c, bw);
}

//vector数据的本地2p, 3p wrap
void wrapAround(const vector<myType> &a, const vector<myType> &b, 
				vector<smallType> &c, size_t size, int32_t bw);
void wrap3(const RSSVectorMyType &a, const vector<myType> &b, 
				vector<smallType> &c, size_t size, int32_t bw);

void multiplyByScalar(const RSSVectorMyType &a, size_t scalar, RSSVectorMyType &b);
// void transposeVector(const RSSVectorMyType &a, RSSVectorMyType &b, size_t rows, size_t columns);
void zeroPad(const RSSVectorMyType &a, RSSVectorMyType &b, 
			size_t iw, size_t ih, size_t f, size_t Din, size_t B);
// void convToMult(const RSSVectorMyType &vec1, RSSVectorMyType &vec2, 
// 				size_t iw, size_t ih, size_t f, size_t Din, size_t S, size_t B);






/*********************** TEMPLATE FUNCTIONS ***********************/ 

template <typename T,typename U>                                                   
std::pair<T,U> operator+(const std::pair<T,U> & l,const std::pair<T,U> & r) {   
    return {l.first+r.first,l.second+r.second};
}                                      

template <typename T,typename U>                                                   
std::pair<T,U> operator-(const std::pair<T,U> & l,const std::pair<T,U> & r) {   
    return {l.first-r.first,l.second-r.second};
}

template <typename T, typename U>                                                   
std::pair<T,U> operator^(const std::pair<T,U> & l, const std::pair<T,U> & r) {   
    return {l.first ^ r.first, l.second ^ r.second};
}

template <typename T>                                                   
T operator*(const std::pair<T,T> & l, const std::pair<T,T> & r) {   
    return {l.first * r.first + l.second * r.first + l.first * r.second};
}

template <typename T, typename U>                                                   
std::pair<U, U> operator*(const T a, const std::pair<U,U> & r) {   
    return {a * r.first, a * r.second};
}

template <typename T>                                                   
std::pair<T,T> operator<<(const std::pair<T,T> & l, const int shift) {   
    return {l.first << shift, l.second << shift};
}   

template<typename T>
void addVectors(const vector<T> &a, const vector<T> &b, vector<T> &c, size_t size)
{
	for (size_t i = 0; i < size; ++i)
		c[i] = a[i] + b[i];
}

template<typename T>
void subtractVectors(const vector<T> &a, const vector<T> &b, vector<T> &c, size_t size)
{
	for (size_t i = 0; i < size; ++i)
		c[i] = a[i] - b[i];
}

template<typename T>
void copyVectors(const vector<T> &a, vector<T> &b, size_t size)
{
	for (size_t i = 0; i < size; ++i)
		b[i] = a[i];
}










#include <chrono>
#include <utility>

typedef std::chrono::high_resolution_clock::time_point TimeVar;

#define duration(a) std::chrono::duration_cast<std::chrono::milliseconds>(a).count()
#define timeNow() std::chrono::high_resolution_clock::now()

template<typename F, typename... Args>
double funcTime(F func, Args&&... args){
    TimeVar t1=timeNow();
    func(std::forward<Args>(args)...);
    return duration(timeNow()-t1);
}

#endif

