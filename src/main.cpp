#include <filesystem>
#include <stdexcept>
#include <string>
#include <vector>

namespace fs = std::filesystem;

std::vector< std::filesystem::directory_entry > get_file_list( std::string const &folder_path );
void ensure_path_is_a_folder( std::string const &path_str );

int main()
{
    return 0;
}

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

std::vector< std::filesystem::directory_entry > get_file_list( std::string const &folder_path )
{
    std::vector< std::filesystem::directory_entry > files;

    for( auto &file : fs::directory_iterator( folder_path ) )
    {
        if( file.is_regular_file() )
        {
            files.emplace_back( file );
        }
    }

    return files;
}
