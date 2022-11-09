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

typedef struct {
    ll x, y;
} point;

int sgn(ll n){
    if(n < 0){
        return -1;
    }
    if(n > 0){
        return 1;
    }
    return 0;
}

inline point sum(point v1, point v2){
    return {v1.x + v2.x, v1.y + v2.y};
}

inline point diff(point v1, point v2){
    return {v2.x - v1.x, v2.y - v1.y};
}

// Squared distance
inline ll dist(point p1, point p2){
    point v = diff(p1, p2);
    return v.x * v.x + v.y * v.y;
}

inline ll dot(point v1, point v2){
    return v1.x * v2.x + v1.y * v2.y;
}

inline ll det(point v1, point v2){
    return v1.x * v2.y - v1.y * v2.x;
}

// Interval intersection
inline point intersect_intervals(point i1, point i2){
    return {max(i1.x, i2.x), min(i1.y, i2.y)};
}

// Check if interval is empty
inline bool empty(point i){
    return i.x > i.y;
}

/* Line L through l1 and l2. Looking from l1 to l2:
    (x, y) on L                 --> returns 0
    (x, y) to the left of L     --> returns > 0
    (x, y) to the right of L    --> returns < 0
*/
inline ll point_vs_line(point l1, point l2, point p){
    return det(diff(l1, l2), diff(l1, p));
}

inline bool intersect(point r1, point r2, point s1, point s2){
    int b1 = sgn(point_vs_line(r1, r2, s1)) * sgn(point_vs_line(r1, r2, s2));
    int b2 = sgn(point_vs_line(s1, s2, r1)) * sgn(point_vs_line(s1, s2, r2));
    if(b1 == 1 || b2 == 1){
        return false;
    }
    // Segments could be collinear and not intersecting
    point rx = {min(r1.x, r2.x), max(r1.x, r2.x)};
    point sx = {min(s1.x, s2.x), max(s1.x, s2.x)};
    point ry = {min(r1.y, r2.y), max(r1.y, r2.y)};
    point sy = {min(s1.y, s2.y), max(s1.y, s2.y)};
    point ix = intersect_intervals(rx, sx);
    point iy = intersect_intervals(ry, sy);
    return !empty(ix) && !empty(iy);
}

/* 
    Returns TWICE the area of a simple polygon (not necessarily convex, but not self-intersecting and without holes).
    Points must be stored in p in clockwise or counterclockwise order.
    Time: O(n)
*/
inline ll area(point p[], int n){
    ll a = 0;
    for(int i = 2; i < n; ++i){
        a += det(diff(p[0], p[i]), diff(p[i - 1], p[i]));
    }
    return abs(a);
}

int main(){
    /*
    auto start = chrono::high_resolution_clock::now();
    */
    
    ios_base::sync_with_stdio(false);   // unsync C- and C++-streams (stdio, iostream)
    cin.tie(NULL);  // untie cin from cout (no automatic flush before read)

    int T;
    cin >> T;
    loop(t, T){
        point r1, r2, s1, s2;
        cin >> r1.x >> r1.y >> r2.x >> r2.y >> s1.x >> s1.y >> s2.x >> s2.y;
        if(intersect(r1, r2, s1, s2)){
            cout << "YES" << endl;
        }else{
            cout << "NO" << endl;
        }
    }

    /*
    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
    cout << duration.count() << endl;
    */
    return 0;
}
