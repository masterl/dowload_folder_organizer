#include "fs_operations.hpp"

#include <sstream>
#include <tuple>

namespace bfs = boost::filesystem;
namespace bs  = boost::system;

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

    void move_file( Path const &from, Path const &to_directory )
    {
        auto const from_hash = get_file_sha1( from );
        auto const to_template =
            Path( to_directory ).append( from.filename().string() );
        auto const fail_if_exists{bfs::copy_option::fail_if_exists};

        auto to{to_template};
        int error_count{1};

        while( true )
        {
            if( !bfs::exists( bfs::status( to ) ) )
            {
                copy_file( from, to, fail_if_exists );
                break;
            }

            auto const to_hash = get_file_sha1( to );

            if( to_hash == from_hash )
            {
                break;
            }

            std::ostringstream string_builder;

            auto const [stem, extension] =
                split_path_on_extension( to_template );

            string_builder << stem;
            string_builder << "_(" << error_count << ')';
            string_builder << extension;

            ++error_count;

            to = string_builder.str();
        }

        bfs::remove( from );
    }

    static std::tuple< std::string, std::string >
    split_path_on_extension( Path const &path )
    {
        auto const stem{path.stem().string()};

        return {path.parent_path().append( stem ).string(),
                path.extension().string()};
    }

} // namespace organizer
