#include <iostream>
#include <vector>
using namespace std;


struct s1
{
  int velocity;
  //int configuration;
};

typedef struct s1 state;

struct s2
{
  int x;
  int y;
};

typedef struct s2 position;

typedef std::vector<position> pos_vec_t;

class Primitive 
{
  private:
    state q_i;
    state q_f;
    position pos_f;
    string cost;
    pos_vec_t swath;    
    position pos_min;
    position pos_max;

  public:
    Primitive(state , state , position , string , pos_vec_t , position , position );
    state get_q_i();
    state get_q_f();
    position get_pos_f();
    string get_cost();
    pos_vec_t get_swath();
    position get_pos_min();
    position get_pos_max();
    ~Primitive();  
};
