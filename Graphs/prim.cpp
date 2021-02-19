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


// Time: O(m + nlog(n)) where n = |V|, m = |E|
ll prim(vector<ip> G[], int n){
	priority_queue<ip, vector<ip>, greater<ip> > H;
	bool done[n];
	memset(done, false, n * sizeof(done[0]));
	done[0] = true;
	for(ip p : G[0]){
		H.push({p.s, p.f});
	}
	ll mst = 0;
	while(!H.empty()){
		ip p = H.top();
		H.pop();
		if(!done[p.s]){
			mst += p.f;
			done[p.s] = true;
			for(ip q : G[p.s]){
				if(!done[q.f]){
					H.push({q.s, q.f});
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
	printf("%lld", prim(G, n));
}