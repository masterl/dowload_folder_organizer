#include "fs_operations.hpp"

namespace bfs = boost::filesystem;

namespace organizer
{
    DirEntries get_file_list( std::string const &folder_path )
    {
        DirEntries files;

        for( auto &file : bfs::directory_iterator( folder_path ) )
        {
            if( is_regular_file( file.status() ) )
            {
                files.emplace_back( file );
            }
        }

        return files;
    }

    Date get_modification_time( boost::filesystem::path const &path )
    {
        struct tm *timeinfo;
        std::time_t const raw_time{bfs::last_write_time( path )};

        timeinfo = localtime( &raw_time );

        return boost::gregorian::date_from_tm( *timeinfo );
    }
} // namespace organizer
