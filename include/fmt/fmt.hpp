#include <cstdint>
#include <cstdarg>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "fmt/tree.hpp"

namespace fmt
{

//! Standard printf with an indent.
//! \param indent Number of spaces printed before your text.
//! \param fmt Standard printf format string.
//! \param .. Standard printf arguments.
//!
inline void iprintf(uint32_t indent, const char* fmt, ...)
{
    char* fullFormat = (char*)alloca(strlen(fmt) + indent + 1);
    std::memset(fullFormat, ' ', indent);
    std::strcpy(fullFormat + indent, fmt);

    va_list vlist;
    va_start(vlist, fmt);
    vprintf(fullFormat, vlist);
    va_end(vlist);
}

//! Standard fprintf with an indent.
//! \param file The FILE to print to.
//! \param indent Number of spaces printed before your text.
//! \param fmt Standard fprintf format string.
//! \param .. Standard fprintf arguments.
//!
inline void ifprintf(FILE* file, uint32_t indent, const char* fmt, ...)
{
    char* fullFormat = (char*)alloca(strlen(fmt) + indent + 1);
    std::memset(fullFormat, ' ', indent);
    std::strcpy(fullFormat + indent, fmt);

    va_list vlist;
    va_start(vlist, fmt);
    vfprintf(file, fullFormat, vlist);
    va_end(vlist);
}

} // namespace fmt
