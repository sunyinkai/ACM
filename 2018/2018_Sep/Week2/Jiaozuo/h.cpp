#include<bits/stdc++.h>
#define lson l,m,rt<<1
#define rson m+1,r,rt<<1|1
using namespace std; 
const int maxn = 2e5 + 10;
const int MAXN=maxn;
const int INF=1e9+7;
int t1[maxn], t2[maxn], c[maxn];
 
inline bool cmp(int* r, int a,int b,int l){
    return r[a] == r[b] && r[a+l] == r[b+l];
}
 
void da(int str[], int sa[], int Rank[], int lcp[], int n, int m){
    ++n;
    int i, j, p, *x = t1, *y = t2;
    for (i = 0; i < m; ++i) c[i] = 0;
    for (i = 0; i < n; ++i) c[x[i] = str[i] ]++;
    for (i = 1; i < m; ++i) c[i] += c[i-1];
    for (i = n-1; i >= 0; --i) sa[--c[x[i] ] ] = i;
    for (j = 1; j <= n; j <<= 1){
        p = 0;
        for (i = n-j; i < n; ++i) y[p++] = i;
        for (i = 0; i < n; ++i) if (sa[i] >= j) y[p++] = sa[i] - j;
        for (i = 0; i < m; ++i) c[i] = 0;
        for (i = 0; i < n; ++i) c[x[y[i] ] ]++;
 
        for (i = 1; i < m; ++i) c[i] += c[i-1];
        for (i = n-1; i >= 0; --i) sa[--c[x[y[i] ] ] ] = y[i];
 
        swap(x,y);
        p = 1; x[sa[0] ] = 0;
        for (i = 1; i < n; ++i){
            x[sa[i] ] = cmp(y, sa[i-1], sa[i], j) ? p-1 : p++;
 
        }
        if (p >= n)break;
        m= p;
    }
    int k = 0;
    n--;
    for (i = 0; i <= n; ++i) Rank[sa[i] ] = i;
    for (i = 0; i < n; ++i){
        if (k)--k;
        j = sa[Rank[i]-1 ];
        while(str[i+k] == str[j+k])++k;
        lcp[Rank[i] ] = k;
    }
}
 
int lcp[maxn], a[maxn], sa[maxn], Rank[maxn];
 
char s[maxn];
 
int len;

int d[MAXN*4+1007];
inline void PushUp(int rt){
	d[rt]=min(d[rt<<1],d[rt<<1|1]);
}

inline void build(int *A,int l,int r,int rt){
	if(l==r){
		d[rt]=A[l];
		return ;
	}
	int m=(l+r)/2;
	build(A,lson);
	build(A,rson);
	PushUp(rt);
}

int query(int L,int R,int l,int r,int rt){//询问(L,R)区间的最小值
	if(l>=L&&r<=R)return d[rt];
	int m=(l+r)/2;
	int res=INF;
	if(L<=m)res=min(res,query(L,R,lson));
	if(R>m)res=min(res,query(L,R,rson));
	return res;
}

inline int ask(int l,int r){
    if (l == r) return len - sa[r]; /// l == r的话 是一个串， 返回本身的长度即可。
	return  query(l+1,r,0,len+1,0);
}
 
int main(){

    int A,B;
	//freopen("in.txt","r",stdin);
    while(~scanf("%s%d%d", s,&A,&B)){
        len = strlen(s);
		for(int i=0;i<=4*len+10;++i)d[i]=0;
        for (int i = 0; i < len; ++i){
            a[i] = s[i] - 'A' + 1;
        }
        da(a, sa, Rank, lcp, len, 30);
		build(lcp,0,len+1,0);
        long long ans = 0;
        int k=A;
        int p=B-A+1;
        for (int i = 1; i + k - 1 <= len; ++i){
            ans += ask(i, i + k - 1);
            if (i - p > 0)ans -= ask(i - p, i + k - 1); ///注意边界问题。
            if (i + k <= len)ans -= ask(i, i + k);
            if (i - p > 0 && i + k <= len)ans += ask(i - p , i + k);
        }
		cout<<ans<<endl;
 
    }
    return 0;
}

