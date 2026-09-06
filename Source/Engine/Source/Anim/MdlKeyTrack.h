#pragma once

#include "MdlData.h"
#include <cmath>

// ============================================================================
// MDLKEYTRACK 辅助函数
// ============================================================================

// 查找关键帧索引
template<typename T>
void MdlFindKey(const MDLKEYTRACK<T>& track, uint32_t time, uint32_t& keyIndex, float& ratio) {
    if (track.keys.Count() == 0) {
        keyIndex = 0;
        ratio = 0.0f;
        return;
    }

    if (track.keys.Count() == 1) {
        keyIndex = 0;
        ratio = 0.0f;
        return;
    }

    // 二分查找
    uint32_t low = 0;
    uint32_t high = track.keys.Count() - 1;

    while (low < high) {
        uint32_t mid = (low + high) / 2;
        if (track.keys[mid].time < time) {
            low = mid + 1;
        } else {
            high = mid;
        }
    }

    keyIndex = low;

    // 计算插值比例
    if (keyIndex > 0) {
        uint32_t prevTime = track.keys[keyIndex - 1].time;
        uint32_t currTime = track.keys[keyIndex].time;

        if (currTime > prevTime) {
            ratio = static_cast<float>(time - prevTime) / static_cast<float>(currTime - prevTime);
        } else {
            ratio = 0.0f;
        }
    } else {
        ratio = 0.0f;
    }
}

// ============================================================================
// 插值函数
// ============================================================================

// 线性插值 (float)
inline float MdlLerp(float a, float b, float t) {
    return a + (b - a) * t;
}

// 线性插值 (C3Vector)
inline C3Vector MdlLerp(const C3Vector& a, const C3Vector& b, float t) {
    return C3Vector(
        a.x + (b.x - a.x) * t,
        a.y + (b.y - a.y) * t,
        a.z + (b.z - a.z) * t
    );
}

// 线性插值 (C2Vector)
inline C2Vector MdlLerp(const C2Vector& a, const C2Vector& b, float t) {
    return C2Vector(
        a.x + (b.x - a.x) * t,
        a.y + (b.y - a.y) * t
    );
}

// 四元数球面线性插值 (SLerp)
inline MDLROTKEYFRAME MdlSlerp(const MDLROTKEYFRAME& a, const MDLROTKEYFRAME& b, float t) {
    float dot = a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;

    // 如果点积为负，反转一个四元数以确保最短路径
    MDLROTKEYFRAME b2 = b;
    if (dot < 0.0f) {
        b2.x = -b2.x;
        b2.y = -b2.y;
        b2.z = -b2.z;
        b2.w = -b2.w;
        dot = -dot;
    }

    // 如果点积接近1，使用线性插值
    if (dot > 0.9995f) {
        return MDLROTKEYFRAME(
            a.x + (b2.x - a.x) * t,
            a.y + (b2.y - a.y) * t,
            a.z + (b2.z - a.z) * t,
            a.w + (b2.w - a.w) * t,
            a.time
        );
    }

    float angle = acosf(dot);
    float sinAngle = sinf(angle);
    float factorA = sinf((1.0f - t) * angle) / sinAngle;
    float factorB = sinf(t * angle) / sinAngle;

    return MDLROTKEYFRAME(
        a.x * factorA + b2.x * factorB,
        a.y * factorA + b2.y * factorB,
        a.z * factorA + b2.z * factorB,
        a.w * factorA + b2.w * factorB,
        a.time
    );
}

// 颜色插值
inline MDLCOLORKEYFRAME MdlLerpColor(const MDLCOLORKEYFRAME& a, const MDLCOLORKEYFRAME& b, float t) {
    return MDLCOLORKEYFRAME(
        static_cast<uint8_t>(a.r + (b.r - a.r) * t),
        static_cast<uint8_t>(a.g + (b.g - a.g) * t),
        static_cast<uint8_t>(a.b + (b.b - a.b) * t),
        a.time
    );
}

// ============================================================================
// 关键帧获取函数
// ============================================================================

