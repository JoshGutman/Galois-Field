#include <cmath>
#include <iostream>
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
			if (i + 1 >= px.length() || px[i + 1] == '+') {
				this->px += 2;
			}

			// x^n  -->  this.px += pow(2, n)
			else {
				i += 2;
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



// Galois Field Division
unsigned int GF::divide(unsigned int x, unsigned int y) {

	int inverse = eea(this->px, y);
	return multiply(x, inverse);

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



// Extended Euclidian Algorithm to find modular multiplicative inverse (recursive)
int GF::eea(int a, int b) {

	int q1 = ea(a, b)[0];
	int r2 = ea(a, b)[1];
	int t2 = q1 * (-1);

	int q2 = ea(b, r2)[0];
	int r3 = ea(b, r2)[1];

	int out = ea_recurse(r2, r3, q2, t2, 1);

	if (out < 0) {
		out += a;
	}
	return out;
}

// Helper function for eea
int* GF::ea(int a, int b) {

	int out[2];
	out[0] = (a / b);
	out[1] = (a - (b*out[0]));

	return out;
}

// Helper function for eea
int GF::ea_recurse(int a, int b, int q, int t1, int t2) {
	if (b >= 1) {
		int newQ = ea(a, b)[0];
		int newR = ea(a, b)[1];
		int tempT = t2 - (t1*q);

		int x = ea_recurse(b, newR, newQ, tempT, t1);
	}
	if (b < 1) {
		return t1;
	}
}



// Removes all insatances of character from str
// Used in GF(string px)
string GF::removeAll(char character, string str) {
	string out;
	while (str.find(character) != -1) {
		out = str.erase(str.find(character), 1);
	}
	return out;
}