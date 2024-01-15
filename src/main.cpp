#include <iostream>
#include <string>

#include "directory_processors.hpp"
#include "fs_operations.hpp"
#include "generators.hpp"
#include "validators.hpp"

namespace org = organizer;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cout
            << "You need to specify the target folder:\n"
            << argv[0] << " TARGET_FOLDER";
        
        return EXIT_FAILURE;
    }

    std::string const folder_path{argv[1]};

    try
    {
        org::ensure_path_is_a_folder( folder_path );

        DestFolders const dest_folders = org::create_dest_folders( folder_path );

        auto file_list = org::get_file_list( folder_path );

        org::process_images( dest_folders.at( "images" ), file_list );
        org::process_compressed( dest_folders.at( "compressed" ), file_list );
        org::process_audios( dest_folders.at( "audios" ), file_list );
        org::process_pdfs( dest_folders.at( "pdfs" ), file_list );
        org::process_documents( dest_folders.at( "documents" ), file_list );
        org::process_sources( dest_folders.at( "sources" ), file_list );
    }
    catch( std::exception &error )
    {
        std::cerr << error.what() << "\n";
    }

    return EXIT_SUCCESS;
}
