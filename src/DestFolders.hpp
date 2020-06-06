#ifndef DEST_FOLDERS_HPP
#define DEST_FOLDERS_HPP

#include "types.hpp"

namespace organizer
{
    struct DestFolders
    {
        DestFolders( Path const &base )
            : images{base / "images"}
            , compressed{base / "compressed"}
            , audios{base / "audios"}
            , pdf{base / "pdf"}
            , documents{base / "documents"}
            , sources{base / "sources"}
        {
        }

        Path const images;
        Path const compressed;
        Path const audios;
        Path const pdf;
        Path const documents;
        Path const sources;
    };
} // namespace organizer

#endif
