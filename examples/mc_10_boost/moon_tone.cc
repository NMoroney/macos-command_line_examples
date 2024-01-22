// © 2024 : github.com/NMoroney
// MIT License 
//

#include <fstream>
#include <iostream>

#include "boost/date_time/local_time/local_time.hpp"

#include "MoonPhase.h"    // https://github.com/signetica/MoonPhase


namespace n8m {

  using PosixTime = boost::posix_time::ptime;
  using Date      = boost::gregorian::date;
  using Calendar  = boost::gregorian::gregorian_calendar;
  using DayItr    = boost::gregorian::day_iterator;


  int compute_moon_tone(const PosixTime& posix_time, 
                        const PosixTime& time_t_epoch) {

    auto duration { posix_time - time_t_epoch };
    auto delta_seconds { duration.total_seconds() };

    MoonPhase moon_phase;
    moon_phase.calculate((time_t)delta_seconds);

    return (int)(255.0 * moon_phase.fraction);
  }


  void moon_tone_one() {
    using std::cout;
    cout << "moon tone one :\n";

    PosixTime time_t_epoch(Date { 1970 , 1, 1 }),
              posix_time(Date { 2024, 1, 25 });

    auto tone = compute_moon_tone( posix_time, time_t_epoch);

    cout << "tone : " << tone << "\n";
 
    cout << "\nboost version : " 
         << BOOST_VERSION / 100000 << "."
         << BOOST_VERSION / 100 % 100 << "."
         << BOOST_VERSION % 100 << "\n\n";
  }

  int end_of_month_day_number(const int year, const int month) {
    return Calendar::end_of_month_day(year, month);
  }
   
  void moon_tone_two() {
    using std::cout;
    cout << "moon tone two :\n";

    PosixTime time_t_epoch(Date { 1970 , 1, 1 });

    int year { 2024 };
    std::vector<std::string> abr { "", "Jan", "Feb", "Mar", "Apr", "May", "Jun",
        "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };

    std::ofstream ofs("temp.html");
    ofs << "<html>\n<head>\n"
        << "<style type=\"text/css\"> body { font-family: Helvetica, Arial, Sans-Serif; } </style>\n"
        << "</hesd><br>" << year << " : moon tone <br>\n<table>\n";

    for (int month = 1; month <= 12; ++month) {
      int eom_day = end_of_month_day_number(year, month);

      ofs << "  <tr>\n"
          << "    <td>" << abr[month] << "</td>\n";
      DayItr itr(Date { year, month, 1 });
      auto eom_date( Date{year, month, eom_day} );
      while (itr <= eom_date) {
        int day { itr->day() };
        PosixTime posix_time(Date { year, month, day });
        auto tone = compute_moon_tone( posix_time, time_t_epoch);
        auto s { std::to_string(tone) };
        std::string rgb { "rgb(" + s + "," + s + "," + s + ")" },
                    style { "style=\"background-color:" + rgb + ";\"" };
        ofs << "    <td " << style << ">";
        s = std::to_string(255 - tone);
        rgb = "rgb(" + s + "," + s + "," + s + ")";
        style = "<p style=\"color:" + rgb + ";\">";
        ofs << style << (day < 10 ? "0" : "")  << day;
        ofs << "</p></td>\n";
        ++itr;
      }
      ofs << "  </tr>\n";
    }
    ofs << "</table>\n</html>\n";

  }

}

int main() {

  n8m::moon_tone_one();     // moon tone for single date

  n8m::moon_tone_two();        // moon tones for entire year and format as html

  return 0;

}

