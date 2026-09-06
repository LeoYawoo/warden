#pragma once

#include "MdlData.h"
#include "../Base/MsgBuffer.h"
#include "../Base/Status.h"
#include <cstdint>
#include <string>

// ============================================================================
// MdlBinReader - MDX 二进制格式读取器
// 基于 IDA 反编译的暴雪原始代码实现
// ============================================================================

class MdlBinReader {
public:
    MdlBinReader();
    ~MdlBinReader();

    // 从缓冲区读取 MDL 数据
    bool Read(MsgBuffer& buffer, MDLDATA& data, Status& status);

    // 从文件读取 MDL 数据
    bool ReadFile(const char* filePath, MDLDATA& data, Status& status);

private:
    // 读取文件头
    bool ReadHeader(MsgBuffer& buffer, MDLHEADERSECTION& header, Status& status);

    // 读取模型信息
    bool ReadModel(MsgBuffer& buffer, MDLMODELSECTION& model, Status& status);

    // 读取动画序列 (无 count 前缀，通过 chunkSize 计算 count)
    bool ReadSequences(MsgBuffer& buffer, uint32_t chunkSize, MDLArray<MDLSEQUENCESSECTION>& sequences, Status& status);

    // 读取全局序列
    bool ReadGlobalSequences(MsgBuffer& buffer, MDLArray<MDLGLOBALSEQSECTION>& globalSeqs, Status& status);

    // 读取声音
    bool ReadSounds(MsgBuffer& buffer, MDLArray<MDLSOUNDSECTION>& sounds, Status& status);

    // 读取材质 (无 count 前缀)
    bool ReadMaterials(MsgBuffer& buffer, uint32_t chunkSize, MDLArray<MDLMATERIALSECTION>& materials, Status& status);

    // 读取纹理 (无 count 前缀)
    bool ReadTextures(MsgBuffer& buffer, uint32_t chunkSize, MDLArray<MDLTEXTURESECTION>& textures, Status& status);

    // 读取纹理动画
    bool ReadTextureAnimations(MsgBuffer& buffer, MDLArray<MDLTEXANIMSECTION>& texAnims, Status& status);

    // 读取几何体
    bool ReadGeosets(MsgBuffer& buffer, MDLArray<MDLGEOSETSECTION>& geosets, Status& status);

    // 读取几何体动画
    bool ReadGeosetAnimations(MsgBuffer& buffer, MDLArray<MDLGEOSETANIMSECTION>& geosetAnims, Status& status);

    // 读取骨骼
    bool ReadBones(MsgBuffer& buffer, MDLArray<MDLBONESECTION>& bones, Status& status);

    // 读取灯光
    bool ReadLights(MsgBuffer& buffer, MDLArray<MDLLIGHTSECTION>& lights, Status& status);

    // 读取辅助对象
    bool ReadHelpers(MsgBuffer& buffer, MDLArray<MDLGENOBJECT>& helpers, Status& status);

    // 读取附件
    bool ReadAttachments(MsgBuffer& buffer, MDLArray<MDLATTACHMENTSECTION>& attachments, Status& status);

    // 读取粒子发射器
    bool ReadParticleEmitters(MsgBuffer& buffer, MDLArray<MDLPARTICLEEMITTER>& emitters, Status& status);

    // 读取相机
    bool ReadCameras(MsgBuffer& buffer, MDLArray<MDLCAMERASECTION>& cameras, Status& status);

    // 读取事件
    bool ReadEvents(MsgBuffer& buffer, MDLArray<MDLEVENTSECTION>& events, Status& status);

    // 读取碰撞形状
    bool ReadCollisionShapes(MsgBuffer& buffer, MDLArray<MDLCOLLISIONSHAPE>& shapes, Status& status);

    // 读取丝带发射器
    bool ReadRibbonEmitters(MsgBuffer& buffer, MDLArray<MDLRIBBONEMITTER>& ribbons, Status& status);

    // 读取关键帧轨道
    template<typename T>
    bool ReadKeyTrack(MsgBuffer& buffer, MDLKEYTRACK<T>& track, Status& status);

    // 读取关键帧数据
    template<typename T>
    bool ReadKeyframes(MsgBuffer& buffer, MDLArray<T>& keys, uint32_t count, Status& status);

    // 读取 chunk 标签
    uint32_t ReadChunkTag(MsgBuffer& buffer);

    // 读取 chunk 大小
    uint32_t ReadChunkSize(MsgBuffer& buffer);

    // 跳过 chunk
    bool SkipChunk(MsgBuffer& buffer, uint32_t size);
};
