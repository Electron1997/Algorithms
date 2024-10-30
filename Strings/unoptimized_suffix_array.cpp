// Solution to https://codeforces.com/edu/course/2/lesson/2/3/practice/contest/269118/problem/B
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
 
/*  // SET WITH INDEXING
// Implements logarithmic find_by_order() and order_of_key()
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> indexed_set;
*/
 
/*  // RANDOM NUMBER GENERATOR
// rng() generates u.a.r. from [0, 2^32 - 1]
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
*/

// Space: O(n), Time: O(nlog^2(n)) often with good constant
// Time O(nlog(n)) is possible with counting based radix sort
constexpr size_t N = 3e5;
 
int l, n, suf[N + 1], c[N + 1], aux[N + 1];
 
string s;
 
inline bool cmp(const int i, const int j){
    if(c[i] == c[j]){
        return c[(i + l) % n] < c[(j + l) % n];
    }
    return c[i] < c[j];
}

inline void comp_suf(){
    s += '$';
    n = s.size();
    loop(i, n){
        c[i] = s[i] - '$';
    }
    l = 1;
    iota(suf, suf + n, 0);
    while(l < n){
        sort(suf, suf + n, cmp);
        int k = 0;
        aux[suf[0]] = 0;
        for(int i = 1; i < n; ++i){
            k += cmp(suf[i - 1], suf[i]);
            aux[suf[i]] = k;
        }
        loop(i, n) c[i] = aux[i];
        l <<= 1;
    }
}
 
int main(){
    /*
    auto start = chrono::high_resolution_clock::now();
    */
    
    ios_base::sync_with_stdio(false);   // unsync C- and C++-streams (stdio, iostream)
    cin.tie(NULL);  // untie cin from cout (no automatic flush before read)

    cin >> s;
    comp_suf();
    int m; cin >> m;
    loop(i, m){
        string p; cin >> p;
        int l = 0, r = n - 1;
        while(l < r){
            int m = (l + r + 1) / 2;
            if(s.substr(suf[m], p.size()) < p){
                l = m;
            }else{
                r = m - 1;
            }
        }
        int L = 0, R = n;
        while(L < R){
            int M = (L + R) / 2;
            if(p < s.substr(suf[M], p.size())){
                R = M;
            }else{
                L = M + 1;
            }
        }
        cout << L - l - 1 << endl;
    }
 
    /*
    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
    cout << duration.count() << endl;
    */
    return 0;
}
