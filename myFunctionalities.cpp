#include "myFunctionalities.h"
#include "Precompute.h"
#include <thread>

using namespace std;
// extern string SECURITY_TYPE;
extern int partyNum;
extern sci::NetIO *io;
extern sci::OTPack<sci::NetIO> *otpack;
extern MillionaireProtocol<sci::NetIO> *mill;

/**
 * 对mill通信进行初始化，Party_A不参与mill->compare通信
 * 本系统的Party_A=0, Party_B =1=sci::ALICE, Party_C =2= sci::BOB
 */
void millInit(){
    if(partyNum != PARTY_A){
        io = new NetIO(partyNum == PARTY_B ? nullptr : "127.0.0.1", 32000);
        otpack = new OTPack<NetIO>(io, partyNum);
        mill = new MillionaireProtocol<sci::NetIO>(partyNum, io, otpack);
        cout<<"mill 实例化完成！"<<endl;
    }else{
        cout<<"Party_A(partyNum=0)跳过io, otpack, mill实例化"<<endl;
    }
}


/**
* 共享数据生成函数。各方得到data的share值,存在变量a里。a都是MyType的pair构成的向量,data是个vector
* TODO:加上识别数据到底由谁来共享,目前默认由A来共享数据
* @param 
* data:要共享的数据
* a: 存储data的2共3形式结果
* @return 
**/
void getAShares(RSSVectorMyType &a, vector<myType> &data, int32_t bw){
    assert(bw <= 64);
	uint64_t mask = (bw == 64 ? -1 : ((1ULL << bw) - 1));
	size_t size = data.size();
    assert((a.size() == data.size()) && "in func getAShares, a.size != data.size");
	vector<myType> tmp(size, 0),rb(size, 0), rc(size, 0);

	if (partyNum == PARTY_A)
	{
		//调用precompute里面生成随机数的部分
		//A生成两个随机数向量rb,rc
		getRandomNum(rb, bw);
		getRandomNum(rc, bw);
		for (int i = 0; i < size; ++i)
		{
			a[i].first = (data[i] - rb[i] - rc[i]) & mask;
			a[i].second = rb[i] & mask;

			tmp[i] = a[i].first & mask;
		}
		//随机数rb，rc发给B, rc和a[i].first发给C
		// sendVector<myType>(rb, PARTY_B, size);
		// sendVector<myType>(rc, PARTY_B, size);
        sendTwoVectors<myType>(rb, rc, PARTY_B, size, size);
        sendTwoVectors<myType>(rc, tmp, PARTY_C, size, size);

		// sendVector<myType>(rc, PARTY_C, size);
		// sendVector<myType>(tmp, PARTY_C, size);
	}
	else if (partyNum == PARTY_B)
	{
		// receiveVector<myType>(rb, PARTY_A, size);
		// receiveVector<myType>(rc, PARTY_A, size);
        receiveTwoVectors<myType>(rb, rc, PARTY_A, size, size);
		for (int i = 0; i < size; ++i)
		{
			a[i].first = rb[i] & mask;
			a[i].second = rc[i] & mask;
		}
	}
	else if (partyNum == PARTY_C)
	{
		// receiveVector<myType>(rc, PARTY_A, size);
		// receiveVector<myType>(tmp, PARTY_A, size);
        receiveTwoVectors<myType>(rc, tmp, PARTY_A, size, size);

		for (int i = 0; i < size; ++i)
		{
			a[i].first = rc[i] & mask;
			a[i].second = tmp[i] & mask;
		}
	}
}

void getAShares3in3(vector<myType> &a, vector<myType> &data, int32_t bw){
    assert(bw <= 64);
	uint64_t mask = (bw == 64 ? -1 : ((1ULL << bw) - 1));
	size_t size = a.size();
	vector<myType> tmp(size, 0),rb(size, 0), rc(size, 0);

	if (partyNum == PARTY_A)
	{
		//调用precompute里面生成随机数的部分
		//A生成两个随机数向量rb,rc
		getRandomNum(rb, bw);
		getRandomNum(rc, bw);
		for (int i = 0; i < size; ++i)
		{
			a[i] = (data[i] - rb[i] - rc[i]) & mask;
		}
        sendVector<myType>(rb, PARTY_B, size);
        sendVector<myType>(rc, PARTY_C, size);
	}
	else if (partyNum == PARTY_B)
	{
		receiveVector<myType>(rb, PARTY_A, size);
		// receiveVector<myType>(rc, PARTY_A, size);
        // receiveTwoVectors<myType>(rb, rc, PARTY_A, size, size);

		for (int i = 0; i < size; ++i)
		{
			a[i] = rb[i] & mask;
		}
	}
	else if (partyNum == PARTY_C)
	{
		receiveVector<myType>(rc, PARTY_A, size);
		// receiveVector<myType>(tmp, PARTY_A, size);
        // receiveTwoVectors<myType>(rc, tmp, PARTY_A, size, size);

		for (int i = 0; i < size; ++i)
		{
			a[i] = rc[i] & mask;
		}
	}
}

void getAShares3in3(vector<myType> &a, vector<smallType> &data, int32_t bw){
    assert(bw <= 64);
	uint64_t mask = (bw == 64 ? -1 : ((1ULL << bw) - 1));
	size_t size = a.size();
	vector<myType> tmp(size, 0),rb(size, 0), rc(size, 0);

	if (partyNum == PARTY_A)
	{
		//调用precompute里面生成随机数的部分
		//A生成两个随机数向量rb,rc
		getRandomNum(rb, bw);
		getRandomNum(rc, bw);
		for (int i = 0; i < size; ++i)
		{
			a[i] = (uint64_t(data[i]) - rb[i] - rc[i]) & mask;
		}
        sendVector<myType>(rb, PARTY_B, size);
        sendVector<myType>(rc, PARTY_C, size);
	}
	else if (partyNum == PARTY_B)
	{
		receiveVector<myType>(rb, PARTY_A, size);
		// receiveVector<myType>(rc, PARTY_A, size);
        // receiveTwoVectors<myType>(rb, rc, PARTY_A, size, size);

		for (int i = 0; i < size; ++i)
		{
			a[i] = rb[i] & mask;
		}
	}
	else if (partyNum == PARTY_C)
	{
		receiveVector<myType>(rc, PARTY_A, size);
		// receiveVector<myType>(tmp, PARTY_A, size);
        // receiveTwoVectors<myType>(rc, tmp, PARTY_A, size, size);

		for (int i = 0; i < size; ++i)
		{
			a[i] = rc[i] & mask;
		}
	}
}


