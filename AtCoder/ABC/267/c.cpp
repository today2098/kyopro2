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

template<typename Type> inline bool chmin(Type &a,const Type &b){if(a>b){a=b;return true;}return false;}
template<typename Type> inline bool chmax(Type &a,const Type &b){if(a<b){a=b;return true;}return false;}

int main(){
    int n,m;
    cin>>n>>m;

    vector<ll> a(n);
    for(auto &in:a) cin>>in;

    vector<ll> sum(n+1,0);  // sum[i]:=(a[:i]の累積和).
    FOR(i,1,n+1) sum[i]=sum[i-1]+a[i-1];

    ll tmp=0;
    REP(i,m) tmp+=sum[m]-sum[i];

    ll ans=tmp;
    FOR(i,m,n){
        tmp-=sum[i]-sum[i-m];
        tmp+=m*a[i];
        debug(tmp);
        chmax(ans,tmp);
    }

    cout<<ans<<endl;
}
