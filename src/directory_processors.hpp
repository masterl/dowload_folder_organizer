#ifndef DIRECTORY_PROCESSORS_HPP
#define DIRECTORY_PROCESSORS_HPP

#include "types.hpp"

namespace organizer
{
    void process_images( Path const &dest_folder_path, DirEntries const &files );
    void process_compressed( Path const &dest_folder_path, DirEntries const &files );
    void process_audios( Path const &dest_folder_path, DirEntries const &files );
    void process_pdfs( Path const &dest_folder_path, DirEntries const &files );
    void process_documents( Path const &dest_folder_path, DirEntries const &files );
} // namespace organizer

#endif
