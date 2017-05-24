// DataStructureProject.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "EightPuzzle.h"
#include "DBFS.h"
#include "IDA.h"
#include "Astar.h"
#include <windows.h>
#include <psapi.h>
#pragma comment(lib,"psapi.lib")

size_t before,after;
HANDLE handle;
PROCESS_MEMORY_COUNTERS pmc;
size_t getCurrentMem() {
	handle = GetCurrentProcess();
	GetProcessMemoryInfo(handle, &pmc, sizeof(pmc));
	return pmc.WorkingSetSize;
}
int main()
{
	int * puzzle = new int[9];
	cout << "Please Enter Puzzle" << endl;
	for (int i = 0; i < 9; i++) {
		cin >> puzzle[i];
	}
	int * target = new int[9];
	cout << "Please Enter Target" << endl;
	for (int i = 0; i < 9; i++) {
		cin >> target[i];
	}
	try
	{
		
		EightPuzzle *e = new EightPuzzle(puzzle, target);
		cout << "BFS + Hash Search Start" << endl;
		clock_t start, end;
		before = getCurrentMem();
		start = clock();
		e->solve();
		end = clock();
		after = getCurrentMem();
		cout << "Search Finish In " << end - start << " ms" << endl;
		cout << "Mem Usage: " << ((after - before) >> 10) << "K" << endl;
		cout << "Path is shown below" << endl;
		e->output();
		//e.release();
		delete e;
		cout << "BFS + Hash Search Finish" << endl;
		cout << endl;
		DBFS *b = new DBFS(puzzle, target);
		cout << "DBFS Start" << endl;
		before = getCurrentMem();
		start = clock();
		b->solve();
		end = clock();
		after = getCurrentMem();
		cout << "Search Finish In " << end - start << " ms" << endl;
		cout << "Mem Usage: " << ((after - before) >> 10) << "K" << endl;
		b->output();
		delete b;
		cout << "DBFS Finish" << endl << endl;

		IDA *i = new IDA(puzzle, target);
		cout << "IDA* Start" << endl;
		start = clock();
		i->solve();
		end = clock();
		cout << "Search Finish In " << end - start << " ms" << endl;
		i->output();
		delete i;
		cout << "IDA* Finish" << endl << endl;

		Astar *a = new Astar(puzzle, target);
		cout << "A* Start" << endl;
		before = getCurrentMem();
		start = clock();
		a->solve();
		end = clock();
		after = getCurrentMem();
		cout << "Search Finish In " << end - start << " ms" << endl;
		cout << "Mem Usage: " << ((after - before) >> 10) << "K" << endl;
		a->output();
		//b.release();
		cout << "A* Finish" << endl << endl;
		delete a;
		delete puzzle;
		delete target;
	}
	catch (...)
	{
		cout << "Error!" << endl;
	}
	
	system("pause");
    return 0;
}

