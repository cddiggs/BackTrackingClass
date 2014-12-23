#ifndef BACKTRACK_H
#define BACKTRACK_H
#include<vector>

class BT
{
 public:
  BT(int NMaxC, bool Stop_When_Found, void * In, int Nsols=0){
    num_sol=Nsols; maxcandidates=NMaxC; finished=Stop_When_Found; input=In;};
  //main backtracking code
  void backtrack();
  int get_num_sols(){ return num_sol;};

  //problem specific codes
  //insert a candidate to a and do some updates
  virtual void make_move(); 
  //reverse the make_move's effect 
  virtual void unmake_move();  
  //build all possible candidates and store in c based on the current state 
  virtual void construct_candidates(std::vector<int> &c); 
  //test if a sol is found and update the num_sol if needed 
  virtual bool is_a_solution();  
  //when a sol is found, process .. such as print it nicely
  virtual void process_solution(); 

 private:
  //problem specific data ...such as how to determine if a sol is found..
  void * input; 
  //store the partial solution...a.size() is the next a to fill
  std::vector<int> a;  
   //most of the time, it is a dummy.  But who knows..
  int maxcandidates; 
  //true: stop once a sol is found, otherwise find all
  bool finished; 
  //count the number of sols
  int num_sol;  
};


#endif
