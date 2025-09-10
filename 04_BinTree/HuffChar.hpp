#define N_CHAR (0x80 - 0x20)
struct HuffChar{
	char ch; int weight;
	HuffChar(char c = '^', int w = 0):ch(c), weight(w) { };
	bool operator< (HuffChar const& hc){return weight < hc.weight;}
	bool operator== (HuffChar const& hc){return weight == hc.weight;}
};

