// sudoku.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include "string.h"
#include "math.h"

using namespace std;

int n=0;
int sdk[9][9];

bool judge_row(int x, int y, int m)
{
	int i;
	for (i = 0; i < 9; i++)
	{
		if (i != y && sdk[x][i] == m) return false;
	}
	return true;
}

bool judge_column(int x, int y, int m)
{
	int i;
	for (i = 0; i < 9; i++)
	{
		if (i != x && sdk[i][y] == m) return false;
	}
	return true;
}

bool judge_box(int x, int y, int m)
{
	int box_x, box_y, i, j;
	box_x = x / 3;
	box_y = y / 3;
	box_x = box_x * 3;
	box_y = box_y * 3;
	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 3; j++)
		{
			if ((box_x + i != x) && (box_y + j != y) && (sdk[box_x + i][box_x + j] == m)) return false;
		}
	}
	return true;
}

bool judge(int x, int y, int m)
{
	if (judge_box(x, y, m) && judge_row(x, y, m) && judge_column(x, y, m)) return true;
	else return false;
}

bool fill(int m)
{
	int i, x, y; //x是第m个元素的行数，y是列数
	if (m >= 81) return true;
	x = m / 9;
	y = m % 9;
	if (sdk[x][y] == 0)
	{
		for (i = 1; i <= 9; i++)
		{
			if (judge(x, y, i))
			{
				sdk[x][y] = i;
				return fill(m + 1);
			}
		}
	}
	else return fill(m + 1);
	return false;
}

void solve(FILE *fp)
{
	int i, j;
	int beginning;
	FILE *output;
	errno_t err;
	err = fopen_s(&output, "D:\sudoku.txt", "w");
	while (fscanf_s(fp, "%d", &beginning) != EOF)
	{
		sdk[0][0] = beginning;
		for (i = 1; i < 9; i++) fscanf_s(fp, "%d", &sdk[0][i]);
		for (i = 1; i < 9; i++)
		{
			for (j = 0; j < 9; j++) fscanf_s(fp, "%d", &sdk[i][j]);
		}
		if (fill(0))
		{
			for (i = 0; i < 9; i++)
			{
				for (j = 0; j < 8; j++) fprintf_s(output, "%d ", sdk[i][j]);
				fprintf_s(output, "%d\n", sdk[i][8]);
			}
			fprintf_s(output, "\n");
		}
	}
	cout << "求解完毕" << endl;
	return;
}

int main(int argc,char *argv[])
{
	if (argc != 3) cout << "参数数量错误" << endl;
	else
	{
		if (argv[1][0] == '-'&&argv[1][1] == 'c'&&strlen(argv[1]) == 2)
		{
			int flag = 1;//flag=1表示参数合乎规范,flag=0表示参数含非数字字符，flag=-1表示数字超出范围
			if (strlen(argv[2]) >= 8)
			{
				flag = -1;
			}
			else
			{
				for (int i = 0; i < strlen(argv[2]); i++)
				{
					if (argv[2][i] >= '9' || argv[2][i] < '0')
					{
						flag = 0;
						break;
					}
					n = n * 10 + argv[2][i] - '0';
				}
				if (n == 0 || n > 1000000)
				{
					flag = -1;
				}
			}
			if (flag == 0) cout << "请输入数字" << endl;
			else if (flag == -1) cout << "请输入数字N（1<=N<=1000000）" << endl;
			else
			{
				cout << n << endl;
				//开始创建数独
			}
		}
		else if (argv[1][0] == '-'&&argv[1][1] == 's'&&strlen(argv[1]) == 2)
		{
			FILE *fp;
			errno_t err;
			err = fopen_s(&fp, argv[2], "r");
			if (fp == NULL) cout << "找不到该文件" << endl;
			else solve(fp); //开始解数独
		}
		else cout << "请使用正确的指令（“-c”或“-s”）" << endl;
	}
	return 0;
}
