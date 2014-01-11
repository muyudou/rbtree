#include <iostream>
using namespace std;

const int m = 8;
const int n = 7;

//返回值结构
struct twoArrayPair
{
	char b[m][n];
	int c[m][n];
};

/*************************************************************/
/*
c[m][n]：保存了X和Y的LCS长度
b[m][n]: 帮助构造最优解

           0                          若i = 0 或 j = 0;
c[i][j] =  c[i-1][j-1]+1              若i, j > 0 且xi = yi;
           max(c[i][j-1], c[i-1][j])  若i,j > 0 且 xi != yi;
*/
/*************************************************************/
twoArrayPair *LCSLength(char *x, char *y)
{
	twoArrayPair *twoArray = new twoArrayPair;

	//c, b数组初始化
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			(twoArray->b)[i][j] = ' ';
			(twoArray->c)[i][j] = 0;
		}
	}

	for (int i = 1; i < m; i++)
	{
		for (int j = 1; j < n; j++)
		{
			if (x[i] == y[j])
			{
				(twoArray->c)[i][j] = (twoArray->c)[i-1][j-1]+1;
				(twoArray->b)[i][j] = '\\';
			}
			else if ((twoArray->c)[i-1][j] >= (twoArray->c)[i][j-1])
			{
				(twoArray->c)[i][j] = (twoArray->c)[i-1][j];
				(twoArray->b)[i][j] = '|';
			}
			else
			{
				(twoArray->c)[i][j] = (twoArray->c)[i][j-1];
				(twoArray->b)[i][j] = '-';
			}
		}
	}
	return twoArray;
}

//打印LCS
void printLCS(char (*b)[n], char *x, int i, int j)
{
	if (i == 0 | j == 0)
	   return;
	if (b[i][j] == '\\')
	{
		printLCS(b, x, i-1, j-1);
		cout << x[i];
	}
	else if (b[i][j] == '|')
	    printLCS(b, x, i-1, j);
	else
		printLCS(b, x, i, j-1);
}

int main()
{
	char x[] = "0ABCBDAB";
	char y[] = "0BDCABA";

	twoArrayPair *tt = LCSLength(x, y);
	cout << "x与y的最长公共子序列是：" << endl;
	printLCS(tt->b, x, m-1, n-1);
	cout << endl;

	system("pause");
	return 0;
}
