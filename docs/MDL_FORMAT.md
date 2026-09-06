# WC3 MDX/MDL 模型格式实现文档

## 概述

本文档描述了在 warden 项目中实现的 WC3 MDX/MDL 模型文件解析系统。

## 文件结构

```
Source/Engine/Source/Anim/
├── MdlData.h           # MDL 格式数据结构定义
├── MdlKeyTrack.h       # 动画轨道模板和插值函数
├── MdlBinReader.h/cpp  # MDX 二进制格式读取器
├── MdlInterp.h/cpp     # 动画插值系统
├── CMdlModel.h/cpp     # MDL 模型类
├── MdlRender.h/cpp     # MDL 渲染辅助类

Source/Engine/Source/Frame/
├── CModelFrame.h/cpp   # 更新: 支持 MDL 模型

Source/Engine/Source/Model/
├── ModelCreate.h/cpp   # 更新: MDL 模型创建工厂

tests/Anim/
└── TestMdlData.cpp     # 单元测试
```

## MDX 文件格式

### 文件签名
- MDLX (0x584C444D) - 二进制格式
- MDL (0x204C444D) - 文本格式

### Chunk 结构
每个 chunk 包含:
- Tag (4 bytes) - chunk 标识符
- Size (4 bytes) - chunk 大小 (包含头部)
- Data (Size - 8 bytes) - chunk 数据

### 主要 Chunk

| Chunk | Tag | 结构体 | 说明 |
|-------|-----|--------|------|
| MDLX | - | MDLHEADERSECTION | 文件头 |
| MDL* | - | MDLMODELSECTION | 模型信息 |
| SEQS | 0x53455153 | MDLSEQUENCESSECTION | 动画序列 |
| GLBS | 0x534F4C47 | MDLGLOBALSEQSECTION | 全局序列 |
| SNDS | 0x53444E53 | MDLSOUNDSECTION | 声音 |
| MATS | 0x5354414D | MDLMATERIALSECTION | 材质 |
| TEXS | 0x53584554 | MDLTEXTURESECTION | 纹理 |
| TEXA | 0x41584554 | MDLTEXANIMSECTION | 纹理动画 |
| GEOS | 0x534F4547 | MDLGEOSETSECTION | 几何体 |
| GEOA | 0x414F4547 | MDLGEOSETANIMSECTION | 几何体动画 |
| BONE | 0x454E4F42 | MDLBONESECTION | 骨骼 |
| LITE | 0x4554494C | MDLLIGHTSECTION | 灯光 |
| HELP | 0x4C504548 | MDLGENOBJECT | 辅助对象 |
| ATCH | 0x48435441 | MDLATTACHMENTSECTION | 附件 |
| PREM | 0x4D455250 | MDLPARTICLEEMITTER | 粒子发射器 |
| CAMS | 0x534D4143 | MDLCAMERASECTION | 相机 |
| EVTS | 0x53545645 | MDLEVENTSECTION | 事件 |
| PRE2 | 0x32455250 | MDLPARTICLEEMITTER2 | 粒子发射器2 |
| CLID | 0x44494C43 | MDLCOLLISIONSHAPE | 碰撞形状 |
| RIBB | 0x42424952 | MDLRIBBONEMITTER | 丝带发射器 |

## 关键帧类型

| 类型 | 结构体 | 说明 |
|------|--------|------|
| 位移 | MDLTRANSKEYFRAME | float x, y, z + uint32 time |
| 旋转 | MDLROTKEYFRAME | float x, y, z, w (四元数) + uint32 time |
| 缩放 | MDLSCALEKEYFRAME | float x, y, z + uint32 time |
| 透明度 | MDLALPHAKEYFRAME | float alpha + uint32 time |
| 颜色 | MDLCOLORKEYFRAME | uint8 r, g, b + uint32 time |
| 强度 | MDLINTENSITYKEYFRAME | float intensity + uint32 time |
| 衰减 | MDLATTENKEYFRAME | float attenuation + uint32 time |
| 浮点属性 | MDLFLOATPROPKEYFRAME | float value + uint32 time |
| 翻页 | MDLFLIPBOOKKEY | uint32 value + uint32 time |
| 整数 | MDLINTKEY | uint32 value + uint32 time |
| 事件 | MDLEVENTKEY | uint32 value + uint32 time |
| 声音 | MDLSOUNDKEYFRAME | uint32 value + uint32 time |

