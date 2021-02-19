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
typedef pair<int, int> ip;

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

// Maximum number of elements in the DSU
const int N = 10005;

int par[N], h[N], comp;

// Time: O(n)
void init(int n = N){
	comp = n;
	loop(i, n){
		par[i] = i;
		h[i] = 1;
	}
}

// Time: ~O(1)
int find(int i){
	if(par[i] == i){
		return i;
	}
	par[i] = find(par[i]);
	return par[i];
}

// Time: O(1)
void unite(int i, int j){
	int s = find(i);
	int t = find(j);
	if(s != t){
		--comp;
		if(h[t] > h[s]){
			swap(s, t);
		}else if(h[t] == h[s]){
			++h[s];
		}
		par[t] = s;
	}
}

// Time: O(mlog(n)) where n = |V|, m = |E|
ll boruvka(vector<ip> G[], int n){
	init(n);
	ll mst = 0;
	while(comp > 1){
		ip e[n];
		loop(i, n){
			e[i] = {-1, INT_MAX};
		}
		loop(i, n){
			int u = find(i);
			for(ip p : G[i]){
				int v = find(p.f);
				if(u != v && p.s < e[u].s){
					e[u] = {v, p.s};
				}
			}
		}
		loop(i, n){
			int u = find(i);
			if(u == i){
				int v = find(e[u].f);
				if(u != v){
					mst += e[u].s;
					unite(u, v);
				}
			}
		}
	}
	return mst;
}

int main(){
	int n, m;
	scanf("%d %d", &n, &m);
	vector<ip> G[n];
	loop(i, m){
		int u, v, w;
		scanf("%d %d %d", &u, &v, &w);
		G[u].push_back({v, w});
		G[v].push_back({u, w});
	}
	printf("%lld", boruvka(G, n));
}