//Submatrix sum - 2D Segment Tree
//Query types : 1) Sum of given submatrix , 2) Add given value to all elements in submatrix.

#include<bits/stdc++.h>
#define ll long long
#define MOD 1000000007
using namespace std;

static struct IO {
	char tmp[1 << 10];
 
	// fast input routines
	char cur;
 
//#define nextChar() (cur = getc_unlocked(stdin))
//#define peekChar() (cur)
	inline char nextChar() { return cur = getc_unlocked(stdin); }
	inline char peekChar() { return cur; }
 
	inline operator bool() { return peekChar(); }
	inline static bool isBlank(char c) { return (c < '-' && c); }
	inline bool skipBlanks() { while (isBlank(nextChar())); return peekChar() != 0; }
 
	inline IO& operator >> (char & c) { c = nextChar(); return *this; }
 
	inline IO& operator >> (char * buf) {
		if (skipBlanks()) {
			if (peekChar()) {
				*(buf++) = peekChar();
				while (!isBlank(nextChar())) *(buf++) = peekChar();
			} *(buf++) = 0; } return *this; }
 
	inline IO& operator >> (string & s) {
		if (skipBlanks()) {	s.clear(); s += peekChar();
			while (!isBlank(nextChar())) s += peekChar(); }
		return *this; }
 
	inline IO& operator >> (double & d) { if ((*this) >> tmp) sscanf(tmp, "%lf", &d); return *this;	}
 
#define defineInFor(intType) \
	inline IO& operator >>(intType & n) { \
		if (skipBlanks()) { \
			int sign = +1; \
			if (peekChar() == '-') { \
				sign = -1; \
				n = nextChar() - '0'; \
			} else \
				n = peekChar() - '0'; \
			while (!isBlank(nextChar())) { \
				n += n + (n << 3) + peekChar() - 48; \
			} \
			n *= sign; \
		} \
		return *this; \
	}
 
defineInFor(int)
defineInFor(unsigned int)
defineInFor(long long)
 
	// fast output routines
 
//#define putChar(c) putc_unlocked((c), stdout)
	inline void putChar(char c) { putc_unlocked(c, stdout); }
	inline IO& operator << (char c) { putChar(c); return *this; }
	inline IO& operator << (const char * s) { while (*s) putChar(*s++); return *this; }
 
	inline IO& operator << (const string & s) { for (int i = 0; i < (int)s.size(); ++i) putChar(s[i]); return *this; }
 
	char * toString(double d) { sprintf(tmp, "%lf%c", d, '\0'); return tmp; }
	inline IO& operator << (double d) { return (*this) << toString(d); }
 
 
#define defineOutFor(intType) \
	inline char * toString(intType n) { \
		char * p = (tmp + 30); \
		if (n) { \
			bool isNeg = 0; \
			if (n < 0) isNeg = 1, n = -n; \
			while (n) \
				*--p = (n % 10) + '0', n /= 10; \
			if (isNeg) *--p = '-'; \
		} else *--p = '0'; \
		return p; \
	} \
	inline IO& operator << (intType n) { return (*this) << toString(n); }
 
defineOutFor(int)
defineOutFor(long long)
 
#define endl ('\n')
#define cout __io__
#define cin __io__
} __io__;


static int a[1025][1025];
static int p[20000001],lazy[20000001];

void init(int node,int x1,int y1,int x2,int y2)
{
	if(x1>x2 || y1>y2)
	{
		p[node] = lazy[node] = 0;
		return ;
	}

	if(x1==x2 && y1==y2)
	{
		p[node] = 0;//Special case , a[x1][y1] in general
	}
	else
	{
		int ymid = (y1+y2)/2,xmid = (x1+x2)/2;
		init(4*node+1,x1,y1,xmid,ymid);
		init(4*node+2,x1,ymid+1,xmid,y2);
		init(4*node+3,xmid+1,y1,x2,ymid);
		init(4*node+4,xmid+1,ymid+1,x2,y2);
		p[node] = p[4*node+1] + p[4*node+2] + p[4*node+3] + p[4*node+4];
	}
	//p[node]%=MOD;
	lazy[node] = 0;
}


