## 一些关于语法的伪代码

### v0.0.1
```c++
#include "docvm.h"
#include "basebtn.h"//假设是一个控件库

int main()
{
    // new vm 对象
    docvm::VM mechine = new docvm::vm();
    mechine
    .setGraphisEngine(gl)//gl是个enum
    .is_GC(false)//是否自动为成员管理内存
    .debug(true);

    // 引入控件库
    ctrl = basebtn::init();
    if (!ctrl) return -1;

    // 导出对象
    docvm::Viewport* view;
    mechine.export_viewport(view);

    // 设置属性
    view
    ->setViewportSize(800, 600);

    // canva
    view->canva
    ->button(100, 100)
    ->text("你好")
    ->save();

    mechine.init(); // 卡在这里
    mechine.terminate();

    return 0;
}
```