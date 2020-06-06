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
        auto const to_template =
            Path( to_directory ).append( from.filename().string() );
        auto const fail_if_exists{bfs::copy_option::fail_if_exists};
        auto ec{bs::errc::make_error_code( bs::errc::errc_t::io_error )};

        auto to{to_template};
        int error_count{1};

        while( ec )
        {
            // copy_file( from, to, fail_if_exists, ec );

            {
                std::cout << "File: " << from.string() << '\n';
                std::cout << "Hash: " << get_file_sha1( from ) << '\n';
                break;
            }

            if( ec )
            {
                std::ostringstream string_builder;

                auto const [stem, extension] =
                    split_path_on_extension( to_template );

                string_builder << stem;
                string_builder << "_(" << error_count << ')';
                string_builder << extension;

                ++error_count;

                to = string_builder.str();

                // std::cout << to << '\n';

                if( error_count > 5 )
                {
                    break;
                }
            }
        }
    }

    static std::tuple< std::string, std::string >
    split_path_on_extension( Path const &path )
    {
        auto const stem{path.stem().string()};

        return {path.parent_path().append( stem ).string(),
                path.extension().string()};
    }

} // namespace organizer
