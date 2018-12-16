// sudoku.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include "string.h"
#include "math.h"

using namespace std;

int n=0;

void solve(FILE *fp)
{
	cout << "开始求解" << endl;
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
