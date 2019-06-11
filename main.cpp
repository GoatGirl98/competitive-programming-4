#include <bits/stdc++.h>

using namespace std;

template<class T> using min_heap = priority_queue<T, vector<T>, greater<T>>;

#define FOR(i, a, b) for (int i=a; i<(b); i++)
#define F0R(i, a) for (int i=0; i<(a); i++)
#define F0R1(i, a) for (int i=1; i<=(a); i++)
#define FORd(i, a, b) for (int i = (b)-1; i >= a; i--)
#define F0Rd(i, a) for (int i = (a)-1; i >= 0; i--)
#define F0Rd1(i, a) for (int i=a; i>0; i--)
#define SORT(vec) sort(vec.begin(), vec.end())
#define RSORT(vec) sort(vec.rbegin(), vec.rend())
#define MIN(a, b) a = min(a, b)
#define MAX(a, b) a = max(a, b)

#define INF 1000000010
#define LL_INF 4500000000000000000
#define LSOne(S) (S & (-S))
#define EPS 1e-9
#define pA first
#define pB second
#define mp make_pair
#define pb push_back
#define PI acos(-1.0)
#define ll long long
#define MOD (int)(2e+9+11)
#define SET(vec, val, size) for (int i = 0; i < size; i++) vec[i] = val;
#define SET2D(arr, val, dim1, dim2) F0R(i, dim1) F0R(j, dim2) arr[i][j] = val;
#define SET3D(arr, val, dim1, dim2, dim3) F0R(i, dim1) F0R(j, dim2) F0R(k, dim3) arr[i][j][k] = val;
#define SET4D(arr, val, dim1, dim2, dim3, dim4) F0R(i, dim1) F0R(j, dim2) F0R(k, dim3) F0R(l, dim4) arr[i][j][k][l] = val;
#define READGRID(arr, dim) F0R(i, dim) F0R(j, dim) cin >> arr[i][j];
#define all(x) (x).begin(), (x).end()

typedef pair<int, int> ii;
typedef pair<int, ii> iii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<ii> vii;
typedef vector<iii> viii;
typedef vector<ll> vl;

void setupIO(const string &PROB = "") {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    if (PROB.length() != 0) {
        ifstream infile(PROB + ".in");
        if (infile.good()) {
            freopen((PROB + ".in").c_str(), "r", stdin);
            freopen((PROB + ".out").c_str(), "w", stdout);
        }
    }
}

/* ============================ */

ll dp[3001][3001];
ll dp2[3001][3001];

int mod = 998244353;

ll gcd(ll a, ll b) {
    return b == 0 ? a : gcd(b, a % b);
}

ll power(ll base, ll pwr, ll mod) {
    ll res = 1;
    base = base % mod;
    while (pwr > 0) {
        if (pwr & 1) res = (res*base) % mod;
        pwr = pwr >> 1;
        base = (base*base)%mod;
    }
    return res;
}

// Find modular multiplicative inverse of x under modulo m
ll modInverse(ll x, ll m) {
    ll g = gcd(x, m);
    if (g != 1) {
        // Inverse doesn't exist!!
        return -1;
    } else {
        // answer is x^(m-2) % m
        return power(x, m - 2, m);
    }
}

int main() {
    setupIO();

    int n, m;
    cin >> n >> m;
    int like[n];
    F0R(i, n) cin >> like[i];
    int init_weight[n];
    F0R(i, n) cin >> init_weight[i];
    int weight_like = 0, weight_nolike = 0;
    F0R(i, n) {
        if (like[i]) weight_like += init_weight[i];
        else weight_nolike += init_weight[i];
    }

    /*
     * dp[w][i][j]
     * Expected weight of item with current weight w after all m operations
     * assume i increments and j decrements have happened already
     *
     * dp for liked weights
     * dp2 for disliked weights
     */
    F0Rd(k, 3001) {
        F0R(i, k+1) {
            int j = k - i;
            if (k == m) {
                dp[i][j] = 1;
                dp2[i][j] = 1;
                continue;
            }

            int totWeight = weight_like + weight_nolike + i - j;
            if (totWeight <= 0) continue;
            dp[i][j] = (dp[i+1][j]) % mod * modInverse(totWeight, mod) % mod;
            dp[i][j] += ((weight_like + i - 1)*dp[i+1][j]) % mod * modInverse(totWeight, mod) % mod;
            dp[i][j] += ((weight_nolike - j)*dp[i][j+1]) % mod * modInverse(totWeight, mod) % mod;
            dp[i][j] %= mod;

            if (isnan(dp[i][j])) {
                dp[i][j] = 0;
            }

            dp2[i][j] = (dp2[i][j+1]) % mod * modInverse(totWeight, mod) % mod;
            dp2[i][j] += ((weight_like + i)*dp2[i+1][j]) % mod * modInverse(totWeight, mod) % mod;
            dp2[i][j] += ((weight_nolike - j - 1)*dp2[i][j+1]) % mod * modInverse(totWeight, mod) % mod;
            dp2[i][j] %= mod;

            if (isnan(dp2[i][j])) {
                dp2[i][j] = 0;
            }
        }
    }

    F0R(i, n) {
        if (like[i]) {
            cout << init_weight[i]*dp[0][0]%mod << endl;
        } else {
            cout << init_weight[i]*dp2[0][0]%mod << endl;
        }
    }

    return 0;
}
