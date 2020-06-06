#include <filesystem>
#include <iostream>
#include <string>
#include <vector>

#include "validators.hpp"

namespace fs = std::filesystem;

FileList get_file_list( std::string const &folder_path );

int main()
{
    std::string const folder_path{"/home/leonardo/Downloads"};

    try
    {
        ensure_path_is_a_folder( folder_path );

        for( auto &file : get_file_list( folder_path ) )
        {
            std::cout << file.path() << '\n';
        }
    }
    catch( std::exception &error )
    {
        std::cerr << error.what() << "\n";
    }

    return 0;
}

FileList get_file_list( std::string const &folder_path )
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
