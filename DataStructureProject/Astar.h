#pragma once
#include "stdafx.h"
class Astar
{
public:
	Astar(int *a, int *r);
	~Astar();
	void input(int *a, int *r);
	void solve();
	void output();
	void reset();
private:
	int *puzzle, *target;
	long long result;
	int manhattan[9][9];
	bool solved = false;
	
	struct state {
		long long status;
		int g;	//Depth
		int h;	//Distance
		int f;	//g+h
		state(long long s, int a, int b) {
			status = s;
			g = a;
			h = b;
			f = g + h;
		}
	};
	
	struct cmp {
		bool operator()(const state * a, const state * b) {
			return a->f > b->f;
		}
	};
	stack<long long> out;
	priority_queue<state*, vector<state*>, cmp> open;
	unordered_set<long long> close;
	unordered_map<long long, state*> inopen;
	unordered_map<long long, long long> path;
	void check();
	void checkPuzzle(int *p);
	void genManhattan();
	void swapAndSet(long long p);
	void addToOpen(long long p, long long next);
	int distance(long long p);
	long long genLong(int *p);
	int * genArray(long long p);
	void output(long long p);

};

