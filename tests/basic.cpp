#include <cstdlib>
#include <fmt/fmt.hpp>

void print_tree(uint32_t level = 0, uint32_t shift = 4)
{
    if (level == 5) return;
    if (level == 0) {
        fmt::tprintf(level, shift, "Test\n");
        print_tree(level + 1, shift);
        return;
    }

    uint32_t nextLevel = level;
    fmt::tprintf(nextLevel, shift, "Test\n");
    fmt::tprintf(nextLevel, shift, "Test\n");
    fmt::tprintf(nextLevel, shift, "Test\n");
    fmt::tprintf_last(nextLevel, shift, "Test\n");
    print_tree(level + 1, shift);
}

int main(int argc, char* argv[])
{
    print_tree();
    return EXIT_SUCCESS;
}
