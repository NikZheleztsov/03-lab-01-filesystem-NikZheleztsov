#include "account.h"
#include <boost/filesystem.hpp>
#include <boost/system/error_code.hpp>
#include <map>
#include <memory>
#include <string>

namespace fs = boost::filesystem;
using namespace boost::system;

extern std::unique_ptr<std::ostream> out;

void analyze_dir(fs::path path,
        std::map<uint32_t, Account>& acc_map)
{
    for (const auto& entry : fs::directory_iterator(path))
    {
        if (fs::is_directory(entry) || fs::is_symlink(entry))
            analyze_dir(entry, acc_map);

        else {
            if (entry.path().filename().string().starts_with("balance") && 
                    entry.path().stem().extension().string() != "old")
            {
                std::string file_name = entry.path().filename().string();

                auto first_of = file_name.find_first_of("_");
                auto last_of = file_name.find_last_of("_");

                if (first_of != last_of && first_of != std::string::npos &&
                        last_of != std::string::npos)
                {
                    try
                    {
                        //////////////////////////////////////
                        uint32_t acc_num = std::stoul(
                                file_name.substr(first_of + 1, 
                                    file_name.size() - first_of - last_of + 1));
                        *out << acc_num;
                            
                    } catch (...) {
                        continue;
                    }

                } else
                    continue;
            }
        }
    }
}
