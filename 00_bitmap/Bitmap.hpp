#include <string.h>
#include <stdio.h>
#define Rank int

class Bitmap{
private:
	unsigned char * M;
	Rank N,_sz;//N*sizeof(char)*8个比特中含有_sz个有效位
protected:
	void init(Rank n){
		M = new unsigned char[N = (n+7)/8];
		memset(M, 0, N);
		_sz = 0; 
	}
public:
	Bitmap(int n = 8){ 
		M = new unsigned char[N = (n+7)/8]; 
		memset(M ,0 ,N);
	}
	//void *memset(void *ptr, int value, size_t num);	
	//ptr：指向要设置的内存块起始地址。
	//value：要填充的值（会被转换成 unsigned char 后填充）。
	//num：要设置的字节数。
	Bitmap(char* file ,Rank n = 8){//从指定文件中读取位图
		init(n);
		FILE* fp = fopen(file, "r");
		fread(M, sizeof(char),N,fp);
		//size_t fread(void *ptr, size_t size, size_t count, FILE *stream);
		// **ptr**：目标缓冲区指针，读到的数据会存放在这里。
		//**size**：每个元素的大小（单位：字节）。
		//**count**：要读取多少个这样的元素。  
		//**stream**：文件指针。
		fclose(fp);
		for(Rank k = 0,_sz = 0; k<n;k++)
			_sz += test(k);
	}
	~Bitmap(){delete[] M; M = nullptr;}
	void expand(Rank k);
	void dump(char* file);
	char* bit2string( Rank n );
	void set(int k);
	void clear(int k);
	bool test(int k);
};


bool Bitmap::test(int k){
	return M[k>>3] & (0x80 >>(k & 0x07));
}


void Bitmap::set(int k){
	if(test(k)) return;
	expand(k);
	_sz++;
	M[k>>3] |= (0x80 >> (k&0x07));
}
void Bitmap::clear(int k){
	if(!test(k)) return;
	expand(k);
	_sz--;
	M[k>>3] &= ~(0x80 >> (k&0x07));
}

void Bitmap::dump( char* file ){ //将位图整体导出至指定的文件，以便对此后的新位图批量初始化
	 FILE* fp = fopen( file, "w" ); 
	 fwrite( M, sizeof ( char ), N, fp ); 
	 fclose( fp ); 
}
char* Bitmap::bit2string( Rank n ) { //将前n位转换为字符串——
	expand( n - 1 ); //此时可能被访问的最高位为bitmap[n - 1]
	char* s = new char[n + 1]; s[n] = '\0'; //字符串所占空间，由上层调用者负责释放
	for ( Rank i = 0; i < n; i++ ) s[i] = test( i ) ? '1' : '0';
	return s; //返回字符串位置
}
void Bitmap::expand( Rank k ) { //若被访问的Bitmap[k]已出界，则需扩容
	if ( k < 8 * N ) return; //仍在界内，无需扩容
	Rank oldN = N; unsigned char* oldM = M;
	init( 2 * k ); //与向量类似，加倍策略
	safe_memcpy( M, N, oldM, oldN );
	delete[] oldM; //原数据转移至新空间
}

int safe_memcpy(void* dest, size_t destsz, const void* src, size_t count) {
    if (count > destsz) {
        // 相当于 memcpy_s 的安全保护
        memset(dest, 0, destsz);
        return -1; // 表示失败
    }
    memcpy(dest, src, count);
    return 0; // 成功
}
