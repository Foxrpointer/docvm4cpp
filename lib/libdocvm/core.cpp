// core

#include <iostream>
#include "core.hpp"

// docvm4u
extern "C" void docvm4u() __attribute__((weak));

// 如果有 docvm4u 函数
[[gnu::constructor]] void run_user_init_if_exists() {
    if ((void*)docvm4u != nullptr) {
        std::cout << "Library: Found user-defined initialization function, running it..." << std::endl;
        docvm4u(); // 调用用户定义的函数
        std::cout << "Library: User-defined initialization complete." << std::endl;
    } else {
        std::cout << "Library: No user-defined initialization function found, skipping." << std::endl;
    }
}

// 核心类的构造函数
docvm::Core::Core()
{
    
}