#pragma once
class DBFS
{
public:
	DBFS(int *a, int *r);
	~DBFS();
	void input(int *a, int * r);
	void solve();
	void output();
	void reset();
private:
	int *puzzle, *target;
	long long result;
	long long fEnd, reverseEnd;
	bool solved = false;
	queue<long long> toCheck;
	queue<long long> reverseToCheck;
	stack<long long> out;
	unordered_set<long long> checked;
	unordered_set<long long> reverseChecked;
	unordered_map<long long, long long> path;
	unordered_map<long long, long long> path2;
	void check();
	void swapAndAdd(long long p);
	void swapAndAdd2(long long p);
	void addToQueue(long long o, long long p);
	void addToQueue2(long long o, long long p);
	void checkPuzzle(int *p);
	long long genLong(int *p);
	int * genArray(long long p);
	void output(long long p);

};

