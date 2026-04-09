#include <iostream>
// 假设已经包含了必要的 OpenGL 头文件 (如 glad.h 或 glew.h) 和数学库 (如 glm)
#include <glad/glad.h> // 或 #include <GL/glew.h>
#include <GLFW/glfw3.h>

// 顶点着色器源码 (使用 GLSL 语言)
const char* vertexShaderSource = R"(
#version 330 core
layout (location = 0) in vec3 aPos; // 输入顶点属性，位置坐标 (x, y, z)

void main()
{
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0); // 将顶点位置传递给下一阶段 (光栅化)，并设置齐次坐标 w=1.0
}
)";

// 片段着色器源码 (使用 GLSL 语言)
const char* fragmentShaderSource = R"(
#version 330 core
out vec4 FragColor; // 输出的片段颜色

void main()
{
    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f); // 设置输出颜色为橙红色 (RGBA: Red=1.0, Green=0.5, Blue=0.2, Alpha=1.0)
}
)";

int main()
{
    // --- 1. 初始化 GLFW ---
    // glfw: 初始化库
    if (!glfwInit())
    {
        std::cout << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    // glfw: 配置 OpenGL 版本和上下文类型 (核心模式)
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // --- 2. 创建窗口 (以及 OpenGL 上下文) ---
    // glfw: 创建一个窗口对象
    GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL Triangle Example", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate(); // 如果创建失败，需要终止 GLFW
        return -1;
    }
    // glfw: 将窗口的上下文设置为当前线程的主上下文
    glfwMakeContextCurrent(window);

    // --- 3. 加载 OpenGL 函数指针 (例如使用 GLAD) ---
    // glad: 加载 OpenGL 所需的所有函数指针。必须在创建 OpenGL 上下文后调用。
    // if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) // GLAD 方式
    // {
    //     std::cout << "Failed to initialize GLAD" << std::endl;
    //     return -1;
    // }
    // 或者 GLEW 方式:
    // if (glewInit() != GLEW_OK)
    // {
    //     std::cout << "Failed to initialize GLEW" << std::endl;
    //     return -1;
    // }

    // --- 4. 编译着色器 ---
    // 顶点着色器
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER); // 创建一个顶点着色器对象
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL); // 将源码附加到着色器对象
    glCompileShader(vertexShader); // 编译着色器

    // 检查编译错误
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // 片段着色器
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER); // 创建一个片段着色器对象
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL); // 将源码附加到着色器对象
    glCompileShader(fragmentShader); // 编译着色器

    // 检查编译错误
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // --- 5. 创建着色器程序 (Shader Program) ---
    unsigned int shaderProgram = glCreateProgram(); // 创建一个着色器程序对象
    glAttachShader(shaderProgram, vertexShader); // 将顶点着色器附加到程序
    glAttachShader(shaderProgram, fragmentShader); // 将片段着色器附加到程序
    glLinkProgram(shaderProgram); // 链接着色器程序

    // 检查链接错误
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    // 着色器对象在链接完成后即可删除，因为它们已经被复制到程序对象中了
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // --- 6. 定义顶点数据和缓冲 ---
    // 定义三角形的三个顶点坐标 (x, y, z)
    float vertices[] = {
         0.0f,  0.5f, 0.0f,  // Top
        -0.5f, -0.5f, 0.0f,  // Bottom Left
         0.5f, -0.5f, 0.0f   // Bottom Right
    };

    // 创建顶点数组对象 (VAO) 和顶点缓冲对象 (VBO)
    unsigned int VAO, VBO;
    glGenVertexArrays(1, &VAO); // 生成一个 VAO 的 ID
    glGenBuffers(1, &VBO);      // 生成一个 VBO 的 ID

    // 绑定 VAO (之后的操作会作用于这个 VAO)
    glBindVertexArray(VAO);

    // 绑定 VBO (之后的操作会作用于这个 VBO)
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // 将顶点数据复制到 VBO 中
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // 设置顶点属性指针，告诉 OpenGL 如何解析顶点数据
    // layout(location = 0) 的 aPos 属性
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0); // 启用第 0 个顶点属性

    // 解绑 VBO (可选，但推荐)
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    // 解绑 VAO (可选，但推荐)
    glBindVertexArray(0);

    // --- 7. 渲染循环 ---
    while (!glfwWindowShouldClose(window)) // 当窗口未被要求关闭时
    {
        // 处理输入事件 (例如 ESC 键退出)
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);

        // --- 渲染指令 ---
        // 设置清空屏幕所用的颜色 (这里是深蓝色)
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        // 清空颜色缓冲区
        glClear(GL_COLOR_BUFFER_BIT);

        // 使用我们的着色器程序
        glUseProgram(shaderProgram);
        // 绑定我们准备好的顶点数组对象
        glBindVertexArray(VAO);
        // 执行绘制调用，绘制一个由 3 个顶点组成的图元 (在这里是三角形)
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // glfw: 交换前后缓冲区 (双缓冲机制)
        glfwSwapBuffers(window);
        // glfw: 拉取事件 (例如键盘、鼠标输入)
        glfwPollEvents();
    }

    // --- 8. 清理资源 ---
    // 删除 VAO 和 VBO
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    // 删除着色器程序
    glDeleteProgram(shaderProgram);

    // glfw: 终止 GLFW，清理资源
    glfwTerminate();
    return 0;
}