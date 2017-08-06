#include <cstdlib>
#include <fmt/fmt.hpp>

int main()
{
    fmt::TreeSettings settings;
    settings.bar = '|';
    settings.elbow = '+';
    settings.shift = 4;

    fmt::Tree tree(settings);

    tree.printf_root("Root\n");
    tree.printf_level(1, "Test\n");
    tree.printf_level(2, "Test\n");
    tree.printf_last(2, "Test\n");
    tree.printf_level(1, "Test\n");
    tree.printf_level(2, "Test\n");
    tree.printf_last(2, "Test\n");
    tree.printf_last(1, "Test\n");
    tree.printf_level(2, "Test\n");
    tree.printf_level(2, "Test\n");
    tree.printf_last(2, "Test\n");

    return EXIT_SUCCESS;
}
