#include "stdafx.h"
#include "IDA.h"
#define result 4890576741

IDA::IDA()
{
}


IDA::~IDA()
{
}

void IDA::input(int * a)
{
	puzzle = a;
}

void IDA::solve()
{
	check();
	if (!solved)
		return;
	solved = false;
	long long p = genLong();
	while (!ida(p, 0, distance(p))) {
		limit++;
	}
}

bool IDA::ida(long long status, int depth, int dis)
{
	if (status == result)
	{
		solved = true;
		cout << "Solved in " << depth << " steps" << endl;
		return true;
	}

	if (depth + dis > limit)
		return false;

	long long i, j = 0;
	for (i = 15; (i&status) != 0; i = i << 4, j++);
	long long b, next;
	//向上移动
	b = (i << 12)&status;
	next = (~(i << 12))&status;
	next = (~i)&next;
	next = (b >> 12) | next;
	if (ida(next, depth + 1, distance(next)))
		return true;

	//向下移动
	b = (i >> 12)&status;
	next = (~(i >> 12))&status;
	next = (~i)&next;
	next = (b << 12) | next;
	if (ida(next, depth + 1, distance(next)))
		return true;

	//向左移动
	if (j % 3 != 2) {
		b = (i << 4)&status;
		next = (~(i << 4))&status;
		next = (~i)&next;
		next = (b >> 4) | next;
		if (ida(next, depth + 1, distance(next)))
			return true;
	}

	//向右移动
	if (j % 3 != 0) {
		b = (i >> 4)&status;
		next = (~(i >> 4))&status;
		next = (~i)&next;
		next = (b << 4) | next;
		if (ida(next, depth + 1, distance(next)))
			return true;
	}

	return false;
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

long long IDA::genLong()
{
	long long status = 0;
	for (int i = 0; i < 9; i++) {
		status = status << 4;
		status += puzzle[i];
	}
	return status;
}
