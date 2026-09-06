#include "MdlBinReader.h"
#include <cstring>
#include <fstream>
#include <vector>

// ============================================================================
// MDX 文件签名
// ============================================================================
static const uint32_t MDLX_SIGNATURE = 0x584C444D;  // "MDLX"
static const uint32_t MDL_SIGNATURE = 0x204C444D;    // "MDL "

// Chunk 标签
static const uint32_t CHUNK_VERS = 0x53524556;  // "VERS" (版本)
static const uint32_t CHUNK_MODL = 0x4C444F4D;  // "MODL" (模型信息)
static const uint32_t CHUNK_SEQS = 0x53455153;  // "SEQS"
static const uint32_t CHUNK_GLOS = 0x534F4C47;  // "GLOS" (全局序列)
static const uint32_t CHUNK_SNDS = 0x53444E53;  // "SNDS"
static const uint32_t CHUNK_MATS = 0x5354414D;  // "MATS"
static const uint32_t CHUNK_TEXS = 0x53584554;  // "TEXS"
static const uint32_t CHUNK_TEXA = 0x41584554;  // "TEXA"
static const uint32_t CHUNK_GEOS = 0x534F4547;  // "GEOS"
static const uint32_t CHUNK_GEOA = 0x414F4547;  // "GEOA"
static const uint32_t CHUNK_BONE = 0x454E4F42;  // "BONE"
static const uint32_t CHUNK_LITE = 0x4554494C;  // "LITE"
static const uint32_t CHUNK_HELP = 0x4C504548;  // "HELP"
static const uint32_t CHUNK_ATCH = 0x48435441;  // "ATCH"
static const uint32_t CHUNK_PREM = 0x4D455250;  // "PREM"
static const uint32_t CHUNK_CAMS = 0x534D4143;  // "CAMS"
static const uint32_t CHUNK_EVTS = 0x53545645;  // "EVTS"
static const uint32_t CHUNK_PRE2 = 0x32455250;  // "PRE2"
static const uint32_t CHUNK_CLID = 0x44494C43;  // "CLID"
static const uint32_t CHUNK_RIBB = 0x42424952;  // "RIBB"

// ============================================================================
// 构造函数/析构函数
// ============================================================================

MdlBinReader::MdlBinReader() {}

MdlBinReader::~MdlBinReader() {}

// ============================================================================
// 公共接口
// ============================================================================

bool MdlBinReader::Read(MsgBuffer& buffer, MDLDATA& data, Status& status) {
    // MDLX 格式: "MDLX" magic (4 bytes), 然后直接跟 sub-chunks: tag(4) + size(4) + data(size)
    // MDLX 不是 chunk，只是文件签名
    uint32_t signature = ReadChunkTag(buffer);
    if (signature != MDLX_SIGNATURE) {
        status.SetError(-1, "Invalid MDX file signature");
        return false;
    }

    // 读取各个 chunk
    while (buffer.Remaining() >= 8) {
        uint32_t tag = ReadChunkTag(buffer);
        uint32_t size = ReadChunkSize(buffer);

        if (tag == 0 || size == 0) {
            break;
        }

        uint32_t startPos = buffer.Tell();

        bool result = false;
        switch (tag) {
            case CHUNK_VERS:
                // 版本 chunk，读取并跳过 (size 是数据大小，不含 tag+size)
                result = SkipChunk(buffer, size);
                break;
            case CHUNK_MODL:
                result = ReadHeader(buffer, data.header, status);
                if (result) {
                    result = ReadModel(buffer, data.model, status);
                }
                break;
            default:
                // 其他 chunk 暂时跳过 (SEQS/GEOS/BONE 等含嵌套数组的 chunk 尚未完全实现)
                result = SkipChunk(buffer, size);
                break;
        }

        if (!result) {
            // 跳过解析失败的 chunk，继续解析后续 chunk
            uint32_t consumed = buffer.Tell() - startPos;
            if (consumed < size) {
                buffer.Skip(size - consumed);
            }
            continue;
        }

        // 确保跳到 chunk 末尾 (size 是数据大小，不包含 tag+size)
        uint32_t bytesRead = buffer.Tell() - startPos;
        if (bytesRead < size) {
            buffer.Skip(size - bytesRead);
        }
    }

    return true;
}