bool rect_overlap(int x1,int y1,int x2,int y2,int x3,int y3,int x4,int y4)
{
	return !(y2<y3 || y1>y4 || x2<x3 || x1>x4);
}

bool pt_inside_rect(int x,int y,int x1,int y1,int x2,int y2)
{
	return (x>=x1 && x<=x2 && y>=y1 && y<=y2);
}

bool rect_inside_rect(int x1,int y1,int x2,int y2,int x3,int y3,int x4,int y4)
{
	return pt_inside_rect(x1,y1,x3,y3,x4,y4) && pt_inside_rect(x2,y2,x3,y3,x4,y4);	
}


void update(int node,int x1,int y1,int x2,int y2,int qx1,int qy1,int qx2,int qy2,int value)
{
	if(x1>x2 || y1>y2 || !rect_overlap(x1,y1,x2,y2,qx1,qy1,qx2,qy2))return ;

	if(lazy[node])
	{
		p[node]+=(lazy[node]*(x2-x1+1)*(y2-y1+1));
		p[node]%=MOD;
		lazy[4*node+1]+=lazy[node],lazy[4*node+2]+=lazy[node],lazy[4*node+3]+=lazy[node],lazy[4*node+4]+=lazy[node];
		lazy[node] = 0;
	}

	if(rect_inside_rect(x1,y1,x2,y2,qx1,qy1,qx2,qy2))
	{
		p[node]+=(value*(x2-x1+1)*(y2-y1+1));
		if(x1!=x2 || y1!=y2)
		{
			lazy[4*node+1]+=value,lazy[4*node+2]+=value,lazy[4*node+3]+=value,lazy[4*node+4]+=value;
		}
	}
	else
	{
		int ymid = (y1+y2)/2,xmid = (x1+x2)/2;
		update(4*node+1,x1,y1,xmid,ymid,qx1,qy1,qx2,qy2,value);
		update(4*node+2,x1,ymid+1,xmid,y2,qx1,qy1,qx2,qy2,value);
		update(4*node+3,xmid+1,y1,x2,ymid,qx1,qy1,qx2,qy2,value);
		update(4*node+4,xmid+1,ymid+1,x2,y2,qx1,qy1,qx2,qy2,value);
		p[node] = p[4*node+1] + p[4*node+2] + p[4*node+3] + p[4*node+4];
	}
	//p[node]%=MOD;
}


int query(int node,int x1,int y1,int x2,int y2,int qx1,int qy1,int qx2,int qy2)
{
	if(x1>x2 || y1>y2 || !rect_overlap(x1,y1,x2,y2,qx1,qy1,qx2,qy2))return 0;

	if(lazy[node])
	{
		p[node]+=(lazy[node]*(x2-x1+1)*(y2-y1+1));
		p[node]%=MOD;
		lazy[4*node+1]+=lazy[node],lazy[4*node+2]+=lazy[node],lazy[4*node+3]+=lazy[node],lazy[4*node+4]+=lazy[node];
		lazy[node] = 0;
	}

	if(rect_inside_rect(x1,y1,x2,y2,qx1,qy1,qx2,qy2))
	{
		return p[node];
	}
	else
	{
		int ymid = (y1+y2)/2,xmid = (x1+x2)/2;
		int v1 = query(4*node+1,x1,y1,xmid,ymid,qx1,qy1,qx2,qy2);
		int v2 = query(4*node+2,x1,ymid+1,xmid,y2,qx1,qy1,qx2,qy2);
		int v3 = query(4*node+3,xmid+1,y1,x2,ymid,qx1,qy1,qx2,qy2);
		int v4 = query(4*node+4,xmid+1,ymid+1,x2,y2,qx1,qy1,qx2,qy2);
		p[node] = p[4*node+1] + p[4*node+2] + p[4*node+3] + p[4*node+4];
		//p[node]%=MOD;
		return (v1+v2+v3+v4);
	}
	
}

