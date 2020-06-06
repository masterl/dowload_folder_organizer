#include "validators.hpp"

#include <filesystem>
#include <stdexcept>

namespace fs = std::filesystem;

void ensure_path_is_a_folder( std::string const &path_str )
{
    fs::directory_entry const entry{path_str};

    if( !entry.is_directory() )
    {
        throw std::domain_error( "Download path should point to a folder!\n"
                                 "  Invalid path: [" +
                                 path_str + "]" );
    }
}
