#include "bstree.hpp"
#include <iostream>

void read_comands(bstree_ptr<int> root);

int main()
{
    auto root = bstree<int>::make();
    read_comands(root);
}

void read_comands(bstree_ptr<int> root)
{
    char c;
    int x;
    while (std::cin >> c)
    {
        switch (c)
        {
        case 'i':
            std::cin >> x;
            root = bstree<int>::insert(x, root);
            break;
        case 'r':
            std::cin >> x;
            root = bstree<int>::remove(x, root);
            break;
        case 's':
            std::cin >> x;
            if (bstree<int>::search(x,root) == true)
                std::cout << "true\n";
            else
                std::cout << "false\n";
            break;
        case 'h':
            std::cout << bstree<int>::height(root) << "\n";
            break;
        case 'p':
            std::cout << root << "\n";
            break;
        default:
            break;
        }
    }
}
