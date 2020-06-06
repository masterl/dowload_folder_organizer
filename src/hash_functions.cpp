#include "hash_functions.hpp"

#include <fstream>
#include <mhash.h>

namespace organizer
{
    std::string get_file_sha1( Path const &path )
    {
        int bytes_read = 1;
        MHASH td;
        char buffer[1024];
        unsigned char *hash;

        std::ifstream file{path.string(), std::ios::binary};

        if( !file.is_open() )
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
            bytes_read = file.readsome( buffer, 1024 );

            mhash( td, buffer, bytes_read );
        }

        hash = static_cast< unsigned char * >( mhash_end( td ) );

        std::ostringstream string_builder;

        string_builder.fill( '0' );

        for( unsigned i = 0; i < mhash_get_block_size( MHASH_SHA1 ); i++ )
        {
            string_builder << std::setw( 2 ) << std::hex
                           << static_cast< unsigned int >( hash[i] );
        }

        free( hash );

        return string_builder.str();
    }
} // namespace organizer
