#include "timer.h"
#include <thread>
using namespace std::chrono_literals;
int
main () {

  cdf::timer::timer_t t{};
  
  t.tic ("prova");
  t.tic ("prova2");
    
  t.tic ("prova");
  t.toc ("prova");
  
  t.tic ("prova");
  t.toc ("prova");
  
  t.tic ("prova2");
  t.toc ("prova2");

  t.tic ("prova");
  t.toc ("prova");

  t.print_report ();
  
  return 0;
}
