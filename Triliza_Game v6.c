//TRILIZA GAME 
//CREATOR THANASIS CHARISOUDIS
//

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <conio.h>
#define del 20 

int best_move(int (*numb)[3]);
int IsWinner(int (*numb)[3]);
int rand_multi(char *name1,char *name2,char *side,char *pc_side);
void delay(time_t dur);
void intro_graph(time_t durs);
void wait(int entr);
void loading_fx(void);

//in multiplayer mode (game-choice==2) pc <==> player 2
int main()	//OK!
{
	system("chcp 1253"); //in order to accept also greek names
	
	clock_t t; //time
	int durs=8,wait1=2,d,ti,i,pc_starts[50]={0},pc_st,swich=0,game2,j,game_choice,null,null0,num,pc_num,numb[3][3],win,pl_win_pc,pl_win_pl,pl_draw,pl_games,a,pl_side,moves_pl[80],moves_pc[80],res[80],point,name_len,pl_gaps,min,sec,secg[80],ming[80],sum_min,sum_sec,sum_moves,best_game,worst_game,max,posi,posj;
	bool cn=true,pc_num_found=false,not_last=true,not_first=false,con2con,con_side,con_num,EMPTY,con_win,ch,ch_ans,con_name,flag5;
	char c_board[3][3],f_ans,ans1[80],playground[3][3],name[80],name1[27],name2[27],choice[80],side,pc_side,anal,nums[10],game_pic[50][9],start[50][27]={32},pll_side,pl_pc_side,pl_1[27],pl_2[27];
	float p;

	//Define some vars that should not be initialized in the loop
	pl_win_pc=0; pl_win_pl=0; pl_draw=0; pl_games=1; 
	for (i=0;i<80;i++) 
	{
		secg[i]=0;
		ming[i]=0;
	}     
	
 	f_ans='y';
  	while (f_ans=='y' || f_ans=='Y')
	{			  	
		//Initialize all matrices together, as they're all 3 by 3	
		d=49;
		for (i=0;i<3;i++) 
		{
			for (j=0;j<3;j++)
			{
				c_board[i][j]=d;      //C_board is used for putting numbers (as chars) in cells
				d+=1;
				playground[i][j]=' '; //Playground is the empty matrix that's beeing filled by players' movements
				numb[i][j]=0;       //Zeroing control matrix
			}
		}
		game2=0;
		//CLEAR SCREEN - GOOGLE TOLD ME THAT
		system("cls");
	
		//display prokatarktika only if i==1
		if (pl_games==1)
		{
			intro_graph(durs);
			system("cls");
			
		//----- START OF THE GAME ------//
		
			puts("\nWelcome to your first triliza game!\n\nChoose a mode (1/2):\n");
			printf("1.   Player  %c  /  Pc       \n",92);
			  printf("2.  Player    %c/ s  Player  \n\nYour choice: ",92);
			bool con=true;
			do{
			scanf("%d",&game_choice);
			fflush(stdin);
			if (game_choice!=1 && game_choice!=2) printf("\nNot valid choice. Try Again: ");
			else con=false;
			}while (con);
			//CLEAR CHOICE SELECTION
			system ("cls");
			puts("\nWelcome to triliza game!\n");
			if (game_choice==1) printf("< Single-Player Mode >\n"); else printf("< Multi-Player Mode >\n");	
			
			//get player(s) name(s)
			for (int mi=0;mi<game_choice;++mi)
			{
				con_name=true;
				while (con_name)
				{
					for (i=0;i<80;i++) name[i]=32;
					if (game_choice==2) printf("\nPlayer %d ",mi+1);
					else printf("\n");
					printf("Name: ");
					scanf("%s",name);
					fflush;
					
					//find name length - Needed in statistics window
					name_len=strlen(name);
					//If name's >=27 chars then pl_gaps<=0 in the game analysis board
					if (name_len<=20 && name_len>=2) con_name=false; 
					else printf("\nName length out of bounds (%d chars). Re-enter a name 2 to 20 characters.\n",name_len);
				}
				if (name[0]>90) name[0]-=32;  // convert first letter to capital
				if (game_choice==2 && mi==0) {for(int mii=0;mii<27;++mii) name1[mii]=name[mii];}
				else if (game_choice==2 && mi==1) {for(int mii=0;mii<27;++mii) name2[mii]=name[mii];}
			}
			//assign general names "above all changes"
			for (int ml=0;ml<27;ml++)
			{	
				pl_1[ml]=name1[ml];
				pl_2[ml]=name2[ml];
			}
			//for statistics: who started
			if (game_choice==2)
			{
				int ci=0;
				do 
				{
					start[0][ci]=name1[ci];
					ci++; 
				}
				while (ci<27 && name1[ci]!='\0');
			}
			//Choosing Side W/ Check
			if (game_choice==2) printf("\n%s, you choose side first.",name1);
			else printf("\n%s, you have to choose a side. ",name);
			pl_side=1;
			ch=false;
			con_side=true;
			while (con_side)
			{
				printf("\nChoose a side ('o' or 'x'): ");
				scanf("%s",choice);
				fflush;
				
				if (choice[0]==111)
				{
					con_side=false;
					side=111;
				}
				else if (choice[0]==120)
				{
					con_side=false;
					ch=true;
				}
				else
				{
					printf("\nOnly 'o' & 'x' are allowed as sides.\n");
					//choosing for user if he has not entered correct value for 4 times
					if (pl_side==3) 
					{
						con_side=false;
						puts("\nIt seems that you can't insert correct value. I will choose for you...");
						side=110;
					}
					else pl_side++;
				}
			}
			
			//pc_side is the left char
			if (side='o') 
				if (ch) 
				{
					pc_side='o'; 
					side='x';	
				}	
				else pc_side='x';         //Could not work before
			else pc_side='o';
			
			//"above all" chars --> for game(s) analysis window 
			if (pl_games==1 && game_choice==2)
			{
				pll_side=side;
				pl_pc_side=pc_side;
			}
			
			if (game_choice==2) printf("\n\nOk, %s, is '%c'. Therefore, %s is '%c'.\n\nHere's the playground\n",name1,side,name2,pc_side);
			else printf("\n\nOk, %s, you are '%c'. Therefore, i am '%c'.\n\nHere's the playground\n",name,side,pc_side);
			printf("\n %c | %c | %c \n-----------\n %c | %c | %c \n-----------\n %c | %c | %c \n",playground[0][0],playground[0][1],playground[0][2],playground[1][0],playground[1][1],playground[1][2],playground[2][0],playground[2][1],playground[2][2]);
		
			printf("\nEvery cell points to a number (1-9):\n");
			printf("\n %c | %c | %c \n-----------\n %c | %c | %c \n-----------\n %c | %c | %c \n",c_board[0][0],c_board[0][1],c_board[0][2],c_board[1][0],c_board[1][1],c_board[1][2],c_board[2][0],c_board[2][1],c_board[2][2]);	
		
			if (game_choice==2) printf("\nSince one chooses a number that points to an empty cell, \nhe'll see his side in that cell. \nAfter that it's the other's turn to place his side in the playground.\nEach of you manages to fill an entire row or column or diagonal first wins.\n");
			else printf("\nSince you choose a number that points to an empty cell, you'll see your side in that cell. \nAfter that it's my turn to place my side in the playground.\nEach of us manages to fill an entire row or column or diagonal first wins.\n");
		}
		else 
		{
			if (game_choice==2)
			{
				swich=rand_multi(name1,name2,&side,&pc_side);
				if (swich) //fill statistics board of who started
				{
					int ci=0;
					do 
					{
						start[pl_games-1][ci]=name1[ci];
						ci++; 
					}
					while (ci<27 && name1[ci]!='\0');
				}	
				printf("\n\nOk, %s & %s.\n\nHere's the playground (%s is '%c' & %s is '%c', as before): \n",name1,name2,name1,side,name2,pc_side);
			}
			else 
			{
				printf("\n\nOk, %s.\n\nHere's the playground (you are '%c' & i am '%c', as before): \n",name,side,pc_side);
								
				//random start in single player mode
				srand(time(NULL)); //generating numbers w/ different initial value
				if (game_choice==1 && (pl_games+(rand()%200+1))%2==0)
				{
					pc_starts[pl_games-1]=1;  //for statistics
					not_first=not_last=true;	// avoiding user's first && last move
				}
			}
			printf("\n %c | %c | %c \n-----------\n %c | %c | %c \n-----------\n %c | %c | %c \n",playground[0][0],playground[0][1],playground[0][2],playground[1][0],playground[1][1],playground[1][2],playground[2][0],playground[2][1],playground[2][2]);
		}
	//---- Main Part ----//
		printf("\nOk, we are ready. "); 
		if (pc_starts[pl_games-1]==1) printf("Now, it's my turn to start.\n");
		printf("Let,s play! ");	system("pause");
		system("cls");
	
		t = clock(); //Begin clock
		
		//initialize boolean values --> bug fix
		if (pl_games>1) 
		{
			pc_num_found=false;
			cn=true;
		}
		
		i=1;
		if (pc_starts[pl_games-1]) pc_st=8;
		else pc_st=6;
		con_win=true;
		while (i<pc_st && (con_win)) 
		{
			//
			if (pc_starts[pl_games-1]==0)
			{
				if (i==5) //only in case of draw make automatically user's last move
				{
					con_num=false;
					flag5=true;
 					for (ti=0;ti<3 && flag5;ti++)
					{	
						for (a=0;a<3;a++)
						{
							if (numb[ti][a]==0)
     						{
								num=(3*ti)+a+1;
	   							flag5=false;
		  					//not using brake so as to take last empty since first will be taken by pc via best_move()
		  					}
						}
					}
				}
				else con_num=true;
			}
			else 
			{	//checking in case pc starts
				if (i>=6) //only in case of draw make automatically user's last move
				{
					con_num=false;
					pc_num_found=true;
					flag5=true;
 					for (ti=0;ti<3 && flag5;ti++)
					{	
						for (a=0;a<3;a++)
						{
							if (numb[ti][a]==0)
     						{
								pc_num=(3*ti)+a+1;
	   							flag5=false;
		  						break;
		  					}
						}
					}
				}
				else con_num=true;
			}
			
		//Getting a right value from user
			if (i==6 && not_last==true) cn=false;
		//Begin Loop
			while (con_num && !not_first && cn)  //not first is true if pc starts 
			{
				//Asking for a number of c_board w/ check
				if (i==1) 
				{
					printf("\nGame: %d\n\n",pl_games);
					//printing the numbers for cls
					if (game_choice==2)
					{
						printf("\n      %c | %c | %c \n     -----------  %s, you are %c.\n      %c | %c | %c     \n     -----------  %s, you are %c.\n      %c | %c | %c \n",c_board[0][0],c_board[0][1],c_board[0][2],name1,side,c_board[1][0],c_board[1][1],c_board[1][2],name2,pc_side,c_board[2][0],c_board[2][1],c_board[2][2]);
						printf("\n\n%s, choose a number in order to get started: ",name1);
					}
					else
					{ 
						printf("\n      %c | %c | %c \n     -----------\n      %c | %c | %c    %s, you are %c. \n     -----------\n      %c | %c | %c \n",c_board[0][0],c_board[0][1],c_board[0][2],c_board[1][0],c_board[1][1],c_board[1][2],name,side,c_board[2][0],c_board[2][1],c_board[2][2]);
						printf("\n\nChoose a number in order to get started: ");
					}
				}
				else if (i!=pc_st-1)
				{
					if (game_choice==2) printf("\n%s, choose your next move (from the remaining numbers): ",name1);
					else printf("\nChoose your next move (from the remaining numbers): ");
				}

				scanf("%s",nums);  //Reading user's choice
				fflush;
				//to avoid causing panik when a char inserted
				num=atoi(nums);
				if (num>=1 && num<=9) 
				{
		
				//Checking if the cell chosen is available
					EMPTY=false;
					if ( num!=3  &&  num!=6  &&  num!=9 ) //For nums t.w.: num%3=0 i ahve to take a separate condition so that the match between num & numb[] is correct
					{	
						if ( numb[num/3][num%3-1]==0 )
							EMPTY=true;
					}
					else
					{	
						if ( numb[num/3-1][2]==0 ) EMPTY=true;
					}
		
				//If it's empty stop the loop
					if (EMPTY) 
						con_num=false;
					else
					{
						printf("The position %d is not empty. Choose only one of the remaining cells!\n",num);							
					//Showing the remaining cells so as to make a right choice
						printf("\nHere are the remaining numbers-cells:\n");
						printf("\n      %c | %c | %c \n     -----------\n      %c | %c | %c \n     -----------\n      %c | %c | %c \n",c_board[0][0],c_board[0][1],c_board[0][2],c_board[1][0],c_board[1][1],c_board[1][2],c_board[2][0],c_board[2][1],c_board[2][2]);		
			
					}
				}
				else
				{
					if (i==1) system("cls");   //Fixing print error only in first loop
					printf("\nYou can only choose a number between 1 and 9\n"); 
				}
			}
			if (!not_first)
			{
			//Putting the user's value in the right cell in each matrix
				if ( num<=3 )
				{
					numb[0][num-1]=1;  //In the numbers matrix the 1 means user and -1 means pc
					playground[0][num-1]=side;  //Putting user's chosen char in the playground 
					c_board[0][num-1]=' ';     // Deleting the number the cell that it points to has been chosen
					if (i==5 && game_choice==1)
					{
						posi=0;
						posj=num-1;
					}
				}
				else if ( num<=6 )
				{
					numb[1][num-4]=1;  
					playground[1][num-4]=side; 
					c_board[1][num-4]=' '; 
					if (i==5 && game_choice==1)
					{
						posi=1;
						posj=num-4;
					}
				}
				else
				{
					numb[2][num-7]=1;  
					playground[2][num-7]=side; 
					c_board[2][num-7]=' '; 
					if (i==5 && game_choice==1)
					{
						posi=2;
						posj=num-7;
					}
				}
			}
			else not_first=false; //to be able to write down next move
			//--------delay before pc's mpove
			if (game_choice==1 )
			{
				system("cls");
				printf("\nGame: %d\n\n\n",pl_games);	
				printf("\n      %c | %c | %c \n     -----------    %c ---> %s\n      %c | %c | %c \n     -----------    %c ---> Pc\n      %c | %c | %c \n",playground[0][0],playground[0][1],playground[0][2],side,name,playground[1][0],playground[1][1],playground[1][2],pc_side,playground[2][0],playground[2][1],playground[2][2]);
				if (i!=5) wait(1);
			}
			//---------move on
			//in player vs player check win after each move (after third round of moves)
			if (game_choice==2 && i>=3) 
			{
				game2=IsWinner(numb);  //if one has won don't con
				if (game2!=0) con_win=false;
			}
			
		//After submitting results i'll have them printed (User's move)
			system("cls");
			printf("\nGame: %d\n\n",pl_games);
			if (i==5 && game_choice!=2) 
			{
				printf("My move is: %d. After my move the playground's like : \n",pc_num);
				playground[posi][posj]=32;//deleting th last cell
				printf("\n      %c | %c | %c \n     -----------    %c ---> %s\n      %c | %c | %c \n     -----------    %c ---> Pc\n      %c | %c | %c \n",playground[0][0],playground[0][1],playground[0][2],side,name,playground[1][0],playground[1][1],playground[1][2],pc_side,playground[2][0],playground[2][1],playground[2][2]);
				playground[posi][posj]=side;  //re putting the previus value
				wait(3);
				system("cls");
				printf("\nGame: %d\n\n",pl_games);
				printf("After my move the only available cell was %d.\n",num);
				printf("\n      %c | %c | %c \n     -----------    %c ---> %s\n      %c | %c | %c \n     -----------    %c ---> Pc\n      %c | %c | %c \n",playground[0][0],playground[0][1],playground[0][2],side,name,playground[1][0],playground[1][1],playground[1][2],pc_side,playground[2][0],playground[2][1],playground[2][2]); 
			}
			else printf("\n      %c | %c | %c \n     -----------    %c ---> %s\n      %c | %c | %c \n     -----------    %c ---> %s\n      %c | %c | %c \n",playground[0][0],playground[0][1],playground[0][2],side,name1,playground[1][0],playground[1][1],playground[1][2],pc_side,name2,playground[2][0],playground[2][1],playground[2][2]); 
		//User has the last move
			if (i<pc_st-1 && game2==0)
			{
			//Having user's choice i can make mine (best one) 
				if (game_choice==2)
				{
					con_num=true;
					while (con_num)
					{
					if (i==1) printf("\n%s, choose your first move: ",name2);
					else printf("\n%s, choose your next move (from the remaining numbers): ",name2);
					scanf("%s",nums);  //Reading user's choice
					fflush;
					//to avoid causing panik when a char inserted
					num=atoi(nums);
					if (num>=1 && num<=9) 
					{
			
					//Checking if the cell chosen is available
						EMPTY=false;
						if ( num!=3  &&  num!=6  &&  num!=9 ) //For nums t.w.: num%3=0 i ahve to take a separate condition so that the match between num & numb[] is correct
						{	
								if ( numb[num/3][num%3-1]==0 )
								EMPTY=true;
						}
						else
						{	
							if ( numb[num/3-1][2]==0 ) EMPTY=true;
						}
		
					//If it's empty stop the loop
						if (EMPTY) 
							con_num=false;
						else
						{
							printf("The position %d is not empty. Choose only one of the remaining cells!\n",num);							
						//Showing the remaining cells so as to make a right choice
							printf("\nHere are the remaining numbers-cells:\n");
							printf("\n      %c | %c | %c \n     -----------\n      %c | %c | %c \n     -----------\n      %c | %c | %c \n",c_board[0][0],c_board[0][1],c_board[0][2],c_board[1][0],c_board[1][1],c_board[1][2],c_board[2][0],c_board[2][1],c_board[2][2]);			
						}
					}
					else printf("\nYou can only choose a number between 1 and 9\n"); 
					}
					pc_num=num;
				}
				else 
				{
					if (pc_num_found==false) pc_num=best_move(numb);	
				}
			}
			check_win: if (i<pc_st-1)
			{
			//Putting the pc's value in the right cell in each matrix
				if ( pc_num<=3)
				{
					numb[0][pc_num-1]=-1;  //In the numbers matrix the 1 means user and -1 means pc
					playground[0][pc_num-1]=pc_side;  //Putting pc's char in the playground 
					c_board[0][pc_num-1]=' ';     // Deleting the number, the cell that it points to, has been chosen
				}
				else if (pc_num<=6)
				{
					numb[1][pc_num-4]=-1;  
					playground[1][pc_num-4]=pc_side; 
					c_board[1][pc_num-4]=' '; 
				}
				else
				{
					numb[2][pc_num-7]=-1;  
					playground[2][pc_num-7]=pc_side; 
					c_board[2][pc_num-7]=' '; 
				}
			}	
		//Checking Win
			if (i>=3 && game2==0)
			{
				win=IsWinner(numb);
				if (win!=0)	con_win=false; //Stop loop	
				if (win==2)	
				{
					//My turn - did not write down to be simpler
					//printf("\nNow it's my turn...'\n");
					// In defeat : system("pause"); ---> To be totally visible
					system("cls");
					printf("\nGame : %d\n",pl_games);
					if (game_choice!=2) 
					{
						printf("\nMy move is: %d. After my move the playground's like : \n",pc_num);
						printf("\n      %c | %c | %c \n     -----------    %c ---> %s\n      %c | %c | %c \n     -----------    %c ---> Pc\n      %c | %c | %c \n",playground[0][0],playground[0][1],playground[0][2],side,name,playground[1][0],playground[1][1],playground[1][2],pc_side,playground[2][0],playground[2][1],playground[2][2]);
					}
					else printf("\n      %c | %c | %c \n     -----------    %c ---> %s\n      %c | %c | %c \n     -----------    %c ---> %s\n      %c | %c | %c \n",playground[0][0],playground[0][1],playground[0][2],side,name1,playground[1][0],playground[1][1],playground[1][2],pc_side,name2,playground[2][0],playground[2][1],playground[2][2]); 
				}
			}		
			
		//If the winner hasn't been found (con_win=true) keep on playing		
			if (con_win && i<pc_st-1)
			{	
			 //My turn
				system("cls");
				//Clearing screen and printing only the latest playground update		
				printf("\nGame: %d\n",pl_games);
				if (game_choice!=2) printf("\nMy move is: %d. After my move the playground's like : \n",pc_num);
				else printf("\n");
				if (game_choice!=2) printf("\n      %c | %c | %c \n     -----------    %c ---> %s\n      %c | %c | %c \n     -----------    %c ---> Pc\n      %c | %c | %c \n",playground[0][0],playground[0][1],playground[0][2],side,name,playground[1][0],playground[1][1],playground[1][2],pc_side,playground[2][0],playground[2][1],playground[2][2]);
				else printf("\n      %c | %c | %c \n     -----------    %c ---> %s\n      %c | %c | %c \n     -----------    %c ---> %s\n      %c | %c | %c \n",playground[0][0],playground[0][1],playground[0][2],side,name1,playground[1][0],playground[1][1],playground[1][2],pc_side,name2,playground[2][0],playground[2][1],playground[2][2]); 
			}
			i++;
			if (i==7) break;
		}	
		
		//Statistics
		point=pl_games-1; //matrices start from 0 whereas pl_gmaes from 1
		if (game_choice==1)
		{	
			//Giving Result
			if (win==0)
			{
				printf("\nNice, we have a draw!\n");
				moves_pl[point]=i-1;
				moves_pc[point]=i-2;
				pl_draw++;	
			}	
			else if (win==1)  
			{
				printf("\nBravo, you have won!!\n");
				moves_pl[point]=i-1;
				moves_pc[point]=i-2;
				pl_win_pl++;	
			}	
			else 
			{
				printf("\nDefeat:( Don't Give Up!\n");
				moves_pc[point]=i-1;
				moves_pl[point]=i-1;
				pl_win_pc++;
			}
			res[point]=win;
		}
		else
		{
			//Giving Result
			if (game2==0 && win==0)
			{
				printf("\nNice, we have a draw!\n");
				if (swich)
				{
					moves_pl[point]=i-1;
					moves_pc[point]=i-2;
				}
				else
				{
					moves_pc[point]=i-1;
					moves_pl[point]=i-2;	
				}
				pl_draw++;	
				res[point]=0;
			}	
			else if (win==1 || game2==1)  
			{
				printf("\n%s won!!\n",name1);
				if (swich==0)
				{
					moves_pl[point]=i-1;
					moves_pc[point]=i-2;
					pl_win_pl++;
					res[point]=1;
				}
				else 
				{
					moves_pc[point]=i-1;
					moves_pl[point]=i-1;
					pl_win_pc++;
					res[point]=2;
				}
			}	
			else 
			{
				printf("\n%s won!!\n",name2);
				if (swich==0)
				{
					moves_pc[point]=i-1;
					moves_pl[point]=i-1;
					pl_win_pc++;
					res[point]=2;
				}
				else
				{
					moves_pl[point]=i-1;
					moves_pc[point]=i-2;
					pl_win_pl++;
					res[point]=1;					
				}
			}
		}
		//time manipulation
		t=clock()-t;         //GOOGLE TOLD ME THAT
		sec=(int)((float)t)/CLOCKS_PER_SEC;  
		min=(int)sec/60;
		sec=sec%60;
		secg[point]=sec;
		ming[point]=min;
		printf ("\nGame duration: %02d:%02d sec\n",ming[point],secg[point]);
		//keeping game pic
		int g,g1,g2=0;
		for (g=0;g<3;++g)
		{
			for (g1=0;g1<3;++g1)	
			{
				game_pic[point][g2]=playground[g][g1];  //taking current playground a pic
				++g2;
			}
		}
		//Asking for new game w/ answer's check	
		con2con=true;
		ch_ans=false;
    	while (con2con)
    	{
			printf("\nDo you want to try one more time? ('Y' for YES, 'N' for NO): ");
  	  		scanf("%s",ans1);
  	  		fflush;
  	  
  	  		if (ans1[0]=='Y'||ans1[0]=='y')  //These are the only accepted answwers
			{	
				con2con=false;
				f_ans=ans1[0];
				system("cls");
			}
			else if (ans1[0]=='N'||ans1[0]=='n')  					//These are the only accepted answwers
			{
				system("cls");// printing results in a clean screen
				con2con=false;
				ch_ans=true;
			}
  	  		else 
				printf("\nNot acceptable char. \nPlease give only the acceptable char ('Y' or 'N') in the following question.\n"); 
    	}
    	
		if (ch_ans) f_ans='n';	//doing this in order to work. Did not work before
		else f_ans='y';
		
    	//Got the answer
		if (f_ans=='y'||f_ans=='Y') 
		{	
			pl_games++;

		}
		//if ans negative ---> print results
		else                       
		{
			if (pl_games==1 && game_choice==1)              //No use of statisticks in a solo game
			{	
				printf("\nYou made %d moves.\n",i-1);							
				printf("\nThank You!\n");
			}
			else if (game_choice==1)                        //Print game statistics
			{
				if (pl_win_pl==0) 
				{
					printf("\n\n%s you did not manage to win me in any of the %d games we played.\nBut it's allright! ",name,pl_games);
					if (pl_draw==1) printf("We had a draw.");
					else if (pl_draw>1) printf("We had %d times a draw.",pl_draw);
					printf("\n\nThank you for trying. Life goes on!\n\n");
				}
				else 
				{
					//Finding the percentage of players victories
					p=(float)pl_win_pl/pl_games*100;
					
					//Regarding the percentage, characterise the player
					if (p<35.) 
						//Statistics output
						printf("\n\n%s, you got %d out of the %d games we played.\nThanks for trying.\n\n",name,pl_win_pl,pl_games);
					else if (p<55.) 
						//Statistics output
						printf("\n\n%s, you got %d out of the %d games we played, which is good:)\nThanks for trying.\n\n",name,pl_win_pl,pl_games);
					else
						//Statistics output
						printf("\n\n%s, you got %d out of the %d games we played, which is great!\nThanks for trying.\n\n",name,pl_win_pl,pl_games);
				}	
			}
			else printf("\nThank You!\n");
			wait(5);
			
		//================= Print statistics =============================//
			//Loading fx
			loading_fx();
			
			//Show Analysis Window
				sum_min=0;
				sum_sec=0;
				sum_moves=0;
				//Mean time of all games
				for (i=0;i<pl_games;i++)
				{
					sum_min=sum_min+ming[i];
					sum_sec+=secg[i];
					sum_moves+=moves_pl[i];
				}
			if (game_choice==1)
			{
				//Finding Best & Worst Game
				if (pl_games==1 || pl_draw==pl_games)  //print 0 if pl_games ==1 or all games are draws
				{
					best_game=0;
					worst_game=0;
				}
				else if (pl_win_pl==pl_games) //only wins
				{
					max=moves_pl[0];
					worst_game=1;        //initialize values
					min=moves_pl[0];   
					best_game=1;
					for (i=0;i<pl_games;i++)
					{
						if (moves_pl[i]>max)    //the worst game is the one user won with most moves
						{
							max=moves_pl[i];
							worst_game=i+1;
						}
						else if (moves_pl[i]<min)  //the best game is the one user won with least moves
						{
							min=moves_pl[i];
							best_game=i+1;
						}
					}	
				}	
				else if (pl_win_pc==pl_games) //only defeats
				{
					max=moves_pl[0];
					worst_game=1;        //initialize values
					min=moves_pl[0];   
					best_game=1;
					for (i=0;i<pl_games;i++)
					{
						if (moves_pl[i]>max)    //the best game is the one user lost with most moves
						{
							max=moves_pl[i];
							best_game=i+1;
						}
						else if (moves_pl[i]<min)  //the worst game is the one user lost with least moves
						{
							min=moves_pl[i];
							worst_game=i+1;
						}
					}	
				}
				else if (pl_win_pl==0)  //no win, but draws and defeats
				{
					//best_game
					for (i=0;i<pl_games;i++)
					{
						if (res[i]==0)
						{
							best_game=i+1;  //each draw is user's best game - finding first one
							break;
						}
					}
					//worst_game
					for (i=0;i<pl_games;i++)
					{
						if (res[i]==2)
						{
							worst_game=i+1;  //initialize values for searching worst game
							min=moves_pc[i];
							break;
						}
					}
					for (i=0;i<pl_games;i++)
					{
						if (res[i]==2 && moves_pc[i]<min)  //the worst game is the one user lost with least pc moves
						{
							min=moves_pc[i];
							worst_game=i+1;
						}
					}
				}	
				else if (pl_win_pl==0)  //no win, but draws and defeats
				{
					//best_game
					for (i=0;i<pl_games;i++)
					{
						if (res[i]==0)
						{
							best_game=i+1;  //each draw is user's best game - finding first one
							break;
						}
					}
					//worst_game
					for (i=0;i<pl_games;i++)
					{
						if (res[i]==2)
						{
							worst_game=i+1;  //initialize values for searching worst game
							min=moves_pc[i];
							break;
						}
					}
					for (i=0;i<pl_games;i++)
					{
						if (res[i]==2 && moves_pc[i]<min)  //the worst game is the one user lost with least pc moves
						{
							min=moves_pc[i];
							worst_game=i+1;
						}
					}
				}
				else if (pl_draw==0)  //no draw, but wins and defeats
				{
					//best_game
					for (i=0;i<pl_games;i++)
					{
						if (res[i]==1)
						{
							best_game=i+1;  //initialize values for searching worst game
							min=moves_pl[i];
							break;
						}
					}
					for (i=0;i<pl_games;i++)
					{
						if (res[i]==1 && moves_pl[i]<min)  //the best game is the one user won with least moves
						{
							min=moves_pl[i];
							best_game=i+1;
						}
					}
					//worst_game
					for (i=0;i<pl_games;i++)
					{
						if (res[i]==2)
						{
							worst_game=i+1;  //initialize values for searching worst game
							min=moves_pc[i];
							break;
						}
					}
					for (i=0;i<pl_games;i++)
					{
						if (res[i]==2 && moves_pc[i]<min)  //the worst game is the one user lost with least pc moves
						{
							min=moves_pc[i];
							worst_game=i+1;
						}
					}
				}	
				else if (pl_win_pc==0)  //no defeat, but draws and wins
				{
					//best_game
					for (i=0;i<pl_games;i++)
					{
						if (res[i]==1)
						{
							best_game=i+1;  //initialize values for searching worst game
							min=moves_pl[i];
							break;
						}
					}
					for (i=0;i<pl_games;i++)
					{
						if (res[i]==1 && moves_pl[i]<min)  //the best game is the one user won with least moves
						{
							min=moves_pl[i];
							best_game=i+1;
						}
					}
					//worst_game
					for (i=0;i<pl_games;i++)
					{
						if (res[i]==0)
						{
							worst_game=i+1;  //each draw is user's worst game - finding first one
							break;
						}
					}
				}
				else      // defeats, draws and wins
				{
					//best_game
					for (i=0;i<pl_games;i++)
					{
						if (res[i]==1)
						{
							best_game=i+1;  //initialize values for searching worst game
							min=moves_pl[i];
							break;
						}
					}
					for (i=0;i<pl_games;i++)
					{
						if (res[i]==1 && moves_pl[i]<min)  //the best game is the one user won with least moves
						{
							min=moves_pl[i];
							best_game=i+1;
						}
					}
					//worst_game
					for (i=0;i<pl_games;i++)
					{
						if (res[i]==2)
						{
							worst_game=i+1;  //initialize values for searching worst game
							min=moves_pc[i];
							break;
						}
					}
					for (i=0;i<pl_games;i++)
					{
						if (res[i]==2 && moves_pc[i]<min)  //the worst game is the one user lost with least pc moves
						{
							min=moves_pc[i];
							worst_game=i+1;
						}
					}
				}
			}
			else if (anal!=27 && game_choice==2)  //in player vs player mode: best game is name1 best game - worst game==name2 best game
			{
				worst_game=best_game=0;
				if (pl_games!=1 && pl_draw!=pl_games)
				{
					//finding name1 best_game
					for (i=0;i<pl_games;++i)
					{
						if (res[i]==1)
						{
							min=moves_pl[i];
							best_game=i+1;
							break;
						}
					}
					for (i=0;i<pl_games;++i)
					{
						if (res[i]==1 && moves_pl[i]<min)
						{ 
							min=moves_pl[i]; //finding won game w/ least move for player 1
							best_game=i+1;
						}
					}
					//finding name2 best_game
					for (i=0;i<pl_games;++i)
					{
						if (res[i]==2)
						{
							min=moves_pc[i];
							worst_game=i+1;
							break;
						}
					}
					for (i=0;i<pl_games;++i)
					{	
						if (res[i]==2 && moves_pc[i]>min)
						{
				    		min=moves_pc[i]; //finding won game w/ least move for player 2
				    		worst_game=i+1;
				    	}
					}
				}
			}
			float wait_game_analysis=1;
				//------------------------------- print game(s) analysis --------------------------------------------//
				system("cls");
				printf("   _________________________________________________________________________ \n"); wait(33);
				printf("  |-------------------------------------------------------------------------|\n"); wait(33);
				printf("  |                                                                         |\n"); wait(33);
				printf("  |                UNBEATABLE TRILIZA - 'It's worth trying!'                |\n"); wait(33);
				printf("  |                                                                         |\n"); wait(33);
				printf("  |     Game(s) Analysis                                                    |\n"); wait(33);
				printf("  |                                                                         |\n"); wait(33);
				if (game_choice==1)
				{
				printf("  |     Name : %s (%c)",name,side);
				//Printing gaps so as for the right lines to appear right
				if (pl_games<=9) pl_gaps=24-name_len;
				else pl_gaps=23-name_len;
				for (i=0;i<pl_gaps;i++) printf(" ");
				}
				else
				{
				printf("  |     Player 1: %s (%c)",pl_1,pll_side);
				//Printing gaps so as for the right lines to appear right
				pl_gaps=61-strlen(pl_1);
				for (i=0;i<pl_gaps-7;i++) printf(" ");
				printf("|\n"); wait(33);
				printf("  |     Player 2: %s (%c)",pl_2,pl_pc_side);
				//Printing gaps so as for the right lines to appear right
				if (pl_games<=9) pl_gaps=21-strlen(pl_2);
				else pl_gaps=20-strlen(pl_2);
				for (i=0;i<pl_gaps;i++) printf(" ");
				}	
				if (game_choice==1) 
				{
				printf("     < Single Player Mode >      |\n",pl_games); wait(33);
				printf("  |                                                                         |\n"); wait(33);	
				printf("  |       Game #   |  Player Moves  |  Pc Moves  |  Time   |  Result        |\n"); wait(33);
				printf("  |    ------------|----------------|------------|---------|----------      |\n"); wait(33);	
				}
				else 
				{
				printf("      < Multi Player Mode >      |\n",pl_games); wait(33);
				printf("  |                                                                         |\n"); wait(33);
				printf("  |       Game #   |  Pl. 1 Moves |  Pl. 2 Moves |  Time   |  Result        |\n"); wait(33);
				printf("  |    ------------|--------------|--------------|---------|----------      |\n"); wait(33);
				}
				//printing analysis matrix
				for (i=0;i<pl_games;i++)
				{
					if (i<=8) 
					{
						if (res[i]==0) 
						{
							if (game_choice==1)	
				{printf("  |         %d      |        %d       |      %d     |  %02d:%02d  |   Draw         |\n",i+1,moves_pl[i],moves_pc[i],ming[i],secg[i]); wait(33); }
		   					else 
		   		{printf("  |         %d      |       %d      |       %d      |  %02d:%02d  |   Draw         |\n",i+1,moves_pl[i],moves_pc[i],ming[i],secg[i]); wait(33); }
						}
						else if (res[i]==1) 
						{
							if (game_choice==1) 
				{printf("  |         %d      |        %d       |      %d     |  %02d:%02d  |    Win         |\n",i+1,moves_pl[i],moves_pc[i],ming[i],secg[i]); wait(33);}
							else
				{printf("  |         %d      |       %d      |       %d      |  %02d:%02d  |   Won 1        |\n",i+1,moves_pl[i],moves_pc[i],ming[i],secg[i]); wait(33); }
						}
						else
						{
							if (game_choice==1) 
				{printf("  |         %d      |        %d       |      %d     |  %02d:%02d  |  Defeat        |\n",i+1,moves_pl[i],moves_pc[i],ming[i],secg[i]); wait(33); }
							else 
				{printf("  |         %d      |       %d      |       %d      |  %02d:%02d  |   Won 2        |\n",i+1,moves_pl[i],moves_pc[i],ming[i],secg[i]); wait(33); }
							
						}
					}
					else 
					{
						if (res[i]==0) 
						{
							if (game_choice==1)	
				{printf("  |        %d      |        %d       |      %d     |  %02d:%02d  |   Draw         |\n",i+1,moves_pl[i],moves_pc[i],ming[i],secg[i]); wait(33); }
		   					else 
		   		{printf("  |        %d      |       %d      |       %d      |  %02d:%02d  |   Draw         |\n",i+1,moves_pl[i],moves_pc[i],ming[i],secg[i]); wait(33); }
						} 
						else if (res[i]==1) 
						{
							if (game_choice==1) 
				{printf("  |        %d      |        %d       |      %d     |  %02d:%02d  |    Win         |\n",i+1,moves_pl[i],moves_pc[i],ming[i],secg[i]); wait(33); }
							else
				{printf("  |        %d      |       %d      |       %d      |  %02d:%02d  |   Won 1        |\n",i+1,moves_pl[i],moves_pc[i],ming[i],secg[i]); wait(33); }
						}
						else
						{
							if (game_choice==1) 
				{printf("  |        %d      |        %d       |      %d     |  %02d:%02d  |  Defeat        |\n",i+1,moves_pl[i],moves_pc[i],ming[i],secg[i]); wait(33); }
							else 
				{printf("  |        %d      |       %d      |       %d      |  %02d:%02d  |   Won 2        |\n",i+1,moves_pl[i],moves_pc[i],ming[i],secg[i]); wait(33); }
							
						}
					}
					if(pl_games>=2)
					{
						if (game_choice==1) 
				{printf("  |                |                |            |         |                |\n");	wait(33); }
						else 
				{printf("  |                |              |              |         |                |\n");  wait(33); }
					}
				printf("  |                                                                         |\n"); wait(33);wait(33);
				printf("  |                                          %c | %c | %c                      |\n",game_pic[i][0],game_pic[i][1],game_pic[i][2]);
				printf("  |                                         -----------                     |\n");
				printf("  |         The Game ended up like this:     %c | %c | %c                      |\n",game_pic[i][3],game_pic[i][4],game_pic[i][5]);
				printf("  |         (");
				if (game_choice==2)
				{
				int ci=0; do{printf("%c",start[i][ci]); ci++;}while (start[i][ci]!='\0');	printf(" started)");
				for (int cci=0;cci<21-ci;cci++) printf (" "); 
				} 
				else
				{
					if (pc_starts[i]==1)
					{	printf("Pc started)");
						for (int cci=0;cci<19;cci++) printf (" ");
					}
					else 
					{	printf("%s",name); printf(" started)");	
						for (int cci=0;cci<21-strlen(name);cci++) printf (" ");
					}
				}
				printf(" -----------                     |\n");
				printf("  |                                          %c | %c | %c                      |\n",game_pic[i][6],game_pic[i][7],game_pic[i][8]);
				printf("  |                                                                         |\n");
				if(pl_games>=2 && /* fromm here */ pl_games-i>1)  //fixing two games stats printing error
				{
					if (game_choice==1) printf("  |                |                |            |         |                |\n");	 
					else printf("  |                |              |              |         |                |\n");
				}
				wait(33);
				}
				printf("  |                                                                         |\n"); wait(33);
				if (game_choice==1)	printf("  |     Total "); 
				else printf("  |     Pl. 1 "); 
				printf("Winnings: %d ",pl_win_pl);
				if (game_choice==1) printf("<--");
				else printf("   ");
				if (pl_win_pl<=9) printf(" ");                                                                                  //for correct show up             
				printf("                       Total Games: %d",pl_games); if (pl_games<=9) printf(" "); printf("        |\n"); wait(33); //
				printf("  |                                                                         |\n"); wait(33);	
				if (game_choice==1)	printf("  |     Total Defeats : %d ",pl_win_pc);
				else printf("  |     Pl. 2 Winnings: %d ",pl_win_pc); 
				if (pl_win_pc<=9) printf(" ");
				printf("                Average Game Duration: %02d:%02d     |\n",(int)sum_min/pl_games,(int)sum_sec/pl_games); wait(33);
				printf("  |                                                                         |\n");	 wait(33);
				printf("  |     Total Draws   : %d   ",pl_draw);
				if (pl_draw<=9) printf(" ");
				printf("            Average User Moves/Game: %.1f       |\n",(float)sum_moves/pl_games); wait(33);
				printf("  |                                                                         |\n"); wait(33);	
				printf("  |                                                                         |\n"); wait(33);			
				if (game_choice==1)
				{printf("  |                    Your Best Game* : %d",best_game); if(best_game<=9) printf(" "); printf("                                 |\n"); wait(33);}  //for correct show-up
				else
				{printf("  |                    Pl. 1 Best Game*: %d",best_game); if(best_game<=9) printf(" "); printf("                                 |\n"); wait(33); }  //for correct show-up
				if (game_choice==1)
				{printf("  |                    Your Worst Game*: %d",worst_game); if(worst_game<=9) printf(" "); printf("                                 |\n"); wait(33);}//
				else
				{printf("  |                    Pl. 2 Best Game*: %d",worst_game); if(best_game<=9) printf(" "); printf("                                 |\n");  wait(33);}  //for correct show-up
				printf("  |                                                                         |\n"); wait(33);
				printf("  |               *If only one game played or all draws ==> 0               |\n"); 	
				printf("  |                                                                         |\n"); 					
				printf("  |                                                                         |\n"); 
				printf("  |-------------------------------------------------------------------------|\n"); 
				printf("  |_________________________________________________________________________|\n\n"); wait(33); wait(33);					
		}
	}
 	printf("                                              "); system("pause");
	delay(del); 
	exit(1000);
}

