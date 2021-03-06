// ConsoleApplication420.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#define  _CRT_SECURE_NO_WARNINGS
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
struct L {
	char be[maxn];
	char ed[maxn];
	char number[maxn];
	int num;
	bool es;
	L() :es(1) {}
};
typedef ticket node;
class TicketSystem {
private:
	vector<node>BuyPP;//买票票系统
	L nodes[999];//订单
	int queue[30] = {};
	int tot = 0;//订单号
public:
	int findNode(char number[])//判断某班次是否已经存在
	{
		for (int i = 0; i < BuyPP.size(); i++)
			if (!strcmp(number, BuyPP[i].number))return i;
		return -1;
	}
	//查找班次(不存在返回-1，否则返回下标)
	void findNode_by_des(int i,int &a, int &b, char be[], char ed[])
	{
			int bok = 0, eok = 0;
			for (int m = 0; strlen(BuyPP[i].station[m]); m++)
			{
				if ((bok == 0) && (strcmp(BuyPP[i].station[m], be) == 0)) { bok = 1; a = m; }
				else
					if ((bok == 1) && (eok == 0) && (strcmp(BuyPP[i].station[m], be) == 0)) {
						eok = 1; b = m; break;
					}
				if (bok&&eok) break;
			}
			
	}
	//查找班次（利用引用传值，返回出发站点与终止站点的下标）
	bool deleteNode(char number[])
	{
		int pos = findNode(number);
		if (pos == -1)return false;
		else
		{
			int ok = 1;
			for(int i=0;strlen(BuyPP[pos].station[i]);i++)
				if (BuyPP[pos].rest[i] != 100) { ok = 0; break; }
			if (ok)
			{
				vector<node>::iterator it = BuyPP.begin();
				for (int i = 0; i < pos; i++)it++;
				BuyPP.erase(it);
				return true;
			}
			else
				return false;
		}
	}
	//删除班次
	bool addNode(char input[])//添加手动输入的班次（文件输入还不会）
	{
		char buf[maxn];
		sscanf(input, "%[^,]", buf);
		node t;
		if (findNode(buf) != -1)return false;
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
	//添加班次
	/*bool chaNode(char number[])
	{
		int pos = findNode(number);
		if (pos == -1)return false;
		else
		{
			return true;
		}
	}
	*/
	bool checkNode_by_num(char number[])
	{
		int pos = findNode(number);
		if (pos == -1) { cout << "查无此班次，请确认输入无误" << endl; return false; }
		else
		{
			cout << number << ",100|";
			for (int i = 0; strlen(BuyPP[pos].station[i]); i++)
			{
				cout << BuyPP[pos].station[i] << "," << BuyPP[pos].rest[i] << "|";
			}
			cout << endl;
		}
	}
	//利用班次号查询某班车信息
	void sort(int a[], int n)
	{
		for (int i = 1; i < n; i++)
		{
			int j = i, t = i;
			for (; j >= 1 && cmp(BuyPP[a[j]].number, BuyPP[a[j - 1]].number); j--)
				a[j] = a[j - 1];
			a[j] = t;
		}
	}
	//排序
	bool cmp(char a[], char b[])
	{
		if (a[0] > b[0])return true;
		else
			if (a[0] < b[0])return false;
			else
			{
				int a_num, b_num;
				sscanf(a, "%d", a_num);
				sscanf(b, "%d", b_num);
				if (a_num > b_num)return true;
				else
					return false;
			}
	}
	//判断字符串a是否大于字符串b
	void printNode(int a[], int n,char b[])
	{
		for (int i = 0; i < n; i++)
		{
			cout << BuyPP[a[i]].number << "          余票数：     ";
			int m;
			for (m = 0; strcmp(BuyPP[a[i]].station[m], b) != 0; m++);
			cout << BuyPP[a[i]].rest[m]<<endl;
		}
	}
	//打印
	bool checkNode_by_des(char be[], char ed[])
	{
		memset(queue, 0, sizeof(queue));
		int cnt = 0;
		for (int i = 0; i < BuyPP.size(); i++)
		{
			int bok = 0, eok = 0;
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
		sort(queue, cnt);
		printNode(queue, cnt, be);
	}
	//利用终点查询班次与余票
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
	//从文件中输出班次
	void buildList(char number[],char be[],char ed[],int num)
	{
		strcpy(nodes[++tot].number, number);
		strcpy(nodes[tot].be ,be);
		strcpy(nodes[tot].ed , ed);
		nodes[tot].num = num;
		cout << "订单号为：";
		printf("%03d", tot);
	}
	//生成订单
	void viewList()
	{
		cout << "订单号      车次    起点        终点        票数" << endl;
		for (int i = 1; i <= tot; i++)
		{
			if (nodes[i].es)
			{
				printf("%03d    %4s  %8s  %8s  %d\n", tot,nodes[i].number,nodes[i].be,nodes[i].ed,nodes[i].num);
			}
		}
	}
	//查看订单
	bool  outputList()
	{
		FILE *fp = fopen("d:\\info.txt", "w");
		if (fp == NULL) {
			cout << "读取文件错误！\n"; return false;
		}
		else
		{
			fprintf(fp, "订单号      车次    起点        终点        票数\n");
			for (int i = 1; i <= tot; i++)
			{
				if (nodes[i].es)
				{
					fprintf(fp,"%03d    %4s  %8s  %8s  %d\n", tot, nodes[i].number, nodes[i].be, nodes[i].ed, nodes[i].num);
				}
			}
		}
		fclose(fp);
		return true;
	}
	//输出订单
	void buyTicket()
	{
		char be[maxn], ed[maxn],number[maxn];
		int num,a,b,des;
		cin >> be >> ed;
		checkNode_by_des(be, ed);
		cout << "购买的班次：" ;
		cin >> number;cout << endl;
		cout << "购买的数量：" ;
		cin >> num;cout << endl;
		des = findNode(number);
		findNode_by_des(des,a, b, be, ed);
		if (BuyPP[des].rest[a] < num) { cout << "票数不足！" << endl; return; }
		else
		{
			buildList(number,be, ed, num);
			cout << ".  购票成功！" << endl;
			for (int i = a; i <= b; i++)
			{
				BuyPP[des].rest[i] -= num;
			}
			return;
		}
	}
	//买票
	void returnTicket()
	{
		int num,m,a,b,n;
		cout << "请输入订单号：";
		cin >> num; cout << endl;
		n = nodes[num].num;//确定票数
		m = findNode(nodes[num].number);//确定班次
		findNode_by_des(m, a, b, nodes[num].be, nodes[num].ed);//确定起点与终点
		nodes[num].es = 0;
		for (int i = a; i <= b; i++)
		{
			BuyPP[m].rest[i] += n;
		}
		cout << "退票成功！" << endl;
	}
	//退票

};

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
