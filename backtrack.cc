#include "backtrack.h"
#include<iostream>
using namespace std;

void BT::backtrack()
{
  vector<int> c;
  int i;
  if (is_a_solution()){
    process_solution();
  }
  else{
    construct_candidates(c);
    for (i=0; i<c.size(); i++) {
      a.push_back(c[i]);
      make_move();//assuming and configuring the system so it think c[i] is part of a sol
      backtrack();  //assuming c[i] is part of a sol, what is next?
      if (finished){  //should we terminate earlier
	return;
      }
      //well...eithe c[i] is not part of a sol or we want more.  Let's reverse
      //what make_move has done
      unmake_move();
      //remove c[i] from a
      a.pop_back();
    }
  }
  return ;
}
