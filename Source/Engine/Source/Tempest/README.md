# NTempest Math Library

NTempest 是暴雪魔兽世界客户端的数学库命名空间，提供游戏引擎所需的基础数学类型和运算。

## 概述

本库逆向自 WoW 客户端二进制，包含向量、矩阵、四元数、平面、矩形等核心数学类型，广泛用于地形渲染、骨骼动画、物理碰撞、UI 布局等系统。

## 类型一览

### 向量类型

| 类型 | 说明 | 成员 |
|------|------|------|
| `C2Vector` | 2D 浮点向量 | `float x, y` |
| `C3Vector` | 3D 浮点向量 | `float x, y, z` |
| `C4Vector` | 4D 浮点向量 | `float x, y, z, w` |
| `C2iVector` | 2D 整数向量 | `int x, y` |
| `C2uVector` | 2D 软浮点向量 | `unsigned int x, y` |
| `C3uVector` | 3D 软浮点向量 | `unsigned int x, y, z` |
| `CImVector` | ARGB 颜色向量 | `union { struct {uint8_t b,g,r,a}; uint32_t value; }` |

### 矩阵类型

| 类型 | 说明 | 用途 |
|------|------|------|
| `C33Matrix` | 3×3 矩阵 | 旋转、缩放 |
| `C34Matrix` | 3×4 矩阵 | 骨骼变换 |
| `C44Matrix` | 4×4 矩阵 | 完整变换（平移、旋转、缩放、投影） |
| `C22uMatrix` | 2×2 软浮点矩阵 | 特殊用途 |

### 其他类型

| 类型 | 说明 |
|------|------|
| `C4Quaternion` | 四元数，用于平滑旋转插值 |
| `C4Plane` | 平面（法线 + 距离），用于碰撞检测 |
| `CRect` | 矩形（minX, minY, maxX, maxY），用于 UI 和碰撞 |
| `CAaSphere` | 轴对齐包围球 |

### 工具类

| 类型 | 说明 |
|------|------|
| `CMath` | 数学常量和工具函数（三角函数、插值、钳制等） |
| `CMathi` | 底层数学实现（软浮点、定点数） |
| `CRandom` | 随机数生成器 |

## 主要功能

### C2Vector - 2D 向量

```cpp
C2Vector v(3.0f, 4.0f);
float mag = v.Mag();           // 长度 = 5.0
float dot = v.Dot(other);      // 点积
C2Vector sum = v + other;      // 加法
v.Normalize();                 // 归一化
float angle = v.AxisAngle();   // 转换为角度
```

### C3Vector - 3D 向量

```cpp
C3Vector a(1, 0, 0), b(0, 1, 0);
float dot = a.Dot(b);          // 点积 = 0
C3Vector cross = a.Cross(b);   // 叉积 = (0, 0, 1)
a.Normalize();                 // 归一化
C3Vector proj;
proj.ProjectionOnPlane(point, normal);  // 平面投影
```

### C4Quaternion - 四元数

```cpp
// 单位四元数（无旋转）
C4Quaternion identity;

// 从轴角创建
C4Quaternion q = C4Quaternion::Slerp(0.5f, q1, q2);  // 球面插值
C4Quaternion nlerp = C4Quaternion::Nlerp(0.5f, q1, q2);  // 线性插值

// 转换为旋转矩阵
C33Matrix rot = q.ToMatrix();
```

### C44Matrix - 4×4 矩阵

```cpp
// 单位矩阵
C44Matrix m = C44Matrix::Identity();

// 旋转
C44Matrix rotZ = C44Matrix::RotationAroundZ(3.14159f / 2.0f);  // Z轴90度
C44Matrix rotX = C44Matrix::RotationAroundX(angle);

// 视图和投影
C44Matrix view = C44Matrix::LookAt(eye, target, up);
C44Matrix proj = C44Matrix::Perspective(fov, aspect, near, far);

// 变换
m.Translate(offset);
m.Scale(scale);
```

### C4Plane - 平面

```cpp
// 从三个点创建
C4Plane plane(p1, p2, p3);

// 计算点到平面距离
float dist = plane.Distance(point);

// 判断点在哪一侧
float d = plane.Dot(point);  // 正=前方，负=后方，0=平面上
```

### CRect - 矩形

