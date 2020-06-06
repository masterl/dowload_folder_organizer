#include "generators.hpp"

namespace organizer
{
    DestFolders create_dest_folders( Path const &base_path )
    {
        DestFolders dest_folders;

        dest_folders["images"] = Path( base_path ).append( "images" ).string();

        return dest_folders;
    }
} // namespace organizer
