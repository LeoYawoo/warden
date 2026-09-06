#pragma once

#include <cstdint>
#include <string>

// Forward declarations
class CM2Model;
class CMdlModel;

// ============================================================================
// ModelCreate - 模型创建工厂
// 根据文件扩展名创建对应的模型实例
// ============================================================================

class ModelCreate {
public:
    // 创建模型 (根据文件类型自动选择)
    static void* CreateModel(const char* filePath);

    // 创建 M2 模型 (WoW)
    static CM2Model* CreateM2Model(const char* filePath);

    // 创建 MDL 模型 (WC3)
    static CMdlModel* CreateMdlModel(const char* filePath);

    // 检查文件类型
    static bool IsM2File(const char* filePath);
    static bool IsMdlFile(const char* filePath);

    // 获取文件扩展名
    static std::string GetExtension(const char* filePath);
};
