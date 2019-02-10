#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include "TicketSystem.h"
#include "L.h"
#define maxn 30
#define maxv 1100
using namespace std;
typedef ticket node;

class TicketSystem 
{
private:
	vector <node> BuyPP;//买票票系统
	L nodes[999];//订单
	int queue[30] = {};
	int tot = 0;//订单号
public:
	int findNode(char number[]);
	void findNode_by_des(int i, int &a, int &b, char be[], char ed[]);
	bool deleteNode(char number[]);
	bool addNode(char input[]);
	bool checkNode_by_num(char number[]);
	void sort(int a[], int n);
	bool cmp(char a[], char b[]);
	void printNode(int a[], int n, char b[]);
	void checkNode_by_des(char be[], char ed[]);
	bool add_file();
	void buildList(char number[], char be[], char ed[], int num);
	bool outputList();
	void viewList();
	void buyTicket();
	void returnTicket();
	void main_menu();
	void nodes_system();
	void list_system();
	void ticket_system();
};