void getBShares(RSSVectorMyType &a, vector<myType> &data, int32_t bw){
    assert(bw <= 64);
	uint64_t mask = (bw == 64 ? -1 : ((1ULL << bw) - 1));
	size_t size = a.size();
	vector<myType> tmp(size, 0),rb(size, 0), rc(size, 0);

	if (partyNum == PARTY_A)
	{
		//调用precompute里面生成随机数的部分
		//A生成两个随机数向量rb,rc
		getRandomNum(rb, bw);
		getRandomNum(rc, bw);
		for (int i = 0; i < size; ++i)
		{
			a[i].first = (data[i] ^ rb[i] ^ rc[i]) & mask;
			a[i].second = rb[i] & mask;

			tmp[i] = a[i].first & mask;
		}
		//随机数rb，rc发给B, rc和a[i].first发给C
		// sendVector<myType>(rb, PARTY_B, size);
		// sendVector<myType>(rc, PARTY_B, size);
		// sendVector<myType>(rc, PARTY_C, size);
		// sendVector<myType>(tmp, PARTY_C, size);
        sendTwoVectors<myType>(rb, rc, PARTY_B, size, size);
        sendTwoVectors<myType>(rc, tmp, PARTY_C, size, size);
	}
	else if (partyNum == PARTY_B)
	{
		// receiveVector<myType>(rb, PARTY_A, size);
		// receiveVector<myType>(rc, PARTY_A, size);
        receiveTwoVectors<myType>(rb, rc, PARTY_A, size, size);

		for (int i = 0; i < size; ++i)
		{
			a[i].first = rb[i] & mask;
			a[i].second = rc[i] & mask;
		}
	}
	else if (partyNum == PARTY_C)
	{
		// receiveVector<myType>(rc, PARTY_A, size);
		// receiveVector<myType>(tmp, PARTY_A, size);
        receiveTwoVectors<myType>(rc, tmp, PARTY_A, size, size);

		for (int i = 0; i < size; ++i)
		{
			a[i].first = rc[i] & mask;
			a[i].second = tmp[i] & mask;
		}
	}
}

void getBShares(RSSVectorSmallType &a, vector<smallType> &data, int32_t bw){
    assert(bw <= 8);
	uint64_t mask = (bw == 8 ? -1 : ((1ULL << bw) - 1));
	size_t size = a.size();
	vector<smallType> tmp(size, 0),rb(size, 0), rc(size, 0);

	if (partyNum == PARTY_A)
	{
		//调用precompute里面生成随机数的部分
		//A生成两个随机数向量rb,rc
		getRandomNum(rb, bw);
		getRandomNum(rc, bw);
		for (int i = 0; i < size; ++i)
		{
			a[i].first = (data[i] ^ rb[i] ^ rc[i]) & mask;
			a[i].second = rb[i] & mask;

			tmp[i] = a[i].first & mask;
		}
		//随机数rb，rc发给B, rc和a[i].first发给C
		// sendVector<myType>(rb, PARTY_B, size);
		// sendVector<myType>(rc, PARTY_B, size);
		// sendVector<myType>(rc, PARTY_C, size);
		// sendVector<myType>(tmp, PARTY_C, size);
        sendTwoVectors<smallType>(rb, rc, PARTY_B, size, size);
        sendTwoVectors<smallType>(rc, tmp, PARTY_C, size, size);
	}
	else if (partyNum == PARTY_B)
	{
		// receiveVector<myType>(rb, PARTY_A, size);
		// receiveVector<myType>(rc, PARTY_A, size);
        receiveTwoVectors<smallType>(rb, rc, PARTY_A, size, size);

		for (int i = 0; i < size; ++i)
		{
			a[i].first = rb[i] & mask;
			a[i].second = rc[i] & mask;
		}
	}
	else if (partyNum == PARTY_C)
	{
		// receiveVector<myType>(rc, PARTY_A, size);
		// receiveVector<myType>(tmp, PARTY_A, size);
        receiveTwoVectors<smallType>(rc, tmp, PARTY_A, size, size);

		for (int i = 0; i < size; ++i)
		{
			a[i].first = rc[i] & mask;
			a[i].second = tmp[i] & mask;
		}
	}
}


void getBShares3in3(vector<myType> &a, vector<myType> &data, int32_t bw){
    assert(bw <= 64);
	uint64_t mask = (bw == 64 ? -1 : ((1ULL << bw) - 1));
	size_t size = a.size();
	vector<myType> tmp(size, 0),rb(size, 0), rc(size, 0);

	if (partyNum == PARTY_A)
	{
		//调用precompute里面生成随机数的部分
		//A生成两个随机数向量rb,rc
		getRandomNum(rb, bw);
		getRandomNum(rc, bw);
		for (int i = 0; i < size; ++i)
		{
			a[i] = (data[i] ^ rb[i] ^ rc[i]) & mask;
		}
        sendVector<myType>(rb, PARTY_B, size);
        sendVector<myType>(rc, PARTY_C, size);
	}
	else if (partyNum == PARTY_B)
	{
		receiveVector<myType>(rb, PARTY_A, size);
		// receiveVector<myType>(rc, PARTY_A, size);
        // receiveTwoVectors<myType>(rb, rc, PARTY_A, size, size);

		for (int i = 0; i < size; ++i)
		{
			a[i] = rb[i] & mask;
		}
	}
	else if (partyNum == PARTY_C)
	{
		receiveVector<myType>(rc, PARTY_A, size);
		// receiveVector<myType>(tmp, PARTY_A, size);
        // receiveTwoVectors<myType>(rc, tmp, PARTY_A, size, size);

		for (int i = 0; i < size; ++i)
		{
			a[i] = rc[i] & mask;
		}
	}
}

void getBShares3in3(vector<smallType> &a, vector<smallType> &data, int32_t bw){
    assert(bw <= 8);
	uint64_t mask = (bw == 8 ? -1 : ((1ULL << bw) - 1));
	size_t size = a.size();
	vector<smallType> tmp(size, 0),rb(size, 0), rc(size, 0);

	if (partyNum == PARTY_A)
	{
		//调用precompute里面生成随机数的部分
		//A生成两个随机数向量rb,rc
		getRandomNum(rb, bw);
		getRandomNum(rc, bw);
		for (int i = 0; i < size; ++i)
		{
			a[i] = (data[i] ^ rb[i] ^ rc[i]) & mask;
		}
        sendVector<smallType>(rb, PARTY_B, size);
        sendVector<smallType>(rc, PARTY_C, size);
	}
	else if (partyNum == PARTY_B)
	{
		receiveVector<smallType>(rb, PARTY_A, size);
		// receiveVector<myType>(rc, PARTY_A, size);
        // receiveTwoVectors<myType>(rb, rc, PARTY_A, size, size);

		for (int i = 0; i < size; ++i)
		{
			a[i] = rb[i] & mask;
		}
	}
	else if (partyNum == PARTY_C)
	{
		receiveVector<smallType>(rc, PARTY_A, size);
		// receiveVector<myType>(tmp, PARTY_A, size);
        // receiveTwoVectors<myType>(rc, tmp, PARTY_A, size, size);

		for (int i = 0; i < size; ++i)
		{
			a[i] = rc[i] & mask;
		}
	}
}


