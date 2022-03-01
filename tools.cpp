
#include "tools.h"
#include <stdint.h>
#include <mutex> 
#include <bitset>
// #include "EigenMatMul.h"

using namespace std;
// using namespace Eigen;


// smallType additionModPrime[PRIME_NUMBER][PRIME_NUMBER];
// smallType subtractModPrime[PRIME_NUMBER][PRIME_NUMBER];
// smallType multiplicationModPrime[PRIME_NUMBER][PRIME_NUMBER];

void emptyToolsInit(){
	cout<<"the void tools initialize function."<<endl;
}



void log_print(string str)
{
#if (LOG_DEBUG)
	cout << "----------------------------" << endl;
	cout << "Started " << str << endl;
	cout << "----------------------------" << endl;	
#endif
}


void error(string str)
{
	cout << "Error: " << str << endl;
	exit(-1);
}

string which_network(string network)
{
	if (network.find("SecureML") != std::string::npos)
		return "SecureML";
	else if (network.find("MiniONN") != std::string::npos)
		return "MiniONN";
	else if (network.find("Sarda") != std::string::npos)
		return "Sarda";
	else if (network.find("LeNet") != std::string::npos)
		return "LeNet";
	else if (network.find("AlexNet") != std::string::npos)
		return "AlexNet";
	else if (network.find("VGG16") != std::string::npos)
		return "VGG16";
	else 
		error("network not recognised in which_network");

}

void print_myType(myType var, string message, string type)
{
	if (BIT_SIZE == 64)
	{
		if (type == "BITS")
			cout << message << ": " << bitset<BIT_SIZE>(var) << endl;
		else if (type == "FLOAT")
			cout << message << ": " << (static_cast<int64_t>(var))/(float)(1 << FLOAT_PRECISION) << endl;
		else if (type == "SIGNED")
			cout << message << ": " << static_cast<int64_t>(var) << endl;
		else if (type == "UNSIGNED")
			cout << message << ": " << var << endl;
	}
	if (BIT_SIZE == 32)
	{
		if (type == "BITS")
			cout << message << ": " << bitset<BIT_SIZE>(var) << endl;
		else if (type == "FLOAT")
			cout << message << ": " << (static_cast<int32_t>(var))/(float)(1 << FLOAT_PRECISION) << endl;
		else if (type == "SIGNED")
			cout << message << ": " << static_cast<int32_t>(var) << endl;
		else if (type == "UNSIGNED")
			cout << message << ": " << var << endl;
	}
}

void print_linear(myType var, string type)
{
	if (BIT_SIZE == 64)
	{
		if (type == "BITS")
			cout << bitset<BIT_SIZE>(var) << " ";
		else if (type == "FLOAT")
			cout << (static_cast<int64_t>(var))/(float)(1 << FLOAT_PRECISION) << " ";
		else if (type == "SIGNED")
			cout << static_cast<int64_t>(var) << " ";
		else if (type == "UNSIGNED")
			cout << var << " ";	
	}
	if (BIT_SIZE == 32)
	{
		if (type == "BITS")
			cout << bitset<BIT_SIZE>(var) << " ";
		else if (type == "FLOAT")
			cout << (static_cast<int32_t>(var))/(float)(1 << FLOAT_PRECISION) << " ";
		else if (type == "SIGNED")
			cout << static_cast<int32_t>(var) << " ";
		else if (type == "UNSIGNED")
			cout << var << " ";	
	}
}


//TODO:因为funcReconstruct没定义所以暂时注释掉
// extern void funcReconstruct(const RSSVectorMyType &a, vector<myType> &b, size_t size, string str, bool print);
// void print_vector(RSSVectorMyType &var, string type, string pre_text, int print_nos)
// {
// 	size_t temp_size = var.size();
// 	vector<myType> b(temp_size);
// 	funcReconstruct(var, b, temp_size, "anything", false);
// 	cout << pre_text << endl;
// 	for (int i = 0; i < print_nos; ++i){
// 		print_linear(b[i], type);
// 		// if (i % 10 == 9)
// 			// std::cout << std::endl;
// 	}
// 	cout << endl;
// }

void print_vector(RSSVectorMyType &var, string type, string pre_text, int print_nos){

}

void print_vector(RSSVectorSmallType &var, string type, string pre_text, int print_nos){

}