//puts pc in stand-by mode
void delay(time_t dur)
{
	time_t start,fin;
	time(&start);
	int k=dur;
	do 
	{
		time(&fin);
		if (int(dur-(fin-start))==k)
		{
			if (kbhit()) break;
			system("cls");
			printf("\n    ##############  ##     ##        ##        ####      ##  ##     ## ");
			printf("\n          ##        ##     ##       ####       #####     ##  ##   ##   ");
			printf("\n          ##        ##     ##      ##  ##      ##  ##    ##  ## ##     ");
			printf("\n          ##        #########     ########     ##   ##   ##  ###      ");
			printf("\n          ##        ##     ##    ##      ##    ##    ##  ##  ## ##     ");
			printf("\n          ##        ##     ##   ##        ##   ##     #####  ##   ##   ");
			printf("\n          ##        ##     ##  ##          ##  ##      ####  ##     ## ");
			printf("\n          ");		    
			printf("\n                      ##      ##      ###      ##      ## ");	
			printf("\n                       ##    ##     ##   ##    ##      ## ");				
			printf("\n                        ##  ##     ##     ##   ##      ## ");	
			printf("\n                         ####      ##     ##   ##      ##  ");	
			printf("\n                          ##       ##     ##   ##      ##  ");	
			printf("\n                          ##        ##   ##     ##    ##  ");	
			printf("\n                          ##          ###         ####     \n");
			puts("\n Creator: Thanasis          ");
			puts("          Charisoudis          \n");
			puts(" E.E. DEPT.          ");
			puts(" D.U.TH. GREECE          ");
			printf("\n\n\n Press any key to exit...\n (Exiting in: ");
			printf("%02d) \n\n\n\n\n\n\n\n\n\n\n\n\n\n",(int)dur-(fin-start));
			k--; //printing nums only ine time
		}
	}
	while ((fin-start)<dur);
}

