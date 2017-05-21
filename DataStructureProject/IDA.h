#pragma once
class IDA
{
public:
	IDA();
	~IDA();
	void input(int * a);
	void solve();
private:
	int * puzzle;
	int manhattan[9][9] =
	{
		{2,1,2,1,0,1,2,1,2},
		{0,1,2,1,2,3,2,3,4},
		{1,0,1,2,1,2,3,2,3},
		{2,1,0,3,2,1,4,3,2},
		{3,2,1,2,1,0,3,2,1},
		{4,3,2,3,2,1,2,1,0},
		{3,2,3,2,1,2,1,0,1},
		{2,3,4,1,2,3,0,1,2},
		{1,2,3,0,1,2,1,2,3},
	};
	bool solved = false;
	int limit;
	bool ida(long long status, int depth, int dis);
	int distance(long long p);
	void check();
	long long genLong();
};

