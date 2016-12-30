#include <cmath>
#include "GF.h"


// Constructor that accepts an unsigned int
GF::GF(unsigned int px) {
	this->px = px;
}


// Constructor that accepts a polynomial in the form of a string
// Example: "x^8 + x^4 + x^3 + x + 1".  Case and spaces do not matter.
GF::GF(string px) {

	this->px = 0;

	// Remove all spaces from px
	px = removeAll(' ', px);

	// Generate int from string px
	for (int i = 0; i < px.length(); i++) {

		// x^1 or x^n+
		if (px[i] == 'x') {
			
			// x^1  -->  this.px += pow(2,1)
			if (i+1 >= px.length() || px[i+1] == '+') {
				this->px += 2;
			}

			// x^n  -->  this.px += pow(2, n)
			else {
				i+=2;
				string temp = "";
				while (i < px.length() && isdigit(px[i])) {
					temp += px[i++];
				}
				this->px += pow(2, stoi(temp));
			}
		}

		// 1  -->  this.px += 1
		else if (px[i] == '1') {
			this->px += 1;
		}
	}
}



// Galois Field multiplication
unsigned int GF::multiply(unsigned int x, unsigned int y) {

	unsigned int out = 0;
	short counter = 0;

	// Like normal binary multiplication, except XOR intermediate results instead of adding
	while (x > 0) {
		if (x & 1) {
			out ^= (y << counter);
		}
		x >>= 1;
		counter++;
	}

	// Perform result % px in order to keep the result within the closed field
	out = mod(out, this->px);

	return out;
}



// Galois Field modulus
unsigned int GF::mod(unsigned int x, unsigned int m) {
	unsigned int msbM = mostSignificantBit(m);

	// Keep XORing x by    m << ((most significant bit position of m) - (most significant bit position of x))
	// until x is less than m
	while (x > m) {
		unsigned int high = mostSignificantBit(x);
		unsigned int xpx = m << (high - msbM);
		x ^= xpx;
	}
	return x;
}



// Returns most significant bit position of x (Big Endian)
unsigned int GF::mostSignificantBit(unsigned int x) {
	int counter = 0;
	while (x > 0) {
		x >>= 1;
		counter++;
	}
	return counter;
}



// Removes all insatances of character from str
// Used in GF(string px)
string GF::removeAll(char character, string str) {
	string out;
	while (str.find(character) != -1) {
		out = str.erase(str.find(character),1);
	}
	return out;
}
