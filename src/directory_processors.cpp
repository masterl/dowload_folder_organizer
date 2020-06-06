#include "directory_processors.hpp"

#include "fs_operations.hpp"
#include "validators.hpp"

#include <iostream>

namespace organizer
{
    void process_images( Path const &dest_folder_path, DirEntries const &files )
    {
        for( auto &file : files )
        {
            if( is_image( file.path() ) && is_old( file ) )
            {
                move_file( file.path(), dest_folder_path );
            }
        }
    }

    void process_compressed( Path const &dest_folder_path,
                             DirEntries const &files )
    {
        for( auto &file : files )
        {
            if( is_compressed( file.path() ) && is_old( file ) )
            {
                move_file( file.path(), dest_folder_path );
            }
        }
    }

    void process_audios( Path const &dest_folder_path, DirEntries const &files )
    {
        for( auto &file : files )
        {
            if( is_audio( file.path() ) && is_old( file ) )
            {
                move_file( file.path(), dest_folder_path );
            }
        }
    }
} // namespace organizer
