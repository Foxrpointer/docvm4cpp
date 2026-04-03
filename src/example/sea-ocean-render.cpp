// 渲染函数
#include "sea-ocean-render.hpp"

void render_func()
{
    /// 顶点输入
    /// 逆时针定义顶点
    /// 渲染的时候逆时针渲染。可以被判断为正面
    /// 背面会被OpenGL当成看不到的面剔除...
    float vertices[] = {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f
    };

    /// 生成 VBO 对象 Vertex Buffer Object
    /// n是数量，buffers是缓冲区的句柄
    /// VBO是句柄，不是指针
    unsigned int VBO;
    glGenBuffers(1, &VBO);

    /// 绑定VBO到当前活跃的ARRAY_BUFFER
    /// 后续所有 gl*Buffer* 操作默认作用于该 VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    /// 把顶点数据上传到显存
    /// GL_STATIC_DRAW表示数据只上传一次，多次绘制
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    /// GL_ARRAY_BUFFER 必须和VBO一样 ↑

    glVertexAttribPointer(
    0,                  // attribute 0（对应 layout(location=0)）
    3,                  // 每个顶点 3 个分量 (x,y,z)
    GL_FLOAT,           // 数据类型
    GL_FALSE,           // 不归一化
    3 * sizeof(float),  // 步长（stride）= 12 字节
    (void*)0            // 起始偏移
    );
    glEnableVertexAttribArray(0);  // 必须启用！默认禁用
    /// 顶点着色器

}