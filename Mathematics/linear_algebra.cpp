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

const ull MD = 1e9 + 7;

template<ull MOD>
struct modint{
    
    ull val;

    modint() : val(0) {}

    modint(ull n) : val(n % MOD) {}

    modint operator + (const modint &b) const {
        return (val + b.val) % MOD;
    }

    modint operator * (const modint &b) const {
        return (val * b.val) % MOD;
    }

    friend ostream &operator << (ostream &out, const modint &mi){
        out << mi.val;
        return out;
    }

    friend istream &operator >> (istream &in, modint &mi){
        in >> mi.val;
        return in;
    }

};

template<class type>
type zero(){
    if(typeid(type) == typeid(modint<10>)){
        return modint<MD>(0);
    }
    return 0;
}

template<class type>
type one(){
    if(typeid(type) == typeid(modint<10>)){
        return modint<MD>(1);
    }
    return 1;
}

template<class type, int N, int M>
struct matrix{

    type data[N][M];

    matrix(){
        for(int i = 0; i < N; ++i){
            for(int j = 0; j < M; ++j){
                data[i][j] = zero<type>();
            }
        }
    }

    matrix(type *ptr){
        for(int i = 0; i < N; ++i){
            for(int j = 0; j < M; ++j){
                data[i][j] = *(ptr + M * i + j);
            }
        }
    }

    friend ostream &operator << (ostream &out, const matrix &A){
        for(int i = 0; i < N; ++i){
            for(int j = 0; j < M; ++j){
                out << A.data[i][j] << " ";
            }
            out << endl;
        }
        return out;
    }

    friend istream &operator >> (istream &in, matrix &A){
        for(int i = 0; i < N; ++i){
            for(int j = 0; j < M; ++j){
                in >> A.data[i][j];
            }
        }
    }

};

template<class type, int N>
matrix<type, N, N> identity(){
    matrix<type, N, N> I = *(new matrix<type, N, N>());
    for(int i = 0; i < N; ++i){
        I.data[i][i] = one<type>();
    }
    return I;
}

template<int N, int M>
matrix<double, N, M> random(){
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    uniform_real_distribution<> uar(0, 1);
    matrix<double, N, M> A = *(new matrix<double, N, M>());
    for(int i = 0; i < N; ++i){
        for(int j = 0; j < N; ++j){
            A[i][j] = uar(rng);
        }
    }
    return A;
}

template<class type, int N, int M>
matrix<type, N, M> sum(matrix<type, N, M> A, matrix<type, N, M> B){
    matrix<type, N, M> S = *(new matrix<type, N, M>());
    memcpy(S.data, A.data, N * M * sizeof(type));
    loop(i, N){
        loop(j, M){
            S.data[i][j] = S.data[i][j] + B.data[i][j];
        }
    }
    return S;
}

template<class type, int L, int N, int M>
matrix<type, L, M> product(matrix<type, L, N> A, matrix<type, N, M> B){
    matrix<type, L, M> P = *(new matrix<type, L, M>());
    for(int i = 0; i < L; ++i){
        for(int j = 0; j < M; ++j){
            for(int k = 0; k < N; ++k){
                P.data[i][j] = P.data[i][j] + A.data[i][k] * B.data[k][j];
            }
        }
    }
    return P;
}

// Time: O(N^3log(n)) (could be sped up to O(t(n) + log(Nlog(n))) with O(t(n)) eigendecomposition)
template<class type, int N>
matrix<type, N, N> power(matrix<type, N, N> A, ull n){
    matrix<type, N, N> P = identity<type, N>();
    while(n){
        if(n & 1){
            P = product(P, A);
        }
        A = product(A, A);
        n >>= 1;
    }
    return P;
}

modint<MD> D[2][2] = {{modint<MD>(0), modint<MD>(1)},
                  {modint<MD>(1), modint<MD>(1)}};

int main(){
	/*	// IO
	ios_base::sync_with_stdio(false);	// unsync C- and C++-streams (stdio, iostream)
	cin.tie(NULL);	// untie cin from cout (no automatic flush before read)
	*/
    ull n;
    cin >> n;
    matrix<modint<MD>, 2, 2> A(&D[0][0]);
    auto P = power(A, n);
    cout << P.data[0][1] << endl;
    return 0;
}
