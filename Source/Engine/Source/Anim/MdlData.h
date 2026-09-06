#pragma once

#include <cstdint>
#include <cstring>
#include "../Tempest/C3Vector.h"
#include "../Tempest/C2Vector.h"
#include "../Tempest/CAaBox.h"
#include "Type.h"

using namespace Tempest;

// ============================================================================
// MDLArray - 类似 M2Array 的偏移数组模板
// 用于 MDX 文件中的数据引用
// ============================================================================
template<typename T>
struct MDLArray {
    uint32_t count;
    uint32_t offset;

    T& operator[](uint32_t i) {
        T* data = reinterpret_cast<T*>(reinterpret_cast<uintptr_t>(this) + this->offset);
        return data[i];
    }

    const T& operator[](uint32_t i) const {
        const T* data = reinterpret_cast<const T*>(reinterpret_cast<uintptr_t>(this) + this->offset);
        return data[i];
    }

    uint32_t Count() const { return count; }

    T* Data() {
        return reinterpret_cast<T*>(reinterpret_cast<uintptr_t>(this) + this->offset);
    }

    const T* Data() const {
        return reinterpret_cast<const T*>(reinterpret_cast<uintptr_t>(this) + this->offset);
    }
};

// ============================================================================
// 关键帧结构体
// ============================================================================

// 位移/缩放关键帧 (float x, y, z + time)
struct MDLCOORD3FKEYFRAME {
    float x, y, z;
    uint32_t time;

    MDLCOORD3FKEYFRAME() : x(0), y(0), z(0), time(0) {}
    MDLCOORD3FKEYFRAME(float x, float y, float z, uint32_t t)
        : x(x), y(y), z(z), time(t) {}
};

// 位移关键帧
struct MDLTRANSKEYFRAME : MDLCOORD3FKEYFRAME {
    MDLTRANSKEYFRAME() : MDLCOORD3FKEYFRAME() {}
    MDLTRANSKEYFRAME(float x, float y, float z, uint32_t t)
        : MDLCOORD3FKEYFRAME(x, y, z, t) {}
};

// 缩放关键帧
struct MDLSCALEKEYFRAME : MDLCOORD3FKEYFRAME {
    MDLSCALEKEYFRAME() : MDLCOORD3FKEYFRAME() {}
    MDLSCALEKEYFRAME(float x, float y, float z, uint32_t t)
        : MDLCOORD3FKEYFRAME(x, y, z, t) {}
};

// 旋转关键帧 (四元数)
struct MDLROTKEYFRAME {
    float x, y, z, w;
    uint32_t time;

    MDLROTKEYFRAME() : x(0), y(0), z(0), w(1.0f), time(0) {}
    MDLROTKEYFRAME(float x, float y, float z, float w, uint32_t t)
        : x(x), y(y), z(z), w(w), time(t) {}
};

// 透明度关键帧
struct MDLALPHAKEYFRAME {
    float alpha;
    uint32_t time;

    MDLALPHAKEYFRAME() : alpha(0), time(0) {}
    MDLALPHAKEYFRAME(float a, uint32_t t) : alpha(a), time(t) {}
};

// 颜色关键帧
struct MDLCOLORKEYFRAME {
    uint8_t r, g, b;
    uint8_t padding;
    uint32_t time;

    MDLCOLORKEYFRAME() : r(255), g(255), b(255), padding(0), time(0) {}
    MDLCOLORKEYFRAME(uint8_t r, uint8_t g, uint8_t b, uint32_t t)
        : r(r), g(g), b(b), padding(0), time(t) {}
};

// 强度关键帧
struct MDLINTENSITYKEYFRAME {
    float intensity;
    uint32_t time;

    MDLINTENSITYKEYFRAME() : intensity(1.0f), time(0) {}
    MDLINTENSITYKEYFRAME(float i, uint32_t t) : intensity(i), time(t) {}
};

// 衰减关键帧
struct MDLATTENKEYFRAME {
    float attenuation;
    uint32_t time;

    MDLATTENKEYFRAME() : attenuation(0), time(0) {}
    MDLATTENKEYFRAME(float a, uint32_t t) : attenuation(a), time(t) {}
};

