// docvm lib 头文件

/*!
 * @file  docvm4u.hpp
 * @brief docvm 的静态库类与函数声明头文件
 * @author Kyuujuu Kitsuneduka <Foxrpointer>
 * @date 2026-4-14
 * @version 0.0.1
 */

/*! 
 * @defgroup docvm4u 入口函数
 * @brief 用户可选的初始化函数
 * @param core 初始化好的 docvm::Core 的引用
 *
 * 库会尝试在加载时自动调用一个名为 `docvm4u` 的 C 风格函数。
 * 如果用户想要在库加载时执行特定的初始化逻辑，
 * 可以在自己的源文件中定义一个如下签名的函数：
 * extern "C" void docvm4u(docvm::Core& core);
 * 如果不定义此函数，库将跳过初始化步骤。
 */

#pragma once

/// @brief docvm 命名空间
namespace docvm
{
    // core 类
    class Core
    {
        public:
        Core();
    };
}