// extern void funcReconstruct(const RSSVectorSmallType &a, vector<smallType> &b, size_t size, string str, bool print);
// void print_vector(RSSVectorSmallType &var, string type, string pre_text, int print_nos)
// {
// 	size_t temp_size = var.size();
// 	vector<smallType> b(temp_size);
// 	funcReconstruct(var, b, temp_size, "anything", false);
// 	cout << pre_text << endl;
// 	for (int i = 0; i < print_nos; ++i){
// 		cout << b[i] << " ";
// 		// if (i % 10 == 9)
// 			// std::cout << std::endl;
// 	}
// 	cout << endl;
// }
//TODO:因为funcReconstruct没定义所以暂时注释掉


void matrixMultRSS(const RSSVectorMyType &a, const RSSVectorMyType &b, vector<myType> &temp3, 
					size_t rows, size_t common_dim, size_t columns,
				 	size_t transpose_a, size_t transpose_b)
{
#if (!USING_EIGEN)
/********************************* Triple For Loop *********************************/
	RSSVectorMyType triple_a(rows*common_dim), triple_b(common_dim*columns);

    for (size_t i = 0; i < rows; ++i)
    {
        for (size_t j = 0; j < common_dim; ++j)
        {
            if (transpose_a)
                triple_a[i*common_dim + j] = a[j*rows + i];
            else
                triple_a[i*common_dim + j] = a[i*common_dim + j];
        }
    }
 
    for (size_t i = 0; i < common_dim; ++i)
    {
        for (size_t j = 0; j < columns; ++j)
        {
            if (transpose_b)
                triple_b[i*columns + j] = b[j*common_dim + i];  
            else
                triple_b[i*columns + j] = b[i*columns + j]; 
        }
    }
 
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < columns; ++j)
        {
            temp3[i*columns + j] = 0;
            for (int k = 0; k < common_dim; ++k)
            {
                temp3[i*columns + j] += triple_a[i*common_dim + k].first * triple_b[k*columns + j].first +
                                        triple_a[i*common_dim + k].first * triple_b[k*columns + j].second +
                                        triple_a[i*common_dim + k].second * triple_b[k*columns + j].first;
            }
        }
    }
/********************************* Triple For Loop *********************************/	
#endif
#if (USING_EIGEN)
/********************************* WITH EIGEN Mat-Mul *********************************/
	eigenMatrix eigen_a(rows, common_dim), eigen_b(common_dim, columns), eigen_c(rows, columns);

	for (size_t i = 0; i < rows; ++i)
	{
		for (size_t j = 0; j < common_dim; ++j)
		{
			if (transpose_a)
			{
				eigen_a.m_share[0](i, j) = a[j*rows + i].first;
				eigen_a.m_share[1](i, j) = a[j*rows + i].second;
			}
			else
			{
				eigen_a.m_share[0](i, j) = a[i*common_dim + j].first;
				eigen_a.m_share[1](i, j) = a[i*common_dim + j].second;
			}
		}
	}

	for (size_t i = 0; i < common_dim; ++i)
	{
		for (size_t j = 0; j < columns; ++j)
		{
			if (transpose_b)
			{
				eigen_b.m_share[0](i, j) = b[j*common_dim + i].first;	
				eigen_b.m_share[1](i, j) = b[j*common_dim + i].second;	
			}
			else
			{
				eigen_b.m_share[0](i, j) = b[i*columns + j].first;	
				eigen_b.m_share[1](i, j) = b[i*columns + j].second;	
			}
		}
	}

	eigen_c = eigen_a * eigen_b;

	for (size_t i = 0; i < rows; ++i)
		for (size_t j = 0; j < columns; ++j)
				temp3[i*columns + j] = eigen_c.m_share[0](i,j);
/********************************* WITH EIGEN Mat-Mul *********************************/
#endif
}



myType dividePlain(myType a, int b)
{
	assert((b != 0) && "Cannot divide by 0");
	
	if (BIT_SIZE == 32)
		return static_cast<myType>(static_cast<int32_t>(a)/static_cast<int32_t>(b));
	if (BIT_SIZE == 64)
		return static_cast<myType>(static_cast<int64_t>(a)/static_cast<int64_t>(b));
}

