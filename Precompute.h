
#ifndef PRECOMPUTE_H
#define PRECOMPUTE_H

#pragma once
#include "globals.h"
#include "connect.h" 
#include <random>
#include <iostream>
extern int partyNum;

void emptyPrecomputeInit();

void getSharedZero(RSSVectorMyType &z, int length);
void getSharedRandomNum(RSSVectorMyType &r, int length);
void getRandomNum(std::vector<myType> &r, int32_t bw);
void getRandomNum(std::vector<uint8_t> &r, int32_t bw);

/* TODO: 上面三个函数对应的smallType类型的重载 */

//改了d的类型
void getDividedShares(RSSVectorMyType &r, RSSVectorMyType &rPrime, size_t d, size_t size);
void getRandomBitShares(RSSVectorSmallType &a, size_t size);
void getSelectorBitShares(RSSVectorSmallType &c, RSSVectorMyType &m_c, size_t size);
void getShareConvertObjects(RSSVectorMyType &r, RSSVectorSmallType &shares_r, RSSVectorSmallType &alpha, size_t size);
void getTriplets(RSSVectorMyType &a, RSSVectorMyType &b, RSSVectorMyType &c, 
				size_t rows, size_t common_dim, size_t columns);
void getTriplets(RSSVectorMyType &a, RSSVectorMyType &b, RSSVectorMyType &c, size_t size);
void getTriplets(RSSVectorSmallType &a, RSSVectorSmallType &b, RSSVectorSmallType &c, size_t size);


#endif