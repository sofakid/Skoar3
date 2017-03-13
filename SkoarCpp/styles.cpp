#include "lex.hpp"
//#include "styles.hpp"

namespace SkoarStyles {

    std::wostream& operator << (std::wostream& out, const SkoarStyles::EStyle& obj)
    {
        out << static_cast<std::underlying_type<SkoarStyles::EStyle>::type>(obj);
        return out;
    }

}