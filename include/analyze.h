#ifndef ANALYZE_H
#define ANALYZE_H

#include "account.h"
#include <boost/filesystem.hpp>
#include <map>
#include <memory>

namespace fs = boost::filesystem;

void analyze_dir(fs::path, 
    std::map<uint32_t, Account>& acc_map);

#endif // ANALYZE_H
