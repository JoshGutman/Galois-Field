#include <string>

using namespace std;

#ifndef GF_H
#define GF_H

class GF {

public:
	GF(unsigned int);
	GF(string);
	unsigned int multiply(unsigned int, unsigned int);
	unsigned int mod(unsigned int, unsigned int);

private:
	unsigned int mostSignificantBit(unsigned int);
	string removeAll(char, string);
	unsigned int px;

};



#endif
