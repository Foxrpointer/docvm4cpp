成功的 GL Render 示例

```cpp
// main.cpp
// qwen的render-example代码
// 我需要细细品味
#include <glad/glad.h> // 必须在GLFW之前包含
#include <GLFW/glfw3.h>
#include <iostream>

// 错误回调函数 (用于GLFW)
void glfwErrorCallback(int error, const char* description) {
    std::cerr << "GLFW Error " << error << ": " << description << std::endl;
}

// OpenGL错误检查宏
#define GLCall(x) do { \
    x; \
    GLenum err = glGetError(); \
    if(err != GL_NO_ERROR) { \
        std::cerr << "OpenGL Error: " << err << " at line " << __LINE__ << " in " << __FILE__ << std::endl; \
        exit(EXIT_FAILURE); \
    } \
} while(0)

const char* vertexShaderSource = R"(
#version 330 core
layout (location = 0) in vec3 aPos;
void main() {
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
}
)";

const char* fragmentShaderSource = R"(
#version 330 core
out vec4 FragColor;
void main() {
    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f); // 橙色
}
)";

unsigned int createShader(unsigned int type, const char* source) {
    unsigned int shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, NULL);
    glCompileShader(shader);

    int success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
        glDeleteShader(shader);
        return 0;
    }
    return shader;
}

unsigned int createProgram(unsigned int vertexShader, unsigned int fragmentShader) {
    unsigned int program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);

    int success;
    char infoLog[512];
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(program, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER_PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        glDeleteProgram(program);
        return 0;
    }
    return program;
}

int main() {
    // 1. 初始化GLFW
    glfwSetErrorCallback(glfwErrorCallback);
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    // 2. 配置GLFW
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // 3. 创建窗口
    GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL Window", NULL, NULL);
    if (window == NULL) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // 4. 初始化GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    float vertices[] = {
         0.5f,  0.5f, 0.0f,  // 右上角
         0.5f, -0.5f, 0.0f,  // 右下角
        -0.5f, -0.5f, 0.0f,  // 左下角
        -0.5f,  0.5f, 0.0f   // 左上角
    };
    unsigned int indices[] = { // 注意索引从0开始!
        0, 1, 3, // 第一个三角形
        1, 2, 3  // 第二个三角形
    };

    unsigned int VBO, VAO, EBO;
    GLCall(glGenVertexArrays(1, &VAO));
    GLCall(glGenBuffers(1, &VBO));
    GLCall(glGenBuffers(1, &EBO));

    GLCall(glBindVertexArray(VAO));

    GLCall(glBindBuffer(GL_ARRAY_BUFFER, VBO));
    GLCall(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW));

    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO));
    GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW));

    GLCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0));
    GLCall(glEnableVertexAttribArray(0));

    // 确保VAO被解除绑定
    glBindVertexArray(0); 

    unsigned int vertexShader = createShader(GL_VERTEX_SHADER, vertexShaderSource);
    if (!vertexShader) return -1;

    unsigned int fragmentShader = createShader(GL_FRAGMENT_SHADER, fragmentShaderSource);
    if (!fragmentShader) return -1;

    unsigned int shaderProgram = createProgram(vertexShader, fragmentShader);
    if (!shaderProgram) return -1;

    // 渲染循环
    while (!glfwWindowShouldClose(window)) {
        // 处理输入
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);

        // 渲染
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        GLCall(glUseProgram(shaderProgram)); // 使用着色器程序
        GLCall(glBindVertexArray(VAO));      // 绑定VAO
        GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0)); // 绘制两个三角形

        // 交换颜色缓冲
        glfwSwapBuffers(window);
        // 检查并触发事件
        glfwPollEvents();
    }

    // 清理资源
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(shaderProgram);

    glfwTerminate();
    return 0;
}
```