//只重建一个数值，非vector形式
void getAReconstructOne(RSSMyType &data, myType &result,  string str, bool print, int32_t bw){
	log_print("Reconst: RSSMyType to myType, Arithmetic, not vector");
    assert(bw <= 64);
	uint64_t mask = (bw == 64 ? -1 : ((1ULL << bw) - 1));
    vector<uint64_t> data_next(1, 0), data_prev(1, 0);
    data_next[0] = data.first;

    thread *threads = new thread[2];
	threads[0] = thread(sendVector<myType>, ref(data_next), nextParty(partyNum), 1);
	threads[1] = thread(receiveVector<myType>, ref(data_prev), prevParty(partyNum), 1);
	for (int i = 0; i < 2; i++)
		threads[i].join();
	delete[] threads;

    result = (data.first + data.second + data_prev[0]) & mask;
    cout<<str<<result<<endl;
}

/**
* reconstruct Arithmetic shares(myType)
* @param 
* a: data
* b: result
* str:输出时候的提示信息
* print:是否要输出到终端
* @return 
**/
void getAReconstruct(RSSVectorMyType &data, vector<myType> &result, size_t size, string str, bool print, int32_t bw){
	log_print("Reconst: RSSMyType to myType, Arithmetic");
	assert(data.size() == size && "data.size mismatch for reconstruct function");
    assert(bw <= 64);

	uint64_t mask = (bw == 64 ? -1 : ((1ULL << bw) - 1));

	vector<myType> data_next(size), data_prev(size);
	for (int i = 0; i < size; ++i)
	{
		data_prev[i] = 0;
		data_next[i] = data[i].first;
		result[i] = data[i].first + data[i].second;
	}

	thread *threads = new thread[2];
	threads[0] = thread(sendVector<myType>, ref(data_next), nextParty(partyNum), size);
	threads[1] = thread(receiveVector<myType>, ref(data_prev), prevParty(partyNum), size);
	for (int i = 0; i < 2; i++)
		threads[i].join();
	delete[] threads;

	for (int i = 0; i < size; ++i)
		result[i] = (result[i] + data_prev[i]) & mask;

	if (print)
	{
		std::cout << str << ": \t\t";
		for (int i = 0; i < size; ++i)
			print_linear(result[i], "UNSIGNED");
		std::cout << std::endl;
	}

}

void getBReconstruct(RSSVectorMyType &data, vector<myType> &result, size_t size, string str, bool print, int32_t bw){
	log_print("Reconst: RSSMyType to myType, Boolean");
	assert(data.size() == size && "data.size mismatch for reconstruct function");
	assert(result.size() == size && "result.size mismatch for reconstruct function");
    assert(bw <= 64);

	uint64_t mask = (bw == 64 ? -1 : ((1ULL << bw) - 1));

	vector<myType> data_next(size), data_prev(size);
	for (int i = 0; i < size; ++i)
	{
		data_prev[i] = 0;
		data_next[i] = data[i].first;
		result[i] = data[i].first ^ data[i].second;
	}

	thread *threads = new thread[2];
	threads[0] = thread(sendVector<myType>, ref(data_next), nextParty(partyNum), size);
	threads[1] = thread(receiveVector<myType>, ref(data_prev), prevParty(partyNum), size);
	for (int i = 0; i < 2; i++)
		threads[i].join();
	delete[] threads;

	for (int i = 0; i < size; ++i)
		result[i] = (result[i] ^ data_prev[i]) & mask;

	if (print)
	{
		std::cout << str << ": \t\t";
		for (int i = 0; i < size; ++i)
			print_linear(result[i], "UNSIGNED");
		std::cout << std::endl;
	}

}

void getBReconstruct(RSSVectorSmallType &data, vector<smallType> &result, size_t size, string str, bool print, int32_t bw){
	log_print("Reconst: RSSMyType to myType, Boolean");
	assert(data.size() == size && "data.size mismatch for reconstruct function");
	assert(result.size() == size && "result.size mismatch for reconstruct function");
    assert(bw <= 8);

	uint64_t mask = (bw == 8 ? -1 : ((1ULL << bw) - 1));

	vector<smallType> data_next(size), data_prev(size);
	for (int i = 0; i < size; ++i)
	{
		data_prev[i] = 0;
		data_next[i] = data[i].first;
		result[i] = data[i].first ^ data[i].second;
	}

	thread *threads = new thread[2];
	threads[0] = thread(sendVector<smallType>, ref(data_next), nextParty(partyNum), size);
	threads[1] = thread(receiveVector<smallType>, ref(data_prev), prevParty(partyNum), size);
	for (int i = 0; i < 2; i++)
		threads[i].join();
	delete[] threads;

	for (int i = 0; i < size; ++i)
		result[i] = (result[i] ^ data_prev[i]) & mask;

	if (print)
	{
		std::cout << str << ": \t\t";
		for (int i = 0; i < size; ++i)
			print_linear(result[i], "UNSIGNED");
		std::cout << std::endl;
	}

}


void getAReconstruct3in3(vector<myType> &data, vector<myType> &result, size_t size, string str, int32_t bw, bool print){
    log_print("Reconst: myType, myType，Arithmetic， 3-out-of-3");
	assert(data.size() == size && "data.size mismatch for reconstruct function");
	assert(result.size() == size && "result.size mismatch for reconstruct function");
    assert(bw <= 64);

	uint64_t mask = (bw == 64 ? -1 : ((1ULL << bw) - 1));
	vector<myType> temp_A(size,0), temp_B(size, 0);

	if (partyNum == PARTY_A or partyNum == PARTY_B)
		sendVector<myType>(data, PARTY_C, size);

	if (partyNum == PARTY_C)
	{
		receiveVector<myType>(temp_A, PARTY_A, size);
		receiveVector<myType>(temp_B, PARTY_B, size);
		addVectors<myType>(temp_A, data, temp_A, size);
		addVectors<myType>(temp_B, temp_A, result, size);
		//异或mask
		for(int i=0; i<size; ++i){
			result[i] = result[i] & mask;
		}
		sendVector<myType>(result, PARTY_A, size);
		sendVector<myType>(result, PARTY_B, size);
	}

	if (partyNum == PARTY_A or partyNum == PARTY_B)
		receiveVector<myType>(result, PARTY_C, size);

	if (print)
	{
		std::cout << str << ": \t\t";
		for (int i = 0; i < size; ++i)
			print_linear(result[i], "UNSIGNED");
		std::cout << std::endl;
	}

}

void getBReconstruct3in3(vector<myType> &data, vector<myType> &result, size_t size, string str, int32_t bw, bool print){
    log_print("Reconst: smallType, smallType， Boolean， 3-out-of-3");
	assert(data.size() == size && "data.size mismatch for reconstruct function");
	assert(result.size() == size && "result.size mismatch for reconstruct function");
    assert(bw <= 64);
	uint64_t mask = (bw == 64 ? -1 : ((1ULL << bw) - 1));
	vector<myType> temp_A(size,0), temp_B(size, 0);

	if (partyNum == PARTY_A or partyNum == PARTY_B)
		sendVector<myType>(data, PARTY_C, size);

	if (partyNum == PARTY_C)
	{
		receiveVector<myType>(temp_A, PARTY_A, size);
		receiveVector<myType>(temp_B, PARTY_B, size);
		// addVectors<myType>(temp_A, a, temp_A, size);
		// addVectors<myType>(temp_B, temp_A, b, size);
		// //异或mask
		for(int i=0; i<size; ++i){
            result[i] = data[i] ^ temp_A[i] ^temp_B[i];
			result[i] = result[i] & mask;
		}
		sendVector<myType>(result, PARTY_A, size);
		sendVector<myType>(result, PARTY_B, size);
	}

	if (partyNum == PARTY_A or partyNum == PARTY_B)
		receiveVector<myType>(result, PARTY_C, size);

	if (print)
	{
		std::cout << str << ": \t\t";
		for (int i = 0; i < size; ++i)
			print_linear(result[i], "UNSIGNED");
		std::cout << std::endl;
	}

}


