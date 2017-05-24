#pragma once
#define NUM_DUPLICATED 1
#define NUM_INVALID 2

class PuzzleException
{
public:
	PuzzleException(int e);
	~PuzzleException();
	int getError();
private:
	int error;
};

