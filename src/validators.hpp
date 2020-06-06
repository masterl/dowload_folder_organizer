#ifndef VALIDATORS_HPP
#define VALIDATORS_HPP

#include <filesystem>
#include <string>

void ensure_path_is_a_folder( std::string const &path_str );
bool is_image( std::filesystem::path const &file_path );

#endif
