#pragma once
#include "stdafx.h"
class EightPuzzle
{
public:
	EightPuzzle(int *a, int *r);
	~EightPuzzle();
	void input(int *a,int *r);
	void solve();
	void output();
	void reset();
	int getSteps();
	int getVisit();
private:
	int *puzzle, *target;
	int visit = 0;
	long long result;
	bool solved = false;
	stack<long long> out;
	queue<long long> toCheck;
	unordered_set<long long> checked;
	unordered_map<long long,long long> path;
	void check();
	void checkPuzzle(int *p);
	void swapAndAdd(long long p);
	void addToQueue(long long o,long long p);
	long long genLong(int *p);
	int * genArray(long long p);
	void output(long long p);
};