// 浮点属性关键帧
struct MDLFLOATPROPKEYFRAME {
    float value;
    uint32_t time;

    MDLFLOATPROPKEYFRAME() : value(0), time(0) {}
    MDLFLOATPROPKEYFRAME(float v, uint32_t t) : value(v), time(t) {}
};

// 翻页关键帧
struct MDLFLIPBOOKKEY {
    uint32_t value;
    uint32_t time;

    MDLFLIPBOOKKEY() : value(0), time(0) {}
    MDLFLIPBOOKKEY(uint32_t v, uint32_t t) : value(v), time(t) {}
};

// 整数关键帧
struct MDLINTKEY {
    uint32_t value;
    uint32_t time;

    MDLINTKEY() : value(0), time(0) {}
    MDLINTKEY(uint32_t v, uint32_t t) : value(v), time(t) {}
};

// 事件关键帧
struct MDLEVENTKEY {
    uint32_t value;
    uint32_t time;

    MDLEVENTKEY() : value(0), time(0) {}
    MDLEVENTKEY(uint32_t v, uint32_t t) : value(v), time(t) {}
};

// 声音关键帧
struct MDLSOUNDKEYFRAME {
    uint32_t value;
    uint32_t time;

    MDLSOUNDKEYFRAME() : value(0), time(0) {}
    MDLSOUNDKEYFRAME(uint32_t v, uint32_t t) : value(v), time(t) {}
};

// ============================================================================
// MDL 字符串类型
// ============================================================================

// MDL 固定长度字符串
template<int MaxLen>
struct CMdlString {
    char data[MaxLen];

    CMdlString() { memset(data, 0, MaxLen); }

    const char* c_str() const { return data; }

    void Set(const char* str) {
        if (str) {
            strncpy(data, str, MaxLen - 1);
            data[MaxLen - 1] = '\0';
        } else {
            memset(data, 0, MaxLen);
        }
    }
};

// ============================================================================
// MDL 包围盒
// ============================================================================

struct CMdlBounds {
    C3Vector min;
    C3Vector max;

    CMdlBounds() : min(0, 0, 0), max(0, 0, 0) {}
};

// ============================================================================
// Section 结构体
// ============================================================================

// 文件头 Section
struct MDLHEADERSECTION {
    char name[256];
    uint8_t hasAnimation;

    MDLHEADERSECTION() : hasAnimation(0) { memset(name, 0, sizeof(name)); }
};

// 模型 Section
struct MDLMODELSECTION {
    uint32_t flags;
    float animationBounds[6];  // min xyz, max xyz
    uint32_t blendTime;

    MDLMODELSECTION() : flags(0), blendTime(0) {
        memset(animationBounds, 0, sizeof(animationBounds));
    }
};

// 动画序列 Section
struct MDLSEQUENCESSECTION {
    CMdlString<80> name;
    uint32_t interval[2];
    float moveSpeed;
    uint32_t flags;
    int32_t frequency;
    int32_t replay[2];
    int32_t blendTime;
    CAaBox bounds;
    int32_t nextAnimation;

    MDLSEQUENCESSECTION() : moveSpeed(0), flags(0), frequency(0), blendTime(0), nextAnimation(-1) {
        interval[0] = interval[1] = 0;
        replay[0] = replay[1] = 0;
    }
};

// 全局序列 Section
struct MDLGLOBALSEQSECTION {
    uint32_t duration;

    MDLGLOBALSEQSECTION() : duration(0) {}
};

// 声音 Section
struct MDLSOUNDSECTION {
    CMdlString<80> name;
    uint32_t flags;
    uint32_t fileId;
    uint32_t tracking;

    MDLSOUNDSECTION() : flags(0), fileId(0), tracking(0) {}
};

// 材质 Section
struct MDLMATERIALSECTION {
    uint32_t flags;
    int32_t blendMode;

    struct TextureLayer {
        uint32_t textureId;
        uint32_t tvertexAnimId;
    };

    TextureLayer textureLayers[2];

