#include<iostream>
#include<fstream>
#include<string>
#include <time.h>// I just did the second extra credit 
using namespace std;

struct sb
{
	int row;
	int column;
	char center; 
}*savedboard;
char **board;
/*using this one dynamic array struct--savedboard to store all the characters including '|',' ','+' etc and the value of current player
and these players' row and column for output. At the same time, store the value of current player into two dimension array--board and its 
current row and column for checking the winning condition 
*/
int playerNum;
int winseqNum;
int boardNum;
bool fileexsit=true;

void wait(int seconds)/*this fuction are used for when loading the saved game, 
					  actually place each player's symbol one at a time with an appropriate delay.(I set the delay time as 1 second) */
{
	clock_t ewait;
	ewait=clock()+seconds*CLK_TCK;
	while(clock()<ewait){}
}

bool checkWinningPossible(int playerNum,int boardNum,int winseqNum)/*For a new game, check to ensure that winning is possible given the criteria specified, 
																   and display an error if not. if this function returns false, winnng is impossible*/
{
	if(playerNum==1)
	{
		cout<<"Sorry, we don't accept only one player. Please input again."<<endl;
		return false;
	}
	if(boardNum==2 )
	{
		cout<<"The board number should be more than 2. Please input again."<<endl;
		return false;
	}
	if(winseqNum==1 )
	{
		cout<<"The win sequence should be more than 2. Please input again."<<endl;
		return false;
	}
	if(playerNum>26)
	{
		cout<<"The number of players cannot be greater than 26."<<endl;
	}
	if(winseqNum>boardNum) 
	{
		cout<<"The win sequence count should be smaller or eaqual to board number. Please input again."<<endl;
		return false;
	}
	if(boardNum*boardNum<=playerNum)
	{
		cout<<"Too many players! Please input again."<<endl;
		return false;
	}
	if(boardNum>=20)
	{
		cout<<"because the maximum characters a line could support is 1024, so please input the board number smaller than 20"<<endl;
		return false;
	}
	return true;
}

