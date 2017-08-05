#include <cstdint>
#include <cstdarg>
#include <cstdio>
#include <cstring>

#define FMT_LEVEL_TERMINATOR '+'
#define FMT_LEVEL_BAR '|'
#define FMT_LEVEL_FILL ' '

// Nothing fancy for now, just a bunch of tree/indented printing stuff.

namespace fmt
{
void iprintf(uint32_t indent, const char* fmt, ...);
void ifprintf(FILE* file, uint32_t indent, const char* fmt, ...);
void tprintf(uint32_t level, uint32_t shiftPerLevel, const char* fmt, ...);
void tfprintf(FILE* file, uint32_t level, uint32_t shiftPerLevel, const char* fmt, ...);
}


namespace fmt
{

inline void iprintf(uint32_t indent, const char* fmt, ...)
{
    char fullFormat[strlen(fmt) + indent + 1];
    std::memset(fullFormat, ' ', indent);
    std::strcpy(fullFormat + indent, fmt);

    va_list vlist;
    va_start(vlist, fmt);
    vprintf(fullFormat, vlist);
    va_end(vlist);
}

inline void ifprintf(FILE* file, uint32_t indent, const char* fmt, ...)
{
    char fullFormat[strlen(fmt) + indent + 1];
    std::memset(fullFormat, ' ', indent);
    std::strcpy(fullFormat + indent, fmt);

    va_list vlist;
    va_start(vlist, fmt);
    vfprintf(file, fullFormat, vlist);
    va_end(vlist);
}

inline void tprintf(uint32_t level, uint32_t shiftPerLevel, const char* fmt, ...)
{
    uint32_t formatPreambleSize = level * shiftPerLevel;
    if (formatPreambleSize == 0) {
        va_list vlist;
        va_start(vlist, fmt);
        vprintf(fmt, vlist);
        va_end(vlist);
        return;
    }

    char fullFormat[strlen(fmt) + formatPreambleSize + 1];
    std::memset(fullFormat, FMT_LEVEL_FILL, formatPreambleSize);
    std::strcpy(fullFormat + formatPreambleSize, fmt);

    // Write the bars.
    //uint32_t i = 0;
    //for (; i != lastBar; i += shiftPerLevel)
    //    fullFormat[i] = '|';

    // Fill in the tail end with the bend and the leading dashes.
    uint32_t lastBar = formatPreambleSize-shiftPerLevel;
    fullFormat[lastBar] = FMT_LEVEL_BAR;
    std::memset(&fullFormat[lastBar + 1], '-', shiftPerLevel-1);

    va_list vlist;
    va_start(vlist, fmt);
    vprintf(fullFormat, vlist);
    va_end(vlist);
}

inline void tfprintf(FILE* file, uint32_t level, uint32_t shiftPerLevel, const char* fmt, ...)
{
    uint32_t formatPreambleSize = level*shiftPerLevel;
    if (formatPreambleSize == 0) {
        va_list vlist;
        va_start(vlist, fmt);
        vfprintf(file, fmt, vlist);
        va_end(vlist);
        return;
    }

    char fullFormat[strlen(fmt) + formatPreambleSize + 1];
    std::memset(fullFormat, FMT_LEVEL_FILL, formatPreambleSize);
    std::strcpy(fullFormat + formatPreambleSize, fmt);

    // Write the bars.
    uint32_t lastBar = formatPreambleSize-shiftPerLevel;
    uint32_t i = 0;
    for (; i != lastBar; i += shiftPerLevel)
        fullFormat[i] = '|';

    // Fill in the tail end with the bend and the leading dashes.
    fullFormat[i] = FMT_LEVEL_BAR;
    std::memset(&fullFormat[lastBar + 1], '-', shiftPerLevel-1);

    va_list vlist;
    va_start(vlist, fmt);
    vfprintf(file, fullFormat, vlist);
    va_end(vlist);
}

inline void tprintf_last(uint32_t level, uint32_t shiftPerLevel, const char* fmt, ...)
{
    uint32_t formatPreambleSize = level * shiftPerLevel;
    if (formatPreambleSize == 0) {
        va_list vlist;
        va_start(vlist, fmt);
        vprintf(fmt, vlist);
        va_end(vlist);
        return;
    }

    char fullFormat[strlen(fmt) + formatPreambleSize + 1];
    std::memset(fullFormat, FMT_LEVEL_FILL, formatPreambleSize);
    std::strcpy(fullFormat + formatPreambleSize, fmt);

    // Write the bars.
    //uint32_t lastBar = formatPreambleSize-shiftPerLevel;
    //uint32_t i = 0;
    //for (; i != lastBar; i += shiftPerLevel)
    //    fullFormat[i] = '|';

    // Fill in the tail end with the bend and the leading dashes.
    uint32_t lastBar = formatPreambleSize-shiftPerLevel;
    fullFormat[lastBar] = FMT_LEVEL_TERMINATOR;
    std::memset(&fullFormat[lastBar + 1], '-', shiftPerLevel-1);

    va_list vlist;
    va_start(vlist, fmt);
    vprintf(fullFormat, vlist);
    va_end(vlist);
}

inline void tfprintf_last(FILE* file, uint32_t level, uint32_t shiftPerLevel, const char* fmt, ...)
{
    uint32_t formatPreambleSize = level*shiftPerLevel;
    if (formatPreambleSize == 0) {
        va_list vlist;
        va_start(vlist, fmt);
        vfprintf(file, fmt, vlist);
        va_end(vlist);
        return;
    }

    char fullFormat[strlen(fmt) + formatPreambleSize + 1];
    std::memset(fullFormat, FMT_LEVEL_FILL, formatPreambleSize);
    std::strcpy(fullFormat + formatPreambleSize, fmt);

    // Fill in the tail end with the bend and the leading dashes.
    uint32_t lastBar = formatPreambleSize-shiftPerLevel;
    fullFormat[lastBar] = FMT_LEVEL_TERMINATOR;
    std::memset(&fullFormat[lastBar + 1], '-', shiftPerLevel-1);

    va_list vlist;
    va_start(vlist, fmt);
    vfprintf(file, fullFormat, vlist);
    va_end(vlist);
}

} // namespace fmt
