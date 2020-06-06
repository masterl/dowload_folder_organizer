#include "utils.hpp"

#include <cctype>

namespace organizer
{
    std::string to_lower_case( std::string const &str )
    {
        std::string lower;

        for( char ch : str )
        {
            lower += tolower( ch );
        }

        return lower;
    }
} // namespace organizer
