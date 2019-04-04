#include<bits/stdc++.h>
#include<stdint.h>
using namespace std;
#define IOS {cin.tie(0);ios_base::sync_with_stdio(false);}
#define N 100005
#define int int64_t
typedef pair<int,int> pii;
const int INF = 1ll<<40;

bitset<N> killed;
int nxt[N],prv[N];
int in[N];

int32_t main()
{
	IOS;
	int n,k,ans = 0;
	priority_queue<pii,vector<pii>,greater<pii> > pq;
	cin >> n >> k;
	for(int i=1;i<=n;i++) cin >> in[i];
	for(int i=1;i<n;i++) in[i] = in[i+1] - in[i],prv[i] = i-1,nxt[i] = i+1,pq.push({in[i],i});
	nxt[n-1] = 0; nxt[0] = prv[0] = 0; in[0] = INF; killed[0] = 1;
	for(int i=0;i<k;i++){
		pii x = pq.top(); pq.pop();
		if(killed[x.second]){
			i--; continue;
		}
		ans += x.first;
		in[x.second] = in[prv[x.second]] + in[nxt[x.second]] - in[x.second];
		killed[prv[x.second]] = killed[nxt[x.second]] = 1;
		prv[x.second] = prv[prv[x.second]];
		if(prv[x.second]) nxt[prv[x.second]] = x.second;
		nxt[x.second] = nxt[nxt[x.second]];
		if(nxt[x.second]) prv[nxt[x.second]] = x.second;
		pq.push({in[x.second],x.second});
	}
	cout << ans << '\n';
   return 0;
}

