#include <cstdlib>
#include <fmt/fmt.hpp>

int main()
{
    fmt::TreeSettings settings;
    settings.shift = 3;

    fmt::Tree tree(settings);

    tree.printf_root("Test\n");
    tree.printf_level(1, "Test\n");
    tree.printf_level(2, "Test\n");
    tree.printf_level(3, "Test\n");
    tree.printf_level(3, "Test\n");
    tree.printf_last(3, "Test\n");
    tree.printf_last(2, "Test\n");

    tree.printf_level(1, "Test\n");
    tree.printf_level(2, "Test\n");
    tree.printf_last(2, "Test\n");

    tree.printf_last(1, "Test\n");
    tree.printf_level(2, "Test\n");
    tree.printf_level(2, "Test\n");
    tree.printf_level(3, "Test\n");
    tree.printf_level(3, "Test\n");
    tree.printf_last(3, "Test\n");
    tree.printf_level(4, "Test\n");
    tree.printf_level(4, "Test\n");
    tree.printf_last(4, "Test\n");

    tree.printf_last(2, "Test\n");
    tree.printf_level(3, "Test\n");
    tree.printf_level(3, "Test\n");
    tree.printf_last(3, "Test\n");
    tree.printf_level(4, "Test\n");
    tree.printf_level(4, "Test\n");
    tree.printf_last(4, "Test\n");

    return EXIT_SUCCESS;
}
