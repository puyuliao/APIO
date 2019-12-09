#include<bits/stdc++.h>
#include<stdint.h>
using namespace std;
#define IOS {cin.tie(0);ios_base::sync_with_stdio(false);}
#define N 505
#define int int64_t
const int MOD = 1000000007;
vector<int> ds;
int a[N],b[N];
int dp[N];
int inv[N];
 
int powmo(int a,int b,int m){
	int r = 1;
	for(;b;b>>=1){
		if(b&1) r = r*a % m;
		a = a*a % m;
	}
	return r;
}
 
int32_t main()
{
	inv[0] = 1;
	for(int i=1;i<N;i++) inv[i] = powmo(i,MOD-2,MOD);
	IOS;
	int n;
	cin >> n;
	for(int i=1;i<=n;i++){
		cin >> a[i] >> b[i];
		ds.push_back(a[i]);
		ds.push_back(b[i]+1);
	}
	sort(ds.begin(),ds.end());
	ds.resize(unique(ds.begin(),ds.end()) - ds.begin());
	for(int i=1;i<=n;i++){
		a[i] = (int)(lower_bound(ds.begin(),ds.end(),a[i]) - ds.begin());
		b[i] = (int)(lower_bound(ds.begin(),ds.end(),b[i]+1) - ds.begin());		
	}
	dp[0] = 1;
	for(int i=0;i+1<ds.size();i++){
		int L = ds[i+1] - ds[i];
		for(int j=n;j>0;j--) if(a[j] <= i && i < b[j]){
			int f = 0, c = L, m = 1;
			for(int k=j-1;k>=0;k--){
				(f += c * dp[k]) %= MOD;
				if(a[k] <= i && i < b[k]) c = c * inv[m+1] % MOD * (L+m) % MOD,m++; 
			}
			(dp[j] += f) %= MOD;
		}
	}
	int ans = 0;
	for(int i=1;i<=n;i++) (ans += dp[i]) %= MOD;
	cout << ans << '\n';
  return 0;
}