void getBReconstruct3in3(vector<smallType> &data, vector<myType> &result, size_t size, string str, int32_t bw, bool print){
    log_print("Reconst: smallType, smallType， Boolean， 3-out-of-3");
	assert(data.size() == size && "data.size mismatch for reconstruct function");
	assert(result.size() == size && "result.size mismatch for reconstruct function");
    assert(bw <= 8);
	uint64_t mask = (bw == 8 ? -1 : ((1ULL << bw) - 1));
	vector<smallType> temp_A(size,0), temp_B(size, 0);

	if (partyNum == PARTY_A or partyNum == PARTY_B)
		sendVector<smallType>(data, PARTY_C, size);

	if (partyNum == PARTY_C)
	{
		receiveVector<smallType>(temp_A, PARTY_A, size);
		receiveVector<smallType>(temp_B, PARTY_B, size);
		// addVectors<smallType>(temp_A, a, temp_A, size);
		// addVectors<myType>(temp_B, temp_A, b, size);
		// //异或mask
		for(int i=0; i<size; ++i){
            result[i] = data[i] ^ temp_A[i] ^ temp_B[i];
			result[i] = result[i] & mask;
		}
		sendVector<myType>(result, PARTY_A, size);
		sendVector<myType>(result, PARTY_B, size);
	}

	if (partyNum == PARTY_A or partyNum == PARTY_B)
		receiveVector<myType>(result, PARTY_C, size);

	if (print)
	{
		std::cout << str << ": \t\t";
		for (int i = 0; i < size; ++i)
			print_linear(result[i], "UNSIGNED");
		std::cout << std::endl;
	}

}


/**
 * 借助随机数截断对进行截断操作
 * @param 
 * a: 共享形式的,待截断数据
 * power: 要截掉的位数
 * size: 向量的size
 * @return 
 */
void getTruncate(RSSVectorMyType &data, int32_t bw, int32_t power){
	log_print("funcTruncate");
    size_t size = data.size();
	RSSVectorMyType r(size), rPrime(size);
	vector<myType> reconst(size);
	uint64_t mask = (bw == 64 ? -1 : ((1ULL << bw) - 1));
    assert(bw <= 64);

	getRandomTruncatePairs(r, rPrime, bw, power, size);
	for (int i = 0; i < size; ++i)
		data[i] = data[i] - rPrime[i];
	
	getAReconstruct(data, reconst, size, "Truncate reconst", false, bw);
	dividePlain(reconst, (1 << power));
	if (partyNum == PARTY_A){
		for (int i = 0; i < size; ++i)
		{
			data[i].first = (r[i].first + reconst[i]) & mask;
			data[i].second = r[i].second;
		}
	}

	if (partyNum == PARTY_B){
		for (int i = 0; i < size; ++i)
		{
			data[i].first = r[i].first;
			data[i].second = r[i].second;
		}
	}

	if (partyNum == PARTY_C){
		for (int i = 0; i < size; ++i)
		{
			data[i].first = r[i].first;
			data[i].second = (r[i].second + reconst[i]) & mask;
		}
	}
}

/**
 * 通过调用mill进行比较来计算wrap值
 * @param 
 * u: A计算得到明文的u
 * v: 调用mill计算得到2共2(可视作3共3)
 * size: 维度
 * bw: x的位宽
 * @return 
 */
void wrap3_uv(RSSVectorMyType &a, vector<smallType> &u, vector<smallType> &v, size_t size, int32_t bw){
	// vector<myType> temp(size, 0);
    assert(bw <= 64);
	uint64_t *temp = new uint64_t[size];
	uint8_t *tmp_v = new uint8_t[size];

	uint64_t mask = (bw == 64 ? -1 : ((1ULL << bw) - 1));
	uint8_t mask_bit = 1;
	
	if(partyNum == PARTY_B){
		//B计算u
        // cout<<"B（ALICE）本地计算u"<<endl;
		for(int i=0; i<size; ++i){
			u[i] = wrapAround(a[i].first, a[i].second, bw) & mask_bit;
			temp[i] = (a[i].first + a[i].second) & mask;
            // cout<<"u[" << i << "]=" << +u[i] <<endl;
		}
		// B公开u
        // cout<<"B（ALICE）公开u"<<endl;
		sendVector<uint8_t>(u, prevParty(partyNum), size);
		sendVector<uint8_t>(u, nextParty(partyNum), size);
	}
	if(partyNum == PARTY_C){
		receiveVector<uint8_t>(u, PARTY_B, size);
        // cout<<"C（BOB）接收u"<<endl;
        //C(BOB)设置比较要用的数据
		for(int i=0; i<size; ++i){
			temp[i] = (mask - a[i].second) & mask;
		}
		
	}
	if(partyNum == PARTY_A){
		receiveVector<uint8_t>(u, PARTY_B, size);
        cout<<"A接收u并设置v为0"<<endl;
		for(int i =0; i<size; ++i){
			v[i] = 0;
		}
	}
	// B和C使用millionaire算法得到v的2共2共享值
	if((partyNum == PARTY_B) || (partyNum == PARTY_C)){
		//2共2，把party_A的v[i]全部赋值为0，实际上可以看做是3共3
        cout<<"before mill->compare"<<endl;
		mill->compare(tmp_v, temp, (int)size, (int)bw, true);
        cout<<"after mill->compare"<<endl;

		for(int i =0; i<size; ++i){
			v[i] = tmp_v[i] & mask_bit;
		}
	}
    
    delete[] temp;
    delete[] tmp_v;

}


/**
 * vectorMUX,通过OT计算 bit * data
 * @param 
 * sel: choice bit
 * x: the data
 * y: result
 * @return void
 */
