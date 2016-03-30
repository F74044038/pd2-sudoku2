#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<cstdlib>
using namespace std;

class Sudoku
{
	public:
	void giveQuestion();		///創一個數獨
	void readIn();			///讀入一個數獨
	void solve();			///解題
		////transform
	void change();
	void changeNum(int a,int b);	////	交換a跟b的數字
	void changeRow(int a,int b);	////	橫的3行為一組 進行交換	0<=a, b<=2
	void changeCol(int a,int b);	////	直的3行為一組 進行交換	0<=a, b<=2
	void rotate(int n);		////	rotate 90 degree n times 0<=n<=100 順時針
	void flip(int n);		////	垂直翻轉 左右翻轉   	
	void transform();		///包含上述四種的轉變
	void printout(bool isans);	///印出
	bool isans();			///判斷現在這個這個有沒有解
	bool findzero();		///找陣列還有沒有0
	void possible(int arr[]);	///找出可能性
	void backtrack();		///跑解
	int allzeroplace();
	static const int size=81;
	private:
	int board[size];		///讀入的板子
	int ans[size];			///
	int zeroindex;			///0的位置
	bool checkunity(int arr[]);	///確認是否有重復 0忽略
	int used[9];
	int possiblenum[9];		///存放位置可能的解
	int answer;			////有幾種答案 在backtrack時用到
	int current;			////possible現在第幾個的
	int question[81];		////題目
	int everyzero[81];
	int y;
};
