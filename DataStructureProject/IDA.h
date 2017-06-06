#pragma once
class IDA
{
public:
	IDA(int *a, int *r);
	~IDA();
	void input(int * a, int * r);
	void solve();
	void output();
	int getSteps();
	int getVisit();
	void reset();
private:
	int * puzzle, *target;
	int visit = 0;
	long long result;
	int manhattan[9][9];
	bool solved = false;
	int limit;
	stack<long long> out;
	bool ida(long long status, int depth, int dis, long long last);
	void genManhattan();
	int distance(long long p);
	void check();
	void checkPuzzle(int *p);
	long long genLong(int * p);
	int * genArray(long long p);
	void output(long long p);
};

