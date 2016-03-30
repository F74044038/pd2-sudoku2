#include"Sudoku.h"
#include<cstdlib>
using namespace std;

void  	Sudoku::readIn(){	//讀入
		for(int i=0;i<size;i++){
		scanf("%d",&board[i]);
		}	
	}
void 	Sudoku::giveQuestion(){
		int question[81]={
		2,0,0,0,3,0,0,0,6,
                0,1,0,9,0,2,0,7,0,
                0,0,5,0,0,0,2,0,0,
                0,3,0,0,2,0,0,4,0,
                9,0,0,8,0,5,0,0,2,
                0,2,0,0,6,0,0,1,0,
                0,0,9,0,0,0,4,0,0,
                0,8,0,4,0,7,0,9,0,
                1,0,0,0,9,0,0,0,8
						};
		for(int i=0;i<size;i++)
                       	printf("%d%c",question[i],(i+1)%9==0?'\n':' ');
	}
//////////////////////////////////////////transform
void	Sudoku::changeNum(int a,int b){
		for(int i=0;i<size;i++){
		if(board[i]==a){board[i]=b;continue;}
		if(board[i]==b){board[i]=a;continue;}
		}
	}
void	Sudoku::changeRow(int a,int b){		///橫
		int temp;
		for(int i=0;i<27;i++){
		temp=board[(a*27+i)];
		board[(a*27+i)]=board[(b*27)+i];
		board[(b*27)+i]=temp;
		}
	}
void  	Sudoku::changeCol(int a,int b){	///直
		int temp;
		for(int i=0;i<3;i++){
			for(int j=0;j<81;j=j+9){
			temp=board[(i+a*3)+j];
			board[(i+a*3)+j]=board[(i+b*3)+j];
			board[(i+b*3)+j]=temp;
			}
		}
	}
void	Sudoku::rotate(int n){
		int temp[81];
		if(n%4==0){return;}	//
		if(n%4==1){		//90度
			for(int i=72,n=0;i<81,n<9;i++,n++){
				for(int j=0,g=0;j<81,g<9;j=j+9,g++){
				temp[n*9+g]=board[i-j];
				}
			}
		}
		if(n%4==2){		//180度
			for(int i=0,j=80;i<81,j>=0;i++,j--){
				temp[i]=board[j];
			}
		}
		if(n%4==3){		//270度
			for(int i=8,n=0 ; i>=0,n<9 ;i--,n++){
				for(int j=0,g=0 ; j<81, g<9 ; j=j+9 ,g++){
				temp[n*9+g]=board[i+j];
				}
			}
		}
		for(int i=0;i<81;i++){	//修改board
			board[i]=temp[i];
		}
}
void	Sudoku::flip(int n){
	int temp[81];
	if(n==0){		//垂直翻轉
		for(int i=72,n=0 ; i>=0,n<9 ; i=i-9,n++){
			for(int j=0,g=0 ;j<9,g<9 ;j++,g++){
			temp[n*9+g]=board[i+j];
			}
		}
	}
	else{			//平行翻轉
		for(int i=8,n=0;i<81,n<9;i=i+9,n++){
			for(int j=0,g=0;j>-9,g<9;j--,g++){
			temp[n*9+g]=board[i+j];
			}
		}
	}
	for(int i=0;i<81;i++){  //修改board
                        board[i]=temp[i];
       	}	
}
void Sudoku::printout(bool isans){
	int i;
	if(isans==0){
		for(i=0;i<size;i++)
			printf("%d%c",board[i],(i+1)%9==0?'\n':' ');
	}
	else
		for(i=0;i<size;i++)
		 	printf("%d%c",ans[i],(i+1)%9==0?'\n':' ');
}
void Sudoku::change(){
	srand(time(NULL));
	changeNum(rand()%9+1,rand()%9+1);
	changeRow(rand()%3,rand()%3);
	changeCol(rand()%3,rand()%3);
	rotate(rand()%101);
	flip(rand()%2);
}

void Sudoku::transform(){
	change();
	printout(false);
}
////////////////////////////////////////////////////////solve
bool 	Sudoku::checkunity(int arr[]){     //確認1~9個數字有沒有重復
        int count[9];
        for(int i=0;i<9;i++){   //初始化
        count[i]=0;
        }
        for(int i=0;i<9;i++){   //算每個各有幾個
        	if(arr[i]==0){continue;}
		else{
        		count[arr[i]-1]=count[arr[i]-1]+1;
		}
        }
        for(int i=0;i<9;i++){   //看有沒有重復的
        	if(count[i]>1){return false;}
        }
        return true;
}

