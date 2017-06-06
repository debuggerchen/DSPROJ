// DataStructureProject.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "EightPuzzle.h"
#include "DBFS.h"
#include "IDA.h"
#include "Astar.h"
#include <algorithm>
#include <random>
#include <vector>
#include <chrono>
#include <windows.h>
#include <psapi.h>
#include <stdio.h>
#pragma comment(lib,"psapi.lib")

int maze[9] = { 0,1,2,3,4,5,6,7,8 };
int target[9] = { 1,2,3,8,0,4,7,6,5 };
int *puzzle = new int[9];
size_t before,after;
HANDLE handle;
clock_t start_t, end_t;
PROCESS_MEMORY_COUNTERS pmc;
vector<int> v;

size_t getCurrentMem() {
	handle = GetCurrentProcess();
	GetProcessMemoryInfo(handle, &pmc, sizeof(pmc));
	return pmc.WorkingSetSize;
}

int main()
{
	setlocale(LC_ALL, "");
	//int * puzzle = new int[9];
	//cout << "输入原状态" << endl;
	//for (int i = 0; i < 9; i++) {
	//	cin >> puzzle[i];
	//}
	//int * target = new int[9];
	//cout << "输入目标状态" << endl;
	//for (int i = 0; i < 9; i++) {
	//	cin >> target[i];
	//}
	/*perm(0, 9);*/
	FILE *fp;
	fopen_s(&fp, "E:/hhh1.csv", "at+");

	try
	{
		int i = 0, k = 0, m;
		while(k<1000) {

			EightPuzzle *e = new EightPuzzle(maze, target);
			DBFS *b = new DBFS(maze, target);
			IDA *ida = new IDA(maze, target);
			Astar *a = new Astar(maze, target);


			cout << "Now At " << i++ << "Attempts. Now Finish" << k <<" ";
			for (int j = 0; j < 9; j++) {
				v.push_back(maze[j]);
			}

			unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
			std::shuffle(v.begin(), v.end(), std::default_random_engine(seed));

			for (int j = 0; j < 9; j++) {
				puzzle[j] = v[j];
			}

			v.clear();

			e->input(puzzle, target);
			
			before = getCurrentMem();
			start_t = clock();
			e->solve();
			end_t = clock();
			after = getCurrentMem();
			m = e->getSteps();
			cout << "BFS ";
			cout << "步数:" << m << "  ";
			cout << "状态数：" << e->getVisit() << " ";
			cout << "用时：" << end_t - start_t << " ms  ";
			cout << "内存占用: " << ((after - before)) << "B  ";
			fprintf_s(fp, "%d,%d,%d,%d,",m,e->getVisit(),end_t-start_t,after-before);
			if (m >= 0)
				k++;
			//e->output();
			//e.release();
			//delete e;
			//cout << "BFS Finish" << endl;
			e->reset();
			//cout << endl;
			cout << "DBFS  ";
			b->input(puzzle, target);
			before = getCurrentMem();
			start_t = clock();
			b->solve();
			end_t = clock();
			after = getCurrentMem();
			m = b->getSteps();
			cout << "步数:" << m << "  ";
			cout << "状态数：" << b->getVisit() << " ";
			cout << "用时：" << end_t - start_t << " ms  ";
			cout << "内存占用：" << ((after - before)) << "B  ";
			fprintf_s(fp, "%d,%d,%d,%d,", m,b->getVisit(), end_t - start_t, after - before);
			//b->output();
			//delete b;
			b->reset();
			//cout << "DBFS Finish" << endl << endl;

			cout << "IDA*  ";
			ida->input(puzzle, target);
			start_t = clock();
			ida->solve();
			end_t = clock();
			m = ida->getSteps();
			cout << "步数:" << m << "  ";
			cout << "状态数：" << ida->getVisit() << " ";
			cout << "用时：" << end_t - start_t << " ms  ";
			fprintf_s(fp, "%d,%d,%d,", m,ida->getVisit() ,end_t - start_t);
			/*cout << "路径：" << endl;*/
			//i->output();
			//delete ida;
			ida->reset();
			//cout << "IDA* Finish" << endl << endl;

			cout << "A*  ";
			a->input(puzzle, target);
			before = getCurrentMem();
			start_t = clock();
			a->solve();
			end_t = clock();
			after = getCurrentMem();
			m = a->getSteps();
			cout << "步数:" << m << "  ";
			cout << "状态数：" << a->getVisit() << " ";
			cout << "用时：" << end_t - start_t << " ms  ";
			cout << "内存占用" << ((after - before)) << "B  ";
			fprintf_s(fp, "%d,%d,%d,%d\n", m, a->getVisit(),end_t - start_t, after - before);
			//cout << "路径：" << endl;
			//a->output();
			//b.release();
			//cout << "A* Finish" << endl << endl;
			//delete a;
			a->reset();

			cout << endl;
			delete e, b, ida, a;
		}
	}
	catch (...)
	{
		cout << "Error!" << endl;
	}
	fclose(fp);
	system("pause");
    return 0;
}

