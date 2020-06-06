#include "generators.hpp"

#include <stdexcept>

namespace bfs = boost::filesystem;

namespace organizer
{
    DestFolders create_dest_folders( Path const &base_path )
    {
        DestFolders dest_folders;

        dest_folders["images"]     = Path( base_path ).append( "images" ).string();
        dest_folders["compressed"] = Path( base_path ).append( "compressed" ).string();
        dest_folders["audios"]     = Path( base_path ).append( "audios" ).string();
        dest_folders["pdf"]        = Path( base_path ).append( "pdf" ).string();
        dest_folders["documents"]  = Path( base_path ).append( "documents" ).string();
        dest_folders["sources"]    = Path( base_path ).append( "sources" ).string();

        for( auto const [key, folder] : dest_folders )
        {
            std::cout << folder << '\n';

            auto const folder_status = bfs::status( folder );

            if( !bfs::exists( folder_status ) )
            {
                bfs::create_directory( folder );
            }
            else if( !bfs::is_directory( folder_status ) )
            {
                throw std::runtime_error( folder + " should be a folder!" );
            }
        }

        return dest_folders;
    }
} // namespace organizer
