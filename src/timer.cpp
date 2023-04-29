#include "timer.h"

namespace cdf::timer {

  timer_t::timepoint timer_t::epoch = timer_t::clock::now ();
  std::map<std::string, std::map<std::string, timer_t::duration>> timer_t::db{};
  std::map<std::string, unsigned long long> timer_t::counts{};
  
  void 
  timer_t::tic (const std::string & s) {
    current = clock::now () - epoch;
    db[s]["current"] = current;
  };
    
  void
  timer_t::toc (const std::string & s) {
    current = clock::now () - epoch;
    db[s]["delta"] = current - db[s]["current"];
    db[s]["current"] = current;
    db[s]["total"] += db[s]["delta"];
    counts[s] ++;
    
    double  dus = (std::chrono::duration_cast<std::chrono::microseconds> (db[s]["delta"])).count () / 1.e6;
    double  us = (std::chrono::duration_cast<std::chrono::microseconds> (db[s]["total"])).count () / 1.e6;
    std::cout << "[" << s << "#" << counts[s] << "] : Elapsed time " << dus << "s";
    std::cout << " (total " << us << "s)" << std::endl;
  };
  
  void
  timer_t::print_report () {

    double total{0.0};
    for (auto const & idb : db) {
      total += (std::chrono::duration_cast<std::chrono::microseconds> (idb.second.at ("total"))).count () / 1.e6;
    }
    std::cout << "Total measured wall.clock time " << total << "s" << std::endl;

    for (auto const & idb : db) {
      double secs = (std::chrono::duration_cast<std::chrono::microseconds> (idb.second.at ("total"))).count () / 1.e6;
      std::cout << "[" << idb.first << "] : "
		<< "#hits " << counts[idb.first] << ", "
		<< secs
		<< "s (" << secs / total * 100.0
		<< "%)" << std::endl;
    }
  };
  
}
