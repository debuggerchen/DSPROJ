// DataStructureProject.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "EightPuzzle.h"
#include "BiSearch.h"
#include "IDA.h"

int main()
{
	int * puzzle = new int[9];
	cout << "Please Enter Puzzle" << endl;
	for (int i = 0; i < 9; i++) {
		cin >> puzzle[i];
	}
	EightPuzzle e;
	e.input(puzzle);
	clock_t start, end;
	cout << "BFS + Hash Search Start" << endl;
	start = clock();
	e.solve();
	end = clock();
	cout << "Search Finish In " << end - start << " ms" << endl;
	cout << "Path is shown below" << endl;
	e.output();
	e.release();
	cout << "BFS + Hash Search Finish" << endl;
	cout << endl;
	BiSearch b;
	b.input(puzzle);
	clock_t start2, end2;
	cout << "DBFS Start" << endl;
	start2 = clock();
	b.solve();
	end2 = clock();
	cout << "Search Finish In " << end2 - start2 << " ms" << endl;
	b.output();
	b.release();
	cout << "DBFS Finish" << endl << endl;

	IDA i;
	i.input(puzzle);
	clock_t start3, end3;
	cout << "IDA* Start" << endl;
	start3 = clock();
	i.solve();
	end3 = clock();
	cout << "Search Finish In " << end3 - start3 << " ms" << endl;
	cout << "IDA* Finish" << endl << endl; 


    return 0;
}