//intro graphics - welcome scr w/ countdown
void intro_graph(time_t durs)
{
	time_t start,fin;
	time(&start);
	int k=durs;
	do 
	{
		time(&fin);
		if (int(durs-(fin-start))==k)
		{
			if (kbhit()) break;
			system("cls");
			puts("\n     B        L\n");
			puts("   N  E     B   E   \n");
			puts(" U     A  A      \n");
			puts("\n        T R I L I Z A  ");
			puts("\n        Creator: Thanasis          \n");
			puts("                 Charisoudis          ");
			printf("        ____");
			printf("\n       /    %c       ",92);
			printf("\n      /  _   %c       ",92);
			printf("\n     /  / %c%c%c|     ",92,92,92);
			printf("\n    /  /  _iiii_       ",92,92,92);	
			printf("\n   /  /  /      %c          o | x |  ",92);
			printf("\n   |  | -| _  _ |-     *  ---|---|---    ",92);
			printf("\n   |  || | o  o | | *        | o | x   ",92);		
			printf("\n   |  | -|   l  |-     *  ---|---|--- ",92);		
			printf("\n   |  |  | %c__/ |          x | x | o  ... ",92,92);	
			printf("\n   %c  |  %c______/ ",92,92);	
			printf("\n\n ");
			printf("\n\n\n Press any key to skip...\n (Starting in: ");
			printf("%02d) \n\n\n\n\n\n\n\n\n\n\n",(int)durs-(fin-start));
			k--; //printing nums only ine time
		}
	}
	while ((fin-start)<durs);
}

