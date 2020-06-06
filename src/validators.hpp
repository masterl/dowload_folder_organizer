#ifndef VALIDATORS_HPP
#define VALIDATORS_HPP

#include "types.hpp"
#include <string>

namespace organizer
{
    void ensure_path_is_a_folder( std::string const &path_str );
    bool is_image( Path const &file_path );
    bool is_compressed( Path const &file_path );
    bool is_audio( Path const &file_path );
    bool is_pdf( Path const &file_path );
    bool is_document( Path const &file_path );
    bool is_source( Path const &file_path );
    bool is_old( boost::filesystem::directory_entry const &file );
} // namespace organizer

#endif
