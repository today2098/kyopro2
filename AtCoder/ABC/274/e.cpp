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

// #define DEBUG
#ifdef DEBUG

#define debug(...) debug_internal(__LINE__, #__VA_ARGS__, __VA_ARGS__)
#define dline(a) dline_internal(__LINE__, #a, a);

template <typename T, class... Args>
void debug_internal(int l, const char *context, T &&first, Args &&...args) {
    constexpr const char *open_brackets = (sizeof...(args) == 0 ? "" : "(");
    constexpr const char *close_brackets = (sizeof...(args) == 0 ? "" : ")");
    std::cerr << "[L" << l << "] " << open_brackets << context << close_brackets << ": "
              << open_brackets << std::forward<T>(first);
    ((std::cerr << ", " << std::forward<Args>(args)), ...);
    std::cerr << close_brackets << std::endl;
}

template <class Class>
void dline_internal(int l, const char *context, const Class &a) {
    std::cerr << "[L" << l << "] " << context << ": ";
    int cnt = 0;
    for(const auto &elem : a) std::cerr << (cnt++ == 0 ? "" : " ") << elem;
    std::cerr << std::endl;
}

#else

#define debug(...) void(0)
#define dline(a) void(0)

#endif

template <typename Type>
using r_priority_queue = std::priority_queue<Type, std::vector<Type>, std::greater<Type> >;

template <typename Type>
std::vector<Type> table(size_t n, Type val) { return std::vector<Type>(n, val); }

template <class... Args>
auto table(size_t n, Args &&...args) {
    auto val = table(std::forward<Args>(args)...);
    return std::vector<decltype(val)>(n, std::move(val));
}

double calc_dist(pii p,pii q){
    const auto &[px,py]=p;
    const auto &[qx,qy]=q;
    double dist=sqrt((ll)(px-qx)*(px-qx)+(ll)(py-qy)*(py-qy));
    return dist;
}

int count_bit(int bit,int l,int r){
    int res=0;
    FOR(i,l,r) res+=(bit>>i)&1;
    return res;
}

int main(){
    int n,m;
    cin>>n>>m;

    vector<pii> vp(n+m);
    for(auto &[x,y]:vp) cin>>x>>y;

    const int num=1<<(n+m);
    auto dp=table(num,n+m,(double)LINF);  // dp[bit][v]:=(通った位置の集合がbit, 現在の位置がvである通り数).
    r_priority_queue<tuple<double,int,int> > pque;
    REP(v,n+m){
        int bit=1<<v;
        dp[bit][v]=calc_dist(pii(0,0),vp[v]);
        debug(bitset<17>(bit),dp[bit][v]);
        pque.emplace(dp[bit][v],bit,v);
    }
    while(!pque.empty()){
        auto [sum,bit,v]=pque.top();
        pque.pop();
        if(sum-dp[bit][v]>EPS) continue;
        debug(bitset<17>(bit),dp[bit][v]);

        int speed=1<<count_bit(bit,n,n+m);
        REP(u,n+m){
            if((bit>>u)&1){}
            else{
                int nbit=bit|(1<<u);
                double cost=(double)calc_dist(vp[v],vp[u])/speed;
                if(dp[nbit][u]-(sum+cost)>EPS){
                    dp[nbit][u]=sum+cost;
                    pque.emplace(dp[nbit][u],nbit,u);
                }
            }
        }
    }

    double ans=LINF;
    int mask=0;
    FOR(i,n,n+m) mask|=1<<i;
    debug(bitset<17>(mask));
    for(int sub=mask;;sub=(sub-1)&mask){
        int bit=sub;
        REP(v,n) bit|=1<<v;
        int speed=1<<count_bit(bit,n,n+m);
        debug(bitset<17>(sub),bitset<17>(bit),speed);
        REP(v,n+m){
            if((bit>>v)&1){
                double cost=(double)calc_dist(vp[v],pii(0,0))/speed;
                ans=min(ans,dp[bit][v]+cost);
                debug(v,dp[bit][v]+cost,ans);
            }
        }
        if(sub==0) break;
    }

    printf("%.10lf\n",ans);
}