//intro graphics - welcome scr w/ countdown
void wait(int entr)
{
	bool printed;
	int i,n=100000000;
	for (int i=0;i<n;i++)
	{
		if (entr!=33 && printed==false) 
		{
			n+=100000000; //more delay in playmode
			if	(entr==3) printf("\nGrabbing the last cell..."); 
			else if (entr==5) n+=1000000000;
			else printf("\nLet me think...");
			printed=true; //print only once
		}
	}
}

//loaing fx before game(s) analysis windows
void loading_fx(void)
{
	int wait_num=50000000,law=0,step=0,numm=0,pos;
	bool pr1,pr2,pr3,pr4,pr5,pr6,pr7,pr8;
	pr1=true; pr2=pr3=pr4=pr5=pr6=pr7=pr8=false;
	for (int gaw=0;gaw<wait_num;gaw++)
	{
		if (step==gaw)
		{
			system("cls");
			printf("\n\n\n\n                    Game Analysis Window is now loading.\n\n");
			
			
			//====== clock ======// print frame by frame the clock ==> pr(i) ,i=1,...,8
			if (pr1)
			{

				printf("                                              |");
				printf("\n                            Please wait...\n");
				pr1=false;   //
				pr2=true;    // open next frame
			}
			else if (pr2) 
			{

				printf("                                              | /");
				printf("\n                            Please wait...\n");
				pr2=false;
				pr3=true;
			} 
			else if (pr3) 
			{

				printf("                                              | /");
				printf("\n                            Please wait...       --\n");
				pr3=false;
				pr4=true;
			} 
			else if (pr4) 
			{

				printf("                                              | /");
				printf("\n                            Please wait...       --\n");
				printf("                                                %c",92);

				pr4=false;
				pr5=true;
			}	
			else if (pr5) 
			{

				printf("                                              | /");
				printf("\n                            Please wait...       --\n");
				printf("                                              | %c",92);
				pr5=false;
				pr6=true;
			}
			else if (pr6) 
			{
				printf("                                              | /");
				printf("\n                            Please wait...       --\n");
				printf("                                            / | %c    ",92);
				pr6=false;
				pr7=true;
			}
			else if (pr7) 
			{
				printf("                                              | /");
				printf("\n                            Please wait... --    --\n");
				printf("                                            / | %c    ",92);
				pr7=false;
				pr8=true;
			}
			else if (pr8) 
			{
				printf("                                            %c | /",92);
				printf("\n                            Please wait... --    --\n");
				printf("                                            / | %c    ",92);
				pr8=false;
				pr1=true;
			}
			
		//======== loading fx =========//
			printf("\n\n\n\n              ");
			if (numm<50)
			{
				for (int faw=0;faw<law;faw++) printf(">"); //printing percentage fx
				pos=law-1;
			}
			else
			{
				for (int faw=0;faw<pos;faw++) printf(">");
				printf(" o ");	
				for (int faw=0;faw<law-pos-2;faw++) printf("<");	
			}
			printf("\n              |");    //setting bar limit - left
			for (int faw=0;faw<law-2;faw++) printf(" "); printf("%d",numm);  //percentage no
			law++;
			//setting bar limit - right
			if (numm!=100) 
			{
				for (int faw=0;faw<(49-numm/2);faw++) printf(" "); 
				printf("|");
			}
			numm+=2;
			printf("\n              0"); for(int faw=0;faw<23;faw++) printf(" "); printf("50"); for(int faw=0;faw<23;faw++) printf(" "); printf("100\n\n\n\n");	//limits no.
		
			step+=990000;	
			wait(33);
		}			
	}	
}

