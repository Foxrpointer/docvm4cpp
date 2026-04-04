// 渲染函数
#include "sea-ocean-render.hpp"

void render_prepare()
{
    /// 顶点输入，逆时针输入。XYZRGB
    float vertecs[] = {
    -0.5f, -0.5f, 0.0f, -0.5f, -0.5f, 0.0f,
    0.5f, -0.5f, 0.0f, 0.5f, -0.5f, 0.0f,
    0.0f,  0.5f, 0.0f, 0.0f,  0.5f, 0.0f
    };

    // 创建VBO。1生成2绑定3赋值
    GLuint posotion_and_color_VBO;
    glGenBuffers(1, &posotion_and_color_VBO);
    glBindBuffer(GL_ARRAY_BUFFER, posotion_and_color_VBO);
    // 把顶点数据上传到显存
    // GL_STATIC_DRAW表示数据只上传一次，多次绘制
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertecs), vertecs, GL_STATIC_DRAW);

    // 创建和绑定VAO。1生成2绑定3启用槽位4赋值
    GLuint VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, posotion_and_color_VBO);
    // 位置的VAO属性
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(
        0,  // 指定0号位置
        3,  // 一个属性3个单位
        GL_FLOAT,   // 那3个单位是float
        GL_FALSE,   // 不归一化
        3*sizeof(float),    // 步长12bytes
        (void* )0   // 无偏移量
    );
    // 颜色的VAO属性
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(
        1,  // 指定1号位置
        3,  // 一个属性3个单位
        GL_FLOAT,   // 那3个单位是float
        GL_FALSE,   // 不归一化
        3*sizeof(float),    // 步长12bytes
        (void* )(3*sizeof(float))   // 偏移量为3个float
    );
}

void render_func()
{
    
}