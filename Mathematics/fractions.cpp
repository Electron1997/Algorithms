#include <bits/stdc++.h>

#define f first
#define s second
#define loop(i, n) for (int i = 0; i < n; ++i)
#define read(a, n) loop($, n) cin >> a[$];
#define show(a, n)                  \
    loop($, n) cout << a[$] << " "; \
    cout << endl;

using namespace std;

typedef long long ll;
typedef unsigned long long ull;

/*
// SET WITH INDEXING
// Implements logarithmic find_by_order() and order_of_key()
// erase does not work with less_equal<T>!
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;

template<typename T>
using indexed_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
*/

/*  // RANDOM NUMBER GENERATOR
// rng() generates u.a.r. from [0, 2^32 - 1]
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
*/

template <typename T>
concept Numeric = requires(T a, T b) {
    { a + b } -> std::same_as<T>;  // Must support addition
    { a * b } -> std::same_as<T>;  // Must support multiplication
    { a / b } -> std::same_as<T>; // Must support division
	  { a < b } -> std::convertible_to<bool>;  // Must support <
    { a <= b } -> std::convertible_to<bool>; // Must support <=
	  { a == b } -> std::convertible_to<bool>; // Must support ==
};

template <Numeric T>
struct frac{

	T num, den;
	
	frac() {}
	frac(T num) : num(num), den(1) {}
	frac(T num, T den) : num(num), den(den) {}
	
	void reduce(){
		T d = gcd(num, den);
		num /= d;
		den /= d;
	}
	
	frac operator + (const frac& other) const {
		T g = gcd(den, other.den);
		T sum_num = num * other.den / g + other.num * den / g;
		T sum_den = den * other.den / g;
		return frac(sum_num, sum_den);
	}
	
	frac operator * (const frac& other) const {
		return frac(num * other.num, den * other.den);
	}

	bool operator == (const frac& other) const {
		return num * other.den == other.num * den;
	}

	bool operator < (const frac& other) const {
		return num * other.den < other.num * den;
	}

	bool operator <= (const frac& other) const {
		return num * other.den <= other.num * den;
	}

	friend std::ostream& operator << (std::ostream& os, const frac& val){
		os << val.num << "/" << val.den;
		return os;
	}

};

frac<ull> best[1 << 8];

int main(){
    /*
    auto start = chrono::high_resolution_clock::now();
    */
    
    ios_base::sync_with_stdio(false);   // unsync C- and C++-streams (stdio, iostream)
    cin.tie(NULL);  // untie cin from cout (no automatic flush before read)

	int n; cin >> n;
	int twos = 0;
	while(n % 2 == 0){
		n /= 2;
		++twos;
	}
	vector<int> odd_factors;
	for(int i = 3; i * i <= n; i += 2){
		while(n % i == 0){
			odd_factors.push_back(i);
			n /= i;
		}
	}
	if(n > 1) odd_factors.push_back(n);
	best[0] = frac<ull>(0);
	int b = 1 << odd_factors.size();
	for(int i = 1; i < b; ++i){
		ull l = 0, k = 1;
		while(1 << l <= i){
			if((1 << l) & i) k *= odd_factors[l];
			++l;
		}
		while(1 << l <= k) ++l;
		best[i] = frac(l * (1 << l), k); best[i].reduce();
		for(int j = 1; j < b; ++j){
			if(!((i | j) & ~i))
				best[i] = min(best[i], best[j] + best[i ^ j]);
		}
	}		
	cout << best[b - 1] + frac<ull>(twos) << endl;

	/*
    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
    cout << duration.count() << endl;
    */
    return 0;
}