## 插值类型

```cpp
enum MDLTRACKTYPE {
    MDL_TRACKTYPE_NONE = 0,      // 无插值
    MDL_TRACKTYPE_LINEAR = 1,    // 线性插值
    MDL_TRACKTYPE_HERMITE = 2,   // Hermite 插值
    MDL_TRACKTYPE_BEZIER = 3     // Bezier 插值
};
```

## 使用示例

### 加载 MDL 模型
```cpp
#include "Anim/CMdlModel.h"
#include "Base/Status.h"

CMdlModel model;
Status status;

if (model.Load("Units/Human/Footman/Footman.mdx", status)) {
    // 模型加载成功
    uint32_t boneCount = model.GetBoneCount();
    uint32_t animCount = model.GetSequenceCount();
}
```

### 动画播放
```cpp
model.SetAnimation(0);  // 设置动画索引
model.SetLoop(true);    // 循环播放
model.Update(0.016f);   // 更新 16ms
```

### 渲染
```cpp
#include "Anim/MdlRender.h"

MdlRender renderer;
renderer.Initialize(model);

// 获取渲染数据
const auto& vertices = renderer.GetVertices();
const auto& indices = renderer.GetIndices();
const auto& batches = renderer.GetBatches();
```

### 在 CModelFrame 中使用
```cpp
CModelFrame frame;
frame.SetModelFile("Units/Human/Footman/Footman.mdx");
frame.SetPlaying(true);
frame.SetAnimation(0);
frame.Update(0.016f);
```

## IDA 反编译参考

### 关键函数地址
| 函数 | 地址 | 说明 |
|------|------|------|
| MDLHANDLER::MDLHANDLER | 0x9DD4D8 | 处理器构造 |
| MDLDATA::MDLDATA | 0x7CE4F8 | 数据构造 |
| MDLBASE::MDLBASE | 0x7CE22C | 基类构造 |
| MDLBASE::~MDLBASE | 0x7CE22C | 基类析构 |
| ReadBinFloatKeyFrames<TRANS> | 0xA292DC | 位移关键帧读取 |
| ReadBinFloatKeyFrames<ROT> | 0xA29528 | 旋转关键帧读取 |
| ReadBinFloatKeyFrames<SCALE> | 0xA290AC | 缩放关键帧读取 |

### 结构体偏移 (MDLBASE 内)
| 偏移 (DWORD) | 结构体 | Chunk |
|--------------|--------|-------|
| 0 | MDLHEADERSECTION | MDLX |
| 520 | MDLMODELSECTION | MDL* |
| 940 | MDLSEQUENCESSECTION[16] | SEQS |
| 3192 | MDLGLOBALSEQSECTION[8] | GLBS |
| 3520 | MDLMATERIALSECTION[8] | MATS |
| 4844 | MDLTEXTURESECTION[8] | TEXS |
| 7084 | MDLGEOSETSECTION[8] | GEOS |
| 9744 | MDLBONESECTION[16] | BONE |
| 12508 | MDLLIGHTSECTION[1] | LITE |
| 13272 | MDLATTACHMENTSECTION[8] | ATCH |
| 17104 | MDLPARTICLEEMITTER[1] | PREM |
| 17732 | MDLCAMERASECTION[1] | CAMS |
| 17956 | MDLEVENTSECTION[8] | EVTS |
| 21596 | MDLCOLLISIONSHAPE[2] | CLID |
| 21992 | MDLRIBBONEMITTER[1] | RIBB |

## 待完成工作

1. **PRE2 粒子发射器** - 结构体需要完整实现
2. **纹理动画** - GetTextureTransform() 待实现
3. **Hermite 插值** - 当前简化为线性插值
4. **内存管理** - 需要智能指针优化
5. **异步加载** - 支持异步加载大文件
6. **LOD 支持** - 多细节层次

## 参考资料

- Magos 规范: http://magos.thejefffiles.com/War3ModelEditor/
- Nub 规范: http://www.wc3campaigns.net/tools/specs/NubMdxFormat.txt
- KMK 规范: http://kmkdesign.8m.com/downloads/
- IDA 数据库: war3_mac_binary/Warcraft III_max1.i64