// 获取位移值
inline C3Vector MdlGetTransValue(const MDLKEYTRACK<MDLTRANSKEYFRAME>& track, uint32_t time) {
    if (track.keys.Count() == 0) {
        return C3Vector(0, 0, 0);
    }

    if (track.keys.Count() == 1) {
        return C3Vector(track.keys[0].x, track.keys[0].y, track.keys[0].z);
    }

    uint32_t keyIndex;
    float ratio;
    MdlFindKey(track, time, keyIndex, ratio);

    if (keyIndex == 0) {
        return C3Vector(track.keys[0].x, track.keys[0].y, track.keys[0].z);
    }

    const auto& a = track.keys[keyIndex - 1];
    const auto& b = track.keys[keyIndex];

    C3Vector va(a.x, a.y, a.z);
    C3Vector vb(b.x, b.y, b.z);

    if (track.interpolationType == MDL_TRACKTYPE_LINEAR) {
        return MdlLerp(va, vb, ratio);
    }

    // Hermite 插值 (简化版)
    return MdlLerp(va, vb, ratio);
}

// 获取旋转值
inline MDLROTKEYFRAME MdlGetRotValue(const MDLKEYTRACK<MDLROTKEYFRAME>& track, uint32_t time) {
    if (track.keys.Count() == 0) {
        return MDLROTKEYFRAME(0, 0, 0, 1.0f, 0);
    }

    if (track.keys.Count() == 1) {
        return track.keys[0];
    }

    uint32_t keyIndex;
    float ratio;
    MdlFindKey(track, time, keyIndex, ratio);

    if (keyIndex == 0) {
        return track.keys[0];
    }

    const auto& a = track.keys[keyIndex - 1];
    const auto& b = track.keys[keyIndex];

    if (track.interpolationType == MDL_TRACKTYPE_LINEAR) {
        return MdlSlerp(a, b, ratio);
    }

    // Hermite 插值 (简化版)
    return MdlSlerp(a, b, ratio);
}

// 获取缩放值
inline C3Vector MdlGetScaleValue(const MDLKEYTRACK<MDLSCALEKEYFRAME>& track, uint32_t time) {
    if (track.keys.Count() == 0) {
        return C3Vector(1.0f, 1.0f, 1.0f);
    }

    if (track.keys.Count() == 1) {
        return C3Vector(track.keys[0].x, track.keys[0].y, track.keys[0].z);
    }

    uint32_t keyIndex;
    float ratio;
    MdlFindKey(track, time, keyIndex, ratio);

    if (keyIndex == 0) {
        return C3Vector(track.keys[0].x, track.keys[0].y, track.keys[0].z);
    }

    const auto& a = track.keys[keyIndex - 1];
    const auto& b = track.keys[keyIndex];

    C3Vector va(a.x, a.y, a.z);
    C3Vector vb(b.x, b.y, b.z);

    if (track.interpolationType == MDL_TRACKTYPE_LINEAR) {
        return MdlLerp(va, vb, ratio);
    }

    return MdlLerp(va, vb, ratio);
}

// 获取透明度值
inline float MdlGetAlphaValue(const MDLKEYTRACK<MDLALPHAKEYFRAME>& track, uint32_t time) {
    if (track.keys.Count() == 0) {
        return 1.0f;
    }

    if (track.keys.Count() == 1) {
        return track.keys[0].alpha;
    }

    uint32_t keyIndex;
    float ratio;
    MdlFindKey(track, time, keyIndex, ratio);

    if (keyIndex == 0) {
        return track.keys[0].alpha;
    }

    const auto& a = track.keys[keyIndex - 1];
    const auto& b = track.keys[keyIndex];

    if (track.interpolationType == MDL_TRACKTYPE_LINEAR) {
        return MdlLerp(a.alpha, b.alpha, ratio);
    }

    return MdlLerp(a.alpha, b.alpha, ratio);
}

// 获取颜色值
inline MDLCOLORKEYFRAME MdlGetColorValue(const MDLKEYTRACK<MDLCOLORKEYFRAME>& track, uint32_t time) {
    if (track.keys.Count() == 0) {
        return MDLCOLORKEYFRAME(255, 255, 255, 0);
    }

    if (track.keys.Count() == 1) {
        return track.keys[0];
    }

    uint32_t keyIndex;
    float ratio;
    MdlFindKey(track, time, keyIndex, ratio);

    if (keyIndex == 0) {
        return track.keys[0];
    }

    const auto& a = track.keys[keyIndex - 1];
    const auto& b = track.keys[keyIndex];

    if (track.interpolationType == MDL_TRACKTYPE_LINEAR) {
        return MdlLerpColor(a, b, ratio);
    }

    return MdlLerpColor(a, b, ratio);
}
