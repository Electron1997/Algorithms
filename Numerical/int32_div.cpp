#include<iostream>
#include<utility>
#include<stdint.h>

using namespace std;

// Returns {0xFFFFFFFF, num} if den is 0
pair<uint32_t, uint32_t> my_udiv(uint32_t num, uint32_t den){
	uint64_t n = num, d = den;
	d <<= 31;
	uint32_t q = 0;
	for(int i = 0; i < 32; ++i){
		q <<= 1;
		if(d <= n){
			q |= 1;
			n -= d;
		}
		d >>= 1;
	}
	return {q, (uint32_t)n};
}

// Returns {q, r} s.t. num = q * den + r w. 0 <= r < den
pair<int32_t, int32_t> my_div(int32_t num, int32_t den){
	uint32_t n = abs(num), d = abs(den);
	pair<int32_t, int32_t> qr = my_udiv(n, d);
	int32_t sgn_num = num >> 31, sgn_den = den >> 31;
	if(sgn_num ^ sgn_den){
		qr.first = -qr.first;
		if(sgn_num){
			--qr.first;
			qr.second = den - qr.second;
		}
	} 	
	return qr;
}

int main(){
	int32_t num, den;
	cin >> num >> den;
	pair<int32_t, int32_t> qr = my_div(num, den);
	cout << qr.first << " " << qr.second << endl;
	return 0;
}
