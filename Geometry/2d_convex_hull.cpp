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

struct point{
    ll x, y;
    inline bool operator < (const point& other) const {
        if(x == other.x) return y < other.y;
        return x < other.x;
    }
    inline point operator + (const point& other) const {
        return {x + other.x, y + other.y};
    }
    inline point operator - (const point& other) const {
        return {x - other.x, y - other.y};
    }
};

inline ll det(const point& p, const point& q){
    return p.x * q.y - p.y * q.x;
}

/* 
    Andrew's monotone chain algorithm (Time: O(nlog(n)))
    !!! p must be sorted !!!
*/
inline vector<point> convex_hull(point p[], int n, bool top){
    vector<point> hull;
    hull.push_back(p[0]);
    hull.push_back(p[1]);
    for(int i = 2; i < n; ++i){
        while(hull.size() > 1){
            point u = hull.back() - hull[hull.size() - 2];
            point v = p[i] - hull.back();
            if((top ? det(u, v) : det(v, u)) > 0){
                hull.pop_back();
            }else{
                break;
            }
        }
        hull.push_back(p[i]);
    }
    return hull;
}

const int N = 2e5;

point p[N];

int main(){
    /*
    auto start = chrono::high_resolution_clock::now();
    */
    
    ios_base::sync_with_stdio(false);   // unsync C- and C++-streams (stdio, iostream)
    cin.tie(NULL);  // untie cin from cout (no automatic flush before read)

    int n; cin >> n;
    loop(i, n){
        cin >> p[i].x >> p[i].y;
    }
    sort(p, p + n);
    vector<point> top = convex_hull(p, n, true);
    vector<point> bot = convex_hull(p, n, false);
    set<point> hull;
    for(point pt : top){
        hull.insert(pt);
    }
    for(point pt : bot){
        hull.insert(pt);
    }
    cout << hull.size() << endl;
    for(point pt : hull){
        cout << pt.x << " " << pt.y << endl;
    }

    /*
    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
    cout << duration.count() << endl;
    */
    return 0;
}
