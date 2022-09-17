#include <bits/stdc++.h>
#define REP(i,n)   for(int i=0;i<(int)(n);++i)
#define FOR(i,l,r) for(int i=(int)(l);i<(int)(r);++i)
#define ALL(v)     (v).begin(),(v).end()
using ll  = long long;
using vi  = std::vector<int>;
using vvi = std::vector<vi>;
using pii = std::pair<int,int>;
using namespace std;
constexpr int       INF  = 1e9;
constexpr long long LINF = 1e18;
constexpr double    EPS  = 1e-10;
constexpr int       MOD  = 998'244'353;
constexpr int       MOD2 = 1e9+7;

template <typename Type>
std::vector<Type> table(size_t n, Type val) { return std::vector<Type>(n, val); }

template <class... Args>
auto table(size_t n, Args &&...args) {
    auto val = table(std::forward<Args>(args)...);
    return std::vector<decltype(val)>(n, std::move(val));
}

int main(){
    int n,m;
    cin>>n>>m;

    vector<ll> a(n);
    for(auto &in:a) cin>>in;

    auto dp=table(n+1,m+1,-LINF);  // dp[i][j]:=(長さjのa[:i]の部分列に対する，与式の最大値). i>j.
    dp[0][0]=0;
    FOR(i,1,n+1){
        dp[i][0]=0;
        FOR(j,1,i+1){
            if(j>m) break;
            dp[i][j]=max(dp[i-1][j],dp[i-1][j-1]+j*a[i-1]);
        }
    }

    cout<<dp[n][m]<<endl;
}
