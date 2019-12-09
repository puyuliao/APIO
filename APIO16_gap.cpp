#include<bits/stdc++.h>
using namespace std;
#include "gap.h"
typedef long long ll;
 
ll findGap(int T,int n){
	if(T==1){
		vector<ll> v1,v2;
		ll ans = 0;
		ll s = 0, t = 1000000000000000000ll,mn,mx;
		for(int i=1,j=n;i<=j;i++,j--){
			MinMax(s,t,&mn,&mx);
			v1.push_back(mn);
			if(i != j) v2.push_back(mx);
			s = mn+1; t=mx-1;
		}
		reverse(v2.begin(),v2.end());
		for(ll i : v2) v1.push_back(i);
		for(int i=0;i<v1.size()-1;i++) ans = max(ans,v1[i+1]-v1[i]);
		return ans;
	}
	else{
		ll ans = 0;
		ll s = 0,t=1000000000000000000ll,mn,mx,gap,last;
		MinMax(s,t,&mn,&mx);
		s = mn + 1, t = mx - 1;
		if(n == 2) return mx - mn;
		gap = (mx-mn+1)/(n);
		last = mn;
		while(s + gap + 1 <= t){
			MinMax(s,s + gap,&mn,&mx);
			if(mn != -1) ans = max(ans,mn - last),last = mx;
			s += gap+1;
		}
		MinMax(s,t,&mn,&mx);
		if(mn != -1) ans = max(ans,mn - last),last = mx;
		ans = max(ans,t+1 - last);
		return ans;
	}
}
