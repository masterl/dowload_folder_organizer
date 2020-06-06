#include "validators.hpp"

#include <algorithm>
#include <stdexcept>
#include <string>
#include <vector>

#include <boost/date_time.hpp>
#include <boost/filesystem.hpp>

#include "fs_operations.hpp"
#include "utils.hpp"

namespace bfs = boost::filesystem;

static std::vector< std::string > image_extensions      = {".png",
                                                      ".jpg",
                                                      ".jpeg",
                                                      ".tiff",
                                                      ".gif"};
static std::vector< std::string > compressed_extensions = {".zip",
                                                           ".tar.gz",
                                                           ".tar.xz",
                                                           ".tar.bz2",
                                                           ".rar"};

namespace organizer
{
    void ensure_path_is_a_folder( std::string const &path_str )
    {
        bfs::directory_entry const entry{path_str};

        if( !is_directory( entry.status() ) )
        {
            throw std::domain_error( "Download path should point to a folder!\n"
                                     "  Invalid path: [" +
                                     path_str + "]" );
        }
    }

    bool is_image( Path const &file_path )
    {
        return std::any_of( image_extensions.begin(),
                            image_extensions.end(),
                            [&file_path]( auto const &extension ) {
                                return extension ==
                                       to_lower_case(
                                           file_path.extension().string() );
                            } );
    }

    bool is_compressed( Path const &file_path )
    {
        return std::any_of( compressed_extensions.begin(),
                            compressed_extensions.end(),
                            [&file_path]( auto const &extension ) {
                                return extension ==
                                       to_lower_case(
                                           file_path.extension().string() );
                            } );
    }

    bool is_old( boost::filesystem::directory_entry const &file )
    {
        int const days_in_month{30};
        int const min_days{4 * days_in_month};

        Date const file_date = get_modification_time( file.path() );

        Date const today( boost::gregorian::day_clock::local_day() );

        auto const diff_in_days = ( today - file_date ).days();

        return diff_in_days > min_days;
    }
} // namespace organizer