// void multiplexer(uint8_t *sel, uint64_t *x, uint64_t *y, int32_t size, int32_t bw_x, int32_t bw_y) 
void multiplexer(vector<uint8_t> select, vector<uint64_t> x, vector<uint64_t> &y, int32_t size, int32_t bw_x, int32_t bw_y){
	// y=0 or y=x； bw_y <= bw_x?
	assert(bw_x <= 64 && bw_y <= 64 && bw_y <= bw_x);
    vector<uint64_t> r(size,0);
    //由于A不参与这个OT的过程
	if(partyNum == PARTY_A){
        getRandomNum(r, bw_y);
        for (int i = 0; i < size; ++i){
			y[i] = r[i];
		}
        sendVector<myType>(r, PARTY_B, size);
	}
	else{
		uint64_t mask_x = (bw_x == 64 ? -1 : ((1ULL << bw_x) - 1));
		uint64_t mask_y = (bw_y == 64 ? -1 : ((1ULL << bw_y) - 1));

		//-corr_data是干什么用的？
		//-用于存储计算过程中的x[i]*(1-2sel[i]), 这个值用于跟bit通过OT相乘
		uint64_t *corr_data = new uint64_t[size];
		uint64_t *data_S = new uint64_t[size];
		uint64_t *data_R = new uint64_t[size];

		uint8_t *sel =new uint8_t[size];
		for (int i = 0; i < size; ++i){
			sel[i] = select[i] & 1;
		}

		//原理:
		// y = (sel_0 \xor sel_1) * (x_0 + x_1)
		// y = (sel_0 + sel_1 - 2*sel_0*sel_1)*x_0 + (sel_0 + sel_1 - 2*sel_0*sel_1)*x_1 
		// y = [sel_0*x_0 + sel_1*(x_0 - 2*sel_0*x_0)]
		//      + [sel_1*x_1 + sel_0*(x_1 - 2*sel_1*x_1)]
		// y = [sel_0*x_0 + sel_1* x_0*(1 - 2*sel_0)]
		//      + [sel_1*x_1 + sel_0* x_1*(1 - 2*sel_1)]
		for (int i = 0; i < size; i++) {
			corr_data[i] = (x[i] * (1 - 2 * uint64_t(sel[i]))) & mask_y;
		}
		if (partyNum == PARTY_B) {
            // cout<<"B(ALICE), before OT\n";
			otpack->iknp_straight->send_cot(data_S, corr_data, size, bw_y);
			otpack->iknp_reversed->recv_cot(data_R, (bool *)sel, size, bw_y);
            // cout<<"B(ALICE), after OT\n";
            receiveVector<myType>(r, PARTY_A, size);
            
		} else if (partyNum == PARTY_C){ 
            // cout<<"C(BOB), before OT\n";
			otpack->iknp_straight->recv_cot(data_R, (bool *)sel, size, bw_y);
			otpack->iknp_reversed->send_cot(data_S, corr_data, size, bw_y);
            // cout<<"C(BOB), after OT\n";

		}
        if(partyNum == PARTY_B){
            for (int i = 0; i < size; i++) {
                y[i] = ((x[i] * uint64_t(sel[i]) + data_R[i] - data_S[i] - r[i]) & mask_y);
		    }
        }
		if(partyNum == PARTY_C){
            for (int i = 0; i < size; i++) {
			    y[i] = ((x[i] * uint64_t(sel[i]) + data_R[i] - data_S[i]) & mask_y);
		    }
        }

		delete[] corr_data;
		delete[] data_S;
		delete[] data_R;
        delete[] sel;
	}
}

// TODO: 还没考虑有符号数/无符号数

// 向量形式的乘法
void vectorMult_nu(RSSVectorMyType &a, RSSVectorMyType &b, RSSVectorMyType &c, int32_t bw_A, int32_t bw_B, int32_t &bw_C, size_t size){
	assert(bw_C <= 64);
  	// assert((bw_C <= (bw_A + bw_B)) && (bw_C >= bw_A) && (bw_C >= bw_B));
	assert((a.size() == size) && "a.size does not match");
	assert((b.size() == size) && "b.size does not match");
	assert((c.size() == size) && "c.size does not match");
  	// int32_t extra_bits = ceil(log2(dim2));

	uint64_t mask_a = (bw_A == 64 ? -1 : ((1ULL << bw_A) - 1));
	uint64_t mask_b = (bw_B == 64 ? -1 : ((1ULL << bw_B) - 1));
	bw_C = (((bw_A + bw_B) < 64) ? (bw_A + bw_B) : 64);
	uint64_t mask_c = (bw_C == 64 ? -1 : ((1ULL << bw_C) - 1));

	uint64_t M = (bw_A == 64 ? 0 : (1ULL << bw_A) );
	uint64_t N = (bw_B == 64 ? 0 : (1ULL << bw_B) );

	
	//local 3in3
	vector<myType> local_00_01_10(size, 0), tempd(size, 0), tempe(size, 0);
	for (int i = 0; i < size; i++)
	{
		local_00_01_10[i] = ((a[i].first & mask_a) * (b[i].first & mask_b))
			+ ((a[i].first & mask_a) * (b[i].second & mask_b))
			+ ((a[i].second & mask_a) * (b[i].first & mask_b));
	}
	cout<<"vectorMult local terms calculated!"<<endl;

	//从wrap开始大改！！！
	// wrap3_uv and multiplexer
	vector<smallType> ua(size, 0), va(size, 0), ub(size, 0), vb(size, 0);
    cout<<"/******************** 开始调用 WRAP *************************/"<<endl;
	wrap3_uv(a, ua, va, size, bw_A);
	wrap3_uv(b, ub, vb, size, bw_B);
    cout<<"wrap values ux, vx, uy, vy calculated!"<<endl;

	vector<uint64_t> aSend(size, 0), bSend(size, 0), mux1_va_b(size, 0), mux2_vb_a(size, 0);
	for (int i = 0; i < size; ++i)
	{
		if(partyNum == PARTY_A){
			aSend[i] = 0;
			bSend[i] = 0;
		}
		if(partyNum ==PARTY_B){
			aSend[i] = (a[i].first + a[i].second) & mask_a;
			bSend[i] = (b[i].first + b[i].second) & mask_b;
		}
		if(partyNum ==PARTY_C){
			aSend[i] = a[i].second & mask_a;
			bSend[i] = b[i].second & mask_b;
		}
	}
	multiplexer(va, aSend, mux1_va_b, size, bw_A, bw_B);
	multiplexer(vb, bSend, mux2_vb_a, size, bw_A, bw_B);
	cout<<"mux1_va_b, mux2_vb_a calculated!"<<endl;

	vector<uint64_t> M_ua_b(size, 0), N_ub_a(size,0);
	for (int i = 0; i < size; i++){
		M_ua_b[i] = M * (ua[i] & 1) * b[i].first;
		N_ub_a[i] = N * (ub[i] & 1) * a[i].first;
	}
	cout<<"M_ua_b, N_ub_a calculated!"<<endl;

	// //wrap 3in3,bool
	// RSSVectorSmallType wrapx(size, std::make_pair(0,0)), wrapy(size, std::make_pair(0,0));
	// wrap3_RSSVector(a, wrapx, bw_A, size);
	// wrap3_RSSVector(b, wrapy, bw_B, size);

	//mux  2in3
	//(1<< bw_A) * wrapx * y
	//(1<< bw_B) * wrapy * x

	// RSSVectorMyType mux1_va_b(size), mux2_vb_a(size);


	//total
	for (int i = 0; i < size; i++)
	{
		//前三项是ABC都有的，C的mux两项都=0
		tempd[i] = (local_00_01_10[i] - M_ua_b[i] - N_ub_a[i] - M * mux1_va_b[i] - N * mux2_vb_a[i]) & mask_c;
		c[i].first = tempd[i];
	}
	// send tempd to prevParty to get 2in3
	thread *threads = new thread[2];
	threads[0] = thread(sendVector<myType>, ref(tempd), prevParty(partyNum), size);
	threads[1] = thread(receiveVector<myType>, ref(tempe), nextParty(partyNum), size);
	for (int i = 0; i < 2; i++)
		threads[i].join();
	delete[] threads;

    cout<<"vectorMult: 3in3 to 2in3"<<endl;
	for (int i = 0; i < size; i++)
	{
		c[i].second = tempe[i] & mask_c;
	}
    cout<<"vectorMult finished!"<<endl;
}

