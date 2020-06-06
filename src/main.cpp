#include <filesystem>
#include <string>
#include <vector>

namespace fs = std::filesystem;

std::vector< std::filesystem::directory_entry > get_file_list( std::string const &folder_path );

int main()
{
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
