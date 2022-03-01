
#include "Precompute.h"
using namespace std;
smallType seed[64] = {
    '0','1','2','3','4','5','6','7','8','9',
    'A','B','C','D','E','F','G','H','I','J',
    'K','L','M','N','O','P','Q','R','S','T',
    'U','V','W','X','Y','Z','a','b','c','d',
    'e','f','g','h','i','j','k','l','m','n',
    'o','p','q','r','s','t','u','v','w','x',
    'y','z','\0','\0'
};

void emptyPrecomputeInit(){
	cout<<"the void precompute initialize function."<<endl;
}




//生成0的共享值，z存放结果，生成的随机数都是Mod 2^length意义下的
void getSharedZero(RSSVectorMyType &z, int bw){
	size_t size = z.size();
	uint64_t ra[size], rb[size], rc[size] = {};
	uint64_t ring = (1<<bw);
	for(int i=0; i< size; ++i){
		srand((int)(time(0)));
		ra[i] = (rand() % ring);
		srand((int)(time(0)));
		rb[i] = rand() % ring;
		rc[i] = (ring - (ra[i] + rb[i]) % ring) % ring;
	}
	//分ABC三方赋值
	if (partyNum == PARTY_A){
		for(int i=0; i<size; ++i){
			z[i].first = ra[i];
			z[i].second = rb[i];
		}
	}
	if (partyNum == PARTY_B){
		for(int i=0; i<size; ++i){
			z[i].first = rb[i];
			z[i].second = rc[i];
		}
	}
	if (partyNum == PARTY_C){
		for(int i=0; i<size; ++i){
			z[i].first = rc[i];
			z[i].second = ra[i];
		}
	}
}


void getSharedRandomNum(RSSVectorMyType &r, int bw){
	size_t size = r.size();
	uint64_t ra[size], rb[size], rc[size] = {};
	uint64_t ring = (1<<bw);
	for(int i=0; i< size; ++i){
		srand((int)(time(0)));
		ra[i] = (rand() % ring);
		srand((int)(time(0)));
		rb[i] = rand() % ring;
		srand((int)(time(0)));
		rc[i] = rand() % ring;
	}
	//分ABC三方赋值
	if (partyNum == PARTY_A){
		for(int i=0; i<size; ++i){
			r[i].first = ra[i];
			r[i].second = rb[i];
		}
	}
	if (partyNum == PARTY_B){
		for(int i=0; i<size; ++i){
			r[i].first = rb[i];
			r[i].second = rc[i];
		}
	}
	if (partyNum == PARTY_C){
		for(int i=0; i<size; ++i){
			r[i].first = rc[i];
			r[i].second = ra[i];
		}
	}
}


/**
 * 生成一个非共享形式的随机数向量
 * @param 
 * r:存放结果
 * bw：最终位宽
 * @return 
 */
void getRandomNum(std::vector<myType> &r, int32_t bw){
	size_t size = r.size();
	uint64_t mask = (bw == 64 ? -1 : ((1ULL << bw) - 1));
	uint64_t ring = (1<<bw);
	for(int i=0; i< size; ++i){
		srand((int)(time(0)));
		r[i] = (rand() % ring) & mask;
	}
}

void getRandomNum(std::vector<uint8_t> &r, int32_t bw){
	size_t size = r.size();
	uint64_t mask = (bw == 64 ? -1 : ((1ULL << bw) - 1));
	uint64_t ring = (1<<bw);
	for(int i=0; i< size; ++i){
		srand((int)(time(0)));
		r[i] = (rand() % ring) & mask;
	}
}

// Currently, 全都等于0(bushi)
// r = 3 and rPrime = 3 * d
// TODO: ReLU produces a bug with this. Why? funcRELU does not even call getDividedShares()
//这里应该是需要完善的，因为precompute里面全是直接分配的0
//这里是计算得到0的共享形式以及共享的截断形式,rPrime就是r'

//为了获得截断对共享下的随机数r'和截断之后的r
void getDividedShares(RSSVectorMyType &r, RSSVectorMyType &rPrime, size_t bw, size_t size)
{
	assert(r.size() == size && "r.size is incorrect");
	assert(rPrime.size() == size && "rPrime.size is incorrect");

	//get r'
	getSharedRandomNum(rPrime, 64);
	//truncate r' to get r
	for (int i = 0; i < size; ++i){
		// r[i].first 
		r[i].first = rPrime[i].first >> bw;
		r[i].second = rPrime[i].second >> bw;
	}

	// for (int i = 0; i < size; ++i)
	// {
	// 	r[i].first = 0;
	// 	r[i].second = 0;
	// 	rPrime[i].first = 0;
	// 	rPrime[i].second = 0;
	// 	// r[i].first = 1;
	// 	// r[i].second = 1;
	// 	// rPrime[i].first = d;
	// 	// rPrime[i].second = d;		
	// }
}