//Finds best move for pc. (Tactics) 
//Returns number of the c_board
int best_move(int (numb)[3][3]) //OK!
{
	int num,i,a,j,p_tr1,p_tr2,s_r[3],s_c[3],p_r[3],p_c[3],s_tr1,s_tr2,pos,row=-1,pre_ret;

	//Find row & columns & diagonals sums &      
	s_tr1=0; 
	p_tr1=0;		//Initialize diagonals first
	s_tr2=0; 
	p_tr2=0;
	for (i=0;i<3;i++)
	{
		s_r[i]=0;  
		p_r[i]=0;  
		s_c[i]=0;
		p_c[i]=0; 
		//diagonals
		s_tr1=s_tr1+numb[i][i];
		if (numb[i][i]==0) p_tr1++;
		
		s_tr2=s_tr2+numb[i][2-i];
		if (numb[i][2-i]==0) p_tr2++;	           
		//rows & columns	
		for (j=0;j<3;j++)
		{
			s_r[i]=s_r[i]+numb[i][j];
			if (numb[i][j]==0) p_r[i]++;  //finding sum and pl for each line
			
			s_c[i]=s_c[i]+numb[j][i];
			if (numb[j][i]==0) p_c[i]++;  //finding sum and pl for each column
		}
	}
	
	//for debugging :	printf("\nnumb : \n %d  |  %d  |  %d \n %d  |  %d  |  %d \n %d  |  %d  |  %d \n",numb[0][0],numb[0][1],numb[0][2],numb[1][0],numb[1][1],numb[1][2],numb[2][0],numb[2][1],numb[2][2]);
	//for debugging : 	printf("\nsums: 1st column: %d (%d z) 2st column: %d (%d z) 3rd column: %d (%d z)\n1st row: %d (%d z)\n2nd row: %d (%d z)     trace: %d (%d z)   anti: %d (%d z)\n3rd row: %d(%d z)",s_c[0],p_c[0],s_c[1],p_c[1],s_c[2],p_c[2],s_r[0],p_r[0],s_r[1],p_r[1],s_tr1,p_tr1,s_tr2,p_tr2,s_r[2],p_r[2]);
	//for debugging :   system("pause");
	
	//casing trick - MPAKALIKO BUT WORKS =====================================> ADD EVERY OTHER CASE HERE 
	if (numb[0][0]==0 && numb[0][1]==-1 && numb[0][2]==1 && numb[1][0]==1 && numb[1][1]==-1 && numb[1][2]==0 && numb[2][0]==0 && numb[2][1]==1 && numb[2][2]==0)
	{
		return(9);
	}
	else if (numb[0][0]==1 && numb[0][1]==-1 && numb[0][2]==0 && numb[1][0]==0 && numb[1][1]==-1 && numb[1][2]==1 && numb[2][0]==0 && numb[2][1]==1 && numb[0][2]==0) 
	{
		return(7);
	}
	else if (numb[0][0]==-1 && numb[0][1]==0 && numb[0][2]==1 && numb[1][0]==1 && numb[1][1]==1 && numb[1][2]==-1 && numb[2][0]==-1 && numb[2][1]==0 && numb[0][2]==1)  //Bug Fix
	{
		return(2);
	}
	//pc winning mode
	else if (s_r[0]==-2 && p_r[0]==1) //first row check for win
	{
		for (a=0;a<3;a++)
		{
			if (numb[0][a]==0)
			pos=a;
		}
		pre_ret=pos+1;
		return (pre_ret);
	}
	else if (s_r[1]==-2 && p_r[1]==1) //2nd row check for win
	{
		for (a=0;a<3;a++)
		{
			if (numb[1][a]==0)
			pos=a;
		}
		pre_ret=pos+4;
		return (pre_ret);
	}
	else if (s_r[2]==-2 && p_r[2]==1) //3rd row check for win
	{
		for (a=0;a<3;a++)
		{
			if (numb[2][a]==0)
			pos=a;
		}
		pre_ret=pos+7;
		return (pre_ret);
	}
	else if (s_c[0]==-2 && p_c[0]==1) //first column check for win
	{
		for (a=0;a<3;a++)
		{
			if (numb[a][0]==0)
			pos=a;
		}
		pre_ret=3*pos+1;
		return (pre_ret);
	}
	else if (s_c[1]==-2 && p_c[1]==1) //2nd column check for win
	{
		for (a=0;a<3;a++)
		{
			if (numb[a][1]==0)
			pos=a;
		}
		pre_ret=3*pos+2;
		return (pre_ret);
	} 
	else if (s_c[2]==-2 && p_c[2]==1) //3rd column check for win
	{
		for (a=0;a<3;a++)
		{
			if (numb[a][2]==0)
			pos=a;
		}
		pre_ret=3*pos+3;
		return (pre_ret);
	}
	else if (s_tr1==-2 && p_tr1==1) //trace check for win
	{
		for (a=0;a<3;a++)
		{
			if (numb[a][a]==0)
			pos=a;
		}
		pre_ret=4*pos+1;
		return (pre_ret);
	}
	else if (s_tr2==-2 && p_tr2==1) //anti-trace check for win
	{
		for (a=0;a<3;a++)
		{
			if (numb[a][2-a]==0)
			pos=a;
		}
		pre_ret=2*pos+3;
		return (pre_ret);
	}
	//user preventing mode
	else if (s_r[0]==2 && p_r[0]==1) //first row check for win
	{
		for (a=0;a<3;a++)
		{
			if (numb[0][a]==0)
			pos=a;
		}
		pre_ret=pos+1;
		return (pre_ret);
	}
	else if (s_r[1]==2 && p_r[1]==1) //2nd row check for win
	{
		for (a=0;a<3;a++)
		{
			if (numb[1][a]==0)
			pos=a;
		}
		pre_ret=pos+4;
		return (pre_ret);
	}
	else if (s_r[2]==2 && p_r[2]==1) //3rd row check for win
	{
		for (a=0;a<3;a++)
		{
			if (numb[2][a]==0)
			pos=a;
		}
		pre_ret=pos+7;
		return (pre_ret);
	}
	else if (s_c[0]==2 && p_c[0]==1) //first column check for win
	{
		for (a=0;a<3;a++)
		{
			if (numb[a][0]==0)
			pos=a;
		}
		pre_ret=3*pos+1;
		return (pre_ret);
	}
	else if (s_c[1]==2 && p_c[1]==1) //2nd column check for win
	{
		for (a=0;a<3;a++)
		{
			if (numb[a][1]==0)
			pos=a;
		}
		pre_ret=3*pos+2;
		return (pre_ret);
	} 
	else if (s_c[2]==2 && p_c[2]==1) //3rd column check for win
	{
		for (a=0;a<3;a++)
		{
			if (numb[a][2]==0)
			pos=a;
		}
		pre_ret=3*pos+3;
		return (pre_ret);
	}
	else if (s_tr1==2 && p_tr1==1) //trace check for win
	{
		for (a=0;a<3;a++)
		{
			if (numb[a][a]==0)
			pos=a;
		}
		pre_ret=4*pos+1;
		return (pre_ret);
	}
	else if (s_tr2==2 && p_tr2==1) //anti-trace check for win
	{
		for (a=0;a<3;a++)
		{
			if (numb[a][2-a]==0)
			pos=a;
		}
		pre_ret=2*pos+3;
		return (pre_ret);
	}
	//deleting trick_no.3 mode (first move only)
	else if (s_tr1==0 && s_tr2==0 && p_tr1>=2 && p_tr2>=2) //check by line 
	{
		if (s_r[0]==0 && numb[1][0]==0)	return (9);
		else return (1);
	}
	//getting center
	else if (numb[1][1]==0) return (5);
	//finding a trick mode
	else if (s_tr1==1 && p_tr1==0 && numb[1][1]==-1) //on trace
	{
		if (numb[1][0]==0) return (4);
		else if (numb[1][2]==0) return (6); 
	}
	else if (s_tr2==1 && p_tr2==0 && numb[1][1]==-1) //on anti-trace
	{
		if (numb[1][0]==0) return (4);
		else if (numb[1][2]==0) return (6); 
	}
	//trick-prevention mode
	else if (s_tr1==1 && p_tr1==0 && numb[1][1]==1) //on trace
	{
		if (numb[2][0]==0) return (7);
		else if (numb[0][2]==0) return (3); 
	}
	else if (s_tr2==1 && p_tr2==0 && numb[1][1]==1) //on anti-trace
	{
		if (numb[0][0]==0) return (1);
		else if (numb[2][2]==0) return (9); 
	}
	//============================================================================================================ attack ==================================================================================================//
	else if (s_r[0]==-1 && p_r[0]==2) //first row check for solo mine
	{
		for (a=0;a<2;a++)
		{
			if (numb[0][a]==0)
			pos=a;
		}
		pre_ret=pos+1;
		return (pre_ret);
	}
	else if (s_r[1]==-1 && p_r[1]==2) //2nd row check for solo mine
	{
		for (a=0;a<2;a++)
		{
			if (numb[1][a]==0)
			pos=a;
		}
		pre_ret=pos+4;
		return (pre_ret);
	}
	else if (s_r[2]==-1 && p_r[2]==2) //3rd row check for solo mine
	{
		for (a=0;a<2;a++)
		{
			if (numb[2][a]==0)
			pos=a;
		}
		pre_ret=pos+7;
		return (pre_ret);
	}
	else if (s_c[0]==-1 && p_c[0]==2) //first column check for solo mine
	{
		for (a=0;a<2;a++)  // only the first zero needed in all loops a from 0 to 1 (not to 2 --> useless loop)
		{
			if (numb[a][0]==0)
			pos=a;
		}
		pre_ret=3*pos+1;
		return (pre_ret);
	}
	else if (s_c[1]==-1 && p_c[1]==2) //2nd column check for solo mine
	{
		for (a=0;a<2;a++)
		{
			if (numb[a][1]==0)
			pos=a;
		}
		pre_ret=3*pos+2;
		return (pre_ret);
	} 
	else if (s_c[2]==-1 && p_c[2]==2) //3rd column check for solo mine
	{
		for (a=0;a<2;a++)
		{
			if (numb[a][2]==0)
			pos=a;
		}
		pre_ret=3*pos+3;
		return (pre_ret);
	}
	else if (s_tr1==-1 && p_tr1==2) //trace check for solo mine
	{
		for (a=0;a<2;a++)
		{
			if (numb[a][a]==0)
			pos=a;
		}
		pre_ret=4*pos+1;
		return (pre_ret);
	}
	else if (s_tr2==-1 && p_tr2==2) //anti-trace check for solo mine
	{
		for (a=0;a<2;a++)
		{
			if (numb[a][2-a]==0)
			pos=a;
		}
		pre_ret=2*pos+3;
		return (pre_ret);
	}
	//============================================================================================================== end of attack =============================================================================================//
	//Opposite (in trace) corners -  Block User
	else if ( numb[0][0]==1 && numb[2][2]==0 )  return (9);      //Down Right corner - Block User
	else if ( numb[2][2]==1 && numb[0][0]==0 )  return (1);      //Up Left corner - Block User
	else if ( numb[2][0]==1 && numb[0][2]==0 )  return (3);	     //Up right corner -  Block User
	else if ( numb[0][2]==1  && numb[2][0]==0 ) return (7);	     //Down left corner -  Block User
	//Take an empty cell
	else 
	{
		for (i=0;i<3;i++)
		{	
			for (a=0;a<3;a++)
			{
				if (numb[i][a]==0)
				pos=a;
				row=i;
				break;
			}
			if (row!=-1)
			{
				pre_ret=(3*row)+pos+1;
				break;
			}
		}
		return (pre_ret);
	}
}

