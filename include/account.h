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
};

#endif // ACCOUNT_H