int checkWhetherWin(int row,int column,char currentPlayer,int winseqNum,int boardNum)
	/*check whether current player wins. Don't care other players, just focus on current one. Imagining current player is the center of 
	the whole board, then compare the value of current player to that of other 8 directions(every row has two directions: 
	the left and the right,column has two directions, two diagonal lines have 4 directions). Using a counter initialized as 1 to count.
	Assuming current row as n, column as m and current player as 'X'. Fisrt using left row direction, if the value of(n,m-1) equals to that of(n,m)
	keep comparing and update counter(counter++). Every time updating counter, just compare the value of counter to win sequence, if equal, 
	then current player wins,else keep comparing.
	If the value of next row and column(n,m-2) is not eaqual to 'X' stop comparing on this left row direction, but don't reset counter this time
	because every row has two direction, after comparing two direction of row and counter still cannot satisfy the win sequence, then reset the
	value of counter to 1, then next direction. After doing all the 8 directions,if counter is not equal to win sequence and board is not full,
	keep ask users to input row and column */
	/* of course, there is another possibility could stop comparing, if next values of row and column are out of the boundary of board. if 
	this occurs, just switch to other direction*/
{
	int count=1;
	row=row-1;
	column=column-1;
	int newrow,newcolumn;
	newrow=row;
	newcolumn=column-1;
	while(count<winseqNum && newrow>=0&& newrow<boardNum && newcolumn>=0 && newcolumn<boardNum)
	{
		if(board[newrow][newcolumn]==currentPlayer  )
		{
			count++;

		}
		if(board[newrow][newcolumn]!=currentPlayer || newrow<0||newrow>=boardNum || newcolumn<0 || newcolumn>=boardNum) break;
		newcolumn--;
	}
	if (count==winseqNum) return 1;
	newrow=row;
	newcolumn=column+1;
	while(count<winseqNum && newrow>=0&& newrow<boardNum && newcolumn>=0 && newcolumn<boardNum)
	{

		if(board[newrow][newcolumn]==currentPlayer )
		{
			count++;

		}
		if(board[newrow][newcolumn]!=currentPlayer || newrow<0||newrow>=boardNum || newcolumn<0 || newcolumn>=boardNum) break;
		newcolumn++;
	}
	if (count==winseqNum) return 1;

	count=1;
	newrow=row-1;
	newcolumn=column;
	while(count<winseqNum && newrow>=0&& newrow<boardNum && newcolumn>=0 && newcolumn<boardNum) 
	{
		if(board[newrow][newcolumn]==currentPlayer ) 
		{
			count++;

		}
		if(board[newrow][newcolumn]!=currentPlayer || newrow<0||newrow>=boardNum || newcolumn<0 || newcolumn>=boardNum) break;
		newrow--;
	}
	if(count==winseqNum) return 1;

	newrow=row+1;
	newcolumn=column;
	while(count<winseqNum && newrow>=0&& newrow<boardNum && newcolumn>=0 && newcolumn<boardNum) 
	{
		if(board[newrow][newcolumn]==currentPlayer ) 
		{
			count++;

		}
		if(board[newrow][newcolumn]!=currentPlayer || newrow<0||newrow>=boardNum || newcolumn<0 || newcolumn>=boardNum) break;
		newrow++;
	}
	if(count==winseqNum) return 1;

	count=1;
	newrow=row-1;
	newcolumn=column-1;
	while(count<winseqNum && newrow>=0&& newrow<boardNum && newcolumn>=0 && newcolumn<boardNum)
	{
		if(board[newrow][newcolumn]==currentPlayer)
		{
			count++;

		}
		if(board[newrow][newcolumn]!=currentPlayer || newrow<0||newrow>=boardNum || newcolumn<0 || newcolumn>=boardNum) break;
		newrow--;
		newcolumn--;
	}
	newrow=row+1;
	newcolumn=column+1;
	while(count<winseqNum && newrow>=0&& newrow<boardNum && newcolumn>=0 && newcolumn<boardNum)
	{
		if(board[newrow][newcolumn]==currentPlayer)
		{
			count++;

		}
		if(board[newrow][newcolumn]!=currentPlayer || newrow<0||newrow>=boardNum || newcolumn<0 || newcolumn>=boardNum) break;
		newrow++;
		newcolumn++;
	}
	if(count==winseqNum) return 1;
	count=1;
	newrow=row-1;
	newcolumn=column+1;
	while(count<winseqNum && newrow>=0&& newrow<boardNum && newcolumn>=0 && newcolumn<boardNum)
	{
		if(board[newrow][newcolumn]==currentPlayer)
		{
			count++;

		}
		if(board[newrow][newcolumn]!=currentPlayer || newrow<0||newrow>=boardNum || newcolumn<0 || newcolumn>=boardNum) break;
		newrow--;
		newcolumn++;
	}
	if(count==winseqNum) return 1;
	newrow=row+1;
	newcolumn=column-1;
	while(count<winseqNum && newrow>=0&& newrow<boardNum && newcolumn>=0 && newcolumn<boardNum)
	{
		if(board[newrow][newcolumn]==currentPlayer)
		{
			count++;

		}
		if(board[newrow][newcolumn]!=currentPlayer || newrow<0||newrow>=boardNum || newcolumn<0 || newcolumn>=boardNum) break;
		newrow++;
		newcolumn--;
	}
	if(count==winseqNum) return 1;

	int countall=0,i,j;
	for(i=0;i<boardNum;i++)
		for(j=0;j<boardNum;j++)
		{
			if(board[i][j]!=' ') countall++;
		}	
		if(countall==boardNum*boardNum) return 2;	
		return 0;
}

