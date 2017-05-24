#include "stdafx.h"
#include "Astar.h"


Astar::Astar(int *a, int *r)
{
	input(a, r);
}


Astar::~Astar()
{
	reset();
}

void Astar::input(int * a, int * r)
{
	checkPuzzle(a);
	checkPuzzle(r);
	puzzle = a;
	target = r;
}

void Astar::solve()
{
	check();
	if (!solved)
		return;
	solved = false;
	result = genLong(target);
	long long p = genLong(puzzle);
	genManhattan();
	state *source = new state(p,0,distance(p));
	open.push(source);
	inopen[p] = source;
	path[p] = -1;
	state *ptr;
	while (!open.empty()) {
		ptr = open.top();
		long long now = ptr->status;
		open.pop();
		close.insert(now);
		if (now == result)
		{
			solved = true;
			break;
		}
		
		swapAndSet(now);
	}

}

void Astar::output()
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

void Astar::reset()
{
	while (!out.empty()) {
		out.pop();
	}

	while (!open.empty()) {
		open.pop();
	}

	close.clear();
	inopen.clear();
	path.clear();

	solved = false;
	puzzle = nullptr;
	target = nullptr;
	result = 0;
}

void Astar::check()
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

void Astar::checkPuzzle(int * p)
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

void Astar::genManhattan()
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

void Astar::swapAndSet(long long p)
{
	long long i, j = 0;
	for (i = 15; (i&p) != 0; i = i << 4, j++);
	long long b, next;
	//向上移动
	if (j < 6)
	{
		b = (i << 12)&p;
		next = (~(i << 12))&p;
		next = (~i)&next;
		next = (b >> 12) | next;
		addToOpen(p, next);
	}

	//向下移动
	if (j > 2)
	{
		b = (i >> 12)&p;
		next = (~(i >> 12))&p;
		next = (~i)&next;
		next = (b << 12) | next;
		addToOpen(p, next);
	}

	//向左移动
	if (j % 3 != 2) {
		b = (i << 4)&p;
		next = (~(i << 4))&p;
		next = (~i)&next;
		next = (b >> 4) | next;
		addToOpen(p, next);
	}

	//向右移动
	if (j % 3 != 0) {
		b = (i >> 4)&p;
		next = (~(i >> 4))&p;
		next = (~i)&next;
		next = (b << 4) | next;
		addToOpen(p, next);
	}

}

void Astar::addToOpen(long long p, long long next)
{
	//Checked
	if (close.find(next) != close.end())
		return;

	if (inopen.find(next) == inopen.end()) {
		state * s = new state(next, inopen[p]->g + 1, distance(next));
		path[next] = p;
		inopen[next] = s;
		open.push(s);
	}
	else if (inopen[next]->g > inopen[p]->g + 1) {
		state * s = new state(next, inopen[p]->g + 1, distance(next));
		path[next] = p;
		inopen[next] = s;
		open.push(s);
	}

}

int Astar::distance(long long p)
{
	int d = 0;
	long long b = p;
	for (int i = 8; i > -1; i--) {
		d += manhattan[(b & 15)][i];
		b = b >> 4;
	}
	return d;
}

long long Astar::genLong(int * p)
{
	long long status = 0;
	for (int i = 0; i < 9; i++) {
		status = status << 4;
		status += p[i];
	}
	return status;
}

int * Astar::genArray(long long p)
{
	int *ptr = new int[9];

	for (int i = 8; i > -1; i--) {
		ptr[i] = p & 15;
		p = p >> 4;
	}

	return ptr;
}

void Astar::output(long long p)
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

//TODO: FInish it
//void Astar::output(long long p)
//{
//	for (int i = 0; i < 9; i++) {
//		if (a[i] > 0)
//			cout << a[i] << " ";
//		else
//			cout << "  ";
//		if (i % 3 == 2)
//			cout << endl;
//	}
//	cout << endl;
//}
