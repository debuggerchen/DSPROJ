#include "stdafx.h"
#include "PuzzleException.h"



PuzzleException::PuzzleException(int e)
{
	switch (e) {
	case NUM_DUPLICATED:
		cout << "Num Duplicated OR Invalid Char!" << endl;
		break;
	case NUM_INVALID:
		cout << "Num Invalid!" << endl;
		break;
	}
}

PuzzleException::~PuzzleException()
{
}

int PuzzleException::getError()
{
	return error;
}
