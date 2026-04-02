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

void callback_ifWindowSizeChanged(GLFWwindow* win, int width, int height);
void callback_keyPushed(GLFWwindow* win, int key, int scancode, int action, int mods);

// 渲染循环
void rendloop(GLFWwindow* win)
{
    // 清理画布
    glClear(GL_COLOR_BUFFER_BIT);

    // 渲染逻辑
    // code...

    // 切换双缓存
    glfwSwapBuffers(win);
}

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

    // 构建窗体对象完毕之后，需要设置监听
    /* 窗体大小 */glfwSetFramebufferSizeCallback(win, callback_ifWindowSizeChanged);
    /* 键盘 */glfwSetKeyCallback(win, callback_keyPushed);

    // *** 加载 OpenGL 函数
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD \n";
        return NULL;
    }

    // *** 设置 OpenGL 视口大小
    glViewport(0, 0, 800, 600);

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

// 对于键盘动作的 callback 函数
void callback_keyPushed(GLFWwindow* win, int key, int scancode, int action, int mods)
{
    switch (key) {
    case GLFW_KEY_W:
        if(action == GLFW_PRESS) std::cout << "pressed: W \n";
        else std::cout << "unPressed: W \n";
    };
}

// 对于窗口大小变化的 callback 函数
void callback_ifWindowSizeChanged(GLFWwindow* win, int width, int height)
{

}