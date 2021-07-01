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

/*  // RANDOM NUMBER GENERATOR
// rng() generates u.a.r. from [0, 2^32 - 1]
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
*/

// Time: O(sqrt(n))
inline map<ull, int> factorize(ull n){
    map<ull, int> factorization;
    while(n % 2 == 0){
        ++factorization[2];
        n /= 2;
    }
    for(ull f = 3; f * f <= n; f += 2){
        while(n % f == 0){
            ++factorization[f];
            n /= f;
        }
    }
    if(n != 1){
        ++factorization[n];
    }
    return factorization;
}

int main(){
    /*
    auto start = chrono::high_resolution_clock::now();
    */
    
    ios_base::sync_with_stdio(false);   // unsync C- and C++-streams (stdio, iostream)
    cin.tie(NULL);  // untie cin from cout (no automatic flush before read)

    int T;
    cin >> T;
    loop(t, T){
        ull n;
        cin >> n;
        map<ull, int> factorization = factorize(n);
        cout << n << " = ";
        for(pair<ull, int> p : factorization){
            cout << p.f << "^" << p.s << " ";
        }
        cout << endl;
    }

    /*
    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
    cout << duration.count() << endl;
    */
    return 0;
}
