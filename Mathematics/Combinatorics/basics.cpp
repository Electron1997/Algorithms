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

/*	// RANDOM NUMBER GENERATOR
// rng() generates u.a.r. from [0, 2^32 - 1]
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
*/

/* // TIME
auto start = chrono::high_resolution_clock::now();
// ...
auto stop = chrono::high_resolution_clock::now();
auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
cout << duration.count() << endl;
*/

// Time: O(min(k, n - k))
ull binomial_coefficient(ull n, ull k){
    if(n < k){
        return 0;
    }
    k = min(k, n - k);
    ull bc = 1;
    for(int i = 0; i < k; ++i){
        bc *= n - i;
        bc /= i + 1;
    }
    return bc;
}

// Time: O(n)
ull catalan(ull n){
    return binomial_coefficient(2 * n, n) / (n + 1);
}

// Time: O(n)
ull factorial(ull n){
    ull f = 1;
    for(int i = 1; i <= n; ++i){
        f *= i;
    }
    return f;
}

// Time: O(n)
ull fibonacci(ull n){
    ull f_0 = 0, f_1 = 1;
    for(int i = 0; i < n; ++i){
        f_1 += f_0;
        f_0 = f_1 - f_0;
    }
    return f_0;
}

// Time: O(log(n))
ull power(ull a, ull b){
    ull p = 1;
    while(b){
        if(b & 1){
            p *= a;
        }
        a *= a;
        b >>= 1;
    }
    return p;
}

// Time: O(n)
ull subfactorial(ull n){
    ull s_0 = 1, s_1 = 0;
    for(int i = 1; i <= n; ++i){
        ull temp = i * (s_0 + s_1);
        s_0 = s_1;
        s_1 = temp;
    }
    return s_0;
}
