#include<bits/stdc++.h>
#include<stdint.h>
using namespace std;
#define IOS {cin.tie(0);ios_base::sync_with_stdio(false);}
#define N 300005
#define int int64_t

inline int hh(int x,int y){
	return x*2000000007 + y;
}

int n;
bitset<N> gg;
unordered_map<int,vector<int> > mp; 
int nb,ans[N],xx[N],yy[N],rr[N];
vector<int> ord;

void build(){
	mp.clear();
	for(int i=0;i<n;i++) if(!gg[i]){
		int t = hh(xx[i]/nb,yy[i]/nb);
		mp[t].push_back(i);
	}
}

bool cov(int i,int j){
	return (xx[i]-xx[j])*(xx[i]-xx[j]) + (yy[i]-yy[j])*(yy[i]-yy[j]) <= (rr[i]+rr[j])*(rr[i]+rr[j]);
}

void qur(int x){
	int bx = xx[x]/nb, by = yy[x]/nb;
	ans[x] = x; gg[x] = 1;
	for(int i=bx-2;i<=bx+2;i++) for(int j=by-2;j<=by+2;j++){
		auto it = mp.find(hh(i,j));
		if(it != mp.end()) for(int k : it->second) if(!gg[k] && cov(k,x)){
			ans[k] = x;
			gg[k] = 1;
		}
	}
}

int32_t main()
{
	IOS;
	cin >> n;
	int mnx,mny; mnx = mny = 1ll<<60;
	ord.resize(n);
	for(int i=0;i<n;i++) {
		cin >> xx[i] >> yy[i] >> rr[i];
		mnx = min(mnx,xx[i]);
		mny = min(mny,yy[i]);
		ord[i] = i;
	}
	for(int i=0;i<n;i++){
		xx[i] = xx[i] - mnx + 1;
		yy[i] = yy[i] - mny + 1;
	}
	stable_sort(ord.begin(),ord.end(),[](int x,int y){return rr[x] > rr[y];});
	nb = 1 << __lg(2*rr[ord[0]]-1); 
	build();
	for(int i : ord) if(!gg[i]){
		while(rr[i] <= (nb>>1)) nb>>=1,build();
		qur(i);
	}
	for(int i=0;i<n;i++) cout << ans[i]+1 << ' ';
   return 0;
}
