#include <bits/stdc++.h>
#define REP(i, n) for(int i = 0; i < (int)(n); ++i)
#define FOR(i, l, r) for(int i = (int)(l); i < (int)(r); ++i)
#define ALL(v) (v).begin(), (v).end()
using ll = long long;
using vi = std::vector<int>;
using vvi = std::vector<vi>;
using pii = std::pair<int, int>;
using namespace std;
constexpr int INF = 1e9;
constexpr long long LINF = 1e18;
constexpr double EPS = 1e-10;
constexpr int MOD = 998'244'353;
constexpr int MOD2 = 1e9 + 7;

template <class Class>
void line(const Class &a, std::string delim = " ") {
    int cnt = 0;
    for(const auto &elem : a) std::cout << (cnt++ == 0 ? "" : delim) << elem;
    std::cout << std::endl;
}

struct Node{
    int val;
    Node *par;
    Node(int val_,Node *par_):val(val_),par(par_){}
};

int main() {
    int q;
    cin>>q;

    auto p=new Node(-1,nullptr);
    map<int,Node *> mp;
    mp[0]=p;
    while(q--){
        string s;
        cin>>s;

        if(s=="ADD"){
            int x;
            cin>>x;
            p=new Node(x,p);
        }else if(s=="DELETE"){
            if(p->par) p=p->par;
        }else if(s=="SAVE"){
            int y;
            cin>>y;
            mp[y]=p;
        }else if(s=="LOAD"){
            int z;
            cin>>z;
            if(mp.find(z)==mp.end()) p=mp[0];
            else p=mp[z];
        }else{
            assert(false);
        }

        cout<<p->val<<endl;
    }
}

// I refer the editorial.