```cpp
CRect r(0, 0, 100, 100);

// 包含检测
bool inside = r.Contains(C2Vector(50, 50));  // true
bool contains = r.Contains(smallRect);        // 包含另一个矩形

// 集合运算
CRect intersection = CRect::Intersection(r1, r2);
CRect u = CRect::Union(r1, r2);

// 扩展
r.Expand(C2Vector(200, 200));  // 扩展以包含点
```

### CMath - 数学工具

```cpp
// 三角函数
float s = CMath::sin(angle);
float c = CMath::cos(angle);

// 工具函数
float clamped = CMath::Clamp(value, 0.0f, 1.0f);
float lerped = CMath::Lerp(a, b, t);
float rad = CMath::DegToRad(180.0f);

// 舍入
int32_t rounded = CMath::fint_n(1.5f);  // 2
```

## 软浮点类型

`C2uVector` 和 `C3uVector` 使用 `unsigned int` 存储软浮点数（SoftFloat），这是暴雪为了在不支持 FPU 的硬件上运行而设计的。这些类型提供：

- `Mag()` - 长度
- `SquaredMag()` - 平方长度
- `Dot()` - 点积
- `Normalize()` - 归一化
- `Scale()` - 缩放

## 文件结构

```
NTempest/
├── C2Vector.h/.cpp      # 2D 向量
├── C3Vector.h/.cpp      # 3D 向量
├── C4Vector.h/.cpp      # 4D 向量
├── C2iVector.h/.cpp     # 2D 整数向量
├── C2uVector.h          # 2D 软浮点向量
├── C3uVector.h          # 3D 软浮点向量
├── CImVector.h          # ARGB 颜色向量
├── C33Matrix.h/.cpp     # 3×3 矩阵
├── C33uMatrix.h         # 3×3 软浮点矩阵
├── C34Matrix.h          # 3×4 矩阵
├── C44Matrix.h/.cpp     # 4×4 矩阵
├── C22uMatrix.h/.cpp    # 2×2 软浮点矩阵
├── C4Quaternion.h/.cpp  # 四元数
├── C4Plane.h/.cpp       # 平面
├── CRect.h/.cpp         # 矩形
├── CiRect.h/.cpp        # 整数矩形
├── CuRect.h             # 软浮点矩形
├── CMath.h              # 数学工具
├── CMathi.h/.cpp        # 底层数学实现
├── CuMath.h             # 软浮点数学
├── CAaBox.h             # 轴对齐包围盒
├── CAaSphere.h/.cpp     # 轴对齐包围球
├── CBoundingBox.h       # 包围盒
├── CRange.h             # 范围
├── CiRange.h            # 整数范围
├── CuRange.h            # 软浮点范围
├── CRandom.h            # 随机数
├── CRandSeed.h          # 随机种子
├── CRndSeed.h           # 另一个随机种子
├── CLinkList.h          # 链表
├── CLinkedNode.h        # 链表节点
├── CLinkedList.h        # 链表实现
├── CLinkedNodeCache.h   # 节点缓存
├── CDynTable.h          # 动态表
├── CDynParms.h          # 动态参数
├── CPriorityQ.h         # 优先队列
├── CMemBlock.h          # 内存块
├── CMemBlockT.h         # 模板内存块
├── CEntity.h            # 实体基类
├── CPresence.h          # 存在基类
├── CPresenceReg.h       # 存在注册
├── CPresenceSys.h       # 存在系统
├── CPresenceSysTagged.h # 带标签的存在系统
├── CPresenceTagged.h    # 带标签的存在
├── CPrRgEntry.h         # 存在注册条目
├── CTargetPrTg.h        # 目标存在
├── CSyncData.h          # 同步数据
├── CThreadData.h        # 线程数据
├── TInstanceCache.h     # 实例缓存
└── README.md            # 本文件
```

## 测试

单元测试位于 `tests/NTempest/` 目录，使用 Google Test 框架。

```bash
# 构建测试
cmake --build cmake-build-debug --target ntempest_tests

# 运行测试
cd cmake-build-debug
./ntempest_tests
```

## 注意事项

1. **IDA 标记** - 代码中保留 `SubXXXXXX()` 等 IDA 分析标记，用于对照原始二进制
2. **结构体偏移** - 注释中的 offset 是 IDA 分析结果，修改结构体时需验证
3. **软浮点** - `C2uVector`/`C3uVector` 使用软件浮点运算，性能较低但兼容性好
4. **命名风格** - 遵循暴雪原始代码风格：`C` 前缀 + PascalCase
