#pragma once
#include "stdafx.h"
class EightPuzzle
{
public:
	EightPuzzle();
	~EightPuzzle();
	void input(int *a);
	void solve();
	void output();
	void release();
private:
	int *puzzle;
	bool solved = false;
	queue<long long> toCheck;
	unordered_set<long long> checked;
	unordered_map<long long,long long> path;
	void check();
	void swapAndAdd(long long p);
	void addToQueue(long long o,long long p);
	long long genInt(int *p);
	int * genArray(long long p);
	void output(long long p);
};

