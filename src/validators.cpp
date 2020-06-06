#include "validators.hpp"

#include <algorithm>
#include <filesystem>
#include <stdexcept>
#include <string>
#include <vector>

namespace fs = std::filesystem;

static std::vector< std::string > image_extensions = {".png", ".jpg", ".jpeg", ".tiff", ".gif"};

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

bool is_image( std::filesystem::path const &file_path )
{
    return std::any_of(
        image_extensions.begin(), image_extensions.end(), [&file_path]( auto const &extension ) {
            return extension == file_path.extension().string();
        } );
}
