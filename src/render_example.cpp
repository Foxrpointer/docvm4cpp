// 有 8 个渲染阶段
// 0. 初始化
// 1. 定点数据
// 2. 三维变换
// 3. 图元装配
// 4. 剪裁切除
// 5. 光栅化
// 6. 片元着色
// 7. 混合测试

#include <iostream>

// 给你们讲一个搞笑的事情
// glad 必须在 glfw 之前引入...
// 在学习 OpenGL 的时候，我为此排查了 2h...
// 不信你可以把顺序调换过来
// by <Kyuujuu Kitsuneduka>
#include "glad/glad.h"
#include "glfw/glfw3.h"


// 初始化 GLFW
GLFWwindow* step0_glfwInit(
    int GL_version_major,
    int GL_version_minor
)
{
    // 初始化
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, GL_version_major);   // 大版本号
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, GL_version_minor);   // 小版本号

    // 启用核心模式
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* win = glfwCreateWindow(800, 600, "Sea Ocean Trangle", NULL, NULL);
    if (!win) return NULL;

    glfwMakeContextCurrent(win);    // 创建窗口上下文
    return win;
}

int main(void)
{
    GLFWwindow* window = step0_glfwInit(4, 0);
    if (!window)
    {
        std::cout << "Error: GLFWwindow 初始化失败。\n";
        return 0;
    }

    // 帧循环
    while(!glfwWindowShouldClose(window))
    {
        /* Render here */
        // glClear(GL_COLOR_BUFFER_BIT);

        /* Swap front and back buffers */
        // glfwSwapBuffers(window);

        /* 处理消息队列 */
        glfwPollEvents();
    }

    // 清理 GLFW 资源
    glfwTerminate();
    return 0;
}