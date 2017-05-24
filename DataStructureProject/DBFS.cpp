#include "stdafx.h"
#include "DBFS.h"
//#define result 4890576741


DBFS::DBFS(int *a, int *r)
{
	input(a, r);
}


DBFS::~DBFS()
{
	reset();
}

void DBFS::input(int * a, int * r)
{
	checkPuzzle(a);
	checkPuzzle(r);
	puzzle = a;
	target = r;
}

void DBFS::solve()
{
	check();
	if (!solved)
		return;
	solved = false;
	result = genLong(target);
	long long p = genLong(puzzle);
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

void DBFS::check()
{
	int k = 0, m = 0;
	for (int i = 0; i < 9; i++) {
		if (puzzle[i] == 0)
			continue;
		for (int j = 0; j < i; j++) {
			if (puzzle[j] > puzzle[i])
				k++;
		}
	}
	
	for (int i = 0; i < 9; i++) {
		if (target[i] == 0)
			continue;
		for (int j = 0; j < i; j++) {
			if (target[j] > target[i])
				m++;
		}
	}

	if (k % 2 == m % 2)
		solved = true;
	else
		solved = false;
}

void DBFS::output()
{
	if (solved)
	{
		int i = -1, j = -1;
		long long now = fEnd;
		do {
			i++;
			out.push(now);
			now = path[now];
		} while (now != -1);

		while (!out.empty()) {
			output(out.top());
			out.pop();
			cout << "  ↓" << endl;
			cout << endl;
		}
		now = reverseEnd;
		
		do {
			j++;
			output(now);
			cout << "  ↓" << endl;
			cout << endl;
			now = path2[now];
		} while (now != -1);
		cout << "End" << endl;
		cout << "Solved With " << i+j+1 << " Steps" << endl;
	}
	else {
		cout << "No Such Path" << endl;
	}
}

void DBFS::reset()
{
	while (!toCheck.empty()) {
		toCheck.pop();
	}

	while (!reverseToCheck.empty()) {
		reverseToCheck.pop();
	}

	while (!out.empty()) {
		out.pop();
	}
	checked.clear();
	reverseChecked.clear();

	path.clear();
	path2.clear();

	solved = false;
	puzzle = nullptr;
	target = nullptr;
	result = 0;
	fEnd = 0;
	reverseEnd = 0;
}


void DBFS::swapAndAdd(long long p)
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

void DBFS::swapAndAdd2(long long p)
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

void DBFS::addToQueue(long long o, long long p)
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

void DBFS::addToQueue2(long long o, long long p)
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

void DBFS::checkPuzzle(int * p)
{
	bool test[9];

	for (int i = 0; i < 9; i++) {
		test[i] = false;
	}

	for (int i = 0; i < 9; i++) {
		if (p[i] > -1 && p[i] < 9) {
			if (test[p[i]]) {
				throw PuzzleException(NUM_DUPLICATED);
			}
			else {
				test[p[i]] = true;
			}
		}
		else {
			throw PuzzleException(NUM_INVALID);
		}
	}
}

long long DBFS::genLong(int * p)
{
	//x64 int
	long long status = 0;
	for (int i = 0; i < 9; i++) {
		status = status << 4;
		status += p[i];
	}
	return status;
}

int * DBFS::genArray(long long p)
{
	int *ptr = new int[9];

	for (int i = 8; i > -1; i--) {
		ptr[i] = p & 15;
		p = p >> 4;
	}

	return ptr;
}

void DBFS::output(long long p)
{
	int * a = genArray(p);
	for (int i = 0; i < 9; i++) {
		if (a[i] > 0)
			cout << a[i] << " ";
		else
			cout << "  ";
		if (i % 3 == 2)
			cout << endl;
	}
	cout << endl;

}

