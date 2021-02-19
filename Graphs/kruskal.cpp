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

struct edge{
	int u, v, w;

	bool operator < (const edge& other) const{
		return w < other.w;
	}
};

// Maximum number of elements in the DSU
const int N = 10005;

int par[N], h[N];

// Time: O(n)
void init(int n = N){
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
		if(h[t] > h[s]){
			swap(s, t);
		}else if(h[t] == h[s]){
			++h[s];
		}
		par[t] = s;
	}
}

// Time: O(mlog(n)) where n = |V|, m = |E|
ll kruskal(edge e[], int n, int m){
	init(n); //
	sort(e, e + m);
	int i = 0, k = n - 1;
	ll mst = 0;
	while(k > 0){
		while(find(e[i].u) == find(e[i].v)){
			++i;
			if(i == m){
				return -1;
			}
		}
		mst += e[i].w;
		unite(e[i].u, e[i].v);
		--k;
	}
	return mst;
}

int main(){
	int n, m;
	scanf("%d %d", &n, &m);
	edge e[m];
	loop(i, m){
		scanf("%d %d %d", &e[i].u, &e[i].v, &e[i].w);
	}
	printf("%lld", kruskal(e, n, m));
}