bool gameSaved()//judge whether user wanna save a game, return true and then save the game
{
	string input;
	cout<<"Would you like to save and exit the game? yes or no"<<endl;
	cin>>input;
	while(input!="yes" && input!="no")
	{
		cin.clear();
		cin.sync();
		cout<<"Wrong input, please input again."<<endl;
		cout<<"Would you like to save game? yes or no"<<endl;
		cin>>input;
	}
	if(input=="yes")
	{
		return true;
	}
	else
	{
		return false;
	}

}
void reInput()
{
	int playerNum1,boardNum1,winseqNum1;
	bool r=false;
	cout<<"How many players are playing the game?(We don't allow signal player)"<<endl;
	cin>>playerNum1;
	r=cin.fail();
	while(r)
	{
		cout<<"Invalid number.Please input again."<<endl;
		cout<<"How many players are playing the game?(We don't allow signal player)"<<endl;
		cin.clear();
		cin.sync();
		cin>>playerNum1;
		r=cin.fail();
	}
	cout<<"How large the board should be?"<<endl;
	cin>>boardNum1;
	r=cin.fail();
	while(r)
	{
		cout<<"Invalid number.Please input again."<<endl;
		cout<<"How large the board should be?"<<endl;
		cin.clear();
		cin.sync();
		cin>>boardNum1;
		r=cin.fail();
	}

	cout<<"What the win sequence count should be?"<<endl;
	cin>>winseqNum1;	
	r=cin.fail();
	while(r)
	{		  
		cin.clear();
		cin.sync();
		cout<<"Invalid number.Please input again."<<endl;
		cout<<"What the win sequence count should be?"<<endl;
		cin>>winseqNum1;
		r=cin.fail();
	}
	playerNum=playerNum1;
	boardNum=boardNum1;
	winseqNum=winseqNum1;

}


