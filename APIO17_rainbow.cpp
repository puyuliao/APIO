#include<bits/stdc++.h>
#include<stdint.h>
using namespace std;
#define IOS {cin.tie(0);ios_base::sync_with_stdio(false);}
#define N 200005
#define lowbit(x) (x&-x)
#include"rainbow.h"
struct dbit{
	vector<int> v[N];
	int n,m;
	void init(int _n,int _m){
		n = _n,m = _m;
		for(int i=1;i<=n;i++) v[i].clear();
	}
	void ins(int x,int y){
		for(;x<=n;x+=lowbit(x)) v[x].push_back(y);
	}
	void preprocess(){
		for(int i=1;i<=n;i++){
			sort(v[i].begin(),v[i].end());
		}
	}
	int qur(int x,int y,int xx,int yy){
		if(x > xx || y > yy) return 0;
		int r = 0;
		for(;x;x-=lowbit(x)) r -= (int)(upper_bound(v[x].begin(),v[x].end(),yy) - lower_bound(v[x].begin(),v[x].end(),y));
		for(;xx;xx-=lowbit(xx)) r += (int)(upper_bound(v[xx].begin(),v[xx].end(),yy) - lower_bound(v[xx].begin(),v[xx].end(),y));
		return r;
	}
}bv,be1,be2,bf;
vector<pair<int,int> > v;
set<pair<int,int> > sv,se1,se2,sf;
int xmn,xmx,ymn,ymx;
 
void put(int sr,int sc){
	sv.insert({sr,sc});
	sv.insert({sr+1,sc});
	sv.insert({sr,sc+1});
	sv.insert({sr+1,sc+1});
	se1.insert({sr,sc}); 
	se1.insert({sr,sc+1}); 
	se2.insert({sr,sc}); 
	se2.insert({sr+1,sc}); 
	sf.insert({sr,sc});
}
 
void init(int R,int C,int sr,int sc,int M,char* S){
	bv.init(R+2,C+2);
	be1.init(R+2,C+2); //vert
	be2.init(R+2,C+2); //hori
	bf.init(R+2,C+2);
	sv.clear();
	se1.clear();
	se2.clear();
	sf.clear();
	put(sr,sc);
	xmn = xmx = sr, ymn = ymx = sc;
	for(int j=0;j<M;j++){
		char &i = S[j];
		if(i == 'N') sr--;
		else if(i == 'E') sc++;
		else if(i == 'W') sc--;
		else if(i == 'S') sr++;
		v.push_back({sr,sc});
		xmx = max(xmx,sr);
		xmn = min(xmn,sr);
		ymx = max(ymx,sc);
		ymn = min(ymn,sc);
		put(sr,sc);
	}
	for(auto i : sv) bv.ins(i.first,i.second);
	for(auto i : se1) be1.ins(i.first,i.second);
	for(auto i : se2) be2.ins(i.first,i.second);
	for(auto i : sf) bf.ins(i.first,i.second);
	bv.preprocess();
	be1.preprocess();
	be2.preprocess();
	bf.preprocess();
}
 
int colour(int ar,int ac,int br,int bc){
	int v = (br-ar+bc-ac+2)*2 + bv.qur(ar,ac+1,br,bc);
	int e = (br-ar+bc-ac+2)*2 + be1.qur(ar-1,ac+1,br,bc) + be2.qur(ar,ac,br,bc);
	int f = bf.qur(ar-1,ac,br,bc);
	//cout << v << ' ' << e << ' ' << f << '\n';
	return e-v-f + 1 + (ar < xmn && ac < ymn && br > xmx && bc > ymx);
}