//Checks if there's a dursr (after five moves).
//Returns 1-Player wins, 2-Pc Wins, 0-Noone wins ---SO-FAR--->(Draw)
int IsWinner(int (*numb)[3]) //OK!
{
	int i,j,s_r[3],s_c[3],s_tr1=0,s_tr2=0;
	bool flag;
	
	//Find sums of rows, columns & diagonals
	for (i=0;i<3;i++)
	{
		s_r[i]=0;  
		s_c[i]=0; 
		s_tr1=s_tr1+numb[i][i];
		s_tr2=s_tr2+numb[i][2-i];
		for (j=0;j<3;j++)
		{
			s_r[i]=s_r[i]+numb[i][j];
			s_c[i]=s_c[i]+numb[j][i];		
		}
	}
	
	flag=false;
	//check if user wins first (because pc had the last move)
	for (i=0;i<3;i++)
	{
		if (s_r[i]==3 || s_c[i]==3 || s_tr1==3 || s_tr2==3)
		{
			return (1);
			flag=true;
			break;
		}	
	}
	//check if pc wins
	if (flag==false)
	{
		for (i=0;i<3;i++)
		{
			if (s_r[i]==-3 || s_c[i]==-3 || s_tr1==-3 || s_tr2==-3)
			{
				return (2);
				flag=true;
				break;
			}	
		}
	}
	//if none's a winner return 0
	if (flag==false) return (0);		
}

//rands chaneges names in order to fake random start in multiplayer mode only
//if swap is true it returns 1 else default
int rand_multi(char *name1,char *name2,char *side,char *pc_side)
{
	srand(time(NULL));
	int n=rand()%100+1,i,l1=strlen(name1),l2=strlen(name2);
	char temp[27]={' '},temp1;
	if (n%2==0);
	{
		//swap sides
		temp1=*side;
		*side=*pc_side;
		*pc_side=temp1;
		//swap names
		for (i=0;i<l1;++i) temp[i]=name1[i]; //save name 1
		for (i=0;i<27;++i) name1[i]=32; //delete array to get array 2
		for (i=0;i<l2;++i) name1[i]=name2[i]; //name1=name2
		name1[i]='\0'; //add terminating char at name's end
		for (i=0;i<27;++i) name2[i]=32; //delete array to get array 2
		for (i=0;i<l1;++i) name2[i]=temp[i]; //name1=name2
		name2[i]='\0';
		return (1);
	}
	// by default return (0);
}//+++++ my monkeys +++++// 

