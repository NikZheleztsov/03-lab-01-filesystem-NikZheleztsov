/* Copyright 2021 Nikita Zheleztsov */

#include "./account.h"
#include <boost/system/error_code.hpp>
#include <boost/filesystem.hpp>
#include <chrono>
#include <map>
#include <memory>
#include <string>

namespace fs = boost::filesystem;
namespace chrono = std::chrono;

extern std::unique_ptr<std::ostream> out;

void analyze_dir(fs::path path,
        std::map<uint32_t, Account>& acc_map)
{
    for (const auto& entry : fs::directory_iterator(path))
    {
        if (fs::is_directory(entry) || fs::is_symlink(entry))
            analyze_dir(entry, acc_map);

        else
        {
            if (entry.path().filename().string().starts_with("balance") &&
                    entry.path().stem().extension().string() != ".old")
            {
                std::string file_name = entry.path().filename().string();

                auto first_of = file_name.find_first_of("_");
                auto last_of = file_name.find_last_of("_");

                if (first_of != last_of && first_of != std::string::npos &&
                        last_of != std::string::npos) {
                    uint32_t acc_num;
                    chrono::year_month_day ymd;

                    try
                    {
                        // account number must be 8 char length
                        if ((last_of - first_of - 1) != 8)
                            throw -1;

                        acc_num = std::stoul(
                                file_name.substr(first_of + 1,
                                    last_of - first_of + 1));

                        ymd = chrono::year_month_day(
                                chrono::year(std::stoi(file_name.substr(
                                            last_of + 1, 4))),
                                chrono::month(std::stoi(file_name.substr(
                                            last_of + 5, 2))),
                                chrono::day(std::stoi(file_name.substr(
                                            last_of + 7, 2))) );

                        if (!ymd.ok())
                            throw -1;
                    } catch (...) {
                        continue;
                    }

                    std::string broker =
                        entry.path().parent_path().filename().string();
                    *out << broker << ' ' << file_name << std::endl;

                    auto acc_num_iter = acc_map.find(acc_num);
                    if (acc_num_iter != acc_map.end())
                    {
                        // increment files_num
                        ++acc_num_iter->second.get_files_num();

                        // change date if needed
                        if (acc_num_iter->second.get_ymd() < ymd)
                            acc_num_iter->second.get_ymd() = ymd;

                    } else {
                        Account acc(acc_num, broker, ymd, 1);
                        acc_map.insert({acc_num, acc});
                    }
                } else {
                    continue;
                }
            }
        }
    }
}
