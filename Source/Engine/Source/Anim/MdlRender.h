#pragma once

#include "CMdlModel.h"
#include "../Gx/Buffer.h"
#include "../Tempest/C44Matrix.h"
#include "../Tempest/C3Vector.h"
#include <cstdint>
#include <vector>

using namespace Tempest;

// ============================================================================
// MdlRenderVertex - MDL 渲染顶点
// ============================================================================

struct MdlRenderVertex {
    C3Vector position;
    C3Vector normal;
    C2Vector texCoord;
    uint8_t boneWeights[4];
    uint8_t boneIndices[4];
};

// ============================================================================
// MdlRenderBatch - MDL 渲染批次
// ============================================================================

struct MdlRenderBatch {
    uint32_t vertexStart;
    uint32_t vertexCount;
    uint32_t indexStart;
    uint32_t indexCount;
    uint32_t materialIndex;
    uint32_t textureIndex;
};

// ============================================================================
// MdlRender - MDL 模型渲染器
// 负责将 MDL 模型数据转换为可渲染的格式
// ============================================================================

class MdlRender {
public:
    MdlRender();
    ~MdlRender();

    // 初始化渲染器
    bool Initialize(const CMdlModel& model);

    // 释放资源
    void Release();

    // 更新渲染数据
    void Update(const CMdlModel& model);

    // 获取渲染数据
    const std::vector<MdlRenderVertex>& GetVertices() const { return m_vertices; }
    const std::vector<uint32_t>& GetIndices() const { return m_indices; }
    const std::vector<MdlRenderBatch>& GetBatches() const { return m_batches; }

    // 获取骨骼矩阵
    const std::vector<C44Matrix>& GetBoneMatrices() const { return m_boneMatrices; }

    // 检查是否已初始化
    bool IsInitialized() const { return m_initialized; }

private:
    bool m_initialized;

    // 渲染数据
    std::vector<MdlRenderVertex> m_vertices;
    std::vector<uint32_t> m_indices;
    std::vector<MdlRenderBatch> m_batches;

    // 骨骼矩阵
    std::vector<C44Matrix> m_boneMatrices;

    // 内部方法
    void BuildVertices(const CMdlModel& model);
    void BuildIndices(const CMdlModel& model);
    void BuildBatches(const CMdlModel& model);
    void BuildBoneMatrices(const CMdlModel& model);
};
