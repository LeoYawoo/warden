#pragma once

#include <cstdint>
#include <cstddef>

// jmemstorm - IJG JPEG 库的 Storm 内存管理适配层
// 用于 BLP 文件中的 JPEG 解码

// 内存池类型
enum JPOOL {
    JPOOL_IMAGE = 0,
    JPOOL_SMALL = 1,
    JPOOL_LARGE = 2,
    JPOOL_NUMPOOLS = 3
};

// JPEG 内存管理上下文
struct jmemstorm_context {
    void *cinfo;
    void *error_mgr;
    size_t total_memory;
    size_t memory_limit;
};

// Storm 内存管理函数接口
// 这些函数在 jmemstorm.cpp 中实现，使用 Storm 库的内存管理

// 分配内存（对应 sub_6D2CEC - 第33行）
void* StormAlloc(size_t size);

// 分配内存（对应 sub_6D2D5C - 第55行）
void* StormAllocPool(void *cinfo, size_t size);

// 释放内存（对应 sub_6D2D24）
void StormFree(void *ptr);

// 释放内存（对应 sub_6D2D94）
void StormFreePool(void *cinfo, void *ptr);

// 初始化 jmemstorm 上下文
void jmemstorm_init(jmemstorm_context *ctx);

// 清理 jmemstorm 上下文
void jmemstorm_cleanup(jmemstorm_context *ctx);

// 分配内存池
void* jmemstorm_alloc_pool(jmemstorm_context *ctx, JPOOL pool_id, size_t size);

// 释放内存池
void jmemstorm_free_pool(jmemstorm_context *ctx, JPOOL pool_id);

// 获取内存使用统计
size_t jmemstorm_get_memory_usage(jmemstorm_context *ctx);