bool 	Sudoku::isans(){           /////確認一個數獨是否符合規則的 retrun true or false
        bool result;
        int check[9];
        int now;
        for(int i=0;i<81;i=i+9){        //確認橫的
                for(int j=0;j<9;j++){   //把要檢查的放進check
                check[j]=board[i+j];
                }
                result=checkunity(check);
                if(result==false){return false;}
        }
        for(int i=0;i<9;i++){           //確認直的
                for(int j=0;j<9;j++){
                check[j]=board[i+j*9];
                }
                result=checkunity(check);
                if(result==false){return false;}
        }
        for(int i=0;i<9;i++){                           //確認一組九宮格的
                for(int j=0;j<9;j++){
                now=27*(i/3)+3*(i%3)+9*(j/3)+(j%3);
                check[j]=board[now];
                }
                result=checkunity(check);
                if(result==false){return false;}
        }
        return true;
}
void Sudoku::possible(int arr[]){				///找出0的位置 然後把每個0位置的可能性找出來
	int n=0;
	for(int i=0;i<9;i++){           			////初始化possible
                possiblenum[i]=0;
        }
	for(int i=0;i<81;i++){					///找出第一個0的位置
		if(board[i]==0){zeroindex=i;break;}
	}
	int have[9];			///0~8的位置 存 1~9	
	for(int j=0;j<9;j++){have[j]=0;}///初始化have	
	int row=0,col=0,block=0;
	row=zeroindex/9;		//算出位於第幾列	0~8
	col=zeroindex-9*row;		//算出位於第幾行	0~8
	block=(row/3)*3+(col/3);	//算出位於第幾個九宮格	
	for(int j=row*9;j<row*9+9;j++){	//把已經有的橫排數字放入
		if(arr[j]!=0){
			have[arr[j]-1]=1;
		}
	}
	for(int j=col;j<81;j=j+9){	//把已經有的直行數字放入
		if(arr[j]!=0){
			have[arr[j]-1]=1;
		}
	}
	for(int j=(block/3)*27+(col/3)*3;j<(block/3)*27+(col/3)*3+3;j++){	//把已經有的九宮格內數字放入
		for(int k=0;k<27;k=k+9){
			if(arr[j+k]!=0){
				have[arr[j+k]-1]=1;
			}
		}
	}
	int p=0;
	for(int j=0;j<9;j++){		//把有可能是解的東西存入possible中
		if(have[j]==0){		//把已經有的東西去掉 留我們所沒有的
		possiblenum[p]=j+1;	////0~8 存1~9
		p++;
		}
	}		
}
bool Sudoku::findzero(){			///確認是否還有0
	for(int i=0;i<size;i++){
	if(board[i]==0){return false;}
	}
	return true;
}
int Sudoku::allzeroplace(){
	int x=0;
	for(int i=0;i<81;i++){
	everyzero[i]=0;
	}
	for(int i=0;i<81;i++){
	if(board[i]==0){everyzero[x]=i;x++;}
	}
}
void Sudoku::backtrack(){
	if(isans()!=true){					/////如果判斷現在這個不符合規則就回到上一步
		board[everyzero[y]]=0; 
		possible(board); 
		return;
	}
	if(findzero()==true){					////如果格子沒有0又通過上一行代表已填滿又符合規則就回到上一步 並把答案存到ans中
		for(int h=0;h<size;h++){
		ans[h]=board[h];
		}
		answer=answer+1;
		if(answer==2){						////當有兩個解就終止
			printf("2\n");
              	exit(0);
		}
		board[everyzero[y]]=0;
		possible(board); 
		return;
	}
	possible(board);
	y++;
	if(possiblenum[0]==0){			///0個可能 就回去
		y--;
		board[everyzero[y]]=0;
		possible(board);
		return;
	}
	if(answer>=2){printf("2\n");exit(0);}	 	////程式有兩個解就印出2終止程式
	for(int i=0;possiblenum[i]>0;i++){
		board[everyzero[y]]=possiblenum[i];
		backtrack();	
	}
	y--;
	if(y<0){return;}
	board[everyzero[y]]=0;
	possible(board);
}

void Sudoku::solve(){
	if(isans()==false){		////檢查傳進來的是不是符合規則的
		printf("0\n");
		exit(0);
	}
	if(findzero()==true&&isans()==true){
		printf("1\n");
		printout(false);
		exit(0);
	}
	allzeroplace();	
	answer=0;			///初始化有幾個解
	y=-1;				///起點
	backtrack();			///開始解題
	if(answer==0){			///當題目為無解時
		printf("0\n");
                exit(0);
	}
	if(answer==1){			////有唯一解時
		printf("1\n");
		printout(true);
	}
}


