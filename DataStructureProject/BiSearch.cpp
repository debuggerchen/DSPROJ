#include "stdafx.h"
#include "BiSearch.h"
#define result 4890576741


BiSearch::BiSearch()
{
}


BiSearch::~BiSearch()
{
	while (!toCheck.empty()) {
		toCheck.pop();
	}

	while (!reverseToCheck.empty()) {
		reverseToCheck.pop();
	}
	checked.clear();
	reverseChecked.clear();

	path.clear();
	path2.clear();

}

void BiSearch::input(int * a)
{
	puzzle = a;
}

void BiSearch::solve()
{
	check();
	if (!solved)
		return;
	solved = false;
	long long p = genInt(puzzle);
	addToQueue(-1, p);
	addToQueue2(-1, result);
	while (!solved) {
		if (!toCheck.empty()) {
			long long next = toCheck.front();
			toCheck.pop();
			swapAndAdd(next);
		}
		else {
			break;
		}
		
		if (!reverseToCheck.empty()) {
			long long next = reverseToCheck.front();
			reverseToCheck.pop();
			swapAndAdd2(next);
		}

	}
}

void BiSearch::check()
{
	int k = 0;
	for (int i = 0; i < 9; i++) {
		if (puzzle[i] == 0)
			continue;
		for (int j = 0; j < i; j++) {
			if (puzzle[j] > puzzle[i])
				k++;
		}
	}
	if (k % 2 == 0)
		solved = false;
	else
		solved = true;
}

void BiSearch::output()
{
	if (solved)
	{
		int i = -1, j = -1;
		long long now = fEnd;
		do {
			i++;
			now = path[now];
		} while (now != -1);
		now = reverseEnd;
		do {
			j++;
			now = path2[now];
		} while (now != -1);

		cout << "Solved With " << i+j+1 << " Steps" << endl;
	}
	else {
		cout << "No Such Path" << endl;
	}
}

void BiSearch::release()
{
	while (!toCheck.empty()) {
		toCheck.pop();
	}
	while (!reverseToCheck.empty()) {
		reverseToCheck.pop();
	}
	checked.clear();
	reverseChecked.clear();
	path.clear();
	path2.clear();
	//Consider

}


void BiSearch::swapAndAdd(long long p)
{
	long long i, j = 0;
	for (i = 15; (i&p) != 0; i = i << 4, j++);
	long long b, next;
	//向上移动
	b = (i << 12)&p;
	next = (~(i << 12))&p;
	next = (~i)&next;
	next = (b >> 12) | next;
	addToQueue(p, next);


	//向下移动
	b = (i >> 12)&p;
	next = (~(i >> 12))&p;
	next = (~i)&next;
	next = (b << 12) | next;
	addToQueue(p, next);


	//向左移动
	if (j % 3 != 2) {
		b = (i << 4)&p;
		next = (~(i << 4))&p;
		next = (~i)&next;
		next = (b >> 4) | next;
		addToQueue(p, next);
	}

	//向右移动
	if (j % 3 != 0) {
		b = (i >> 4)&p;
		next = (~(i >> 4))&p;
		next = (~i)&next;
		next = (b << 4) | next;
		addToQueue(p, next);
	}

}

void BiSearch::swapAndAdd2(long long p)
{
	long long i, j = 0;
	for (i = 15; (i&p) != 0; i = i << 4, j++);
	long long b, next;
	//向上移动
	b = (i << 12)&p;
	next = (~(i << 12))&p;
	next = (~i)&next;
	next = (b >> 12) | next;
	addToQueue2(p, next);


	//向下移动
	b = (i >> 12)&p;
	next = (~(i >> 12))&p;
	next = (~i)&next;
	next = (b << 12) | next;
	addToQueue2(p, next);


	//向左移动
	if (j % 3 != 2) {
		b = (i << 4)&p;
		next = (~(i << 4))&p;
		next = (~i)&next;
		next = (b >> 4) | next;
		addToQueue2(p, next);
	}

	//向右移动
	if (j % 3 != 0) {
		b = (i >> 4)&p;
		next = (~(i >> 4))&p;
		next = (~i)&next;
		next = (b << 4) | next;
		addToQueue2(p, next);
	}

}

void BiSearch::addToQueue(long long o, long long p)
{
	if (checked.find(p) == checked.end())
	{
		path[p] = o;
		if (reverseChecked.find(p)!=reverseChecked.end()){
			solved = true;
			fEnd = o;
			reverseEnd = p;
		}

		checked.insert(p);
		toCheck.push(p);
		//const int from = p;
		//path.insert(,)


	}
}

void BiSearch::addToQueue2(long long o, long long p)
{
	if (reverseChecked.find(p) == reverseChecked.end())
	{
		path2[p] = o;
		if (checked.find(p) != checked.end()) {
			fEnd = p;
			reverseEnd = o;
			solved = true;
		}
		reverseChecked.insert(p);
		reverseToCheck.push(p);
		//const int from = p;
		//path.insert(,)


	}

}

long long BiSearch::genInt(int * p)
{
	//x64 int
	long long status = 0;
	for (int i = 0; i < 9; i++) {
		status = status << 4;
		status += p[i];
	}
	return status;
}

int * BiSearch::genArray(long long p)
{
	int *ptr = new int[9];

	for (int i = 8; i > -1; i--) {
		ptr[i] = p & 15;
		p = p >> 4;
	}

	return ptr;
}

void BiSearch::output(long long p)
{
	int * a = genArray(p);
	for (int i = 0; i < 9; i++) {
		cout << a[i] << " ";
		if (i % 3 == 2)
			cout << endl;
	}
	cout << endl;

}

