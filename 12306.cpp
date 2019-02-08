// ConsoleApplication419.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>
#include <algorithm>
#define maxn 30
#define maxv 1100
using namespace std;

struct ticket {
	char number[maxn];
	int size;
	char station[maxn][maxn];
	int  rest[maxn];
	ticket() :size(100) {}
};
typedef ticket node;
vector<node>BuyPP;//买票票系统
int queue[30] = {};
int tot = 0;//订单号

int findNode(char number[])//判断某班次是否已经存在
{
	for (int i = 0; i < BuyPP.size(); i++)
		if (!strcmp(number,BuyPP[i].number))return i;
	return -1;
}

bool deleteNode(char number[])
{
	int pos = findNode(number);
	if (pos== -1)return false;
	else
	{
		vector<node>::iterator it = BuyPP.begin();
		for (int i = 0; i < pos; i++)it++;
		BuyPP.erase(it);
	}
}

bool addNode(char input[])//添加手动输入的班次（文件输入还不会）
{
	char buf[maxn];
	sscanf(input, "%[^,]", buf);
	node t;
	if (findNode(buf)!=-1)return false;
	else
	{
		strcpy(t.number, buf);
		int p = 0, q = 0, len = strlen(input), i = 0;
		while (true)
		{
			int j = 0;
			while (input[p] != '|')p++;
			q = p + 1;
			while (input[q] != '|'&&q < len)q++;
			if (q == len)break;
			for (int m = p + 1; m < q; m++)
				t.station[i][j++] = input[m];
			t.rest[i] = 100;
			t.station[i++][j] = '\0';
			p++;
		}
		BuyPP.push_back(t);
		cout << t.number << endl;
		for (int m = 0; m < i; m++)
			cout << t.station[m] << endl;
		cout << t.size << endl;
	}
}

bool chaNode(char number[])
{
	int pos = findNode(number);
	if (pos == -1)return false;
	else
	{
		return true;
	}
}

bool checkNode(char number[])
{
	int pos = findNode(number);
	if (pos == -1) { cout << "查无此班次，请确认输入无误" << endl; return false; }
	else
	{
		cout << number << ",100|";
		for (int i = 0;strlen(BuyPP[pos].station[i]); i++)
		{
			cout << BuyPP[pos].station[i] << "," << BuyPP[pos].rest[i] << "|";
		}
		cout << endl;
	}
}

void sort(int a[],int n)
{
	for (int i = 1; i < n; i++)
	{
		int j = i,t=i;
		for(;j>=1&&)
	}
}

/*bool cmp(char a[], char b[])
{
	int l1 = strlen(a), l2 = strlen(b);
	int l = min(l1, l2);
	for(int i=0;i)
}*/

bool buyNode(char be[], char ed[])
{
	memset(queue, 0, sizeof(queue));
	int cnt = 0;
	for (int i = 0; i < BuyPP.size(); i++)
	{
		int bok = 0,eok=0;
		for (int m = 0; strlen(BuyPP[i].station[m]); m++)
		{
			if ((bok == 0) && (strcmp(BuyPP[i].station[m], be) == 0))bok = 1;
			else
				if ((bok == 1) && (eok == 0) && (strcmp(BuyPP[i].station[m], be) == 0)) {
					eok = 1; break;
				}
		}
		if (bok&&eok) queue[cnt++] = i;
	}

}
bool add_file()
{
	FILE *fp = fopen("d:\\info.txt", "r");
	if (fp == NULL)return false;
	else
	{
		char input[maxn * 10] = {};
		while (!feof(fp))
		{
			fgets(input, 10 * maxn, fp);
			addNode(input);
		}
		fclose(fp);
		return true;
	}
}

int main()
{
	char name[20] = "d10", name2[20] = "d11";
	if (name > name2)cout << 1;
	else
		cout << 0;
	return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门提示: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