void dividePlain(vector<myType> &vec, int divisor)
{
	assert((divisor != 0) && "Cannot divide by 0");
	
	if (BIT_SIZE == 32)
		for (int i = 0; i < vec.size(); ++i)
			vec[i] = (myType)((double)((int32_t)vec[i])/(double)((int32_t)divisor)); 

	if (BIT_SIZE == 64)
		for (int i = 0; i < vec.size(); ++i)
			vec[i] = (myType)((double)((int64_t)vec[i])/(double)((int64_t)divisor)); 
}

size_t nextParty(size_t party)
{
	size_t ret;

	switch(party)
	{
    case PARTY_A : ret = PARTY_B;
             break;       
    case PARTY_B : ret = PARTY_C;
             break;
    case PARTY_C : ret = PARTY_A;
             break;       
	}	
	return ret;	
}

size_t prevParty(size_t party)
{
	size_t ret;

	switch(party)
	{
    case PARTY_A : ret = PARTY_C;
             break;       
    case PARTY_B : ret = PARTY_A;
             break;
    case PARTY_C : ret = PARTY_B;
             break;       
	}	
	return ret;	
}


void wrapAround(const vector<myType> &a, const vector<myType> &b, 
				vector<smallType> &c, size_t size, int32_t bw)
{
	for (size_t i = 0; i < size; ++i)
		c[i] = wrapAround(a[i], b[i], bw);
}

void wrap3(const RSSVectorMyType &a, const vector<myType> &b, 
				vector<smallType> &c, size_t size, int32_t bw)
{
	for (size_t i = 0; i < size; ++i)
		c[i] = wrap3(a[i].first, a[i].second, b[i], bw);
}


void multiplyByScalar(const RSSVectorMyType &a, size_t scalar, RSSVectorMyType &b)
{
	size_t size = a.size();
	for (int i = 0; i < size; ++i)
	{
		b[i].first  = a[i].first * scalar;
		b[i].second  = a[i].second * scalar;
	}
}

//a is just a vector, b has to be a matrix of size rows*columns 
//such that b read columns wise is the same as a.
// void transposeVector(const RSSVectorMyType &a, RSSVectorMyType &b, size_t rows, size_t columns)
// {
// 	size_t totalSize = rows*columns;

// 	for (int i = 0; i < totalSize; ++i)
// 		b[(i % rows)*columns + (i/rows)] = a[i];
// }

//a is zero padded into b (initialized to zeros) with parameters as passed:
//imageWidth, imageHeight, padding, inputFilters, batchSize
void zeroPad(const RSSVectorMyType &a, RSSVectorMyType &b, 
			size_t iw, size_t ih, size_t P, size_t Din, size_t B)
{
	size_t size_B 	= (iw+2*P)*(ih+2*P)*Din;
	size_t size_Din = (iw+2*P)*(ih+2*P);
	size_t size_w 	= (iw+2*P);

	for (size_t i = 0; i < B; ++i)
		for (size_t j = 0; j < Din; ++j) 
			for (size_t k = 0; k < ih; ++k)
				for (size_t l = 0; l < iw; ++l)
				{
					b[i*size_B + j*size_Din + (k+P)*size_w + l + P]
						= a[i*Din*iw*ih + j*iw*ih + k*iw + l];
				}
}

// //vec1 is reshaped for a "convolutional multiplication" with the following params:  
// //imageWidth, imageHeight, padding, inputFilters, stride, batchSize
// //Here, imageWidth and imageHeight are those of the zeroPadded output.
// void convToMult(const RSSVectorMyType &vec1, RSSVectorMyType &vec2, 
// 				size_t iw, size_t ih, size_t f, size_t Din, size_t S, size_t B)
// {
// 	size_t loc_input, loc_output;
// 	for (size_t i = 0; i < B; ++i)
// 		for (size_t j = 0; j < (ih+2*P)-f+1; j+=S)
// 			for (size_t k = 0; k < (iw+2*P)-f+1; k+=S)
// 			{
// 				loc_output = (i*ow*oh + j*ow + k);
// 				for (size_t l = 0; l < Din; ++l) 
// 				{
// 					loc_input = i*(iw+2*P)*(ih+2*P)*Din + l*(iw+2*P)*(ih+2*P) + j*(iw+2*P) + k;
// 					for (size_t a = 0; a < f; ++a)			//filter height
// 						for (size_t b = 0; b < f; ++b)		//filter width
// 							vec2[(l*f*f + a*f + b)*ow*oh*B + loc_output] = vec1[loc_input + a*(iw+2*P) + b];
// 				}
// 			}
// }
