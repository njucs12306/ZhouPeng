
#include "pch.h"
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include <vector>
#include "TicketSystem.h"
#include "L.h"

using namespace std;

int TicketSystem::findNode(char number[])
{
	for (int i = 0; i < BuyPP.size(); i++)
		if (strcmp(number, BuyPP[i].number)==0)return i;
	return -1;
}
//查找班次(不存在返回-1，否则返回下标)  

void TicketSystem::findNode_by_des(int i, int &a, int &b, char be[], char ed[])
{
	int bok = 0, eok = 0;
	for (int m = 0; strlen(BuyPP[i].station[m]); m++)
	{
		if ((bok == 0) && (strcmp(BuyPP[i].station[m], be) == 0)) { bok = 1; a = m; }
		else
			if ((bok == 1) && (eok == 0) && (strcmp(BuyPP[i].station[m], ed) == 0)) {
				eok = 1; b = m; break;
			}
		if (bok&&eok) break;
	}
}
//查找班次（利用引用传值，返回出发站点与终止站点的下标）  

bool TicketSystem::deleteNode(char number[])
{
	int pos = findNode(number);
	if (pos == -1) { cout << "该班次不存在！\n"; return false; }
	else
	{
		int ok = 1;
		for (int i = 0; strlen(BuyPP[pos].station[i]); i++)
			if (BuyPP[pos].rest[i] != 100) { ok = 0; break; }
		if (ok)
		{
			vector<node>::iterator it = BuyPP.begin();
			for (int i = 0; i < pos; i++)it++;
			BuyPP.erase(it);
			return true;
		}
		else
		{
			cout << "删除失败！\n";
			return false;
		}
	}
	cout << "删除成功！\n";
}
//删除班次  O(n)
bool TicketSystem::addNode(char input[])
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
	}
	cout << "\n添加成功！\n";
}
//添加班次
bool TicketSystem::checkNode_by_num(char number[])
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
//利用班次号查询某班车信息  O(n)
void TicketSystem::sort(int a[], int n)
{
	for (int i = 1; i < n; i++)
	{
		int j = i, t = i;
		for (; j >= 1 && cmp(BuyPP[a[j]].number, BuyPP[a[j - 1]].number); j--)
			a[j] = a[j - 1];
		a[j] = t;
	}
}
//排序 O(n^2)
bool TicketSystem::cmp(char a[], char b[])
{
	if (a[0] > b[0])return true;
	else
		if (a[0] < b[0])return false;
		else
		{
			int a_num, b_num;
			sscanf(a, "%d", &a_num);
			sscanf(b, "%d", &b_num);
			if (a_num > b_num)return true;
			else
				return false;
		}
}
//判断字符串a是否大于字符串b  O(n)
void TicketSystem::printNode(int a[], int n, char b[])
{
	for (int i = 0; i < n; i++)
	{
		cout << BuyPP[a[i]].number << "          余票数：     ";
		int m;
		for (m = 0; strcmp(BuyPP[a[i]].station[m], b) != 0; m++);
		cout << BuyPP[a[i]].rest[m] << endl;
	}
}
//打印
void TicketSystem::checkNode_by_des(char be[], char ed[])
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
				if ((bok == 1) && (eok == 0) && (strcmp(BuyPP[i].station[m], ed) == 0)) {
					eok = 1; break;
				}
		}
		if (bok&&eok) queue[cnt++] = i;
	}
	sort(queue, cnt);
	printNode(queue, cnt, be);
}
//利用终点查询班次与余票 O(n)
bool TicketSystem::add_file()
{
	FILE *fp = fopen("d:\\info.txt", "r");
	if (fp == NULL)return false;
	else
	{
		char input[maxn * 10] = {};
		while (!feof(fp))
		{
			fgets(input, 10 * maxn, fp);
			int k = strlen(input);
			input[k] = '\0';
			addNode(input);
		}
		fclose(fp);
		return true;
	}
}
//从文件中输出班次
void TicketSystem::buildList(char number[], char be[], char ed[], int num)
{
	strcpy(nodes[++tot].number, number);
	strcpy(nodes[tot].be, be);
	strcpy(nodes[tot].ed, ed);
	nodes[tot].num = num;
	cout << "订单号为：";
	printf("%03d", tot);
}
//生成订单
void TicketSystem::viewList()
{
	cout << "订单号      车次    起点        终点        票数" << endl;
	for (int i = 1; i <= tot; i++)
	{
		if (nodes[i].es)
		{
			printf("%03d    %4s  %8s  %8s  %d\n", i, nodes[i].number, nodes[i].be, nodes[i].ed, nodes[i].num);
		}
	}
}
//查看订单
bool  TicketSystem::outputList()
{
	FILE *fp = fopen("d:\\output.txt", "w");
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
				fprintf(fp, "%03d    %4s  %8s  %8s  %d\n", tot, nodes[i].number, nodes[i].be, nodes[i].ed, nodes[i].num);
			}
		}
	}
	fclose(fp);
	return true;
}
//输出订单
void TicketSystem::buyTicket()
{
	char be[maxn], ed[maxn], number[maxn];
	int num, a, b, des;
	cout << "请分别输入起点和终点：";
	cin >> be >> ed;
	cout << endl;
	checkNode_by_des(be, ed);
	cout << "购买的班次：";
	cin >> number; cout << endl;
	cout << "购买的数量：";
	cin >> num; cout << endl;
	des = findNode(number);
	findNode_by_des(des, a, b, be, ed);
	if (BuyPP[des].rest[a] < num) { cout << "票数不足！" << endl; return; }
	else
	{
		buildList(number, be, ed, num);
		cout << ".  购票成功！" << endl;
		for (int i = a; i < b; i++)
		{
			BuyPP[des].rest[i] -= num;
		}
		return;
	}
}
//买票
void TicketSystem::returnTicket()
{
	int num, m, a, b, n;
	cout << "请输入订单号：";
	cin >> num; cout << endl;
	n = nodes[num].num;//确定票数
	m = findNode(nodes[num].number);//确定班次
	findNode_by_des(m, a, b, nodes[num].be, nodes[num].ed);//确定起点与终点
	nodes[num].es = 0;
	if (nodes[num].es == 0)
	{
		for (int i = a; i < b; i++)
		{
			BuyPP[m].rest[i] += n;
		}
		cout << "退票成功！" << endl;
	}
	else
		cout << "退票失败！" << endl;
}
//退票
void TicketSystem::main_menu()
{
	cout << "                                                ----------------------------" << endl
		<< "                                               |       1.录入班次信息       |" << endl
		<< "                                               |       2.操作班次信息       |" << endl
		<< "                                               |       3.查询班次信息       |" << endl
		<< "                                               |       4.售票退票系统       |" << endl
		<< "                                               |       5.导出票务信息       |" << endl
		<< "                                               |       6.退出系统           |" << endl
		<< "                                                ----------------------------" << endl;
	int n;
l:cout << "请输入您选择的功能：";
	cin >> n; cout << endl;
	switch (n)
	{
	case 1:nodes_system(); goto l;
	case 3:ticket_system(); goto l;
	case 4:list_system(); goto l;
	case 5:outputList(); goto l;
	case 6: cout << "已经退出系统！" << endl; break;
	}

}
void TicketSystem::nodes_system()
{
	cout << "                                                ---------------------------" << endl
		<< "                                               |       1.添加修改班次      |" << endl
		<< "                                               |       2.删除班次          |" << endl
		<< "                                               |       3.返回主菜单        |" << endl
		<< "                                                ---------------------------" << endl;
l:cout << "请输入你要使用的功能：";
	int n;
	cin >> n; cout << endl;
	if (n == 1)
	{
		cout << "如果想要手动输入，请输入1；反之输入2:";
		int k; cin >> k;
		if (k == 1)
		{
			char input[200]; cout << "请输入班次信息：\n"; cin >> input; addNode(input); goto l;
		}
		else
		{
			add_file(); cout << "文件输入成功！" << endl; goto l;
		}
	}
	else
		if (n == 2)
		{
			char input[200]; cout << "请输入班次信息：\n";
			cin >> input; deleteNode(input); goto l;
		}
		else
		{
			main_menu();
		}
}
void TicketSystem::ticket_system()
{
	cout << "                                               ----------------------------" << endl
		<< "                                               |      1.按班次查询          |" << endl
		<< "                                               |      2.按出发目的地查询    |" << endl
		<< "                                               |      3.返回主菜单          |" << endl
		<< "                                                ----------------------------" << endl;
l:cout << "请输入你要使用的功能：";
	int n;
	cin >> n; cout << endl;
	if (n == 1)
	{
		cout << "请输入查询的班次号："; char number[maxn]; cin >> number; cout << endl; checkNode_by_num(number); goto l;
	}
	else
		if (n == 2)
		{
			char be[10 * maxn], ed[10 * maxn];
			cout << "请输入起点：";
			cin >> be; cout << endl;
			cout << "请输入终点:";
			cin >> ed; cout << endl;
			checkNode_by_des(be, ed); goto l;
		}
		else
			main_menu();
}
void TicketSystem::list_system()
{
	cout << "                                               ----------------------------" << endl
		<< "                                               |       1.售票               |" << endl
		<< "                                               |       2.订单预览           |" << endl
		<< "                                               |       3.退票               |" << endl
		<< "                                               |       4.返回主菜单         |" << endl
		<< "                                                ----------------------------" << endl;
l:cout << "请输入要选择的功能：";
	int n;
	cin >> n; cout << endl;
	switch (n)
	{
	case 1: buyTicket(); goto l;
	case 2: viewList(); goto l;
	case 3:returnTicket(); goto l;
	case 4:main_menu(); break;
	}
}