    MDLMATERIALSECTION() : flags(0), blendMode(0) {
        memset(textureLayers, 0, sizeof(textureLayers));
    }
};

// 纹理 Section
struct MDLTEXTURESECTION {
    uint32_t replaceableId;
    CMdlString<260> fileName;
    uint32_t flags;

    MDLTEXTURESECTION() : replaceableId(0), flags(0) {}
};

// 纹理动画 Section
struct MDLTEXANIMSECTION {
    uint32_t translationTrack;
    uint32_t rotationTrack;
    uint32_t scalingTrack;

    MDLTEXANIMSECTION() : translationTrack(0), rotationTrack(0), scalingTrack(0) {}
};

// 几何体 Section
struct MDLGEOSETSECTION {
    // 顶点数据
    MDLArray<C3Vector> vertices;
    MDLArray<C3Vector> normals;
    MDLArray<C2Vector> textureCoords;

    // 面数据
    MDLArray<uint16_t> triangles;

    // 矩阵组
    MDLArray<uint32_t> matrixGroups;
    MDLArray<uint8_t> matrixIndices;

    MDLGEOSETSECTION() {}
};

// 几何体动画 Section
struct MDLGEOSETANIMSECTION {
    uint32_t geosetId;
    MDLArray<MDLALPHAKEYFRAME> alphaTrack;

    MDLGEOSETANIMSECTION() : geosetId(0) {}
};

// 骨骼 Section
struct MDLBONESECTION {
    CMdlString<80> name;
    uint32_t nodeId;
    uint32_t flags;
    int32_t parentBone;
    uint32_t submeshId;
    uint32_t unknown[2];

    // 动画轨道
    MDLArray<MDLTRANSKEYFRAME> translationTrack;
    MDLArray<MDLROTKEYFRAME> rotationTrack;
    MDLArray<MDLSCALEKEYFRAME> scaleTrack;

    C3Vector pivot;

    MDLBONESECTION() : nodeId(0), flags(0), parentBone(-1), submeshId(0) {
        memset(unknown, 0, sizeof(unknown));
        pivot = C3Vector(0, 0, 0);
    }
};

// 灯光 Section
struct MDLLIGHTSECTION {
    CMdlString<80> name;
    uint32_t nodeId;
    uint32_t lightType;
    uint32_t flags;
    C3Vector position;
    uint32_t attenuation[2];

    // 动画轨道
    MDLArray<MDLCOLORKEYFRAME> ambientColorTrack;
    MDLArray<MDLINTENSITYKEYFRAME> ambientIntensityTrack;
    MDLArray<MDLCOLORKEYFRAME> diffuseColorTrack;
    MDLArray<MDLINTENSITYKEYFRAME> diffuseIntensityTrack;
    MDLArray<MDLATTENKEYFRAME> attenuationStartTrack;
    MDLArray<MDLATTENKEYFRAME> attenuationEndTrack;
    MDLArray<MDLINTKEY> visibilityTrack;

    MDLLIGHTSECTION() : lightType(0), flags(0) {
        memset(attenuation, 0, sizeof(attenuation));
    }
};

// 辅助对象 Section (Help)
struct MDLGENOBJECT {
    CMdlString<80> name;
    uint32_t nodeId;
    uint32_t type;
    uint32_t reserved;

    MDLGENOBJECT() : nodeId(0), type(0), reserved(0) {}
};

// 声音发射器 Section
struct MDLSOUNDEMITTERSECTION {
    CMdlString<80> name;
    uint32_t nodeId;
    uint32_t soundId;

    MDLArray<MDLSOUNDKEYFRAME> soundTrack;

    MDLSOUNDEMITTERSECTION() : nodeId(0), soundId(0) {}
};

// 附件 Section
struct MDLATTACHMENTSECTION {
    CMdlString<80> name;
    uint32_t nodeId;
    uint32_t attachmentId;
    C3Vector position;

    MDLArray<MDLINTKEY> visibilityTrack;

    MDLATTACHMENTSECTION() : nodeId(0), attachmentId(0) {
        position = C3Vector(0, 0, 0);
    }
};

