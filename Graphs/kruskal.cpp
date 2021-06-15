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

template<int N = 100005>
struct dsu {

	int par[N], size[N];

	dsu(int n = N){
		for(int i = 0; i < n; ++i){
			par[i] = i;
			size[i] = 1;
		}
	}

	// Time: ~O(1)
	int find(int i){
	    if(par[i] != i){
	        par[i] = find(par[i]);
	    }
	    return par[i];
	}

	// Time: ~O(1)
	void join(int i, int j){
	    int s = find(i);
	    int t = find(j);
	    if(s != t){
	        if(size[s] > size[t]){
	            swap(s, t);
	        }
	        par[s] = t;
	        size[t] += size[s];
	    }
	}

	// Time: O(n)
	void reset(int n = N){
	    loop(i, n){
	        par[i] = i;
	        size[i] = 1;
	    }
	}

};

// Time: O(mlog(n)) where n = |V|, m = |E|
ll kruskal(edge e[], int n, int m){
	dsu<> *uf = new dsu<>(n);
	sort(e, e + m);
	int i = 0, k = n - 1;
	ll mst = 0;
	while(k > 0){
		while(uf->find(e[i].u) == uf->find(e[i].v)){
			++i;
			if(i == m){
				return -1;
			}
		}
		mst += e[i].w;
		uf->join(e[i].u, e[i].v);
		--k;
	}
	delete uf;
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
