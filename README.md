# ImageProcessDataFlow

一个用 **Qt 5.15 + C++** 实现的轻量级图像处理数据流框架示例，风格参考 Orange 的节点式工作流：

- 左侧：节点库 + Pipeline 列表
- 右侧：节点流图预览 + 输出图像预览
- 支持加载图片并按 pipeline 顺序执行处理节点

## 当前内置节点

- `Grayscale`：灰度化
- `Invert`：反色
- `Blur3x3`：3x3 均值模糊

## 构建方式

依赖：请先安装 **Qt 5.15**（包含 Widgets 模块）和 CMake。


```bash
cmake -S . -B build
cmake --build build
```

运行：

```bash
./build/ImageProcessDataFlow
```

> 说明：这是一个可扩展骨架，后续可以继续增加：
> - 节点参数编辑器（如卷积核、阈值）
> - 多输入/多输出端口
> - 节点连线约束与循环检测
> - 序列化（保存/加载 workflow）
