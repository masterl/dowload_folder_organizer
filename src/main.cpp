#include <iostream>
#include <string>

#include "fs_operations.hpp"
#include "validators.hpp"

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