//获取一个随机字符
smallType getRandomChar(){
	// 将用于为随机数引擎获得种子
	static std::random_device rd;
	// 以播种标准 mersenne_twister_engine
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<> dis(0, 61);
    return seed[dis(gen)];
}

//获取0的布尔共享还是随机数的布尔共享？多少位？
//计算FuncWrap的时候会用到！！！
//获取zero-Booleanshare
void getRandomBitShares(RSSVectorSmallType &a, size_t size)
{
	assert(a.size() == size && "size mismatch for getRandomBitShares");

	//全部赋值为0
	// for(auto &it : a)
	// 	it = std::make_pair(0,0);
	
	//首先，生成两个随机字符的vector:b1,b2
	//两个字符异或就能得到第三个字符c
	smallType b1[size], b2[size], c[size] = {};
	for(int i =0; i<size; ++i){
		b1[i] = getRandomChar();
		b2[i] = getRandomChar();
		c[i] = b1[i] ^ b2[i];
	}
	
	//分三方进行赋值
	if (partyNum == PARTY_A){
		for(int i=0; i<size; ++i){
			a[i].first = b1[i];
			a[i].second = b2[i];
		}
	}
	if (partyNum == PARTY_B){
		for(int i=0; i<size; ++i){
			a[i].first = b2[i];
			a[i].second = c[i];
		}
	}
	if (partyNum == PARTY_C){
		for(int i=0; i<size; ++i){
			a[i].first = c[i];
			a[i].second = b1[i];
		}
	}
}

//m_0 is random shares of 0, m_1 is random shares of 1 in RSSMyType. 
//This function generates random bits c and corresponding RSSMyType values m_c
void getSelectorBitShares(RSSVectorSmallType &c, RSSVectorMyType &m_c, size_t size)
{
	assert(c.size() == size && "size mismatch for getSelectorBitShares");
	assert(m_c.size() == size && "size mismatch for getSelectorBitShares");
	for(auto &it : c)
		it = std::make_pair(0,0);

	for(auto &it : m_c)
		it = std::make_pair(0,0);
}

//Shares of random r, shares of bits of that, and shares of wrap3 of that.
void getShareConvertObjects(RSSVectorMyType &r, RSSVectorSmallType &shares_r, RSSVectorSmallType &alpha, size_t size)
{
	assert(shares_r.size() == size*BIT_SIZE && "getShareConvertObjects size mismatch");
	for(auto &it : r)
		it = std::make_pair(0,0);

	for(auto &it : shares_r)
		it = std::make_pair(0,0);

	for(auto &it : alpha)
		it = std::make_pair(0,0);
}

//a * b = c
//Triplet verification myType，三个矩阵不一定同型
void getTriplets(RSSVectorMyType &a, RSSVectorMyType &b, RSSVectorMyType &c, 
						size_t rows, size_t common_dim, size_t columns)
{
	assert(((a.size() == rows*common_dim) 
		and (b.size() == common_dim*columns) 
		and (c.size() == rows*columns)) && "getTriplet size mismatch");
	
	for(auto &it : a)
		it = std::make_pair(0,0);

	for(auto &it : b)
		it = std::make_pair(0,0);

	for(auto &it : c)
		it = std::make_pair(0,0);
}

//Triplet verification myType，三个同型矩阵
void getTriplets(RSSVectorMyType &a, RSSVectorMyType &b, RSSVectorMyType &c, size_t size)
{
	assert(((a.size() == size) and (b.size() == size) and (c.size() == size)) && "getTriplet size mismatch");
	
	for(auto &it : a)
		it = std::make_pair(0,0);

	for(auto &it : b)
		it = std::make_pair(0,0);

	for(auto &it : c)
		it = std::make_pair(0,0);
}

//Triplet verification smallType
void getTriplets(RSSVectorSmallType &a, RSSVectorSmallType &b, RSSVectorSmallType &c, size_t size)
{
	assert(((a.size() == size) and (b.size() == size) and (c.size() == size)) && "getTriplet size mismatch");
	
	for(auto &it : a)
		it = std::make_pair(0,0);

	for(auto &it : b)
		it = std::make_pair(0,0);

	for(auto &it : c)
		it = std::make_pair(0,0);
}