// 粒子发射器 Section
struct MDLPARTICLEEMITTER {
    CMdlString<80> name;
    uint32_t nodeId;
    uint32_t emitterType;
    uint32_t particleColorStart;
    uint32_t particleColorMid;
    uint32_t particleColorEnd;
    float particleTextureAnimSpeed;
    uint32_t particleTextureAnimFrameCount;
    uint32_t particleTextureCoordRow;
    uint32_t particleTextureCoordCol;
    uint32_t particleTextureCoordFrameCount;
    uint32_t emissionRate;
    uint32_t speed;
    uint32_t gravity;
    uint32_t lifetime;
    uint32_t emissionAreaLength;
    uint32_t emissionAreaWidth;
    uint32_t zSource;

    MDLArray<MDLINTKEY> emissionRateTrack;
    MDLArray<MDLINTKEY> speedTrack;
    MDLArray<MDLINTKEY> gravityTrack;
    MDLArray<MDLINTKEY> lifetimeTrack;
    MDLArray<MDLINTKEY> emissionAreaLengthTrack;
    MDLArray<MDLINTKEY> emissionAreaWidthTrack;
    MDLArray<MDLINTKEY> zSourceTrack;
    MDLArray<MDLINTKEY> visibilityTrack;

    MDLPARTICLEEMITTER() : emitterType(0), particleColorStart(0), particleColorMid(0),
        particleColorEnd(0), particleTextureAnimSpeed(0), particleTextureAnimFrameCount(0),
        particleTextureCoordRow(0), particleTextureCoordCol(0), particleTextureCoordFrameCount(0),
        emissionRate(0), speed(0), gravity(0), lifetime(0), emissionAreaLength(0),
        emissionAreaWidth(0), zSource(0) {}
};

// 粒子发射器2 Section (PRE2)
struct MDLPARTICLEEMITTER2 {
    // TODO: 完整实现 PRE2 结构
    uint32_t unknown[100];

    MDLPARTICLEEMITTER2() { memset(unknown, 0, sizeof(unknown)); }
};

// 相机 Section
struct MDLCAMERASECTION {
    CMdlString<80> name;
    uint32_t nodeId;
    float fieldOfView;
    float farClip;
    float nearClip;

    MDLArray<MDLTRANSKEYFRAME> positionTrack;
    C3Vector positionPivot;
    MDLArray<MDLTRANSKEYFRAME> targetTrack;
    C3Vector targetPivot;
    MDLArray<MDLINTKEY> rollTrack;

    MDLCAMERASECTION() : fieldOfView(0), farClip(0), nearClip(0) {
        positionPivot = C3Vector(0, 0, 0);
        targetPivot = C3Vector(0, 0, 0);
    }
};

// 事件 Section
struct MDLEVENTSECTION {
    CMdlString<80> name;
    uint32_t nodeId;
    uint32_t eventtype;
    uint32_t eventdata;

    MDLArray<MDLEVENTKEY> eventTrack;

    MDLEVENTSECTION() : nodeId(0), eventtype(0), eventdata(0) {}
};

// 碰撞形状 Section
struct MDLCOLLISIONSHAPE {
    uint32_t type;  // 0=球, 1=箱
    uint32_t bone;
    C3Vector position;
    float radius;

    MDLCOLLISIONSHAPE() : type(0), bone(0), radius(0) {
        position = C3Vector(0, 0, 0);
    }
};

// 丝带发射器 Section
struct MDLRIBBONEMITTER {
    CMdlString<80> name;
    uint32_t nodeId;
    uint32_t ribbonsPerSecond;

    MDLArray<MDLTRANSKEYFRAME> colorTrack;
    MDLArray<MDLALPHAKEYFRAME> alphaTrack;
    MDLArray<MDLSCALEKEYFRAME> heightAboveTrack;
    MDLArray<MDLSCALEKEYFRAME> heightBelowTrack;

    float edgesPerSecond;
    float edgeLifetime;
    float gravity;

    uint32_t textureRows;
    uint32_t textureCols;

    MDLArray<MDLINTKEY> textureSlotTrack;
    MDLArray<MDLINTKEY> visibilityTrack;

