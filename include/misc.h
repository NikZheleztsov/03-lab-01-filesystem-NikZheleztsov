#ifndef MISC_H
#define MISC_H
#include <boost/filesystem.hpp>

namespace fs = boost::filesystem;

// Parsing command line arguments
fs::path parse_cma(int argc, char* argv[]);

#endif // MISC_H
