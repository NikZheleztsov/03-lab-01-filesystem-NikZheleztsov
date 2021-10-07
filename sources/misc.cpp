/* Copyright 2021 Nikita Zheleztsov */

#include <boost/filesystem.hpp>
#include <iostream>
#include <memory>
#include <stdexcept>

namespace fs = boost::filesystem;
extern std::unique_ptr<std::ostream> out;

fs::path parse_cma(int argc, char* argv[])
{
    fs::path path_to_ftp;
    switch (argc)
    {
        case 1:
            std::cout << "Analyzing current directory\n";
            path_to_ftp = fs::current_path();
            break;

        default:
            bool is_ok = false;
            for (int i = 0; i < argc; ++i)
            {
                if (std::string(argv[i]) == "-h") {
                    std::cout << R"(acc_dir [-d
 <dir_to_analyze> [-o <output_file]])" << std::endl;
                    exit(0);

                } else if (std::string(argv[i]) == "-d") {
                    path_to_ftp = fs::path(argv[i + 1]);
                    is_ok = true;

                } else if (std::string(argv[i]) == "-o") {
                    out = std::unique_ptr<std::ostream>
                        (new std::ofstream(argv[i + 1]));
                    is_ok = true;
                }
            }

            if (!is_ok)
                throw std::invalid_argument
                    ("Error while parsing the arguments");
    }

    if (out == nullptr)
        out = std::unique_ptr<std::ostream>
            (new std::ostream(std::cout.rdbuf()));

    return path_to_ftp;
}
