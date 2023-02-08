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

const int N = 2e6;
// Collision probability ~ (# comparisons) / (2 * mod.f * mod.s)
const pair<ull, ull> b = {29, 31}, mod = {1e9 + 7, 1e9 + 9};

string s;
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

// Precompute powers of b and polynomial hash of every prefix of s
// Time: O(1)
inline void hash_prefixes(int n){
    p[0] = {1, 1};
    h[0] = index(s[0]);
    for(int i = 1; i < n; ++i){
        p[i] = p[i - 1] * b % mod;
        h[i] = (h[i - 1] + index(s[i]) * p[i] % mod) % mod;
    }
}

// Returns hash of s[l:r] (r included) multiplied by p^l
// Time: O(1)
inline pair<ull, ull> hash_substr(int l, int r){
    if(l == 0){
        return h[r];
    }
    return (h[r] + (mod - h[l - 1])) % mod;
}

// Returns true iff s[i1:i1+sz1] is not lexicographically smaller than s[i2:i2+sz2]
// Time: O(min(s1, s2))
inline bool cmp(int i1, int sz1, int i2, int sz2){
    int l = 0, r = min(sz1, sz2);
    while(l < r){
        int m = (l + r + 1) / 2;
        if(hash_substr(i1, i1 + m - 1) * p[i2] % mod == hash_substr(i2, i2 + m - 1) * p[i1] % mod){
            l = m;
        }else{
            r = m - 1;
        }
    }
    if(l == min(sz1, sz2)){
        return sz1 <= sz2;
    }
    return s[i1 + l] <= s[i2 + l];
}

int main(){
    /*
    auto start = chrono::high_resolution_clock::now();
    */
    
    ios_base::sync_with_stdio(false);   // unsync C- and C++-streams (stdio, iostream)
    cin.tie(NULL);  // untie cin from cout (no automatic flush before read)

    string t; cin >> t;
    int n = t.size();
    s = string(2 * n, '-');
    copy(t.begin(), t.end(), copy(t.begin(), t.end(), s.begin()));
    hash_prefixes(2 * n);
    int sol = 0;
    for(int i = 1; i < n; ++i){
        if(cmp(i, n, sol, n)){
            sol = i;
        }
    }
    cout << s.substr(sol, n) << endl;

    /*
    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
    cout << duration.count() << endl;
    */
    return 0;
}
