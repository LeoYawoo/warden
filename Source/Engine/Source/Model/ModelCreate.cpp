#include "ModelCreate.h"
#include "../Anim/CMdlModel.h"
#include "../Anim/CM2Model.h"
#include "../Base/Status.h"
#include <algorithm>
#include <cctype>

// ============================================================================
// 模型创建工厂实现
// ============================================================================

void* ModelCreate::CreateModel(const char* filePath) {
    if (!filePath) return nullptr;

    if (IsMdlFile(filePath)) {
        return CreateMdlModel(filePath);
    }

    if (IsM2File(filePath)) {
        return CreateM2Model(filePath);
    }

    return nullptr;
}

CM2Model* ModelCreate::CreateM2Model(const char* filePath) {
    // TODO: 实现 M2 模型创建
    // CM2Model* model = CM2Model::AllocModel(nullptr);
    // if (model) {
    //     model->Load(filePath);
    // }
    return nullptr;
}

CMdlModel* ModelCreate::CreateMdlModel(const char* filePath) {
    CMdlModel* model = new CMdlModel();
    Status status;

    if (!model->Load(filePath, status)) {
        delete model;
        return nullptr;
    }

    return model;
}

bool ModelCreate::IsM2File(const char* filePath) {
    std::string ext = GetExtension(filePath);
    return ext == ".m2" || ext == ".M2";
}

bool ModelCreate::IsMdlFile(const char* filePath) {
    std::string ext = GetExtension(filePath);
    return ext == ".mdx" || ext == ".MDX" || ext == ".mdl" || ext == ".MDL";
}

std::string ModelCreate::GetExtension(const char* filePath) {
    if (!filePath) return "";

    std::string path(filePath);
    size_t pos = path.rfind('.');

    if (pos == std::string::npos) {
        return "";
    }

    std::string ext = path.substr(pos);

    // 转换为小写
    std::transform(ext.begin(), ext.end(), ext.begin(),
        [](unsigned char c) { return static_cast<char>(std::tolower(c)); });

    return ext;
}
