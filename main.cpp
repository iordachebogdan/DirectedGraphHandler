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

    linked_list::LinkedList< std::string > lst2(lst);
    for (linked_list::LinkedList< std::string >::iterator it = lst2.begin(); it != lst2.end(); ++it)
        std::cout << it->size() << ' ' << *it << '\n';

    lst.clear();
    std::cout << lst.empty() << std::endl;
    lst.push_back("aaa");
    std::cout << lst.front() << std::endl;

    return 0;
}