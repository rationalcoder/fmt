#ifndef TREE_HPP
#define TREE_HPP
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <cstdarg>

namespace fmt
{

struct TreeSettings
{
    uint32_t shift = 4;
    char bar = '|';
    char elbow = '+';
};

class Tree
{
public:
    Tree(const TreeSettings& settings)
        : settings_(settings)
    {}

    Tree()
        : settings_()
    {}

public:
    void printf_root(const char* fmt, ...);
    void printf_level(uint32_t level, const char* fmt, ...);
    void printf_last(uint32_t level, const char* fmt, ...);

    void fprintf_root(FILE* file, const char* fmt, ...);
    void fprintf_level(FILE* file, uint32_t level, const char* fmt, ...);
    void fprintf_last(FILE* file, uint32_t level, const char* fmt, ...);

    TreeSettings settings() const { return settings_; }
    void set_settings(const TreeSettings& settings) { settings_ = settings; }

    uint32_t shift() const { return settings_.shift; }
    char bar() const { return settings_.bar; }
    char elbow() const { return settings_.elbow; }

    void set_shift(uint32_t shift) { settings_.shift = shift; }
    void set_bar(char bar) { settings_.bar = bar; }
    void elbow(char elbow) { settings_.elbow = elbow; }
    void reset() { levelTerminationState_.clear(); }

private:
    void resize_level_state(uint32_t level);

public:
    std::vector<bool> levelTerminationState_; // true for terminated.
    TreeSettings settings_;
};

inline void Tree::printf_root(const char* fmt, ...)
{
    va_list vlist;
    va_start(vlist, fmt);
    vprintf(fmt, vlist);
    va_end(vlist);
}

inline void Tree::printf_level(uint32_t level, const char* fmt, ...)
{
    resize_level_state(level);

    uint32_t shiftPerLevel = shift();
    uint32_t formatPreambleSize = level * shiftPerLevel;
    if (formatPreambleSize == 0) {
        va_list vlist;
        va_start(vlist, fmt);
        vprintf(fmt, vlist);
        va_end(vlist);
        return;
    }

    char* fullFormat = (char*)alloca(strlen(fmt) + formatPreambleSize + 1);
    std::memset(fullFormat, ' ', formatPreambleSize);
    std::strcpy(fullFormat + formatPreambleSize, fmt);

    // Write the bars.
    uint32_t lastBar = formatPreambleSize-shiftPerLevel;
    uint32_t logicalBar = 0;
    for (uint32_t i = 0; i != lastBar; i += shiftPerLevel, logicalBar++) {
        if (!levelTerminationState_[logicalBar])
            fullFormat[i] = bar();
    }

    // Fill in the tail end with the bend and the leading dashes.
    fullFormat[lastBar] = bar();
    std::memset(&fullFormat[lastBar + 1], '-', shiftPerLevel-1);

    va_list vlist;
    va_start(vlist, fmt);
    vprintf(fullFormat, vlist);
    va_end(vlist);

    for (int i = level-1; i < (int)levelTerminationState_.size(); i++) {
        levelTerminationState_[i] = false;
    }
}

inline void Tree::printf_last(uint32_t level, const char* fmt, ...)
{
    resize_level_state(level);

    uint32_t shiftPerLevel = shift();
    uint32_t formatPreambleSize = level * shiftPerLevel;
    if (formatPreambleSize == 0) {
        va_list vlist;
        va_start(vlist, fmt);
        vprintf(fmt, vlist);
        va_end(vlist);
        return;
    }

    char* fullFormat = (char*)alloca(strlen(fmt) + formatPreambleSize + 1);
    std::memset(fullFormat, ' ', formatPreambleSize);
    std::strcpy(fullFormat + formatPreambleSize, fmt);

    // Write the bars.
    uint32_t lastBar = formatPreambleSize-shiftPerLevel;
    uint32_t logicalBar = 0;
    for (uint32_t i = 0; i != lastBar; i += shiftPerLevel, logicalBar++) {
        if (!levelTerminationState_[logicalBar])
            fullFormat[i] = bar();
    }

    // Fill in the tail end with the bend and the leading dashes.
    fullFormat[lastBar] = elbow();
    std::memset(&fullFormat[lastBar + 1], '-', shiftPerLevel-1);

    va_list vlist;
    va_start(vlist, fmt);
    vprintf(fullFormat, vlist);
    va_end(vlist);

    levelTerminationState_[level-1] = true;
}

inline void Tree::fprintf_root(FILE* file, const char* fmt, ...)
{
}

inline void Tree::fprintf_level(FILE* file, uint32_t level, const char* fmt, ...)
{
}

inline void Tree::fprintf_last(FILE* file, uint32_t level, const char* fmt, ...)
{
}

inline void Tree::resize_level_state(uint32_t level)
{
    uint32_t size = levelTerminationState_.size();
    if (size < level)
        levelTerminationState_.resize(level);
}

} // namespace fmt

#endif // TREE_HPP
