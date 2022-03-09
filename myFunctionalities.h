#pragma once
#include <iostream>
#include "tools.h"
#include "connect.h"
#include "globals.h"
#include "Millionaire/millionaire.h"
#include "Millionaire/bit-triple-generator.h"
using namespace std;
using namespace sci;

extern void start_time();
extern void start_communication();
extern void end_time(string str);
extern void end_communication(string str);

void millInit();

void getAShares(RSSVectorMyType &a, vector<myType> &data, int32_t bw);
void getAShares3in3(vector<myType> &a, vector<myType> &data, int32_t bw);
void getAShares3in3(vector<myType> &a, vector<smallType> &data, int32_t bw);
void getBShares(RSSVectorMyType &a, vector<myType> &data, int32_t bw);
void getBShares(RSSVectorSmallType &a, vector<smallType> &data, int32_t bw);
void getBShares3in3(vector<myType> &a, vector<myType> &data, int32_t bw);
void getBShares3in3(vector<smallType> &a, vector<smallType> &data, int32_t bw);

void getAReconstructOne(RSSMyType &data, myType &result,  string str, bool print, int32_t bw);
void getAReconstruct(RSSVectorMyType &data, vector<myType> &result, size_t size, string str, bool print, int32_t bw);
void getBReconstruct(RSSVectorMyType &data, vector<myType> &result, size_t size, string str, bool print, int32_t bw);
void getBReconstruct(RSSVectorSmallType &data, vector<smallType> &result, size_t size, string str, bool print, int32_t bw);
void getAReconstruct3in3(vector<myType> &data, vector<myType> &result, size_t size, string str, int32_t bw, bool print);
void getBReconstruct3in3(vector<myType> &data, vector<myType> &result, size_t size, string str, int32_t bw, bool print);
void getBReconstruct3in3(vector<smallType> &data, vector<myType> &result, size_t size, string str, int32_t bw, bool print);

void getTruncate(RSSVectorMyType &data, int32_t bw, int32_t power);

void wrap3_uv(RSSVectorMyType &a, vector<smallType> &u, vector<smallType> &v, size_t size, int32_t bw);
void multiplexer(vector<uint8_t> select, vector<uint64_t> x, vector<uint64_t> &y, int32_t size, int32_t bw_x, int32_t bw_y);
void vectorMult_nu(RSSVectorMyType &a, RSSVectorMyType &b, RSSVectorMyType &c, int32_t bw_A, int32_t bw_B, int32_t &bw_C, size_t size);
void vectorMult_nu_cleartext(vector<uint64_t> &a, vector<uint64_t> &b, vector<uint64_t> &c, int32_t bw_A, int32_t bw_B, int32_t &bw_C, size_t size);

void B2A(RSSVectorSmallType &a, RSSVectorMyType &res, int32_t bw_B, size_t size);
void B2A_vector(vector<smallType> &a, vector<myType> &res, int32_t bw_A, int32_t bw_B, size_t size);
void z_extend(RSSVectorMyType &x, RSSVectorMyType &x_extend, int32_t bw_x, int32_t bw_y, size_t size);
void s_extend();

void dotProduct(RSSVectorMyType &a, RSSVectorMyType &b, RSSMyType &res, int32_t bw_A, int32_t bw_B, int32_t &bw_C, size_t size);
void matMultRSS_local(RSSVectorMyType &a, RSSVectorMyType &b, vector<myType> &c, size_t rows, size_t common_dim, size_t columns, int32_t bw_A, int32_t bw_B, int32_t bw_C);
void copyRSSVectorMyType(RSSVectorMyType &mat, RSSVectorMyType &mat_copy, size_t size);
void matrix_transpose(RSSVectorMyType &mat, RSSVectorMyType &mat_transpose, size_t m, size_t n);
void getSliceRSSVectorMyType(RSSVectorMyType &a, RSSVectorMyType &b, size_t left, size_t right);
void matMult(RSSVectorMyType &a, RSSVectorMyType &b, RSSVectorMyType &c, size_t rows, size_t common_dim, size_t columns, int32_t bw_A, int32_t bw_B, int32_t &bw_C);


