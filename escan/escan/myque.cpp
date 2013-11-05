// myque.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "queue.h"
#include <process.h>
#include <stdlib.h>
#include <windows.h>

char *sexs[] = { "女", "男" };
struct People
{
	char name[20];
	int age;
	bool sex;
};

void enque(void *q)
{
	Queue *qu = (Queue *)q;
	People p;
	while (true)
	{
		int i, j, sex;
		for (i = 0; i < 1024;)
		{
			for (j = 0; j < 10; j++)
			{
				p.name[j] = rand() % 26 + 'a';
			}
			p.name[j] = 0;
			sex = rand() % 2;
			p.age = rand() % 100;
			p.sex = sex ? true : false;
			if (EnQueue(qu, &p) == -1)
			{
				printf("enque error.\n");
				Sleep(1000);
			}
			else
			{
				printf("**入队** name: %s, age: %d, sex: %s\n", p.name, p.age, sexs[sex]);
				i++;
			}
		}
	}
}

void deque(void *q)
{
	People p;
	Queue *qu = (Queue *)q;
	Sleep(5000);
	while (true)
	{
		if (DeQueue(qu, &p) == -1)
		{
			printf("deque error.\n");
		}
		else
		{
			int sex = p.sex ? 1 : 0;
			printf("##出队## name: %s, age: %d, sex: %s\n", p.name, p.age, sexs[sex]);
		}
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	Queue *q = QueueInit(10, sizeof(People));
	_beginthread(enque, 0, q);
	_beginthread(deque, 0, q);
	while (true)
	{
		Sleep(10000000);
	}
	return 0;
}