    MDLRIBBONEMITTER() : ribbonsPerSecond(0), edgesPerSecond(0),
        edgeLifetime(0), gravity(0), textureRows(0), textureCols(0) {}
};

// ============================================================================
// MDL 通用对象指针数组
// ============================================================================

// MDLGENOBJECT* 的数组 (最多64个)
struct MDLGENOBJECTPTRARRAY {
    MDLArray<MDLGENOBJECT*> objects;
};

// ============================================================================
// MDLKEYTRACK - 动画轨道模板
// ============================================================================

// 插值类型
enum MDLTRACKTYPE {
    MDL_TRACKTYPE_NONE = 0,
    MDL_TRACKTYPE_LINEAR = 1,
    MDL_TRACKTYPE_HERMITE = 2,
    MDL_TRACKTYPE_BEZIER = 3
};

// 动画轨道模板
template<typename T>
struct MDLKEYTRACK {
    MDLTRACKTYPE interpolationType;
    MDLArray<T> globalSequence;
    MDLArray<T> keys;

    MDLKEYTRACK() : interpolationType(MDL_TRACKTYPE_NONE) {}
};

// ============================================================================
// MDLDATA - 完整模型数据
// ============================================================================

struct MDLDATA {
    // 文件头
    MDLHEADERSECTION header;

    // 模型信息
    MDLMODELSECTION model;

    // 动画序列
    MDLArray<MDLSEQUENCESSECTION> sequences;

    // 全局序列
    MDLArray<MDLGLOBALSEQSECTION> globalSequences;

    // 声音
    MDLArray<MDLSOUNDSECTION> sounds;

    // 材质
    MDLArray<MDLMATERIALSECTION> materials;

    // 纹理
    MDLArray<MDLTEXTURESECTION> textures;

    // 纹理动画
    MDLArray<MDLTEXANIMSECTION> textureAnimations;

    // 几何体
    MDLArray<MDLGEOSETSECTION> geosets;

    // 几何体动画
    MDLArray<MDLGEOSETANIMSECTION> geosetAnimations;

    // 骨骼
    MDLArray<MDLBONESECTION> bones;

    // 灯光
    MDLArray<MDLLIGHTSECTION> lights;

    // 辅助对象
    MDLArray<MDLGENOBJECT> helpers;

    // 声音发射器
    MDLArray<MDLSOUNDEMITTERSECTION> soundEmitters;

    // 附件
    MDLArray<MDLATTACHMENTSECTION> attachments;

    // 透视点
    MDLArray<C3Vector> pivotPoints;

    // 粒子发射器
    MDLArray<MDLPARTICLEEMITTER> particleEmitters;

    // 相机
    MDLArray<MDLCAMERASECTION> cameras;

    // 事件
    MDLArray<MDLEVENTSECTION> events;

    // 粒子发射器2
    MDLArray<MDLPARTICLEEMITTER2> particleEmitters2;

    // 碰撞形状
    MDLArray<MDLCOLLISIONSHAPE> collisionShapes;

    // 丝带发射器
    MDLArray<MDLRIBBONEMITTER> ribbonEmitters;

    MDLDATA() {}
};

// ============================================================================
// MDLHANDLER - 处理器类型定义
// ============================================================================

// CStatus 前向声明
class CStatus;

// MDL 处理器函数类型
typedef int (*MDLHandlerFunc)(MDLDATA& data, long tag, const char* name, CStatus* status);
typedef int (*MDLHandlerFuncConst)(const MDLDATA& data, long tag, const char* name, CStatus* status);

// MDL 处理器类型
struct MDLHANDLERTYPE {
    MDLHandlerFunc readFunc;
    MDLHandlerFuncConst writeFunc;

    MDLHANDLERTYPE() : readFunc(nullptr), writeFunc(nullptr) {}
    MDLHANDLERTYPE(MDLHandlerFunc read, MDLHandlerFuncConst write)
        : readFunc(read), writeFunc(write) {}
};

// MDL 处理器链表节点
struct MDLHANDLER {
    MDLHANDLERTYPE type;
    MDLHANDLER* next;

    MDLHANDLER() : next(nullptr) {}
};
