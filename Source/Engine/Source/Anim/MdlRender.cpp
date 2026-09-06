#include "MdlRender.h"
#include "MdlKeyTrack.h"

// ============================================================================
// 构造函数/析构函数
// ============================================================================

MdlRender::MdlRender()
    : m_initialized(false) {
}

MdlRender::~MdlRender() {
    Release();
}

// ============================================================================
// 公共接口
// ============================================================================

bool MdlRender::Initialize(const CMdlModel& model) {
    if (!model.IsLoaded()) {
        return false;
    }

    Release();

    BuildVertices(model);
    BuildIndices(model);
    BuildBatches(model);
    BuildBoneMatrices(model);

    m_initialized = true;
    return true;
}

void MdlRender::Release() {
    m_vertices.clear();
    m_indices.clear();
    m_batches.clear();
    m_boneMatrices.clear();
    m_initialized = false;
}

void MdlRender::Update(const CMdlModel& model) {
    if (!m_initialized) {
        return;
    }

    BuildBoneMatrices(model);
}

// ============================================================================
// 私有方法
// ============================================================================

void MdlRender::BuildVertices(const CMdlModel& model) {
    m_vertices.clear();

    const MDLDATA* data = model.GetData();
    if (!data) return;

    // 遍历所有几何体
    for (uint32_t g = 0; g < data->geosets.Count(); g++) {
        const auto& geoset = data->geosets[g];

        // 获取顶点数据
        if (geoset.vertices.Count() == 0) continue;

        const C3Vector* vertices = geoset.vertices.Data();
        const C3Vector* normals = geoset.normals.Data();
        const C2Vector* texCoords = geoset.textureCoords.Data();

        uint32_t vertexStart = static_cast<uint32_t>(m_vertices.size());

        for (uint32_t v = 0; v < geoset.vertices.Count(); v++) {
            MdlRenderVertex vertex;

            // 位置
            vertex.position = vertices[v];

            // 法线
            if (normals && v < geoset.normals.Count()) {
                vertex.normal = normals[v];
            } else {
                vertex.normal = C3Vector(0, 0, 1);
            }

            // 纹理坐标
            if (texCoords && v < geoset.textureCoords.Count()) {
                vertex.texCoord = texCoords[v];
            } else {
                vertex.texCoord = C2Vector(0, 0);
            }

            // 骨骼权重和索引 (简化处理)
            memset(vertex.boneWeights, 0, sizeof(vertex.boneWeights));
            memset(vertex.boneIndices, 0, sizeof(vertex.boneIndices));

            if (geoset.matrixIndices.Count() > v) {
                uint8_t boneIndex = geoset.matrixIndices.Data()[v];
                vertex.boneWeights[0] = 255;
                vertex.boneIndices[0] = boneIndex;
            }

            m_vertices.push_back(vertex);
        }
    }
}

void MdlRender::BuildIndices(const CMdlModel& model) {
    m_indices.clear();

    const MDLDATA* data = model.GetData();
    if (!data) return;

    uint32_t vertexOffset = 0;

    // 遍历所有几何体
    for (uint32_t g = 0; g < data->geosets.Count(); g++) {
        const auto& geoset = data->geosets[g];

        // 获取索引数据
        if (geoset.triangles.Count() == 0) continue;

        const uint16_t* triangles = geoset.triangles.Data();

        for (uint32_t i = 0; i < geoset.triangles.Count(); i++) {
            m_indices.push_back(vertexOffset + triangles[i]);
        }

        vertexOffset += geoset.vertices.Count();
    }
}

void MdlRender::BuildBatches(const CMdlModel& model) {
    m_batches.clear();

    const MDLDATA* data = model.GetData();
    if (!data) return;

    uint32_t vertexOffset = 0;
    uint32_t indexOffset = 0;

    // 遍历所有几何体
    for (uint32_t g = 0; g < data->geosets.Count(); g++) {
        const auto& geoset = data->geosets[g];

        MdlRenderBatch batch;
        batch.vertexStart = vertexOffset;
        batch.vertexCount = geoset.vertices.Count();
        batch.indexStart = indexOffset;
        batch.indexCount = geoset.triangles.Count();
        batch.materialIndex = 0;
        batch.textureIndex = 0;

        m_batches.push_back(batch);

        vertexOffset += geoset.vertices.Count();
        indexOffset += geoset.triangles.Count();
    }
}

void MdlRender::BuildBoneMatrices(const CMdlModel& model) {
    m_boneMatrices.clear();

    const MDLDATA* data = model.GetData();
    if (!data) return;

    uint32_t boneCount = data->bones.Count();
    m_boneMatrices.resize(boneCount);

    for (uint32_t i = 0; i < boneCount; i++) {
        m_boneMatrices[i] = model.GetBoneMatrix(i);
    }
}
