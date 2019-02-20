
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
//���Ұ��(�����ڷ���-1�����򷵻��±�)  

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
//���Ұ�Σ��������ô�ֵ�����س���վ������ֹվ����±꣩  

bool TicketSystem::deleteNode(char number[])
{
	int pos = findNode(number);
	if (pos == -1) { cout << "�ð�β����ڣ�\n"; return false; }
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
			cout << "ɾ��ʧ�ܣ�\n";
			return false;
		}
	}
	cout << "ɾ���ɹ���\n";
}
//ɾ�����  O(n)
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
	cout << "\n��ӳɹ���\n";
}
//��Ӱ��
bool TicketSystem::checkNode_by_num(char number[])
{
	int pos = findNode(number);
	if (pos == -1) { cout << "���޴˰�Σ���ȷ����������" << endl; return false; }
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
//���ð�κŲ�ѯĳ�೵��Ϣ  O(n)
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
//���� O(n^2)
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
//�ж��ַ���a�Ƿ�����ַ���b  O(n)
void TicketSystem::printNode(int a[], int n, char b[])
{
	for (int i = 0; i < n; i++)
	{
		cout << BuyPP[a[i]].number << "          ��Ʊ����     ";
		int m;
		for (m = 0; strcmp(BuyPP[a[i]].station[m], b) != 0; m++);
		cout << BuyPP[a[i]].rest[m] << endl;
	}
}
//��ӡ
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
//�����յ��ѯ�������Ʊ O(n)
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
//���ļ���������
void TicketSystem::buildList(char number[], char be[], char ed[], int num)
{
	strcpy(nodes[++tot].number, number);
	strcpy(nodes[tot].be, be);
	strcpy(nodes[tot].ed, ed);
	nodes[tot].num = num;
	cout << "������Ϊ��";
	printf("%03d", tot);
}
//���ɶ���
void TicketSystem::viewList()
{
	cout << "������      ����    ���        �յ�        Ʊ��" << endl;
	for (int i = 1; i <= tot; i++)
	{
		if (nodes[i].es)
		{
			printf("%03d    %4s  %8s  %8s  %d\n", i, nodes[i].number, nodes[i].be, nodes[i].ed, nodes[i].num);
		}
	}
}
//�鿴����
bool  TicketSystem::outputList()
{
	FILE *fp = fopen("d:\\output.txt", "w");
	if (fp == NULL) {
		cout << "��ȡ�ļ�����\n"; return false;
	}
	else
	{
		fprintf(fp, "������      ����    ���        �յ�        Ʊ��\n");
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
//�������
void TicketSystem::buyTicket()
{
	char be[maxn], ed[maxn], number[maxn];
	int num, a, b, des;
	cout << "��ֱ����������յ㣺";
	cin >> be >> ed;
	cout << endl;
	checkNode_by_des(be, ed);
	cout << "����İ�Σ�";
	cin >> number; cout << endl;
	cout << "�����������";
	cin >> num; cout << endl;
	des = findNode(number);
	findNode_by_des(des, a, b, be, ed);
	if (BuyPP[des].rest[a] < num) { cout << "Ʊ�����㣡" << endl; return; }
	else
	{
		buildList(number, be, ed, num);
		cout << ".  ��Ʊ�ɹ���" << endl;
		for (int i = a; i < b; i++)
		{
			BuyPP[des].rest[i] -= num;
		}
		return;
	}
}
//��Ʊ
void TicketSystem::returnTicket()
{
	int num, m, a, b, n;
	cout << "�����붩���ţ�";
	cin >> num; cout << endl;
	n = nodes[num].num;//ȷ��Ʊ��
	m = findNode(nodes[num].number);//ȷ�����
	findNode_by_des(m, a, b, nodes[num].be, nodes[num].ed);//ȷ��������յ�
	nodes[num].es = 0;
	if (nodes[num].es == 0)
	{
		for (int i = a; i < b; i++)
		{
			BuyPP[m].rest[i] += n;
		}
		cout << "��Ʊ�ɹ���" << endl;
	}
	else
		cout << "��Ʊʧ�ܣ�" << endl;
}
//��Ʊ
void TicketSystem::main_menu()
{
	cout << "                                                ----------------------------" << endl
		<< "                                               |       1.¼������Ϣ       |" << endl
		<< "                                               |       2.���������Ϣ       |" << endl
		<< "                                               |       3.��ѯ�����Ϣ       |" << endl
		<< "                                               |       4.��Ʊ��Ʊϵͳ       |" << endl
		<< "                                               |       5.����Ʊ����Ϣ       |" << endl
		<< "                                               |       6.�˳�ϵͳ           |" << endl
		<< "                                                ----------------------------" << endl;
	int n;
l:cout << "��������ѡ��Ĺ��ܣ�";
	cin >> n; cout << endl;
	switch (n)
	{
	case 1:nodes_system(); goto l;
	case 3:ticket_system(); goto l;
	case 4:list_system(); goto l;
	case 5:outputList(); goto l;
	case 6: cout << "�Ѿ��˳�ϵͳ��" << endl; break;
	}

}
void TicketSystem::nodes_system()
{
	cout << "                                                ---------------------------" << endl
		<< "                                               |       1.����޸İ��      |" << endl
		<< "                                               |       2.ɾ�����          |" << endl
		<< "                                               |       3.�������˵�        |" << endl
		<< "                                                ---------------------------" << endl;
l:cout << "��������Ҫʹ�õĹ��ܣ�";
	int n;
	cin >> n; cout << endl;
	if (n == 1)
	{
		cout << "�����Ҫ�ֶ����룬������1����֮����2:";
		int k; cin >> k;
		if (k == 1)
		{
			char input[200]; cout << "����������Ϣ��\n"; cin >> input; addNode(input); goto l;
		}
		else
		{
			add_file(); cout << "�ļ�����ɹ���" << endl; goto l;
		}
	}
	else
		if (n == 2)
		{
			char input[200]; cout << "����������Ϣ��\n";
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
		<< "                                               |      1.����β�ѯ          |" << endl
		<< "                                               |      2.������Ŀ�ĵز�ѯ    |" << endl
		<< "                                               |      3.�������˵�          |" << endl
		<< "                                                ----------------------------" << endl;
l:cout << "��������Ҫʹ�õĹ��ܣ�";
	int n;
	cin >> n; cout << endl;
	if (n == 1)
	{
		cout << "�������ѯ�İ�κţ�"; char number[maxn]; cin >> number; cout << endl; checkNode_by_num(number); goto l;
	}
	else
		if (n == 2)
		{
			char be[10 * maxn], ed[10 * maxn];
			cout << "��������㣺";
			cin >> be; cout << endl;
			cout << "�������յ�:";
			cin >> ed; cout << endl;
			checkNode_by_des(be, ed); goto l;
		}
		else
			main_menu();
}
void TicketSystem::list_system()
{
	cout << "                                               ----------------------------" << endl
		<< "                                               |       1.��Ʊ               |" << endl
		<< "                                               |       2.����Ԥ��           |" << endl
		<< "                                               |       3.��Ʊ               |" << endl
		<< "                                               |       4.�������˵�         |" << endl
		<< "                                                ----------------------------" << endl;
l:cout << "������Ҫѡ��Ĺ��ܣ�";
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