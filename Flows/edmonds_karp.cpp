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

typedef ll f_type; // Type for flow

const f_type ZERO = 0, INF = LLONG_MAX;

const int N = 1000; // Maximum number of nodes in the network

f_type cap[N][N], flow[N][N];
vector<int> adj[N];
int pre[N];

// Clears adjacency lists, zeroes capacity and flow matrices
void init(int n = N){
    loop(i, n){
    	adj[i].clear();
        loop(j, n){
            cap[i][j] = ZERO;
            flow[i][j] = ZERO;
        }
    }
}

// Adds bidirectional edge to the network
void add(int u, int v, f_type c){
    adj[u].push_back(v);
    adj[v].push_back(u);
    cap[u][v] += c;
    cap[v][u] += c;
}

bool findPath(int n = N, int s = 0, int t = N - 1){
    loop(i, n){
        pre[i] = -1;
    }
    queue<int> Q;
    pre[s] = -2;
    Q.push(s);
    while(!Q.empty()){
        int u = Q.front();
        Q.pop();
        for(int v : adj[u]){
            f_type d = cap[u][v] - flow[u][v];
            if(pre[v] == -1 && d > ZERO){
                pre[v] = u;
                if(v == t){
                    return true;
                }
                Q.push(v);
            }
        }
    }
    return false;
}

f_type augmentFlow(int n = N, int s = 0, int t = N - 1){
    f_type d = INF;
    int v = t;
    while(s != v){
        d = min(d, cap[pre[v]][v] - flow[pre[v]][v]);
        v = pre[v];
    }
    v = t;
    while(s != v){
        flow[pre[v]][v] += d;
        flow[v][pre[v]] -= d;
        v = pre[v];
    }
    return d;
}

f_type maxFlow(int n = N, int s = 0, int t = N - 1){
    f_type f = ZERO;
    while(findPath(n, s, t)){
        f += augmentFlow(n, s, t);
    }
    return f;
}

int main(){
	/*	// IO
	ios_base::sync_with_stdio(false);	// unsync C- and C++-streams (stdio, iostream)
	cin.tie(NULL);	// untie cin from cout (no automatic flush before read)
	*/
    int n, net = 1;
    cin >> n;
    while(n){
        init(n);
        int s, t, m;
        cin >> s >> t >> m;
        loop(i, m){
            int u, v, c;
            cin >> u >> v >> c;
            add(u - 1, v - 1, c);
        }
        cout << "Network " << net++ << endl;
        cout << "The bandwidth is " << maxFlow(n, s - 1, t - 1) << "." << endl << endl;
        cin >> n;
    }
    return 0;
}
