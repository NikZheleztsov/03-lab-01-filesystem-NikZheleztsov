#include <boost/filesystem.hpp>
#include <iostream>

namespace fs = boost::filesystem;

int main (int argc, char* argv[])
{
    fs::path path_to_ftp;
    switch(argc)
    {
        case 1:

    }

    if (argc == 2)
        path_to_ftp = argv[1];
    else 
        std::cout << "Invalid number of arguments";

    return 0;
}