int game()
{
	int nr=1,nc=1,n=1,k,nrr=1;
	char allPossiblePlayer[26]={'X','O','A','B','C','D','E','F','G','H','I','J','K','L','M','N','P','Q','R','S','T','U','V','W','Y','Z'};
	char *actualPlayer;
	bool flagExit=false;	
	int winner=0;
	int i,j;
	bool r1,r2;
	int row,column;
	int index;
	char currentPlayer;
	int cp;
	string yesorno;
	cout<<"Would you like to resume a saved game? yes or no"<<endl;
	cin>>yesorno;
	while(yesorno !="yes" && yesorno !="no")
	{

		cin.clear();
		cin.sync();
		cout<<"Wrong input, please input again."<<endl;
		cout<<"Would you like to resume a saved game? yes or no"<<endl;
		cin>>yesorno;
	}
	if(yesorno=="yes")//resume saved game
	{
		char buffer[1024];
		ifstream myfile("board.txt");
		if(!myfile) 
			{
				cout<<"Unable to resume a saved game or the saved game doesn't exit, please try a new game."<<endl;
				fileexsit=false;
				return 1;
		    }

		myfile>>playerNum>>boardNum>>winseqNum;
		savedboard=new sb[boardNum*boardNum*8+boardNum*8];	

		board=new char*[boardNum*boardNum];
		for (i = 0; i < boardNum; i++)//initialize two dimension board
			board[i]=new char[boardNum];
		for(i=0;i<boardNum;i++)
			for(j=0;j<boardNum;j++)
				board[i][j]=' ';

		myfile.getline(buffer,1024);
		actualPlayer = new char[playerNum];//according to the number of players, choose actual players from allPossiblePlayer array
		for(i=0;i<playerNum;i++)			
			actualPlayer[i]=allPossiblePlayer[i];	

		index=0;		     	
		savedboard[index].center=' ';
		savedboard[index].row=-1;
		savedboard[index].column=-1;
		index++;
		savedboard[index].center=' ';
		savedboard[index].row=-1;
		savedboard[index].column=-1;
		index++;
		savedboard[index].center=' ';
		savedboard[index].row=-1;
		savedboard[index].column=-1;
		index++;
		savedboard[index].center=' ';
		savedboard[index].row=-1;
		savedboard[index].column=-1;
		index++;
		for(k=1;k<=boardNum;k++)
		{
			savedboard[index].center=k/100+48;
			savedboard[index].row=-1;
			savedboard[index].column=-1;
			index++;

			savedboard[index].center=(k/10)%10+48;
			savedboard[index].row=-1;
			savedboard[index].column=-1;
			index++;
			savedboard[index].center=k%10+48;
			savedboard[index].row=-1;
			savedboard[index].column=-1;
			index++;
			savedboard[index].center=' ';
			savedboard[index].row=-1;
			savedboard[index].column=-1;
			index++;
		}
		savedboard[index-1].center='\n';

		int bk=nr;	
		int flag=1;
		while (nr<2*boardNum)
		{
			if(nr%2==1)
			{/*store character '1' as '001' for grid alignment, because we don't know the size of board, 
			 if the user input 10 for the board, then '10' has two charactrers but '1' has only one character, it would affect the 
			 position of other characters*/
				savedboard[index].center=bk/100+48;
				savedboard[index].row=-1;
				savedboard[index].column=-1;
				index++;				
				savedboard[index].center=(bk/10)%10+48;
				savedboard[index].row=-1;
				savedboard[index].column=-1;
				index++;
				savedboard[index].center=bk%10+48;
				savedboard[index].row=-1;
				savedboard[index].column=-1;
				index++;
				savedboard[index].center=' ';
				savedboard[index].row=-1;
				savedboard[index].column=-1;
				index++;
				bk++;
				while(nc<boardNum)/*when initializing the savedboard, calculating all the possible location for the chess pieces
								  and set their corresponding row and column. I use this method, because everytime, when user inputs the 
								  row and column, just scan savedboard, find the position of current row and column in the savedboard,
								  and then set the 'center' value of savedboard as the value of current player. So it's very convenient 
								  to output the whole board on console*/
				{
					savedboard[index].center=' ';
					savedboard[index].row=-1;
					savedboard[index].column=-1;
					index++;
					savedboard[index].center=' ';
					savedboard[index].row=nrr;
					savedboard[index].column=nc;
					index++;
					savedboard[index].center=' ';
					savedboard[index].row=-1;
					savedboard[index].column=-1;
					index++;
					savedboard[index].center='|';
					savedboard[index].row=-1;
					savedboard[index].column=-1;
					index++;
					nc++;

				}
				savedboard[index].center=' ';
				savedboard[index].row=-1;
				savedboard[index].column=-1;
				index++;
				savedboard[index].center=' ';
				savedboard[index].row=nrr;
				savedboard[index].column=nc;
				index++;
				savedboard[index].center=' ';
				savedboard[index].row=-1;
				savedboard[index].column=-1;
				index++;
				savedboard[index].center='\n';
				savedboard[index].row=-1;
				savedboard[index].column=-1;
				index++;
				nrr++;

			}
			else
			{
				savedboard[index].center=' ';
				savedboard[index].row=-1;
				savedboard[index].column=-1;
				index++;				
				savedboard[index].center=' ';
				savedboard[index].row=-1;
				savedboard[index].column=-1;
				index++;
				savedboard[index].center=' ';
				savedboard[index].row=-1;
				savedboard[index].column=-1;
				index++;
				savedboard[index].center=' ';
				savedboard[index].row=-1;
				savedboard[index].column=-1;
				index++;

				while(nc<boardNum)
				{
					savedboard[index].center='-';
					savedboard[index].row=-1;
					savedboard[index].column=-1;
					index++;
					savedboard[index].center='-';
					savedboard[index].row=-1;
					savedboard[index].column=-1;
					index++;
					savedboard[index].center='-';
					savedboard[index].row=-1;
					savedboard[index].column=-1;
					index++;
					savedboard[index].center='+';
					savedboard[index].row=-1;
					savedboard[index].column=-1;
					index++;
					nc++;
				}
				savedboard[index].center='-';
				savedboard[index].row=-1;
				savedboard[index].column=-1;
				index++;
				savedboard[index].center='-';
				savedboard[index].row=-1;
				savedboard[index].column=-1;
				index++;
				savedboard[index].center='-';
				savedboard[index].row=-1;
				savedboard[index].column=-1;
				index++;
				savedboard[index].center='\n';
				savedboard[index].row=-1;
				savedboard[index].column=-1;
				index++;			
			}			
			nr++;
			nc=1;
		}	
		savedboard[index].center='\0';	
		savedboard[index].row=-1;
		savedboard[index].column=-1;
		index=0;
		system("cls");
		cout<<"Please wait..."<<endl;
		while(savedboard[index].center!='\0')
		{
			cout<<savedboard[index].center;
			index++;
		}
		wait(1);
		index=0;

		char player;
		while(!myfile.eof())
		{
			myfile>>row>>column>>player;
			myfile.getline(buffer,1024);
			board[row-1][column-1]=player;
			system("cls");
			while (savedboard[index].row!=row || savedboard[index].column!=column) index++;	

			savedboard[index].center=player;
			index=0;

			while(savedboard[index].center!='\0')
			{
				cout<<savedboard[index].center;
				index++;
			}

			wait(1);// output step in every second

			index=0;
		}

		index=0;
		myfile.close();
		int findCur=0;		
		while(actualPlayer[findCur]!=player) findCur++;
		if(findCur==playerNum-1) cp=0;
		else cp=findCur+1;
		while(winner==0)
		{
			while(cp<playerNum)			
			{
				cout<<"Please input the value of row and column."<<endl;

				cin>>row;
				r1=cin.fail();
				cin>>column;
				r2=cin.fail();

				while(row<0 || row>boardNum||column<0||column>boardNum||r1||r2||board[row-1][column-1]!=' ')
				{
					cin.clear();
					cin.sync();		
					if(row<0 || row>boardNum||column<0||column>boardNum||r1||r2)
					{
						
						cout<<"Please input valid value of row or column"<<endl;
						cout<<"Please input again."<<endl;
						
					}
					else if(board[row-1][column-1]!=' ')
					{
							
						cout<<"This grid is full, please choose other row and column"<<endl;
						cout<<"Please input the value of row and column."<<endl;
					}
					cin>>row;
					r1=cin.fail();
					cin>>column;
					r2=cin.fail();
				}

				index=0;
				while(savedboard[index].row!=row || savedboard[index].column!=column) index++;
				savedboard[index].center=actualPlayer[cp];			
				currentPlayer=actualPlayer[cp];
				board[row-1][column-1]=currentPlayer;
				system("cls");
				index=0;
				while(savedboard[index].center!='\0')
				{
					cout<<savedboard[index].center;
					index++;
				}

				winner=0;
				ofstream fs;
				fs.open("board.txt", ios_base::out | ios_base::app);
				fs<<row;
				fs<<' ';
				fs<<column;
				fs<<' ';
				fs<<currentPlayer;
				fs<<'\n';	

				winner=checkWhetherWin(row,column,currentPlayer,winseqNum,boardNum);

				if( winner==0 && gameSaved()) 
				{

					return 1;
				}
				if(winner==1 || winner==2) break;
				cp++;
			}
			cp=0;
		}

		if(1==winner)cout<<"Game over, Winner is "<<currentPlayer<<endl;		
		if(2==winner)cout<<"No one wins"<<endl;
		return 1;

	}

	if(yesorno=="no")
	{
		cout<<"How many players are playing the game?(We don't allow signal player)"<<endl;
		cin>>playerNum;
		while(!cin>>playerNum)
		{
			cout<<"Invalid number.Please input again."<<endl;
			cout<<"How many players are playing the game?(We don't allow signal player)"<<endl;
			cin.clear();
			cin.sync();
			cin>>playerNum;
		}
		cout<<"How large the board should be?"<<endl;
		cin>>boardNum;
		while(!cin>>boardNum)
		{
			cout<<"Invalid number.Please input again."<<endl;
			cout<<"How large the board should be?"<<endl;
			cin.clear();
			cin.sync();
			cin>>boardNum;
		}

		cout<<"What the win sequence count should be?"<<endl;
		cin>>winseqNum;		
		while(!cin>>winseqNum)
		{		  
			cin.clear();
			cin.sync();
			cout<<"Invalid number.Please input again."<<endl;
			cout<<"What the win sequence count should be?"<<endl;
			cin>>winseqNum;		
		}

		while( !checkWinningPossible(playerNum,boardNum,winseqNum))
		{
			cout<<endl;
			cout<<"Please reinput player number, board number, win sequence: "<<endl;
			reInput();   //reinput the play number, board number, win sequence         

		}
		ofstream fs;
		fs.open("board.txt", ios_base::out );
		fs<<playerNum;
		fs<<' ';
		fs<<boardNum;
		fs<<' ';
		fs<<winseqNum; 				 
		fs<<'\n';
		savedboard=new sb[boardNum*boardNum*8+boardNum*8];	
		index=0;	

		savedboard[index].center=' ';
		savedboard[index].row=-1;
		savedboard[index].column=-1;
		index++;
		savedboard[index].center=' ';
		savedboard[index].row=-1;
		savedboard[index].column=-1;
		index++;
		savedboard[index].center=' ';
		savedboard[index].row=-1;
		savedboard[index].column=-1;
		index++;
		savedboard[index].center=' ';
		savedboard[index].row=-1;
		savedboard[index].column=-1;
		index++;
		for(k=1;k<=boardNum;k++)
		{
			savedboard[index].center=k/100+48;
			savedboard[index].row=-1;
			savedboard[index].column=-1;
			index++;

			savedboard[index].center=(k/10)%10+48;
			savedboard[index].row=-1;
			savedboard[index].column=-1;
			index++;
			savedboard[index].center=k%10+48;
			savedboard[index].row=-1;
			savedboard[index].column=-1;
			index++;
			savedboard[index].center=' ';
			savedboard[index].row=-1;
			savedboard[index].column=-1;
			index++;
		}
		savedboard[index-1].center='\n';


		int bk=nr;	
		int flag=1;
		while (nr<2*boardNum)
		{
			if(nr%2==1)
			{

				savedboard[index].center=bk/100+48;
				savedboard[index].row=-1;
				savedboard[index].column=-1;
				index++;				
				savedboard[index].center=(bk/10)%10+48;
				savedboard[index].row=-1;
				savedboard[index].column=-1;
				index++;
				savedboard[index].center=bk%10+48;
				savedboard[index].row=-1;
				savedboard[index].column=-1;
				index++;
				savedboard[index].center=' ';
				savedboard[index].row=-1;
				savedboard[index].column=-1;
				index++;
				bk++;
				while(nc<boardNum)
				{
					savedboard[index].center=' ';
					savedboard[index].row=-1;
					savedboard[index].column=-1;
					index++;
					savedboard[index].center=' ';
					savedboard[index].row=nrr;
					savedboard[index].column=nc;
					index++;
					savedboard[index].center=' ';
					savedboard[index].row=-1;
					savedboard[index].column=-1;
					index++;
					savedboard[index].center='|';
					savedboard[index].row=-1;
					savedboard[index].column=-1;
					index++;
					nc++;

				}
				savedboard[index].center=' ';
				savedboard[index].row=-1;
				savedboard[index].column=-1;
				index++;
				savedboard[index].center=' ';
				savedboard[index].row=nrr;
				savedboard[index].column=nc;
				index++;
				savedboard[index].center=' ';
				savedboard[index].row=-1;
				savedboard[index].column=-1;
				index++;
				savedboard[index].center='\n';
				savedboard[index].row=-1;
				savedboard[index].column=-1;
				index++;
				nrr++;

			}
			else
			{
				savedboard[index].center=' ';
				savedboard[index].row=-1;
				savedboard[index].column=-1;
				index++;				
				savedboard[index].center=' ';
				savedboard[index].row=-1;
				savedboard[index].column=-1;
				index++;
				savedboard[index].center=' ';
				savedboard[index].row=-1;
				savedboard[index].column=-1;
				index++;
				savedboard[index].center=' ';
				savedboard[index].row=-1;
				savedboard[index].column=-1;
				index++;

				while(nc<boardNum)
				{
					savedboard[index].center='-';
					savedboard[index].row=-1;
					savedboard[index].column=-1;
					index++;
					savedboard[index].center='-';
					savedboard[index].row=-1;
					savedboard[index].column=-1;
					index++;
					savedboard[index].center='-';
					savedboard[index].row=-1;
					savedboard[index].column=-1;
					index++;
					savedboard[index].center='+';
					savedboard[index].row=-1;
					savedboard[index].column=-1;
					index++;
					nc++;
				}
				savedboard[index].center='-';
				savedboard[index].row=-1;
				savedboard[index].column=-1;
				index++;
				savedboard[index].center='-';
				savedboard[index].row=-1;
				savedboard[index].column=-1;
				index++;
				savedboard[index].center='-';
				savedboard[index].row=-1;
				savedboard[index].column=-1;
				index++;
				savedboard[index].center='\n';
				savedboard[index].row=-1;
				savedboard[index].column=-1;
				index++;


			}			
			nr++;
			nc=1;
		}

		savedboard[index].center='\0';	
		savedboard[index].row=-1;
		savedboard[index].column=-1;
		index=0;
		while(savedboard[index].center!='\0')
		{
			cout<<savedboard[index].center;
			index++;
		}
		cout<<endl;

		board=new char*[boardNum*boardNum];
		for (i = 0; i < boardNum; i++)//initialize 
			board[i]=new char[boardNum];
		for(i=0;i<boardNum;i++)
			for(j=0;j<boardNum;j++)
				board[i][j]=' ';

		actualPlayer = new char[playerNum];
		for(i=0;i<playerNum;i++)			
			actualPlayer[i]=allPossiblePlayer[i];	

		winner=0;
		while(winner==0)
		{		

			for(cp=0;cp<playerNum;cp++)
			{   
				currentPlayer=actualPlayer[cp];
				cout<<"Please input the value of row and column."<<endl;
				cin>>row;
				r1=cin.fail();
				cin>>column;
				r2=cin.fail();
				while(row<0 || row>boardNum||column<0||column>boardNum||r1||r2||board[row-1][column-1]!=' ')
				{
					cin.clear();
					cin.sync();		
					if(row<0 || row>boardNum||column<0||column>boardNum||r1||r2)
					{
						cout<<"Please input valid value of row or column"<<endl;
						cout<<"Please input again."<<endl;

					}
					else if(board[row-1][column-1]!=' ')
					{
						cout<<"This grid is full, please choose other row and column"<<endl;
						cout<<"Please input the value of row and column."<<endl;
					}
					cin>>row;
					r1=cin.fail();
					cin>>column;
					r2=cin.fail();
				}


				index=0;
				while (savedboard[index].row!=row || savedboard[index].column!=column) index++;
				savedboard[index].center=currentPlayer;
				board[row-1][column-1]=currentPlayer;
				index=0;
				system("cls");
				while(savedboard[index].center!='\0')
				{
					cout<<savedboard[index].center;
					index++;
				}
				winner=checkWhetherWin(row,column,currentPlayer,winseqNum,boardNum);//judge the current condition whether current player wins

				fs<<row;
				fs<<' ';
				fs<<column;
				fs<<' ';
				fs<<currentPlayer;
				fs<<'\n';		

				if( winner==0 && gameSaved()) 
				{
					fs.close();
					return 1;
				}
				if(winner==1 || winner==2) break;

			}
		}

		if(1==winner)
		{cout<<"Game over, Winner is "<<currentPlayer<<endl;
		fs.close();
		}
		if(2==winner)
		{cout<<"No one wins"<<endl;
		fs.close();
		}
		return 1;

	}
}
int main()
{
	game();
	while(fileexsit==false) 
	{
	   fileexsit=true;
	   game();
	}
	return 1;
}