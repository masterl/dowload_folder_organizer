#include "hash_functions.hpp"

#include <fstream>
#include <mhash.h>

namespace organizer
{
    static std::string hash_to_string( unsigned char const *const hash,
                                       unsigned const block_size )
    {
        std::ostringstream string_builder;

        string_builder.fill( '0' );

        for( unsigned i = 0; i < block_size; i++ )
        {
            string_builder << std::setw( 2 ) << std::hex
                           << static_cast< unsigned int >( hash[i] );
        }

        return string_builder.str();
    }

    std::string get_file_sha1( Path const &path )
    {
        std::ifstream file{path.string(), std::ios::binary};

        if( !file.is_open() )
        {
            return "";
        }

        MHASH td{mhash_init( MHASH_SHA1 )};

        if( td == MHASH_FAILED )
        {
            return "";
        }

        int bytes_read = 1;
        char buffer[1024];
        while( bytes_read != 0 )
        {
            bytes_read = file.readsome( buffer, 1024 );

            if( bytes_read != 0 )
            {
                mhash( td, buffer, bytes_read );
            }
        }

        unsigned char *hash{static_cast< unsigned char * >( mhash_end( td ) )};

        auto const block_size = mhash_get_block_size( MHASH_SHA1 );
        std::string const hash_str{hash_to_string( hash, block_size )};

        free( hash );

        return hash_str;
    }
} // namespace organizer
