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
using r_priority_queue = std::priority_queue<Type, std::vector<Type>, std::greater<Type> >;

template<typename Type> inline bool chmin(Type &a,const Type &b){if(a>b){a=b;return true;}return false;}
template<typename Type> inline bool chmax(Type &a,const Type &b){if(a<b){a=b;return true;}return false;}

int main(){
    int n,m;
    cin>>n>>m;

    vector<ll> a(n);
    for(auto &in:a) cin>>in;

    vvi g(n);
    REP(i,m){
        int u,v;
        cin>>u>>v;
        u--, v--;
        g[u].push_back(v);
        g[v].push_back(u);  
    }

    ll ans=0;
    vector<ll> costs(n);  // costs[v]:=(現時点で頂点vを削除した場合のコスト).
    r_priority_queue<pair<ll,int> > pque;
    REP(v,n){
        ll cost=0;
        for(auto u:g[v]) cost+=a[u];
        costs[v]=cost;
        pque.emplace(cost,v);
    }
    bool seen[n]={};
    while(!pque.empty()){
        auto [cost,u]=pque.top();
        pque.pop();
        if(seen[u]) continue;
        seen[u]=true;

        chmax(ans,cost);
        for(auto v:g[u]){
            if(!seen[v]){
                costs[v]-=a[u];
                pque.emplace(costs[v],v);
            }
        }
    }

    cout<<ans<<endl;
}

// I refered the editorial.
