// opengl
#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <memory>
#include <winscard.h>

namespace docvm
{
enum debug_mode_e
{
    no = 0,
    all = 1,
    onlyRend = 2,   // 仅渲染
    onlyRend_timePerSec = 3 // 仅渲染，但是一秒检查一次
};

// opengl 类 输入的 结构体
interface OpenGL_initializitonStruct
{
    debug_mode_e debug_mode;
    bool enable_memory_pool;    // 启用内存池
};

class OpenGL
{
    private:
    // std::unique_ptr<OpenGL> a;
    OpenGL_initializitonStruct s;

    public:
    OpenGL(OpenGL_initializitonStruct s);
    // OpenGL(const OpenGL& other) = delete;
};
}