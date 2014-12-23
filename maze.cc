//============================================================================
// Name        : maze.cc
// Author      : Chris Diggs
// Date	       : 11/19/2014
// Description : This code will solve a given maze and give the path (r = right, l = left, u = up, d = down)
//
// Input       : 
// n m 
// y y y y y x y t
// y x x y y y x y
// y x x y x y x y
// s y y y y y x y
// y y y y x y y y
// 
// where n is the number of rows
//	 m is the number of columns
//	 x represents a wall
//	 y represents a valid path
//	 s is the starting point
//	 t is the finishing point
//       o is the resulting path
//
// Sample Input: 
// 5 8
// y y y y y x y t
// y x x y y y x y
// y x x y x y x y
// s y y y y y x y
// y y y y x y y y
//
//Sample Output:
//
// y  y  y  y  y  x  y  t 
// y  x  x  y  y  y  x  o 
// y  x  x  y  x  y  x  o 
// s  o  o  o  o  o  x  o 
// y  y  y  y  x  o  o  o 
//
// The path is : rrrrrdrruuu
//
// Compile     : make all  
// How-to-run  : ./maze < maze.dat
//============================================================================

#include <iostream>
#include "backtrack.h"
#include <fstream>
#include <string>
#include <cstdlib>
#include <vector>
#include <queue>
#include<list>
#include<string.h>
#include<algorithm>
#include<stdio.h>
using namespace std;


typedef struct{
  int x,y;
} point;

typedef struct{
  vector< vector<char> > Board;
  vector<char> path; //record the path taken ('r'=right, 'l'=left, 'u'=up, 'd'=down)
  vector<point *> move;  //record all the moves made use for backtracking!
} board;


  // Print puzzle in current state
void printPuzzle(board *);

bool verifyValue(int x_cord, int y_cord);  //aux function to test if the value on added to (x_cord,y_cord) yields no conflict at the current state

int rows, cols;


int main(){
   cin>>rows;
   cin>>cols;

  board *thisboard=new board;
  thisboard->Board.resize(cols);
  for(int i=0;i<cols;i++){
    thisboard->Board[i].resize(rows);
  }
  char temp;

  //Read data.  assume the data set is right, i.e. no checking
  for(int i=0;i<rows;i++){
    for(int j=0;j<cols;j++){

     cin>>temp;
     if(temp=='s'){
       point * StartP = new point;
       StartP->x=j;
       StartP->y=i;
      thisboard->move.push_back(StartP);
     }
     (thisboard->Board)[j][i]=temp;

    }
  }
  // Print the board before solving.
  //printPuzzle(thisboard);

  cout <<endl;
  BT puzzle(9,false, (void*)thisboard);
  puzzle.backtrack();
  if (puzzle.get_num_sols()==0)
    {
      cout<<"\nNo solutions found!\n";
    }
  else{
	cout<<"\nThe path is : ";
	for(int i=0;i<thisboard->path.size();i++){
		cout<<thisboard->path[i];
		
	}
  }
  cout << endl;
  return 0;
} // main


void printPuzzle(board * theboard) {
  for (int y=0; y<rows; y++) {
    for (int x=0; x<cols; x++) {
	cout << " " << theboard->Board[x][y] << " ";
    }
    cout << endl;
  }
} 


//problem specific functions
bool BT::is_a_solution()
{
  board *temp=(board *)(input);
  point * tempP=(temp->move).back();  //the current emptyspace
  int x=tempP->x, y=tempP->y;  
  //the following should be included for any problem
  if (x-1>=0&&temp->Board[x-1][y]=='t')
    {
      finished=true;
      (num_sol)++;
      return true;
    }
  else if (x+1<cols&&temp->Board[x+1][y]=='t')
    {
      finished=true;
      (num_sol)++;
      return true;
    }
  else if (y-1>=0&&temp->Board[x][y-1]=='t')
    {
      finished=true;
      (num_sol)++;
      return true;
    }
   else if (y+1<rows&&temp->Board[x][y+1]=='t')
    {
      finished=true;
      (num_sol)++;
      return true;
    }
  else{
    return false;
  }
}

void BT::process_solution()
{
   board *temp=(board *)(input);
  int x, y;
  for(int i=1; i<temp->move.size();i++){
	x=temp->move[i]->x;
	y=temp->move[i]->y;
	temp->Board[x][y]='o';
  }
 for(int i=0;i<rows;i++){
    for(int j=0;j<cols;j++){

     if((temp->Board)[j][i]=='.')
        (temp->Board)[j][i]='y';
    }
  }
  (temp->Board)[((temp->move).front())->x][((temp->move).front())->y]='s';
  printPuzzle((board *)input);
}

void BT::make_move()  //update board
{
 
  int k=a.size()-1;
  board *temp=(board *)(input);
  point * tempP=(temp->move).back(); 
  int x=tempP->x, y=tempP->y;

  if (a[k]==0)  //0 = west
    {
        point * nextP=new point;
	nextP->x=x-1;
	nextP->y=y;
        temp->move.push_back(nextP);
	(temp->Board)[x-1][y]='.'; 
	temp->path.push_back('l');
    }
  else if (a[k]==1) //1 = east
    {
        point * nextP=new point;
	nextP->x=x+1;
	nextP->y=y;
        temp->move.push_back(nextP);
	(temp->Board)[x+1][y]='.'; 
        temp->path.push_back('r');
    }
  else if (a[k]==2) //2 = north
    {
        point * nextP=new point;
	nextP->x=x;
	nextP->y=y-1;
        temp->move.push_back(nextP);
	(temp->Board)[x][y-1]='.'; 
 	temp->path.push_back('u');
    }
   else if (a[k]==3) //3 =  south
    {
        point * nextP=new point;
	nextP->x=x;
	nextP->y=y+1;
        temp->move.push_back(nextP);
	(temp->Board)[x][y+1]='.'; 
	 temp->path.push_back('d');	
    }
  return;
}

void BT::unmake_move()
{
  board * temp=(board *)(input);
  (temp->move).pop_back();
  (temp->path).pop_back();	
   return;
}

void BT::construct_candidates(std::vector<int>& c)
{
  int t,next, i,j;
  board *temp=(board *)(input);
  point * tempP=(temp->move).back();  
  int x=tempP->x, y=tempP->y; 

  if (x-1>=0&&temp->Board[x-1][y]=='y')  //0 = west
    {
       c.push_back(0);
    }
  if (x+1<cols&&temp->Board[x+1][y]=='y') //1 = east
    {
       c.push_back(1);
    }
  if (y-1>=0&&temp->Board[x][y-1]=='y') //2 = north
    {
      c.push_back(2);
    }
  if (y+1<rows&&temp->Board[x][y+1]=='y') //3 =  south
    {
      c.push_back(3);
    }
}

