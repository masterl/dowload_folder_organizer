#include "fs_operations.hpp"

#include <mhash.h>
#include <sstream>
#include <tuple>

namespace bfs = boost::filesystem;

namespace organizer
{
    static std::tuple< std::string, std::string >
    split_path_on_extension( Path const &path );

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

    static std::tuple< std::string, std::string >
    split_path_on_extension( Path const &path )
    {
        auto const stem{path.stem().string()};

        return {path.parent_path().append( stem ).string(),
                path.extension().string()};
    }

    std::string get_file_sha1( Path const &path )
    {
        int bytes_read = 1;
        MHASH td;
        unsigned char buffer[1024];
        unsigned char *hash;

        FILE *file = fopen( path.string().c_str(), "r" );

        if( !file )
        {
            std::cout << "open failed\n";
            return "";
        }

        td = mhash_init( MHASH_SHA1 );

        if( td == MHASH_FAILED )
        {
            return "";
        }

        while( bytes_read != 0 )
        {
            bytes_read = fread( buffer, 1, 1024, file );
            mhash( td, buffer, bytes_read );
        }

        hash = static_cast< unsigned char * >( mhash_end( td ) );

        std::ostringstream string_builder;

        string_builder.fill( '0' );

        for( int i = 0; i < mhash_get_block_size( MHASH_SHA1 ); i++ )
        {
            string_builder << std::setw( 2 ) << std::hex
                           << static_cast< unsigned int >( hash[i] );
        }

        free( hash );

        return string_builder.str();
    }
} // namespace organizer
