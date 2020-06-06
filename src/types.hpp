#ifndef TYPES_HPP
#define TYPES_HPP

#include <boost/date_time.hpp>
#include <boost/filesystem.hpp>
#include <vector>

using DirEntries = std::vector< boost::filesystem::directory_entry >;
using Date = boost::gregorian::date;
using Path = boost::filesystem::path;

#endif