//向量，明文乘法
void vectorMult_nu_cleartext(vector<uint64_t> &a, vector<uint64_t> &b, vector<uint64_t> &c, int32_t bw_A, int32_t bw_B, int32_t &bw_C, size_t size){
    assert(a.size() == size && b.size() == size);
	uint64_t maskA = (bw_A == 64 ? -1 : ((1ULL << bw_A) - 1));
    uint64_t maskB = (bw_B == 64 ? -1 : ((1ULL << bw_B) - 1));
    uint64_t maskC = (bw_C == 64 ? -1 : ((1ULL << bw_C) - 1));

	for (int i = 0; i < size; ++i)
	{
		c[i] = ((a[i] & maskA) * (b[i] & maskB)) & maskC;
	}
	
}


/**
 * RSS(2in3) Boolean to Arithmetic(bw_B bits)
 * @param 
 * a: Bshare data
 * res: the result in Ashare
 * @return 
 */
void B2A(RSSVectorSmallType &a, RSSVectorMyType &res, int32_t bw_B, size_t size){
    assert(bw_B <= 64 && bw_B >= 1);
    if (bw_B == 1) {
        for (int i = 0; i < size; i++) {
            res[i].first = uint64_t(a[i].first) & 1;
            res[i].second = uint64_t(a[i].second) & 1;
            }
        return;
    }
    uint64_t mask = (bw_B == 64 ? -1 : ((1ULL << bw_B) - 1));

    //A gets [res]_0 = -a1, B gets [res]_1 = -a2 randomly
    vector<myType> minus_a1(size, 0), minus_a2(size,0);
    RSSVectorMyType shared_minus_a1(size), shared_minus_a2(size);

    if(partyNum ==PARTY_A){
        getRandomNum(minus_a1, bw_B);
        getRandomNum(minus_a2, bw_B);
        for (int i = 0; i < size; i++)
        {
            minus_a1[i] = ( 0-minus_a1[i] ) & mask;
            minus_a2[i] = ( 0-minus_a2[i] ) & mask;
            res[i].first = minus_a1[i];
            res[i].second = minus_a2[i];
        }
        // sendTwoVectors<myType>(minus_a1,minus_a2,PARTY_B, size, size);
        sendVector<myType>(minus_a2, PARTY_B, size);
        sendVector<myType>(minus_a1, PARTY_C, size);
    }
    if(partyNum == PARTY_B){
        // res.first = minus_a2
        receiveVector(minus_a2, PARTY_A, size);
    }
    if(partyNum == PARTY_C){
        receiveVector<myType>(minus_a1, PARTY_A, size);
    }
    

    //Bshare (-a1), (-a2)
    getBShares(shared_minus_a1, minus_a1, bw_B);
    getBShares(shared_minus_a2, minus_a2, bw_B);
    
    //temp = b xor (-a1) xor (-a2)
    RSSVectorMyType temp(size);
    xorRSSVectors(a, shared_minus_a1, temp, bw_B,size);
    xorRSSVectors(temp, shared_minus_a2, temp, bw_B,size);

    //C reconstructs [res]_2 = b-a1-a2 = reconstruct(temp)
    // 3in3 to 2in3
    vector<myType> data(size);
    if(partyNum == PARTY_B){
        for (int i = 0; i < size; ++i){
            data[i] = temp[i].first;
        }
        sendVector<myType>(data, PARTY_C, size);
    }
    if(partyNum == PARTY_C){
        receiveVector(data, PARTY_B, size);
	    for (int i = 0; i < size; ++i){
            //b-a1-a2
            res[i].first = (temp[i].first ^ temp[i].second ^ data[i]) & mask;
            //-a1
            res[i].second = minus_a1[i];
            //-a1:vector tosend to B
            data[i] = res[i].first;
        }
        sendVector<myType>(data, PARTY_B, size);
    }
    if(partyNum == PARTY_B){
        receiveVector(data, PARTY_C, size);
        for (int i = 0; i < size; ++i)
        {
            res[i].first = minus_a2[i] & mask;
            res[i].second = data[i] & mask;
        }
        
    }
}

/**
 * 3in3 Boolean to Arithmetic(bw_B bits)
 * @param 
 * a: Bshare data
 * res: the result in Ashare
 * @return 
 */
void B2A_vector(vector<smallType> &a, vector<myType> &res, int32_t bw_A, int32_t bw_B, size_t size){
    assert(bw_A <= 64 && bw_A >= 1);
    assert(bw_B <= 64 && bw_B >= 1);
    if (bw_B == 1) {
        for (int i = 0; i < size; i++) {
            res[i] = uint64_t(a[i]) & 1;
            res[i]= uint64_t(a[i]) & 1;
            }
        return;
    }
    uint64_t mask_A = (bw_A == 64 ? -1 : ((1ULL << bw_A) - 1));
    uint64_t mask_B = (bw_B == 64 ? -1 : ((1ULL << bw_B) - 1));

    vector<myType> recB_a(size, 0);
    getBReconstruct3in3(a, recB_a, size, "", bw_A, false);
    getAShares3in3(res, recB_a, bw_B);


    // //A gets [res]_0 = -a1, B gets [res]_1 = -a2 randomly
    // vector<myType> minus_a1(size, 0), minus_a2(size,0), minus_a1_minus_a2(size,0), shared_minus_a1_minus_a2(size);

    // if(partyNum ==PARTY_A){
    //     getRandomNum(minus_a1, bw_B);
    //     // print_vector(minus_a1, "a1");
    //     getRandomNum(minus_a2, bw_B);
    //     // print_vector(minus_a2, "a2");
    //     // cout<<"party_A: res = minus_a1"<<endl;
    //     for (int i = 0; i < size; i++)
    //     {
    //         // minus_a1[i] = ( mask_B+1-minus_a1[i] ) & mask_B;
    //         // minus_a2[i] = ( mask_B+1-minus_a2[i] ) & mask_B;
    //         minus_a1_minus_a2[i] = (minus_a1[i] + minus_a2[i]) & mask_B;
    //         res[i] = minus_a1[i] & mask_A;
    //         // cout<<"minus_a1["<<i<<"]="<<minus_a1[i]<<endl;
    //         // cout<<"minus_a2["<<i<<"]="<<minus_a2[i]<<endl;
    //     }
    //     sendVector<myType>(minus_a2, PARTY_B, size);
    // }
    // if(partyNum == PARTY_B){
    //     // res = minus_a2
    //     cout<<"party_B: res = minus_a2"<<endl;
    //     receiveVector(minus_a2, PARTY_A, size);
    //     for (int i = 0; i < size; ++i){
    //         res[i] = minus_a2[i] & mask_A;
    //     }
    // }

    // cout<<"Bshare (-a1-a2)"<<endl;
    // //Bshare (-a1-a2)
    // getBShares3in3(shared_minus_a1_minus_a2, minus_a1_minus_a2, bw_B);
    // print_vector(shared_minus_a1_minus_a2, "shared_minus_a1_minus_a2");
    
    // cout<<"temp = b + (-a1-a2)"<<endl;
    // //temp = b xor (-a1) xor (-a2)
    // vector<myType> temp(size, 0);
    // // addVectors<myType, smallType>(a, shared_minus_a1_minus_a2, temp, size);
    // // xorVectors<myType, smallType>(a, shared_minus_a1_minus_a2, temp, size);
    // // xorVectors<myType, myType>(temp, shared_minus_a1_minus_a2, temp, size);
    // for (int i = 0; i < size; ++i)
    // {
    //     temp[i] = (a[i] & mask_A) ^ shared_minus_a1_minus_a2[i] & mask_B;
    // }
    

    // cout<<"C reconstructs [res]_2 = b-a1-a2 = reconstruct(temp)"<<endl;
    // //C reconstructs [res]_2 = b-a1-a2 = reconstruct(temp)
    // if(partyNum == PARTY_A){
    //     sendVector<myType>(temp, PARTY_C, size);
    // }if(partyNum == PARTY_B){
    //     sendVector<myType>(temp, PARTY_C, size);
    // }
    // if(partyNum == PARTY_C){
    //     vector<myType> data(size, 0), temp2(size,0);
    //     receiveVector(data, PARTY_A, size);
    //     receiveVector(temp2, PARTY_B, size);
	//     for (int i = 0; i < size; ++i){
    //         //<b-a1-a2>_A_i = <b>_B_i + <-a1>_B_i + <-a2>_B_i
    //         //关于res的设置不是异或mask_B而是 xor mask_A: 因为B2A主要用在bit2A,有位宽变化，在Bshare b这个数的时候，所有between(bw_A, bw_B)的位均为0，这导致在恢复数据的时候高位基本不可能为0（是随机数），故而会出现低位结果正确而带上高位结果不正确的情况。
    //         //但是这样的话进行reconstruct仍然会有可能有环绕即溢出，怎么解决？
    //         res[i] = (temp[i] ^ temp2[i] ^ data[i]) & mask_A;
    //     }
    // }


}



