# Agile Module

Agile 是暴雪魔兽世界客户端的游戏对象属性/代理系统，提供了一套完整的 Field/Listener/Modifier 架构，用于管理游戏实体的动态属性。

## 概述

本模块逆向自 WoW 客户端二进制，实现了游戏引擎中实体属性的声明、监听和修改机制。该系统广泛用于单位属性管理、技能效果、Buff/Debuff 系统等。

## 核心架构

```
TRefCnt (引用计数基类)
  │
  ├── CPresenceRef (存在引用)
  │     └── CAgentField (代理字段基类)
  │           ├── CRelation (关系基类)
  │           │     ├── CListener (监听器基类)
  │           │     │     ├── FloatListener
  │           │     │     ├── IntegerListener
  │           │     │     ├── PositionListener
  │           │     │     ├── RangeListener
  │           │     │     └── AgentRefListener
  │           │     └── CModifier (修改器基类)
  │           │           ├── FloatModifier
  │           │           ├── IntegerModifier
  │           │           ├── MovementModifier
  │           │           └── PositionModifier
  │           ├── Float (浮点属性)
  │           ├── Integer (整数属性)
  │           ├── Position (位置属性)
  │           │     └── SmartPosition
  │           ├── ProjectilePosition (投射物位置)
  │           └── AgentRef (代理引用)
  │
  ├── CAgentTimer (代理定时器)
  ├── CEventTimer (事件定时器)
  └── CObserver (观察者)
```

## 主要类型

### 属性类型

| 类型 | 说明 | 用途 |
|------|------|------|
| `Float` | 浮点属性 | 生命值、法力值、移动速度等 |
| `Integer` | 整数属性 | 等级、伤害值、冷却时间等 |
| `Position` | 位置属性 | 单位坐标、目标位置等 |
| `SmartPosition` | 智能位置 | 自动更新的位置 |
| `ProjectilePosition` | 投射物位置 | 火球、箭矢等投射物 |
| `AgentRef` | 代理引用 | 指向其他代理的引用 |

### 监听器类型

| 类型 | 说明 | 用途 |
|------|------|------|
| `CListener` | 监听器基类 | 属性变化通知 |
| `FloatListener` | 浮点监听器 | 监听浮点属性变化 |
| `IntegerListener` | 整数监听器 | 监听整数属性变化 |
| `PositionListener` | 位置监听器 | 监听位置变化 |
| `RangeListener` | 范围监听器 | 监听范围内的实体 |
| `AgentRefListener` | 代理引用监听器 | 监听引用变化 |

### 修改器类型

| 类型 | 说明 | 用途 |
|------|------|------|
| `CModifier` | 修改器基类 | 属性修改 |
| `FloatModifier` | 浮点修改器 | 修改浮点属性值 |
| `IntegerModifier` | 整数修改器 | 修改整数属性值 |
| `MovementModifier` | 移动修改器 | 修改移动速度/方向 |
| `PositionModifier` | 位置修改器 | 修改位置属性 |

### 基础设施

| 类型 | 说明 |
|------|------|
| `CStatus` | 状态/错误管理系统 |
| `CStringManager` | 字符串驻留管理器 |
| `CStringMemory` | 字符串内存分配器 |
| `CStringRep` | 引用计数字符串 |
| `CHandleObject` | 句柄对象基类 |
| `CAgentTimer` | 代理定时器 |
| `CEventTimer` | 事件定时器 |

## 使用示例

### Float 属性

```cpp
// 创建浮点属性
Float health(100.0f);

// 读取值
float hp = health.GetValue();  // 100.0f

// 修改值
health += Float(10.0f);  // hp = 110.0f
health -= Float(5.0f);   // hp = 105.0f
health *= 2.0f;          // hp = 210.0f

// 比较
if (health > Float(50.0f)) {
    // 生命值高于 50
}

// 隐式转换
float val = health;  // 210.0f
```

### Integer 属性

```cpp
// 创建整数属性
Integer level(60);
Integer damage(100);

// 声明属性绑定
level.Declare(agentId, fieldId, 0, 0, 0, 0);

// 修改值
level += 1;        // level = 61
damage -= 10;      // damage = 90

// 递增/递减
++level;           // level = 62
level++;           // level = 63

// 隐式转换
int lvl = level;   // 63
```

### Position 属性

```cpp
// 创建位置
Position origin(0.0f, 0.0f, 0.0f);
Position target(10.0f, 10.0f, 0.0f);

// 获取距离
float dist = origin.DistanceTo(target);  // 14.14...

// 获取方向
NTempest::C3Vector dir = origin.DirectionTo(target);

// 移动到目标
origin.MoveTowards(target, 5.0f);  // 移动 5 个单位

// 检查朝向
bool facing = Position::IsFacing(source, target, reference);

// 坐标访问
float x = origin.GetX();
float y = origin.GetY();
float z = origin.GetZ();
```

### CStatus 状态管理

```cpp
// 创建状态对象
CStatus status;

// 添加状态消息
status.Add(STATUS_INFO, "初始化完成");
status.Add(STATUS_WARNING, "资源不足: %d", remaining);
status.Add(STATUS_ERROR, "加载失败: %s", filename);

// 检查状态
if (!status.IsEmpty()) {
    STATUS_TYPE highest = status.GetHighestSeverity();
    if (highest >= STATUS_ERROR) {
        // 处理错误
    }
}

// 合并状态
CStatus otherStatus;
otherStatus.Add(STATUS_INFO, "其他消息");
status.Add(otherStatus);

// 清空
status.Clear();
```

### 继承体系使用

