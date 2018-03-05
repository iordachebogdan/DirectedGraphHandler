#include <iostream>
#include <string>
#include "util_stack.h"

int main() {
    util::Vector<int> v(10, 2);
    util::Vector<int> v2(v);
    const util::Vector<int> v3 = v;

    for (int i = 0; i < (int)v.size(); ++i)
        std::cout << v[i] << ' ';
    v2[2] = 3;
    std::cout << '\n' << v2[2] - v[2] << '\n';
    v2.pop_back();
    std::cout << v2.size() << '\n';
    v2.clear();
    std::cout << v2.size() << '\n';
    std::cout << v3.back() << '\n';
    for (util::Vector<int>::iterator it = v.begin(); it != v.end(); ++it)
        std::cout << *it << ' ';

    util::Stack<int> s1;
    s1.push(1);
    s1.push(2);
    s1.push(1);

    util::Stack<int> s2(s1);
    s1.pop();

    std::cout << '\n' << s1.top() << ' ' << s2.size() << ' ' << s2.top() << '\n';
    s2.clear();
    std::cout << s2.size() << '\n';

    return 0;
}