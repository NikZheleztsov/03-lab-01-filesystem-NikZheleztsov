/* Copyright 2021 Nikita Zheleztsov */

#include "./account.h"
#include "./analyze.h"
#include <boost/filesystem.hpp>
#include <string>
#include <iostream>
#include <map>
#include <memory>
#include "./misc.h"

namespace fs = boost::filesystem;
std::unique_ptr<std::ostream> out;

int main(int argc, char* argv[])
{
    // Parsing command line arguments
    fs::path path_to_ftp;
    try {
        path_to_ftp = parse_cma(argc, argv);
    } catch(std::exception& e) {
        std::cout << e.what() << std::endl;
        std::cout << "acc_dir [-d <dir_to_analyze> [-o <output_file]]"
            << std::endl;
        return 1;
    }

    // Analyzing directory
    std::map<uint32_t, Account> acc_map;
    if (fs::exists(path_to_ftp) && (fs::is_directory(path_to_ftp) ||
                fs::is_symlink(path_to_ftp))) {
        analyze_dir(path_to_ftp, acc_map);

    } else {
        std::cout << "Unable to open the directory\n";
        return 2;
    }

    // Summary info
    if (!acc_map.empty()) {
        *out << "\nSummary:\n";
        for (auto acc : acc_map)
            *out << acc.second;
    }

    return 0;
}