```cpp
// 自定义监听器
class HealthListener : public FloatListener {
public:
    void OnChanged(float oldValue, float newValue) override {
        if (newValue <= 0.0f) {
            // 单位死亡
        }
    }
};

// 自定义修改器
class PoisonModifier : public FloatModifier {
public:
    void Apply(Float &target) override {
        target -= Float(m_damagePerTick);
    }
};
```

## 文件结构

```
Agile/
├── CAgentField.h/.cpp         # 代理字段基类
├── CAgentFieldMini.h/.cpp     # 轻量级代理字段
├── CAgentTimer.h/.cpp         # 代理定时器
├── CEventTimer.h/.cpp         # 事件定时器
├── CListener.h/.cpp           # 监听器基类
├── CModifier.h/.cpp           # 修改器基类
├── CObserver.h/.cpp           # 观察者基类
├── CPresenceRef.h/.cpp        # 存在引用
├── CRelation.h/.cpp           # 关系基类
├── CStatus.h/.cpp             # 状态管理
├── CStringManager.h/.cpp      # 字符串管理器
├── CStringMemory.h/.cpp       # 字符串内存
├── CStringRep.h               # 引用计数字符串
├── CHandleObject.h            # 句柄对象
├── Float.h/.cpp               # 浮点属性
├── FloatListener.h/.cpp       # 浮点监听器
├── FloatModifier.h/.cpp       # 浮点修改器
├── FloatProp.h                # 浮点属性 (空)
├── Integer.h/.cpp             # 整数属性
├── IntegerListener.h/.cpp     # 整数监听器
├── IntegerModifier.h/.cpp     # 整数修改器
├── Position.h/.cpp            # 位置属性
├── PositionListener.h         # 位置监听器
├── PositionModifier.h         # 位置修改器
├── ProjectilePosition.h/.cpp  # 投射物位置
├── RangeListener.h/.cpp       # 范围监听器
├── SmartPosition.h/.cpp       # 智能位置
├── AgentRef.h/.cpp            # 代理引用
├── AgentRefListener.h/.cpp    # 代理引用监听器
├── AgentRefMini.h             # 轻量级代理引用
├── MovementModifier.h/.cpp    # 移动修改器
├── AGILE_TYPE_DATA.h          # 类型数据
├── AgileAgentQuery.h          # 代理查询
├── ARRAY_2D_UNSIGNED.h        # 二维数组
├── BigBuffer.h                # 大缓冲区
├── BigData.h                  # 大数据
├── BigNum.h                   # 大数字
├── BigStack.h                 # 大栈
├── CAngle.h                   # 角度
├── CBitInput.h                # 位输入
├── CDBDatabase.h              # 数据库
├── CHuffman.h                 # Huffman 编码
├── CHuffmanDecoder.h          # Huffman 解码器
├── CHuffmanEncoder.h          # Huffman 编码器
├── Crypt.h                    # 加密
├── CSLKDatabase.h             # SLK 数据库
├── HUFFNODE.h                 # Huffman 节点
├── ProcessSLK.h               # SLK 处理
├── RegistryKey.h              # 注册表键
├── SLK.h                      # SLK 文件
├── slkRow.h                   # SLK 行
├── README.md                  # 本文件
└── tests/                     # 单元测试
    ├── TestCStatus.cpp
    ├── TestFloat.cpp
    ├── TestInteger.cpp
    └── TestPosition.cpp
```

## 测试

单元测试位于 `tests/Agile/` 目录，使用 Google Test 框架。

```bash
# 构建测试
cmake --build cmake-build-debug --target agile_tests

# 运行测试
cd cmake-build-debug
./agile_tests
```

### 测试覆盖

| 测试套件 | 测试数量 | 覆盖内容 |
|----------|----------|----------|
| CStatusTest | 10 | 状态管理、消息添加、严重级别 |
| FloatTest | 16 | 浮点属性、运算符、比较 |
| IntegerTest | 21 | 整数属性、声明、运算符、递增递减 |
| PositionTest | 19 | 位置属性、距离、方向、移动、朝向 |
| **总计** | **66** | |

## 架构设计模式

### Field/Listener/Modifier 模式

```
┌─────────────────────────────────────────────────────────────┐
│                        CAgentField                          │
│  (存储属性值)                                                │
└─────────────────────────────────────────────────────────────┘
         ▲                    ▲                    ▲
         │                    │                    │
    ┌────┴────┐          ┌────┴────┐          ┌────┴────┐
    │ CListener│          │CModifier│          │  Float  │
    │ (监听变化)│          │ (修改值) │          │(具体属性)│
    └─────────┘          └─────────┘          └─────────┘
         │                    │
         ▼                    ▼
    ┌─────────┐          ┌─────────┐
    │OnChanged│          │ Apply   │
    │ 通知回调 │          │ 执行修改 │
    └─────────┘          └─────────┘
```

### 数据流

```
用户操作 → CModifier::Apply() → CAgentField::SetValue()
                                        ↓
                              CListener::OnChanged() → UI 更新/效果触发
```

## 注意事项

1. **IDA 标记** - 代码中保留 `SubXXXXXX()` 等 IDA 分析标记
2. **继承层次** - 大部分类是空壳，仅建立类型关系
3. **CStringManager** - 依赖 Storm 库的内存管理函数
4. **模板类** - `CAgentPtr<T>` 是模板代理指针，用于安全管理代理对象

## 相关模块

- **NTempest** - 数学库，提供向量、矩阵等基础类型
- **Storm** - 系统抽象层，提供内存、线程、文件等底层能力
- **Common** - 通用数据结构（TSList, TSHashTable 等）