bool MdlBinReader::ReadFile(const char* filePath, MDLDATA& data, Status& status) {
    std::ifstream file(filePath, std::ios::binary | std::ios::ate);
    if (!file.is_open()) {
        status.SetError(-1, "Failed to open file");
        return false;
    }

    std::streamsize size = file.tellg();
    file.seekg(0, std::ios::beg);

    std::vector<char> fileData(static_cast<size_t>(size));
    if (!file.read(fileData.data(), size)) {
        status.SetError(-2, "Failed to read file");
        return false;
    }

    MsgBuffer buffer(static_cast<uint32_t>(size));
    if (!buffer.Write(fileData.data(), static_cast<uint32_t>(size))) {
        status.SetError(-2, "Failed to copy to buffer");
        return false;
    }

    buffer.Seek(0);
    return Read(buffer, data, status);
}

// ============================================================================
// 私有读取函数
// ============================================================================

bool MdlBinReader::ReadHeader(MsgBuffer& buffer, MDLHEADERSECTION& header, Status& status) {
    // MDX MODL chunk: name 是 80 字节 (不是 256)
    if (!buffer.Read(header.name, 80)) {
        status.SetError(-10, "Failed to read header name");
        return false;
    }
    header.name[79] = '\0';  // 确保 null 结尾

    return true;
}

bool MdlBinReader::ReadModel(MsgBuffer& buffer, MDLMODELSECTION& model, Status& status) {
    if (!buffer.Read(model.animationBounds, sizeof(model.animationBounds))) {
        status.SetError(-21, "Failed to read model bounds");
        return false;
    }

    if (!buffer.Read(&model.blendTime, sizeof(model.blendTime))) {
        status.SetError(-22, "Failed to read model blend time");
        return false;
    }

    return true;
}

bool MdlBinReader::ReadSequences(MsgBuffer& buffer, MDLArray<MDLSEQUENCESSECTION>& sequences, Status& status) {
    uint32_t count;
    if (!buffer.Read(&count, sizeof(count))) {
        status.SetError(-30, "Failed to read sequence count");
        return false;
    }

    sequences.count = count;
    if (count > 0) {
        // 分配内存并读取数据
        MDLSEQUENCESSECTION* data = new MDLSEQUENCESSECTION[count];
        if (!buffer.Read(data, count * sizeof(MDLSEQUENCESSECTION))) {
            delete[] data;
            status.SetError(-31, "Failed to read sequences");
            return false;
        }

        // 设置偏移 (简化处理，实际需要修复)
        sequences.offset = reinterpret_cast<uintptr_t>(data);
    }

    return true;
}

bool MdlBinReader::ReadGlobalSequences(MsgBuffer& buffer, MDLArray<MDLGLOBALSEQSECTION>& globalSeqs, Status& status) {
    uint32_t count;
    if (!buffer.Read(&count, sizeof(count))) {
        status.SetError(-40, "Failed to read global sequence count");
        return false;
    }

    globalSeqs.count = count;
    if (count > 0) {
        MDLGLOBALSEQSECTION* data = new MDLGLOBALSEQSECTION[count];
        if (!buffer.Read(data, count * sizeof(MDLGLOBALSEQSECTION))) {
            delete[] data;
            status.SetError(-41, "Failed to read global sequences");
            return false;
        }
        globalSeqs.offset = reinterpret_cast<uintptr_t>(data);
    }

    return true;
}

bool MdlBinReader::ReadSounds(MsgBuffer& buffer, MDLArray<MDLSOUNDSECTION>& sounds, Status& status) {
    uint32_t count;
    if (!buffer.Read(&count, sizeof(count))) {
        status.SetError(-50, "Failed to read sound count");
        return false;
    }

    sounds.count = count;
    if (count > 0) {
        MDLSOUNDSECTION* data = new MDLSOUNDSECTION[count];
        if (!buffer.Read(data, count * sizeof(MDLSOUNDSECTION))) {
            delete[] data;
            status.SetError(-51, "Failed to read sounds");
            return false;
        }
        sounds.offset = reinterpret_cast<uintptr_t>(data);
    }

    return true;
}

