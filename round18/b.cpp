#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>
#include<ctime>
#include<functional>
#include<cmath>
#include<vector>
#include<assert.h>
//using namespace std;
using std::min;
using std::max;
using std::swap;
using std::sort;
using std::reverse;
using std::random_shuffle;
using std::lower_bound;
using std::upper_bound;
using std::unique;
using std::vector;
typedef long long ll;
typedef unsigned long long ull;
typedef double db;
typedef std::pair<int,int> pii;
typedef std::pair<ll,ll> pll;
void open(const char *s){
#ifndef ONLINE_JUDGE
	char str[100];sprintf(str,"%s.in",s);freopen(str,"r",stdin);sprintf(str,"%s.out",s);freopen(str,"w",stdout);
#endif
}
void open2(const char *s){
#ifdef DEBUG
	char str[100];sprintf(str,"%s.in",s);freopen(str,"r",stdin);sprintf(str,"%s.out",s);freopen(str,"w",stdout);
#endif
}
int rd(){int s=0,c,b=0;while(((c=getchar())<'0'||c>'9')&&c!='-');if(c=='-'){c=getchar();b=1;}do{s=s*10+c-'0';}while((c=getchar())>='0'&&c<='9');return b?-s:s;}
void put(int x){if(!x){putchar('0');return;}static int c[20];int t=0;while(x){c[++t]=x%10;x/=10;}while(t)putchar(c[t--]+'0');}
int upmin(int &a,int b){if(b<a){a=b;return 1;}return 0;}
int upmax(int &a,int b){if(b>a){a=b;return 1;}return 0;}
const int N=1200000;
const ll p=998244353;
ll fp(ll a,ll b)
{
	ll s=1;
	for(;b;b>>=1,a=a*a%p)
		if(b&1)
			s=s*a%p;
	return s;
}
namespace ntt
{
	const int W=1048576;
	int rev[N];
	ll w[N];
	void init()
	{
		ll s=fp(3,(p-1)/W);
		w[0]=1;
		for(int i=1;i<W/2;i++)
			w[i]=w[i-1]*s%p;
	}
	void ntt(ll *a,int n,int t)
	{
		for(int i=1;i<n;i++)
		{
			rev[i]=(rev[i>>1]>>1)|(i&1?n>>1:0);
			if(rev[i]>i)
				swap(a[i],a[rev[i]]);
		}
		for(int i=2;i<=n;i<<=1)
			for(int j=0;j<n;j+=i)
				for(int k=0;k<i/2;k++)
				{
					ll u=a[j+k];
					ll v=a[j+k+i/2]*w[W/i*k];
					a[j+k]=(u+v)%p;
					a[j+k+i/2]=(u-v)%p;
				}
		if(t==-1)
		{
			reverse(a+1,a+n);
			ll inv=fp(n,p-2);
			for(int i=0;i<n;i++)
				a[i]=a[i]*inv%p;
		}
	}
	void mul(ll *a,ll *b,ll *c,int n,int m,int l)
	{
		static ll a1[N],a2[N];
		int k=1;
		while(k<=n+m)
			k<<=1;
		for(int i=0;i<k;i++)
			a1[i]=a2[i]=0;
		for(int i=0;i<=n;i++)
			a1[i]=a[i];
		for(int i=0;i<=m;i++)
			a2[i]=b[i];
		ntt::ntt(a1,k,1);
		ntt::ntt(a2,k,1);
		for(int i=0;i<k;i++)
			a1[i]=a1[i]*a2[i]%p;
		ntt::ntt(a1,k,-1);
		for(int i=0;i<=l;i++)
			c[i]=a1[i];
	}
}
ll inv[N],fac[N],ifac[N];
int n,m,k;
ll f[N];
ll a[N],b[N],c[N];
ll binom(int x,int y)
{
	return fac[x]*ifac[y]%p*ifac[x-y]%p;
}
int main()
{
	open("b");
	ntt::init();
	inv[1]=fac[0]=fac[1]=ifac[0]=ifac[1]=1;
	for(int i=2;i<=500010;i++)
	{
		inv[i]=-p/i*inv[p%i]%p;
		fac[i]=fac[i-1]*i%p;
		ifac[i]=ifac[i-1]*inv[i]%p;
	}
	scanf("%d%d%d",&n,&m,&k);
	
	for(int i=0;i<=m+1;i++)
	{
		a[i]=(i&1?-1:1)*ifac[i]%p*ifac[m+1-i]%p;
		b[i]=fp(i,m);
	}
	ntt::mul(a,b,c,m+1,m+1,m+1);
	for(int i=0;i<m;i++)
		f[i]=c[i+1]*fac[m+1]%p;
	
	
	for(int i=0;i<m;i++)
		f[i]=f[i]*ifac[m]%p;
	for(int i=m-1;i>=0;i--)
		f[i]=(f[i]+f[i+1])%p;
	for(int i=0;i<m;i++)
		f[i]=fp(f[i],n)%p;
	for(int i=0;i<m;i++)
		f[i]=(f[i]-f[i+1])%p;
	ll ans=0;
	for(int i=0;i<m;i++)
		ans=(ans+fp(i,k)*f[i])%p;
	ans=(ans%p+p)%p;
	printf("%lld\n",ans);
	return 0;
}
