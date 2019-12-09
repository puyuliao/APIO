#include<bits/stdc++.h>
#include<stdint.h>
using namespace std;
#define IOS {cin.tie(0);ios_base::sync_with_stdio(false);}
#define int int64_t
#define __int128 int64_t
#define N 105
#define K 1005
const int INF = 1e9+7;
 
int bb[N][K],ss[N][K];
int w[N][N],dis[N][N];
__int128 dp[N][N];
 
int32_t main()
{
	IOS;
	int n,m,k,a,b,t;
	cin >> n >> m >> k;
	for(int i=1;i<=n;i++) for(int j=1;j<=k;j++) cin >> bb[i][j] >> ss[i][j];
	
	for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) dis[i][j] = INF;
	//for(int i=1;i<=n;i++) dis[i][i] = 0; evil!!!!!!!!!!!!!!!!!!
	for(int i=0;i<m;i++){
		cin >> a >> b >> t;
		dis[a][b] = t; 
	}
	for(int x=1;x<=n;x++) for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) 
			dis[i][j] = min(dis[i][j],dis[i][x] + dis[x][j]);
 
	for(int i=1;i<=n;i++) for(int j=1;j<=n;j++){
		if(j != i && dis[i][j] != INF) {
			for(int x=1;x<=k;x++) if(ss[j][x] >= 0 && bb[i][x] >= 0) w[i][j] = max(w[i][j],ss[j][x] - bb[i][x]);
		}
		else w[i][j] = 0;
	}
 
	int l=0,r = INF;
	while(l!=r){
		int mm = (l+r+1) >> 1;
		for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) {
			dp[i][j] = (__int128)mm*dis[i][j] - w[i][j];
		}
		for(int x=1;x<=n;x++) for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) {
			dp[i][j] = min(dp[i][j],dp[i][x] + dp[x][j]);
		}
		bool gg = false;	
		for(int i=1;i<=n;i++) 
			if(dp[i][i] <= 0) gg = true;
		if(gg) l = mm;
		else r = mm-1;
	}
	cout << l << '\n';
  return 0;
}
