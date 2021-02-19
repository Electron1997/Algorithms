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

// Max size of first and second partition
const int N = 100, M = 100;

// Bipartite graph (list of neighbors for each node in first partition)
vector<int> graph[N];

// Matching (match for each node in second partition, -1 if unmatched)
int matching[M];

bool matched[N], visited[N];

// Seeks an augmenting path and improves matching if possible
bool dfs(int v){
	visited[v] = true;
	for(int w : graph[v]){
		if(matching[w] == -1 || !visited[matching[w]] && dfs(matching[w])){
			matching[w] = v;
			return true;
		}
	}
	return false;
}

// Computes maximal matching greedily
void greedy(int n, int m){
	for(int v = 0; v < n; ++v){
		for(int w : graph[v]){
			if(matching[w] == -1){
				matched[v] = true;
				matching[w] = v;
				break;
			}
		}
	}
}

// Computes maximum matching (Time: O(mn^2))
void kuhn(int n, int m){
	memset(matching, -1, m * sizeof(matching[0]));
	memset(matched, false, n * sizeof(matched[0]));
	greedy(n, m);
	for(int v = 0; v < n; ++v){
		if(!matched[v]){
			memset(visited, false, n * sizeof(visited[0]));
			dfs(v);
		}
	}
}

int main(){

	// Get cardinality of a maximum matching

	// Read graph
    int n, m, k;
    scanf("%d %d %d", &n, &m, &k);
    loop(i, k){
    	int u, v;
    	scanf("%d %d", &u, &v);
    	graph[u].push_back(v);
    }

    // Compute matching
    kuhn(n, m);

    // Count edges in matching
    int card = 0;
    loop(i, m){
    	if(matching[i] != -1){
    		++card;
    	}
    }

    printf("%d\n", card);

    return 0;
    
}