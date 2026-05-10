#include <iostream>
#include "Collections.hpp"

int main() {
    std::cout << "--- Stack Test ---" << std::endl;
    Stack<int> s;
    s.push(1); s.push(2); s.push(3);
    while(!s.empty()) {
        std::cout << s.top() << " "; // Выведет: 3 2 1
        s.pop();
    }

    std::cout << "\n--- Queue Test ---" << std::endl;
    Queue<int> q;
    q.push(1); q.push(2); q.push(3);
    while(!q.empty()) {
        std::cout << q.front() << " "; // Выведет: 1 2 3
        q.pop();
    }
    return 0;
}
