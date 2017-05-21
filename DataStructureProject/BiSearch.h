#pragma once
class BiSearch
{
public:
	BiSearch();
	~BiSearch();
	void input(int *a);
	void solve();

	void output();
	void release();
private:
	int *puzzle;
	long long fEnd, reverseEnd;
	bool solved = false;
	void check();
	queue<long long> toCheck;
	queue<long long> reverseToCheck;
	unordered_set<long long> checked;
	unordered_set<long long> reverseChecked;
	unordered_map<long long, long long> path;
	unordered_map<long long, long long> path2;
	void swapAndAdd(long long p);
	void swapAndAdd2(long long p);
	void addToQueue(long long o, long long p);
	void addToQueue2(long long o, long long p);
	long long genInt(int *p);
	int * genArray(long long p);
	void output(long long p);

};

