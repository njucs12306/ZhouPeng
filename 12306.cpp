// ConsoleApplication415.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <cstring>
#define maxn 30
using namespace std;

struct ticket {
	char number[maxn];
	int size;
	char station[maxn][maxn];
	ticket() :size(100) {}
};
typedef ticket node;
vector <node> BuyPP;//买票票系统
int tot = 0;//订单号

bool findNode(char number[])//判断某班次是否已经存在
{
	for (int i = 0; i < BuyPP.size(); i++)
		if (!strcmp(number,BuyPP[i].number))return true;
	return false;
}

bool addNode(char input[])//添加手动输入的班次（文件输入还不会）
{
	char buf[maxn];
	sscanf(input, "%[^,]", buf);
	node t;
	if (findNode(buf))return false;
	else
		strcpy(t.number, buf);
	int p = 0, q = 0,len=strlen(input),i=0;
	while (true)
	{
		int j = 0;
		while (input[p]!= '|')p++;
		q = p + 1;
		while (input[q]!= '|'&&q<len)q++;
		if (q == len)break;
		for (int m = p + 1; m < q; m++)
			t.station[i][j++] = input[m];
		t.station[i++][j] = '\0';
		p++;
	}
	cout << t.number << endl;
	for (int m = 0; m < i; m++)
		cout << t.station[m] << endl;
	cout <<t.size << endl;
}


int main()
{
	char input[1000] = "D95,100|nju|pju|thu|";
	addNode(input);
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
