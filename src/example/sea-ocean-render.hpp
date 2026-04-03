// 单例类
#pragma once
#include "glad/glad.h"

void render_func();

// 有 7 个渲染阶段
// 1. 顶点数据
// 2. 三维变换
// 3. 图元装配
// 4. 剪裁切除
// 5. 光栅化
// 6. 片元着色
// 7. 混合测试