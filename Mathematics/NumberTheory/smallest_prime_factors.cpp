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

const int N = 100005;

int spf[N];

// Time: O(nlog(log(n)))
inline void precompute_spf(int n = N){
    loop(i, N) spf[i] = 0;
    for(int i = 2; i < N; i += 2){
        spf[i] = 2;
    }
    for(int d = 3; d < N; d += 2){
        for(int i = d; i < N; i += d){
            if(!spf[i]){
                spf[i] = d;
            }
        }
    }
}

// Time: O(log(n))
inline map<int, int> factorize(int n){
    map<int, int> factorization;
    while(spf[n]){
        ++factorization[spf[n]];
        n /= spf[n];
    }
    return factorization;
}

int main(){
    /*
    auto start = chrono::high_resolution_clock::now();
    */
    
    ios_base::sync_with_stdio(false);   // unsync C- and C++-streams (stdio, iostream)
    cin.tie(NULL);  // untie cin from cout (no automatic flush before read)

    precompute_spf();
    
    int T;
    cin >> T;
    loop(t, T){
        int n;
        cin >> n;
        map<int, int> factorization = factorize(n);
        cout << n << " = ";
        for(pair<int, int> p : factorization){
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