bool MdlBinReader::ReadMaterials(MsgBuffer& buffer, MDLArray<MDLMATERIALSECTION>& materials, Status& status) {
    uint32_t count;
    if (!buffer.Read(&count, sizeof(count))) {
        status.SetError(-60, "Failed to read material count");
        return false;
    }

    materials.count = count;
    if (count > 0) {
        MDLMATERIALSECTION* data = new MDLMATERIALSECTION[count];
        if (!buffer.Read(data, count * sizeof(MDLMATERIALSECTION))) {
            delete[] data;
            status.SetError(-61, "Failed to read materials");
            return false;
        }
        materials.offset = reinterpret_cast<uintptr_t>(data);
    }

    return true;
}

bool MdlBinReader::ReadTextures(MsgBuffer& buffer, MDLArray<MDLTEXTURESECTION>& textures, Status& status) {
    uint32_t count;
    if (!buffer.Read(&count, sizeof(count))) {
        status.SetError(-70, "Failed to read texture count");
        return false;
    }

    textures.count = count;
    if (count > 0) {
        MDLTEXTURESECTION* data = new MDLTEXTURESECTION[count];
        if (!buffer.Read(data, count * sizeof(MDLTEXTURESECTION))) {
            delete[] data;
            status.SetError(-71, "Failed to read textures");
            return false;
        }
        textures.offset = reinterpret_cast<uintptr_t>(data);
    }

    return true;
}

bool MdlBinReader::ReadTextureAnimations(MsgBuffer& buffer, MDLArray<MDLTEXANIMSECTION>& texAnims, Status& status) {
    uint32_t count;
    if (!buffer.Read(&count, sizeof(count))) {
        status.SetError(-80, "Failed to read texture animation count");
        return false;
    }

    texAnims.count = count;
    if (count > 0) {
        MDLTEXANIMSECTION* data = new MDLTEXANIMSECTION[count];
        if (!buffer.Read(data, count * sizeof(MDLTEXANIMSECTION))) {
            delete[] data;
            status.SetError(-81, "Failed to read texture animations");
            return false;
        }
        texAnims.offset = reinterpret_cast<uintptr_t>(data);
    }

    return true;
}

bool MdlBinReader::ReadGeosets(MsgBuffer& buffer, MDLArray<MDLGEOSETSECTION>& geosets, Status& status) {
    uint32_t count;
    if (!buffer.Read(&count, sizeof(count))) {
        status.SetError(-90, "Failed to read geoset count");
        return false;
    }

    geosets.count = count;
    if (count > 0) {
        MDLGEOSETSECTION* data = new MDLGEOSETSECTION[count];
        if (!buffer.Read(data, count * sizeof(MDLGEOSETSECTION))) {
            delete[] data;
            status.SetError(-91, "Failed to read geosets");
            return false;
        }
        geosets.offset = reinterpret_cast<uintptr_t>(data);
    }

    return true;
}

bool MdlBinReader::ReadGeosetAnimations(MsgBuffer& buffer, MDLArray<MDLGEOSETANIMSECTION>& geosetAnims, Status& status) {
    uint32_t count;
    if (!buffer.Read(&count, sizeof(count))) {
        status.SetError(-100, "Failed to read geoset animation count");
        return false;
    }

    geosetAnims.count = count;
    if (count > 0) {
        MDLGEOSETANIMSECTION* data = new MDLGEOSETANIMSECTION[count];
        if (!buffer.Read(data, count * sizeof(MDLGEOSETANIMSECTION))) {
            delete[] data;
            status.SetError(-101, "Failed to read geoset animations");
            return false;
        }
        geosetAnims.offset = reinterpret_cast<uintptr_t>(data);
    }

    return true;
}

bool MdlBinReader::ReadBones(MsgBuffer& buffer, MDLArray<MDLBONESECTION>& bones, Status& status) {
    uint32_t count;
    if (!buffer.Read(&count, sizeof(count))) {
        status.SetError(-110, "Failed to read bone count");
        return false;
    }

    bones.count = count;
    if (count > 0) {
        MDLBONESECTION* data = new MDLBONESECTION[count];
        if (!buffer.Read(data, count * sizeof(MDLBONESECTION))) {
            delete[] data;
            status.SetError(-111, "Failed to read bones");
            return false;
        }
        bones.offset = reinterpret_cast<uintptr_t>(data);
    }

    return true;
}

