# MDL/MDX 解析器 TODO

> 最后更新: 2026-09-06
> 当前状态: MODL chunk 解析完成，其他 chunk 全部跳过

## 已完成

- [x] MDLX 文件签名验证
- [x] MODL chunk 解析 (模型名、包围盒、blendTime)
- [x] VERS chunk 跳过
- [x] CMdlModel 加载/释放/动画控制接口
- [x] MdlInterp 骨骼矩阵计算框架
- [x] MdlRender 渲染数据构建框架
- [x] ModelCreate 工厂 (.mdx/.mdl → CMdlModel)
- [x] CModelFrame MDL 模型集成
- [x] Footman.mdx 真实数据测试 (18 tests, all pass)
- [x] C44Matrix/CAaBox API 适配
- [x] MDLArray 内存释放 (ReleaseArray)

## 未完成 — 按优先级排列

### P0: 核心数据解析

#### 9. SEQS/GEOS/BONE/MATS/TEXS chunk 解析

当前状态: switch 中全部 `SkipChunk`，模型加载后无骨骼/几何体/动画数据。

**SEQS (动画序列)**
- chunk 格式: 无 count 前缀，数据直接是 `MDLSEQUENCESSECTION` 数组
- 问题: `sizeof(MDLSEQUENCESSECTION)` = 140, chunk size 1716, 1716/140 = 12.257 (非整数)
- 需要: 验证实际 struct 布局 (可能有 padding 或字段差异)
- Footman 预期: ~12 个动画序列 (Stand, Attack, Spell, Death 等)

**MATS/MTLS (材质)**
- chunk tag 实际是 `MTLS` (0x534C544D)，非 `MATS`
- 格式: 无 count 前缀，`sizeof(MDLMATERIALSECTION)` = 24
- 验证: chunk size 244, 244/24 = 10.16 (非整数)，需确认
- Footman 预期: ~10 个材质

**TEXS (纹理)**
- 格式: 无 count 前缀，`sizeof(MDLTEXTURESECTION)` = 264
- 验证: chunk size 804, 804/264 = 3.04 (非整数)，需确认
- Footman 预期: ~3 个纹理

**GEOS (几何体)**
- 格式: 复杂，每个 geoset 包含 6 个嵌套 MDLArray:
  - vertices (C3Vector[]), normals (C3Vector[]), textureCoords (C2Vector[])
  - triangles (uint16_t[]), matrixGroups (uint32_t[]), matrixIndices (uint8_t[])
- 需要: 逐个读取嵌套数组 (count + data)
- Footman 预期: ~11 个 geoset

**BONE (骨骼)**
- 格式: 复杂，每个 bone 包含:
  - 固定字段: name[80], nodeId, flags, parentBone, submeshId, unknown[2]
  - 3 个动画轨道 (translation/rotation/scale)，每个含:
    - interpolationType (uint32)
    - globalSequenceId (uint32)
    - keyCount (uint32)
    - keys[keyCount] (MDLTRANSKEYFRAME/MDLROTKEYFRAME/MDLSCALEKEYFRAME)
  - pivot (C3Vector)
- 问题: 首次尝试读取 count=96 导致 segfault，格式需进一步验证
- Footman 预期: ~18-30 个骨骼

### P1: 动画质量

#### 7. Hermite 插值

当前状态: `MdlGetTransValue`/`MdlGetScaleValue` 中 Hermite 分支注释写着 "简化版"，实际调用 `MdlLerp` (线性插值)。

```
// Hermite 插值 (简化版)
return MdlLerp(va, vb, ratio);  // ← 应该是 Hermite
```

需要:
- 实现 Hermite 样条插值 (需要 4 个控制点: 前一个、当前、下一个、后一个)
- WC3 大量动画使用 Hermite，直接影响动画平滑度
- 参考: WC3 MDX 格式规范中的 Hermite 插值公式

### P2: 次要功能

#### 1. PRE2 粒子发射器

当前状态: `MDLPARTICLEEMITTER2` 是 `uint32_t unknown[100]` 占位符。

需要:
- 研究 PRE2 chunk 的实际二进制格式
- 定义完整的粒子发射器结构体
- 实现 PRE2 chunk 解析

#### 2. 纹理动画 GetTextureTransform

当前状态: `MdlInterp::GetTextureTransform()` 直接返回 `C44Matrix()` (单位矩阵)。

需要:
- 读取 TEXA chunk 的纹理动画数据
- 实现纹理坐标变换矩阵计算
- 支持平移/旋转/缩放纹理动画

#### 4. 智能指针优化

当前状态: `CMdlModel` 使用 `new/delete`，`MDLArray` 使用原始指针偏移。

需要:
- `MDLDATA` 使用 `std::unique_ptr`
- `MDLArray` 的 offset 改为 `std::vector` 或智能指针
- `CMdlModel::Release()` 简化

#### 8. OpenGL 渲染集成

当前状态: `MdlRender` 独立存在，输出顶点/索引/批次数据，未接入 OpenGL。

需要:
- 与 `CGxDevice` 渲染管线集成
- 创建 VAO/VBO/IBO
- 实现骨骼蒙皮 shader
- 处理材质/纹理绑定

### P3: 测试维护

#### 10. 旧测试挂起

`ErrorHandlingTest.InvalidFile` 挂起 (exit 127)，阻塞测试套件。

可能原因:
- `MsgBuffer(size)` 在文件不存在时的行为
- `MdlBinReader::ReadFile` 的 ifstream 打开失败路径
- 需要调查并修复

已知相关测试:
- `ErrorHandlingTest.InvalidFile` — 加载不存在的文件
- `ErrorHandlingTest.InvalidSignature` — 无效签名缓冲区
- `MdlParseTest.*` — 使用旧的测试路径

## chunk 解析进度

```
VERS  ✅ 跳过
MODL  ✅ 完整解析
SEQS  ❌ 跳过 — 格式待验证
GLOS  ❌ 跳过
SNDS  ❌ 跳过
MTLS  ❌ 跳过 — 格式待验证
TEXS  ❌ 跳过 — 格式待验证
TEXA  ❌ 跳过
GEOS  ❌ 跳过 — 含嵌套数组
GEOA  ❌ 跳过
BONE  ❌ 跳过 — 含嵌套数组，首次尝试 segfault
LITE  ❌ 跳过
HELP  ❌ 跳过
ATCH  ❌ 跳过
PREM  ❌ 跳过
CAMS  ❌ 跳过
EVTS  ❌ 跳过
PRE2  ❌ 跳过 — 结构体未实现
CLID  ❌ 跳过
RIBB  ❌ 跳过
PIVT  ❌ 跳过
```

## 参考资源

- WC3 MDX 格式规范: https://www.wc3c.net/tools/specs/
- 原始二进制参考: `war3_mac_binary/Warcraft III_max1.c` (IDA 反编译)
- ida2sql 查询: `SELECT * FROM functions WHERE name LIKE '%MODL%'`
- 测试数据: `data/mpq/war3.mpq.unpack/Units/Human/Footman/Footman.mdx`
