// Solution to https://codeforces.com/contest/510

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

const int N = 26;

int pos, in_deg[N], order[N];
vector<int> G[N];
bool done[N], visited[N];

bool dfs_cyc(int v){
    visited[v] = true;
    bool cycle = false;
    for(int u : G[v]){
        if(visited[u] && !done[u]){
            cycle = true;
        }else if(!visited[u]){
            cycle |= dfs_cyc(u);
        }
    }
    done[v] = true;
    return cycle;
}

void dfs_ts(int v){
    visited[v] = true;
    for(int u : G[v]){
        if(!visited[u]){
            dfs_ts(u);
        }
    }
    order[v] = pos--;
}

inline bool is_cyclic(int n = N){
    loop(i, n) done[i] = false;
    loop(i, n) visited[i] = false;
    bool cycle = false;
    for(int v = 0; v < n; ++v){
        if(!visited[v]){
            cycle |= dfs_cyc(v);
        }
        if(cycle){
            return true;
        }
    }
    return false;
}

// G must be acyclic!
inline void topological_order(int n = N){
    loop(i, n) visited[i] = false;
    pos = n - 1;
    for(int v = 0; v < n; ++v){
        if(!visited[v] && in_deg[v] == 0){
            dfs_ts(v);
        }
    }
}

int main(){
    /*
    auto start = chrono::high_resolution_clock::now();
    */
    
    ios_base::sync_with_stdio(false);   // unsync C- and C++-streams (stdio, iostream)
    cin.tie(NULL);  // untie cin from cout (no automatic flush before read)

    int n, m = 0;
    cin >> n;

    memset(in_deg, 0, 26 * sizeof(in_deg[0]));
    loop(i, 26) in_deg[i] = 0;
    bool possible = true;
    string s1, s2;
    cin >> s1;
    loop(i, n - 1){
        cin >> s2;
        loop(j, min(s1.size(), s2.size())){
            if(s1[j] != s2[j]){
                G[s1[j] - 'a'].push_back(s2[j] - 'a');
                ++in_deg[s2[j] - 'a'];
                break;
            }
            if(j == min(s1.size(), s2.size()) - 1 && s1.size() > s2.size()){
                possible = false;
            }
        }
        s1 = s2;
    }

    if(!possible || is_cyclic()){
        cout << "Impossible" << endl;
    }else{
        topological_order();
        string sol(26, '-');
        loop(i, 26){
            sol[order[i]] = 'a' + i;
        }
        cout << sol << endl;
    }

    /*
    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
    cout << duration.count() << endl;
    */
    return 0;
}