//零扩展
void z_extend(RSSVectorMyType &x, RSSVectorMyType &x_extend, int32_t bw_x, int32_t bw_y, size_t size){
    if (bw_x == bw_y) {
        for (int i = 0; i < size; ++i)
        {
            x_extend[i].first = x[i].first;
            x_extend[i].second = x[i].second;
        }
        return;
    }
    assert(bw_y > bw_x && "Extended bitwidth should be > original");
    uint64_t mask_x = (bw_x == 64 ? -1 : ((1ULL << bw_x) - 1));
    uint64_t mask_y = (bw_y == 64 ? -1 : ((1ULL << bw_y) - 1));
    uint64_t M = (bw_x == 64 ? 0 :(1ULL << bw_x));
    uint64_t N = (bw_y == 64 ? 0 :(1ULL << bw_y));
    uint8_t *wrap = new uint8_t[size];
    /*
    x = x_0 + x_1 + x_2 - w * M
      = x_0 + x_1 + x_2 - (u + v) * M
    u = u_0 + u_1 + u_2 -w_u * 2^(n-m)
    u * M = (u_0 + u_1 + u_2 -w_u(u0, u1, u2, N-M) * 2^(n-m) ) * M (mod N)
          = (u_0 + u_1 + u_2 )[N-M] * M (mod N)
    ∴ [x]_i = x_i - (u_i【N-M】 + v_i【N-M】) * M
    */
    //求x的wrap得到u,v
    vector<myType> u_extend(size, 0), v_extend(size, 0);
    vector<smallType> u(size, 0), v(size, 0);
    wrap3_uv(x, u, v, size, bw_x);

    //u是公开的，v是3共3的

    //求B2A(u, dest_bw = n-m), B2A(v, dest_bw = n-m)
    // B2A_vector(u, u_extend, 1, bw_y-bw_x, size);
    B2A_vector(v, v_extend, 1, bw_y-bw_x, size);


    //[x]_i = x_i - (u_i【N-M】 + v_i【N-M】) * M
    vector<myType> send(size, 0), recv(size, 0);
    for (int i = 0; i < size; ++i)
    {
        if(partyNum == PARTY_A){
            x_extend[i].first = (x[i].first - uint64_t(u[i] + v_extend[i]) * M) & mask_y;
        }
        else{
            x_extend[i].first = (x[i].first - uint64_t(v_extend[i]) * M) & mask_y;
        }
        send[i] = x_extend[i].first;
    }
    
    //3in3 to 2in3
    thread *threads = new thread[2];
	threads[0] = thread(sendVector<myType>, ref(send), prevParty(partyNum), size);
	threads[1] = thread(receiveVector<myType>, ref(recv), nextParty(partyNum), size);
	for (int i = 0; i < 2; i++)
		threads[i].join();
	delete[] threads;

	for (int i = 0; i < size; ++i)
		x_extend[i].second = recv[i];

    delete[] wrap;
}

//TODO: 符号扩展
void s_extend(){

}


// from SIRNN论文， 点积和乘法计算中，做完运算之后位数是 bw_A + bw_B + extra_bits
//点积
void dotProduct(RSSVectorMyType &a, RSSVectorMyType &b, RSSMyType &res, int32_t bw_A, int32_t bw_B, int32_t &bw_C, size_t size){
	assert((a.size() == size) && "a.size does not match");
	assert((b.size() == size) && "b.size does not match");
  	int32_t extra_bits = ceil(log2(size));
    RSSVectorMyType tmp(size, make_pair(0,0)), a_extend(size, make_pair(0,0));
    
    bw_C = (((bw_A + bw_B + extra_bits) < 64) ? (bw_A + bw_B + extra_bits) : 64);
	uint64_t mask_c = (bw_C == 64 ? -1 : ((1ULL << bw_C) - 1));

    // 对A做零扩展
    z_extend(a, a_extend, bw_A, bw_A + extra_bits, size);
    // 然后调用向量乘法，只不过把每个向量的各项相加
    vectorMult_nu(a_extend, b, tmp, bw_A + extra_bits, bw_B, bw_C, size);

    res = make_pair(0,0);
    for (int i = 0; i < size; ++i){
        res.first += tmp[i].first;
        res.second += tmp[i].second;
    }
    res.first &= mask_c;
    res.second &= mask_c;
}


