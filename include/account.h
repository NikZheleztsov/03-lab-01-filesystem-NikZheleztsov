#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <cstdint>
#include <chrono>
#include <string>

namespace chrono = std::chrono;

class Account
{
    // key
    uint32_t acc_num;

    // other info
    std::string broker;
    chrono::year_month_day ymd;
    uint16_t files_num = 0;

public:
    explicit Account(uint32_t& _a_num, std::string& _brk, 
            chrono::year_month_day& _ymd, uint16_t _f_num) :

        acc_num(_a_num), broker(_brk), 
            ymd(_ymd), files_num(_f_num) {}

    uint16_t& get_files_num()
        {   return files_num;   }

    chrono::year_month_day& get_ymd()
        {   return ymd;     }

    friend std::ostream& operator<< (std::ostream& out, 
            Account& acc);
};

#endif // ACCOUNT_H
