/* Copyright 2021 Nikita Zheleztsov */

#include "./account.h"
#include <chrono>
#include <iomanip>
#include <iostream>

std::ostream& operator<< (std::ostream& out, Account& acc)
{
    out << "broker:" << acc.broker << ' ';

    out << "account:" << std::right << std::setw(8)
        << std::setfill('0') << acc.acc_num << ' ';

    out << "files:" << acc.files_num << ' ';

    out << "lastdate:" << static_cast<int>(acc.ymd.year());
    out << std::right << std::setw(2)  << std::setfill('0')
        << static_cast<unsigned>(acc.ymd.month());
    out << std::right << std::setw(2)  << std::setfill('0') <<
        static_cast<unsigned>(acc.ymd.day()) << std::endl;

    return out;
}
