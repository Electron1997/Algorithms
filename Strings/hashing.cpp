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

const int N = 1e6;
// Collision probability ~ (# comparisons) / (2 * mod.f * mod.s)
const pair<ull, ull> b = {29, 31}, mod = {1e9 + 7, 1e9 + 9};

string s, t;
pair<ull, ull> h[N], p[N];

template <typename T,typename U>                                                   
pair<T,U> operator + (const pair<T,U>& l,const pair<T,U>& r){   
    return {l.f + r.f, l.s + r.s};                                    
}

template <typename T,typename U>                                                   
pair<T,U> operator - (const pair<T,U>& l,const pair<T,U>& r){   
    return {l.f - r.f, l.s - r.s};                                    
}

template <typename T,typename U>                                                   
pair<T,U> operator * (const pair<T,U>& l,const pair<T,U>& r){   
    return {l.f * r.f, l.s * r.s};                                    
}

template <typename T,typename U>                                                   
pair<T,U> operator % (const pair<T,U>& l,const pair<T,U>& r){   
    return {l.f % r.f, l.s % r.s};                                    
}

// If working with strings of different sizes avoid 0
inline pair<ull, ull> index(char c){
    return {c - 'a' + 1, c - 'a' + 1};
}

// Precompute powers of b and polynomial hash of every prefix of s in O(n)
inline void hash_prefixes(int n){
    p[0] = {1, 1};
    h[0] = index(s[0]);
    for(int i = 1; i < n; ++i){
        p[i] = p[i - 1] * b % mod;
        h[i] = (h[i - 1] + index(s[i]) * p[i] % mod) % mod;
    }
}

// Returns hash of s[l:r] (r included) multiplied by p^l in O(1)
inline pair<ull, ull> hash_substr(int l, int r){
    if(l == 0){
        return h[r];
    }
    return (h[r] + (mod - h[l - 1])) % mod;
}

int main(){
    /*
    auto start = chrono::high_resolution_clock::now();
    */
    
    ios_base::sync_with_stdio(false);   // unsync C- and C++-streams (stdio, iostream)
    cin.tie(NULL);  // untie cin from cout (no automatic flush before read)

    cin >> s >> t;
    int n = s.size(), m = t.size();
    hash_prefixes(n);
    pair<ull, ull> h_t = {0, 0};
    loop(i, m){
        h_t = (h_t + index(t[i]) * p[i] % mod) % mod;
    }
    int sol = 0;
    loop(i, n - m + 1){
        if(hash_substr(i, i + m - 1) == (h_t * p[i]) % mod){
            ++sol;
        }
    }
    cout << sol << endl;

    /*
    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
    cout << duration.count() << endl;
    */
    return 0;
}
