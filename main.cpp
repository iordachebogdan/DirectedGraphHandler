#include <iostream>
#include <string>
#include "linked_list.h"

int main() {
    int n;
    std::cin >> n;

    linked_list::LinkedList< std::string > lst;
    while (n--) {
        std::string s;
        std::cin >> s;
        lst.push_back(s);
    }

    for (linked_list::LinkedList< std::string >::iterator it = lst.begin(); it != lst.end(); ++it)
        std::cout << it->size() << ' ' << *it << '\n';

    lst.clear();
    lst.push_back("aaa");
    std::cout << lst.front() << std::endl;

    return 0;
}