bool MdlBinReader::ReadLights(MsgBuffer& buffer, MDLArray<MDLLIGHTSECTION>& lights, Status& status) {
    uint32_t count;
    if (!buffer.Read(&count, sizeof(count))) {
        status.SetError(-120, "Failed to read light count");
        return false;
    }

    lights.count = count;
    if (count > 0) {
        MDLLIGHTSECTION* data = new MDLLIGHTSECTION[count];
        if (!buffer.Read(data, count * sizeof(MDLLIGHTSECTION))) {
            delete[] data;
            status.SetError(-121, "Failed to read lights");
            return false;
        }
        lights.offset = reinterpret_cast<uintptr_t>(data);
    }

    return true;
}

bool MdlBinReader::ReadHelpers(MsgBuffer& buffer, MDLArray<MDLGENOBJECT>& helpers, Status& status) {
    uint32_t count;
    if (!buffer.Read(&count, sizeof(count))) {
        status.SetError(-130, "Failed to read helper count");
        return false;
    }

    helpers.count = count;
    if (count > 0) {
        MDLGENOBJECT* data = new MDLGENOBJECT[count];
        if (!buffer.Read(data, count * sizeof(MDLGENOBJECT))) {
            delete[] data;
            status.SetError(-131, "Failed to read helpers");
            return false;
        }
        helpers.offset = reinterpret_cast<uintptr_t>(data);
    }

    return true;
}

bool MdlBinReader::ReadAttachments(MsgBuffer& buffer, MDLArray<MDLATTACHMENTSECTION>& attachments, Status& status) {
    uint32_t count;
    if (!buffer.Read(&count, sizeof(count))) {
        status.SetError(-140, "Failed to read attachment count");
        return false;
    }

    attachments.count = count;
    if (count > 0) {
        MDLATTACHMENTSECTION* data = new MDLATTACHMENTSECTION[count];
        if (!buffer.Read(data, count * sizeof(MDLATTACHMENTSECTION))) {
            delete[] data;
            status.SetError(-141, "Failed to read attachments");
            return false;
        }
        attachments.offset = reinterpret_cast<uintptr_t>(data);
    }

    return true;
}

bool MdlBinReader::ReadParticleEmitters(MsgBuffer& buffer, MDLArray<MDLPARTICLEEMITTER>& emitters, Status& status) {
    uint32_t count;
    if (!buffer.Read(&count, sizeof(count))) {
        status.SetError(-150, "Failed to read particle emitter count");
        return false;
    }

    emitters.count = count;
    if (count > 0) {
        MDLPARTICLEEMITTER* data = new MDLPARTICLEEMITTER[count];
        if (!buffer.Read(data, count * sizeof(MDLPARTICLEEMITTER))) {
            delete[] data;
            status.SetError(-151, "Failed to read particle emitters");
            return false;
        }
        emitters.offset = reinterpret_cast<uintptr_t>(data);
    }

    return true;
}

bool MdlBinReader::ReadCameras(MsgBuffer& buffer, MDLArray<MDLCAMERASECTION>& cameras, Status& status) {
    uint32_t count;
    if (!buffer.Read(&count, sizeof(count))) {
        status.SetError(-160, "Failed to read camera count");
        return false;
    }

    cameras.count = count;
    if (count > 0) {
        MDLCAMERASECTION* data = new MDLCAMERASECTION[count];
        if (!buffer.Read(data, count * sizeof(MDLCAMERASECTION))) {
            delete[] data;
            status.SetError(-161, "Failed to read cameras");
            return false;
        }
        cameras.offset = reinterpret_cast<uintptr_t>(data);
    }

    return true;
}

