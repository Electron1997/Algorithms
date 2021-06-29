// Solution to https://codeforces.com/contest/237/problem/E

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

/* // TIME
auto start = chrono::high_resolution_clock::now();
// ...
auto stop = chrono::high_resolution_clock::now();
auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
cout << duration.count() << endl;
*/

typedef ll c_type; // Type for cost
typedef ll f_type; // Type for flow

const c_type FREE = 0, IMP = LLONG_MAX;
const f_type ZERO = 0, INF = LLONG_MAX;

const int N = 1000; // Maximum number of nodes in the network

c_type cost[N][N], dist[N];
f_type cap[N][N], flow[N][N];
vector<int> adj[N];
int pre[N];
priority_queue<pair<c_type, int>, vector<pair<c_type, int> >, greater<pair<c_type, int> > > Q;

// Clears adjacency lists, zeroes capacity and flow matrices
void init(int n = N){
    loop(i, n){
        adj[i].clear();
        loop(j, n){
            cap[i][j] = ZERO;
            cost[i][j] = FREE;
            flow[i][j] = ZERO;
        }
    }
}

// Adds directed edge to the network
void add(int u, int v, f_type c, c_type w = FREE){
    adj[u].push_back(v);
    adj[v].push_back(u);
    cap[u][v] += c;
    cost[u][v] = w;
    cost[v][u] = -w;
}

// Dijkstra (works only for positive costs)
bool findPath(int n = N, int s = 0, int t = N - 1){
    loop(i, n){
        dist[i] = IMP;
    }
    loop(i, n){
        pre[i] = -1;
    }
    dist[s] = 0;
    pre[s] = -2;
    Q.push({FREE, s});
    while(!Q.empty()){
        pair<c_type, int> p = Q.top();
        int u = p.second;
        c_type dist_u = p.first;
        Q.pop();
        if(dist[u] != dist_u){
            continue;
        }
        if(u == t){
            return true;
        }
        for(int v : adj[u]){
            f_type d = cap[u][v] - flow[u][v];
            if(pre[v] == -1 && d > ZERO){
                if(dist_u + cost[u][v] < dist[v]){
                    dist[v] = dist_u + cost[u][v];
                    pre[v] = u;
                    Q.push({dist[v], v});
                }
            }
        }
    }
    return false;
}

pair<f_type, c_type> augmentFlow(int n = N, int s = 0, int t = N - 1){
    c_type c = FREE;
    f_type d = INF;
    int v = t;
    while(s != v){
        d = min(d, cap[pre[v]][v] - flow[pre[v]][v]);
        v = pre[v];
    }
    v = t;
    while(s != v){
        c += cost[pre[v]][v] * d;
        flow[pre[v]][v] += d;
        flow[v][pre[v]] -= d;
        v = pre[v];
    }
    return {d, c};
}

pair<f_type, c_type> maxFlow(int n = N, int s = 0, int t = N - 1){
    c_type c = FREE;
    f_type f = ZERO;
    while(findPath(n, s, t)){
        pair<f_type, c_type> inc = augmentFlow(n, s, t);
        f += inc.first;
        c += inc.second;
    }
    return {f, c};
}

int main(){

    ios_base::sync_with_stdio(false);   // unsync C- and C++-streams (stdio, iostream)
    cin.tie(NULL);  // untie cin from cout (no automatic flush before read)

    int c, n, f[26];
    string s, t;
    cin >> t;
    cin >> n;
    
    init(n);

    loop(i, n){
        cin >> s >> c;
        add(0, i + 1, c, i + 1);
        memset(f, 0, 26 * sizeof(int));
        loop(j, s.size()){
            ++f[s[j] - 'a'];
        }
        loop(j, 26){
            if(f[j]){
                add(i + 1, 1 + n + j, f[j]);
            }
        }
    }

    memset(f, 0, 26 * sizeof(int));
    loop(i, t.size()){
        ++f[t[i] - 'a'];
    }

    loop(i, 26){
        if(f[i]){
            add(1 + n + i, n + 28, f[i]);
        }
    }

    pair<f_type, c_type> fl = maxFlow(n + 29, 0, n + 28);

    if(fl.first != t.size()){
        cout << -1 << endl;
    }else{
        cout << fl.second << endl;
    }

    return 0;
}
