#include "stdafx.h"
#include "EightPuzzle.h"
//#define result 4890576741

EightPuzzle::EightPuzzle(int *a, int *r)
{
	input(a, r);
}


EightPuzzle::~EightPuzzle()
{
	reset();
}

void EightPuzzle::input(int * a,int * r)
{
	//bool 
	checkPuzzle(a);
	checkPuzzle(r);
	puzzle = a;
	target = r;
}

void EightPuzzle::solve()
{
	check();
	if (!solved)
		return;
	solved = false;
	result = genLong(target);
	long long p = genLong(puzzle);
	addToQueue(-1, p);
	while (!toCheck.empty()) {
		if (solved) {
			return;
		}
		long long next = toCheck.front();
		toCheck.pop();
		visit++;
		swapAndAdd(next);
	}
	solved = false;
}

void EightPuzzle::output()
{
	if (solved)
	{
		int i = -1;
		long long now = result;
		do {
			i++;
			out.push(now);
			//int *maze = genArray(now);
			//for (int i = 0; i < 9; i++) {
			//	cout << maze[i] << " ";
			//	if (i % 3 == 2)
			//		cout << endl;
			//}
			//cout << endl;
			now = path[now];
		} while (now != -1);

		while (!out.empty()) {
			output(out.top());
			out.pop();
			cout << "  ↓" << endl;
			cout << endl;
		}
		cout << "End" << endl;
		cout << endl;
		cout << "Solved With " << i << " Steps" << endl;
	}
	else {
		cout << "No Such Path" << endl;
	}
}

void EightPuzzle::reset()
{
	while (!toCheck.empty()) {
		toCheck.pop();
	}

	while (!out.empty()) {
		out.pop();
	}
	checked.clear();
	path.clear();
	solved = false;
	puzzle = nullptr;
	target = nullptr;
	result = 0;
	visit = 0;
}

int EightPuzzle::getSteps()
{
	if (solved)
	{
		int i = -1;
		long long now = result;
		do {
			i++;
			//int *maze = genArray(now);
			//for (int i = 0; i < 9; i++) {
			//	cout << maze[i] << " ";
			//	if (i % 3 == 2)
			//		cout << endl;
			//}
			//cout << endl;
			now = path[now];
		} while (now != -1);

		return i;
	}
	else {
		return -1;
	}
}

int EightPuzzle::getVisit()
{
	return visit;
}


void EightPuzzle::check()
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

void EightPuzzle::checkPuzzle(int * p)
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

void EightPuzzle::swapAndAdd(long long p)
{
	long long i, j = 0;
	for (i = 15; (i&p)!=0; i = i << 4, j++);
	long long b,next;
	//向上移动
	b = (i << 12)&p;
	next = (~(i << 12))&p;
	next = (~i)&next;
	next = (b >> 12) | next;
	addToQueue(p,next);


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

void EightPuzzle::addToQueue(long long o,long long p)
{
	if (checked.find(p) == checked.end())
	{
		checked.insert(p);
		toCheck.push(p);
		//const int from = p;
		//path.insert(,)
		path[p] = o;
		
		if (p == result)
			solved = true;
		
	}
}

long long EightPuzzle::genLong(int * p)
{
	//x64 int
	long long status = 0;
	for (int i = 0; i < 9; i++) {
		status = status << 4;
		status += p[i];
	}
	return status;
}

int * EightPuzzle::genArray(long long p)
{
	int *ptr = new int[9];

	for (int i = 8; i > -1; i--) {
		ptr[i] = p & 15;
		p = p >> 4;
	}

	return ptr;
}

void EightPuzzle::output(long long p)
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
