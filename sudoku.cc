//============================================================================
// Name        : sudoku.cc
// Author      : Dr. Enoch Lee - Auburn University Montgomery
// Compile     : make all
// Description : Soduku solver by individual squares
//
// Sample Input:
//
// 1 0 0 0 0 0 0 0 0 
// 0 0 5 4 0 6 1 0 0 
// 0 8 0 0 0 0 0 9 0 
// 0 0 4 0 1 0 5 0 0 
// 0 7 0 0 9 0 0 2 0 
// 0 0 6 0 8 0 3 0 0 
// 0 2 0 1 0 0 0 7 0 
// 0 0 0 5 0 3 6 0 0 
// 0 0 0 0 0 0 0 0 0 
//
//Sample Output:
//
// Solution # 1 : 
//
// -------------------------------
// | 1  4  2 | 8  3  9 | 7  5  6 |
// | 9  3  5 | 4  7  6 | 1  8  2 |
// | 6  8  7 | 2  5  1 | 4  9  3 |
// -------------------------------
// | 8  9  4 | 3  1  2 | 5  6  7 |
// | 3  7  1 | 6  9  5 | 8  2  4 |
// | 2  5  6 | 7  8  4 | 3  1  9 |
// -------------------------------
// | 4  2  3 | 1  6  8 | 9  7  5 |
// | 7  1  9 | 5  2  3 | 6  4  8 |
// | 5  6  8 | 9  4  7 | 2  3  1 |
// -------------------------------
//
// How-To-RUn  : ./sudoku 
// Enter the puzzle file name: evil2.txt
//
// Check out BackTracking Class with Template for a Sudoku solution by row 
// (rather than by each individual chair)
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
  int Board[9][9];
  int freecount;  //how many open squares remain?
  list<point *> emptyspaces;//the empty spaces remain
  vector<point *> move;  //record all the moves made use for backtracking!
} board;


void InitPuzzle(board *);
  // Print puzzle in current state
void printPuzzle(board *);

bool verifyValue(int x_cord, int y_cord);  //aux function to test if the value on added to (x_cord,y_cord) yields no conflict at the current state


int main(){

  //Initpuzzle();
  board *thisboard=new board;
  InitPuzzle(thisboard);
  string fname;
  ifstream infile;
  int temp;
  cout<<"\nEnter the puzzle file name :";
  cin>>fname;
  infile.open(fname.c_str());

  if (!infile){
    cout<<"\nCannot open the file!";
    exit(1);
  }
  //Read data.  assume the data set is right, i.e. no checking
  for(int i=0;i<9;i++){
    for(int j=0;j<9;j++){
      infile>>temp;
      if (temp!=0){
	(thisboard->Board)[j][i]=temp;
	thisboard->freecount=thisboard->freecount-1;
      }
      else{
	point *tempP=new point;
	tempP->x=j;
	tempP->y=i;
	thisboard->emptyspaces.push_back(tempP);
      }
    }
  }
  infile.close();
  // Print the board before solving.
  printPuzzle(thisboard);

  cout <<endl;
  BT puzzle(9,false, (void*)thisboard);
  puzzle.backtrack();
  if (puzzle.get_num_sols()==0)
    {
      cout<<"\nNo solutions found!\n";
    }
  cout << endl;
  return 0;
} // main


void InitPuzzle(board * theboard) {
  for (int y=0; y<9; y++) {
    for (int x=0; x<9; x++) {
      theboard->Board[x][y] = 0;
    }
  }
  theboard->freecount=81;
} //InitPuzzle

void printPuzzle(board * theboard) {
  for (int y=0; y<9; y++) {
    if (y % 3== 0) {
      cout << "-------------------------------" << endl;
    }
    for (int x=0; x<9; x++) {
      if (x % 3 == 0) {
	cout << "|";
      }
      if (theboard->Board[x][y] >0&&theboard->Board[x][y] <10) {
	cout << " " << theboard->Board[x][y] << " ";
      } else {
	cout << " . ";
      }
    }
    cout << "|" << endl;
  }
  cout << "-------------------------------" << endl;
} // printPuzzle


//problem specific functions
bool BT::is_a_solution()
{
  board * temp=(board *)(input);
  bool find=(temp->freecount==0);
  //the following should be included for any problem
  if (find)
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
  board * temp=(board *)(input);
  cout<<"\nSolution # "<<num_sol<<" : \n";
  printPuzzle((board *)input);
}

void BT::make_move()  //update board
{
  int k=a.size()-1;
  board *temp=(board *)(input);
  point * tempP=(temp->emptyspaces).front();  //the current emptyspace
  (temp->emptyspaces).pop_front();
  temp->freecount=temp->freecount - 1;  //update the freecount
  int x=tempP->x, y=tempP->y;
  (temp->move).push_back(tempP);  //record the move.  This is needed for bcaktracking
  (temp->Board)[x][y]=a[k];   //copy a candidate to the board
  return;
}

void BT::unmake_move()
{
  int k=a.size()-1;
  board * temp=(board *)(input);
  point * tempP=(temp->move).back();
  (temp->move).pop_back();
  temp->freecount=temp->freecount + 1;
  int x=tempP->x, y=tempP->y;
  (temp->emptyspaces).push_front(tempP);
  (temp->Board)[x][y]=0;
   return;
}

void BT::construct_candidates(std::vector<int>& c)
{
  int t,next, i,j;
  board *temp=(board *)(input);
  int k=a.size();
  point * tempP=(temp->emptyspaces).front();  //the current emptyspace
  int x=tempP->x, y=tempP->y;  //current space
  //there are 9 cols, 9 rows, and 9 sub-squares
  //the one consiered is on row y row, x col, and (3(x/3),3(y/4)) -subsquare at the relative position of (x%3,y%3)
  int used[10];



  fill_n(used,10,0);
  for(int i=0;i<9;i++){   //col
    if (temp->Board[i][y]!=0){
      used[temp->Board[i][y]]=1;
    }
  }
  for(int i=0;i<9;i++){  //row
    if (temp->Board[x][i]!=0){
      used[temp->Board[x][i]]=1;
    }
  }
  for(int i=0;i<3;i++){  //subgrid
    for(int j=0;j<3;j++){
      if (temp->Board[3*(x/3)+i][3*(y/3)+j]!=0){
	used[temp->Board[3*(x/3)+i][3*(y/3)+j]]=1;
      }
    }
  }
  for(int i=1;i<=9;i++){
    if (used[i]==0){
      c.push_back(i);
    }
  }
}