void matMultRSS_local(RSSVectorMyType &a, RSSVectorMyType &b, vector<myType> &c, size_t rows, size_t common_dim, size_t columns, int32_t bw_A, int32_t bw_B, int32_t bw_C){

    assert(a.size() == rows * common_dim && "a.size does not match");
    assert(b.size() == common_dim * columns && "b.size does not match");
    assert(c.size() == rows * columns && "c.size does not match");

    uint64_t mask_a = (bw_A == 64 ? -1 : ((1ULL << bw_A) - 1));
	uint64_t mask_b = (bw_B == 64 ? -1 : ((1ULL << bw_B) - 1));
	uint64_t mask_c = (bw_C == 64 ? -1 : ((1ULL << bw_C) - 1));


    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            c[i * columns + j] = 0;
            for (int k = 0; k < common_dim; k++) {
                c[i * columns + j] += a[common_dim * i + k].first * b[columns * k + j].first
                                    + a[common_dim * i + k].first * b[columns * k + j].second
                                    + a[common_dim * i + k].second * b[columns * k + j].first;
            }
            c[i * columns + j] &= mask_c;
        }
    }
}


void copyRSSVectorMyType(RSSVectorMyType &mat, RSSVectorMyType &mat_copy, size_t size){
    assert((mat.size() == mat_copy.size()) && (mat.size() == size));

    for (int i = 0; i < size; ++i){
        mat_copy[i].first = mat[i].first;
        mat_copy[i].second = mat[i].second;
    }
    
}


void matrix_transpose(RSSVectorMyType &mat, RSSVectorMyType &mat_transpose, size_t m, size_t n) {
    size_t size = m * n;
    assert(mat.size() == size && "mat.size() != size");
    assert(mat_transpose.size() == size && "mat_copy.size() != size");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            mat_transpose[i * m + j].first = mat[j * n + i].second;
            mat_transpose[i * m + j].first = mat[j * n + i].second;
        }
    }
    cout<<"transpose finished!"<<endl;
}


void getSliceRSSVectorMyType(RSSVectorMyType &a, RSSVectorMyType &b, size_t left, size_t right){
    assert((right > left) && "right index should be larger than the left");
    assert(left >= 0 && "the left index should not be minus");
    assert(right <= a.size() && "the right index should not be larger than a.size()");
    size_t size = right - left;
    assert((b.size() == size) && "b.size() != right - left");
    for (int i = 0; i < b.size(); ++i)
    {
        b[i].first = a[left + i].first;
        b[i].second = a[left + i].second;
    }
    cout<<"got slice [left:right]!"<<endl;
}

// 矩阵乘法,bw_A * bw_B —> bw_A + bw_B + extra_bits
void matMult(RSSVectorMyType &a, RSSVectorMyType &b, RSSVectorMyType &c, size_t rows, size_t common_dim, size_t columns, int32_t bw_A, int32_t bw_B, int32_t &bw_C){
    assert(a.size() == (rows * common_dim) && "a.size does not match");
    assert(b.size() == (common_dim * columns) && "b.size does not match");
    assert(c.size() == (rows * columns) && "c.size does not match");

    int32_t extra_bits = ceil(log2(common_dim));
    bw_C = (((bw_A + bw_B) < 64) ? (bw_A + bw_B) : 64);
    uint64_t mask_a = (bw_A == 64 ? -1 : ((1ULL << bw_A) - 1));
	uint64_t mask_b = (bw_B == 64 ? -1 : ((1ULL << bw_B) - 1));
	uint64_t mask_c = (bw_C == 64 ? -1 : ((1ULL << bw_C) - 1));
    
    RSSVectorMyType a_extend(rows * common_dim, make_pair(0,0)), b_transpose(common_dim * columns, make_pair(0,0));
    //对A做符号扩展或零扩展（TODO: 实际上应该是位宽更大的一方进行扩展）
    // cout<<"extend matrix a."<<endl;
    // z_extend(a, a_extend, bw_A, bw_A + extra_bits, rows * common_dim);
    // cout<<"in function matMult, a_extend finished."<<endl;
    // print_RSSVectorMyType(a_extend, "extended matrix a:");
    // A矩阵保持不变，B转置
    cout<<"transpose matrix b."<<endl;
    // matrix_transpose(b, b_transpose, common_dim, columns);
    for (int i = 0; i < columns; i++) {
        for (int j = 0; j < common_dim; j++) {
            b_transpose[i * common_dim + j].first = b[j * columns + i].first;
            b_transpose[i * common_dim + j].second = b[j * columns + i].second;
        }
    }
    cout<<"in function matMult, transpose finished!"<<endl;

    // A提取出来rows个common_dim维的向量，B转置后提取出来column个common_dim维的向量
    // i:rows循环——>j:columns循环：res[i][j]=A向量[i] dotProduct B向量j

    RSSVectorMyType a_slice(common_dim, make_pair(0,0)), b_slice(common_dim, make_pair(0,0)), tmp(common_dim, make_pair(0,0)), tmp_extend(common_dim, make_pair(0,0));
    // c[i][j] = a第i个common_dim维向量 dotProduct b(after transpose)第j个common_dim维向量

    //
    for (int i = 0; i < rows; ++i)
    {
        cout<<"\n/*******************************************************************/\n"<<endl; 
        cout<<"\ni="<<i<<endl;
        getSliceRSSVectorMyType(a, a_slice, i*common_dim, (i+1)*common_dim);
        print_RSSVectorMyType(a_slice, "a_slice=");
        for (int j = 0; j <columns; ++j)
        {
            cout<<"\nj="<<j<<endl;
            cout<<"getSliceRSSVectorMyType(b_transpose, b_slice, j, j+common_dim);"<<endl;
            getSliceRSSVectorMyType(b_transpose, b_slice, j*common_dim, (j+1)*common_dim);
            print_RSSVectorMyType(b_slice, "b_slice=");

            cout<<"\ncalculating the[i][j]th term without accumulate:";
            vectorMult_nu(a_slice, b_slice, tmp, bw_A, bw_B, bw_C, common_dim);
            cout<<"finished calculating the[i][j]th term without accumulate.";
            print_RSSVectorMyType(tmp, "value of tmp:");
            /*此处注意： 计算完之后，进行accumulate操作时，对于tmp[i]各分量相加的wrap值是不要的，而由于累加带来的进位是要保留的（在更大的位宽bwa+bwb+extrabits）（该问题是由于位宽会扩大造成的），这种情况下不能直接加，所以考虑先将结果进行零扩展，再累加时产生的进位会因为位宽限制不用再考虑*/
            z_extend(tmp, tmp_extend, bw_A+bw_B, bw_A+bw_B+extra_bits, common_dim);

            c[i*columns + j] = make_pair(0, 0);

            for (int k = 0; k < common_dim; ++k){
                c[i*columns + j].first += tmp_extend[k].first;
                c[i*columns + j].second += tmp_extend[k].second;
            }
            cout<<"finished calculating the[i][j]th term accumulated.";
            cout<<"c["<<i<<"]["<<j<<"]="<<+c[i*columns + j].first<<", "<<+c[i*columns + j].second<<endl;
        }
    }
    bw_C = (((bw_A + bw_B + extra_bits) < 64) ? (bw_A + bw_B + extra_bits) : 64);
	mask_c = (bw_C == 64 ? -1 : ((1ULL << bw_C) - 1));
    for (int i = 0; i < rows*columns; ++i)
    {
        c[i].first &= mask_c;
        c[i].second &= mask_c;
    }

    //TODO: 截断在什么地方用？
}

//其它构建块


//除法

//sigmoid

//tanh

//ReLU

//maxpool