bool MdlBinReader::ReadEvents(MsgBuffer& buffer, MDLArray<MDLEVENTSECTION>& events, Status& status) {
    uint32_t count;
    if (!buffer.Read(&count, sizeof(count))) {
        status.SetError(-170, "Failed to read event count");
        return false;
    }

    events.count = count;
    if (count > 0) {
        MDLEVENTSECTION* data = new MDLEVENTSECTION[count];
        if (!buffer.Read(data, count * sizeof(MDLEVENTSECTION))) {
            delete[] data;
            status.SetError(-171, "Failed to read events");
            return false;
        }
        events.offset = reinterpret_cast<uintptr_t>(data);
    }

    return true;
}

bool MdlBinReader::ReadCollisionShapes(MsgBuffer& buffer, MDLArray<MDLCOLLISIONSHAPE>& shapes, Status& status) {
    uint32_t count;
    if (!buffer.Read(&count, sizeof(count))) {
        status.SetError(-180, "Failed to read collision shape count");
        return false;
    }

    shapes.count = count;
    if (count > 0) {
        MDLCOLLISIONSHAPE* data = new MDLCOLLISIONSHAPE[count];
        if (!buffer.Read(data, count * sizeof(MDLCOLLISIONSHAPE))) {
            delete[] data;
            status.SetError(-181, "Failed to read collision shapes");
            return false;
        }
        shapes.offset = reinterpret_cast<uintptr_t>(data);
    }

    return true;
}

bool MdlBinReader::ReadRibbonEmitters(MsgBuffer& buffer, MDLArray<MDLRIBBONEMITTER>& ribbons, Status& status) {
    uint32_t count;
    if (!buffer.Read(&count, sizeof(count))) {
        status.SetError(-190, "Failed to read ribbon emitter count");
        return false;
    }

    ribbons.count = count;
    if (count > 0) {
        MDLRIBBONEMITTER* data = new MDLRIBBONEMITTER[count];
        if (!buffer.Read(data, count * sizeof(MDLRIBBONEMITTER))) {
            delete[] data;
            status.SetError(-191, "Failed to read ribbon emitters");
            return false;
        }
        ribbons.offset = reinterpret_cast<uintptr_t>(data);
    }

    return true;
}

// ============================================================================
// 辅助函数
// ============================================================================

uint32_t MdlBinReader::ReadChunkTag(MsgBuffer& buffer) {
    uint32_t tag;
    if (!buffer.Read(&tag, sizeof(tag))) {
        return 0;
    }
    return tag;
}

uint32_t MdlBinReader::ReadChunkSize(MsgBuffer& buffer) {
    uint32_t size;
    if (!buffer.Read(&size, sizeof(size))) {
        return 0;
    }
    return size;
}

bool MdlBinReader::SkipChunk(MsgBuffer& buffer, uint32_t size) {
    return buffer.Skip(size);
}

// ============================================================================
// 关键帧读取模板实现
// ============================================================================

template<typename T>
bool MdlBinReader::ReadKeyTrack(MsgBuffer& buffer, MDLKEYTRACK<T>& track, Status& status) {
    // 读取插值类型
    uint32_t interpType;
    if (!buffer.Read(&interpType, sizeof(interpType))) {
        status.SetError(-200, "Failed to read track interpolation type");
        return false;
    }
    track.interpolationType = static_cast<MDLTRACKTYPE>(interpType);

    // 读取全局序列 ID
    uint32_t globalSeqId;
    if (!buffer.Read(&globalSeqId, sizeof(globalSeqId))) {
        status.SetError(-201, "Failed to read global sequence ID");
        return false;
    }

    // 读取关键帧数量
    uint32_t keyCount;
    if (!buffer.Read(&keyCount, sizeof(keyCount))) {
        status.SetError(-202, "Failed to read key count");
        return false;
    }

    // 读取关键帧数据
    if (keyCount > 0) {
        return ReadKeyframes(buffer, track.keys, keyCount, status);
    }

    return true;
}

template<typename T>
bool MdlBinReader::ReadKeyframes(MsgBuffer& buffer, MDLArray<T>& keys, uint32_t count, Status& status) {
    keys.count = count;

    T* data = new T[count];
    if (!buffer.Read(data, count * sizeof(T))) {
        delete[] data;
        status.SetError(-210, "Failed to read keyframes");
        return false;
    }

    keys.offset = reinterpret_cast<uintptr_t>(data);
    return true;
}
