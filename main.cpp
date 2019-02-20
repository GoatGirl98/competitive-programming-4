#include <iostream>
#include <string>
#include <utility>
#include <sstream>
#include <algorithm>
#include <stack>
#include <vector>
#include <queue>
#include <map>
#include <set>
#include <bitset>
#include <cmath>
#include <cstring>
#include <iomanip>
#include <fstream>
#include <cassert>
#include <unordered_set>

using namespace std;

template<class T> using min_heap = priority_queue<T, vector<T>, greater<T>>;

#define FOR(i, a, b) for (int i=a; i<(b); i++)
#define F0R(i, a) for (int i=0; i<(a); i++)
#define F0R1(i, a) for (int i=1; i<=(a); i++)
#define FORd(i, a, b) for (int i = (b)-1; i >= a; i--)
#define F0Rd(i, a) for (int i = (a)-1; i >= 0; i--)
#define F0Rd1(i, a) for (int i=a; i>0; i--)
#define SORT(vec) sort(vec.begin(), vec.end())
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

void setupIO(const string &PROB) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    ifstream infile(PROB + ".in");
    if (infile.good()) {
        freopen((PROB + ".in").c_str(), "r", stdin);
        freopen((PROB + ".out").c_str(), "w", stdout);
    }
}

/* ============================ */

bool visited[3000][3000];
int dist[3000][3000];

int main() {
    int p1, p2;
    while (cin >> p1 && p1) {
        SET2D(visited, false, 3000, 3000);
        SET2D(dist, INF, 3000, 3000);

        vii A; A.resize(p1);
        F0R(i, p1) cin >> A[i].pA >> A[i].pB;

        cin >> p2;
        vii B; B.resize(p2);
        F0R(i, p2) cin >> B[i].pA >> B[i].pB;

        queue<ii> q;
        F0R(i, p1) {
            q.push(A[i]);
            dist[A[i].pA][A[i].pB] = 0;
        }
        int dx[4] = { -1, 0, 1, 0 };
        int dy[4] = { 0, 1, 0, -1 };
        while (!q.empty()) {
            ii next = q.front(); q.pop();
            if (visited[next.pA][next.pB]) continue;
            visited[next.pA][next.pB] = true;
            F0R(i, 4) {
                ii bessie = { next.pA + dx[i], next.pB + dy[i] };
                if (bessie.pA < 0 || bessie.pA > 2000 || bessie.pB < 0 || bessie.pB > 2000) continue;
                if (dist[bessie.pA][bessie.pB] > dist[next.pA][next.pB] + 1) {
                    dist[bessie.pA][bessie.pB] = dist[next.pA][next.pB] + 1;
                    q.push(bessie);
                }
            }
        }

        int best = INF;
        F0R(i, p2) MIN(best, dist[B[i].pA][B[i].pB]);
        cout << best << endl;
    }

    return 0;
}
