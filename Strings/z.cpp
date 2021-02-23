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

/* Computes the Z function of s (Time: O(|s|))
   For i > 0, z[i] is the length of the longest substring s[i:x] that is a prefix of s,
   whereas z[0] := 0.
*/
void Z(string& s, int z[]){
    int n = s.size();
    z[0] = 0;
    for(int i = 1, l = -1, r = -1; i < n; ++i){
        if(i <= r){
            z[i] = min(z[i - l], r - i + 1);
        }else{
            z[i] = 0;
        }
        while(i + z[i] < n && s[z[i]] == s[i + z[i]]){
            ++z[i];
        }
        if(i + z[i] - 1 > r){
            l = i;
            r = i + z[i] - 1;
        }
    }
}

int main(){
	/*	// IO
	ios_base::sync_with_stdio(false);	// unsync C- and C++-streams (stdio, iostream)
	cin.tie(NULL);	// untie cin from cout (no automatic flush before read)
	*/
    string pat, txt;
    cin >> txt >> pat;
    int n = pat.size(), m = pat.size() + txt.size();
    pat += txt;
    int z[m], cnt = 0;
    Z(pat, z);
    loop(i, m){
        if(z[i] >= n){
            ++cnt;
        }
    }
    cout << cnt << endl;
    return 0;
}