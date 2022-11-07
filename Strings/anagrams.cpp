// Solution to https://cses.fi/problemset/task/1622/
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

string S;
set<string> P[2];
int f[26], g[26];

inline void generate(int i){
    P[i & 1].clear();
    for(string s : P[1 - (i & 1)]){
        memset(g, 0, 26 * sizeof(int));
        for(char c : s){
            ++g[c - 'a'];
        }
        loop(j, 26){
            if(g[j] < f[j]){
                string t = s;
                t.append(1u, 'a' + j);
                P[i & 1].emplace(t);
            }
        }
    }
}

// Stores the anagrams in P[n & 1] (Time: O(|s|*|s|!*log(|S|)))
inline void compute_anagrams(int n = S.size()){
    P[0].emplace("");
    for(int l = 1; l <= n; ++l){
        generate(l);
    }
}

int main(){
    /*
    auto start = chrono::high_resolution_clock::now();
    */
    
    ios_base::sync_with_stdio(false);   // unsync C- and C++-streams (stdio, iostream)
    cin.tie(NULL);  // untie cin from cout (no automatic flush before read)
    cin >> S;
    memset(f, 0, 26 * sizeof(int));
    int n = S.size();
    for(char c : S){
        ++f[c - 'a'];
    }
    compute_anagrams();
    cout << P[n & 1].size() << endl;
    for(string s : P[n & 1]){
        cout << s << endl;
    }

    /*
    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
    cout << duration.count() << endl;
    */
    return 0;
}
