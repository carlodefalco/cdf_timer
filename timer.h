#ifndef HAVE_TIMER_H
#  define HAVE_TIMER_H

#include <chrono>
#include <iostream>
#include <map>
#include <string>

namespace cdf::timer {

  class timer_t {
  private:

    using clock = std::chrono::high_resolution_clock;
    using timepoint = std::chrono::time_point<clock>;
    using duration = std::chrono::duration<double>;

    static timepoint epoch;
    duration current = clock::now () - clock::now ();
    static std::map<std::string, std::map<std::string, duration>> db;
    static std::map<std::string, unsigned long long> counts;
    
  public:
    
    timer_t () { epoch = clock::now (); };
    ~timer_t () = default;
    timer_t (const timer_t &) = delete;
    timer_t (timer_t &&) = delete;
    
    void tic (const std::string & s);    
    void toc (const std::string & s);
    
    void print_report ();
  };
  
}

#endif
