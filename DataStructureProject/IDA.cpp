#include "stdafx.h"
#include "IDA.h"
//#define result 4890576741

IDA::IDA(int *a, int *r)
{
	input(a, r);
}


IDA::~IDA()
{
	reset();
}

void IDA::input(int * a, int * r)
{
	checkPuzzle(a);
	checkPuzzle(r);
	puzzle = a;
	target = r;
}

void IDA::solve()
{
	check();
	if (!solved)
		return;
	solved = false;
	result = genLong(target);
	long long p = genLong(puzzle);
	genManhattan();
	limit = distance(p);
	while (!ida(p, 0, distance(p),-1)) {
		limit++;
	}
}

void IDA::output()
{
	if (solved)
	{
		int i = -1;
		while (!out.empty()) {
			++i;
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

int IDA::getSteps()
{
	if (solved)
	{
		int i = -1;
		while (!out.empty()) {
			++i;
			out.pop();
		}
		return i;
	}
	else {
		return -1;
	}
}

int IDA::getVisit()
{
	return visit;
}

void IDA::reset()
{
	while (!out.empty()) {
		out.pop();
	}

	solved = false;
	limit = 0;
	result = 0;
	visit = 0;
	puzzle = nullptr;
	target = nullptr;
}

bool IDA::ida(long long status, int depth, int dis, long long last)
{
	visit++;
	if (status == result)
	{
		out.push(status);
		solved = true;
		return true;
	}

	if (depth + dis > limit)
	{
		return false;
	}

	long long i, j = 0;
	for (i = 15; (i&status) != 0; i = i << 4, j++);
	long long b, next;
	//向上移动
	if (j < 6)
	{
		b = (i << 12)&status;
		next = (~(i << 12))&status;
		next = (~i)&next;
		next = (b >> 12) | next;
		if (next != last&&ida(next, depth + 1, distance(next), status))
		{
			out.push(status);
			return true;
		}
	}
	//向下移动
	if (j > 2)
	{
		b = (i >> 12)&status;
		next = (~(i >> 12))&status;
		next = (~i)&next;
		next = (b << 12) | next;
		if (next != last&&ida(next, depth + 1, distance(next), status))
		{
			out.push(status);
			return true;
		}
	}
	//向左移动
	if (j % 3 != 2) {
		b = (i << 4)&status;
		next = (~(i << 4))&status;
		next = (~i)&next;
		next = (b >> 4) | next;
		if (next != last&&ida(next, depth + 1, distance(next),status))
		{
			out.push(status);
			return true;
		}
	}

	//向右移动
	if (j % 3 != 0) {
		b = (i >> 4)&status;
		next = (~(i >> 4))&status;
		next = (~i)&next;
		next = (b << 4) | next;
		if (next != last&&ida(next, depth + 1, distance(next),status))
		{
			out.push(status);
			return true;
		}
	}

	return false;
}

void IDA::genManhattan()
{
	for (int i = 0; i < 9; i++) {
		int num = target[i];
		int x = i % 3;
		int y = i / 3;
		for (int j = 0; j < 9; j++) {
			manhattan[num][j] = abs(j % 3 - x) + abs(j / 3 - y);
		}
	}

}

int IDA::distance(long long p)
{
	int d = 0;
	long long b = p;
	for (int i = 8; i > -1; i--) {
		d += manhattan[(b&15)][i];
		b = b >> 4;
	}
	return d;
}

void IDA::check()
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

void IDA::checkPuzzle(int * p)
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

long long IDA::genLong(int * p)
{
	long long status = 0;
	for (int i = 0; i < 9; i++) {
		status = status << 4;
		status += p[i];
	}
	return status;
}

int * IDA::genArray(long long p)
{
	int *ptr = new int[9];

	for (int i = 8; i > -1; i--) {
		ptr[i] = p & 15;
		p = p >> 4;
	}

	return ptr;
}

void IDA::output(long long p)
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
