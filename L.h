#ifndef L_H
#define L_H

#include <iostream>
#define maxn 30
#define maxv 1100

struct ticket {
	char number[maxn];
	int size;
	char station[maxn][maxn];
	int  rest[maxn];
	ticket() :size(100) {}
};

struct L {
	char be[maxn];
	char ed[maxn];
	char number[maxn];
	int num;
	bool es;
	L() :es(1) {}
};

#endif