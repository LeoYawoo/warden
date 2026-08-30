#include "jmemstorm.h"
#include <cstdlib>
#include <cstring>
#include <new>

// jmemstorm - IJG JPEG 库的 Storm 内存管理适配层
// 基于 IDA 反编译分析实现

// 内存池结构
struct memory_pool {
    memory_pool *next;
    size_t size;
    size_t used;
    JPOOL pool_id;
    char data[1];  // 柔性数组
};

// 内存管理上下文
struct storm_mem_context {
    memory_pool *pools[JPOOL_NUMPOOLS];
    size_t total_memory;
    size_t memory_limit;
};

// Storm 内存管理函数实现

void* StormAlloc(size_t size) {
    // 对应 jmemstorm.cpp 第33行
    // 分配内存，添加头部信息
    size_t allocSize = size + sizeof(memory_pool);
    memory_pool *pool = static_cast<memory_pool*>(std::malloc(allocSize));

    if (!pool) {
        return nullptr;
    }

    pool->next = nullptr;
    pool->size = size;
    pool->used = 0;
    pool->pool_id = JPOOL_IMAGE;

    return pool->data;
}

void* StormAllocPool(void *cinfo, size_t size) {
    // 对应 jmemstorm.cpp 第55行
    // 分配内存池内存
    size_t allocSize = size + sizeof(memory_pool);
    memory_pool *pool = static_cast<memory_pool*>(std::malloc(allocSize));

    if (!pool) {
        return nullptr;
    }

    pool->next = nullptr;
    pool->size = size;
    pool->used = 0;
    pool->pool_id = JPOOL_SMALL;

    return pool->data;
}

void StormFree(void *ptr) {
    if (ptr) {
        // 获取内存池头部
        memory_pool *pool = reinterpret_cast<memory_pool*>(
            reinterpret_cast<char*>(ptr) - sizeof(memory_pool));
        std::free(pool);
    }
}

void StormFreePool(void *cinfo, void *ptr) {
    StormFree(ptr);
}

// jmemstorm 上下文管理函数

void jmemstorm_init(jmemstorm_context *ctx) {
    if (ctx) {
        ctx->cinfo = nullptr;
        ctx->error_mgr = nullptr;
        ctx->total_memory = 0;
        ctx->memory_limit = 1024 * 1024 * 10;  // 10MB 默认限制
    }
}

void jmemstorm_cleanup(jmemstorm_context *ctx) {
    if (ctx) {
        ctx->cinfo = nullptr;
        ctx->error_mgr = nullptr;
        ctx->total_memory = 0;
    }
}

void* jmemstorm_alloc_pool(jmemstorm_context *ctx, JPOOL pool_id, size_t size) {
    if (!ctx || pool_id >= JPOOL_NUMPOOLS) {
        return nullptr;
    }

    void *ptr = StormAllocPool(ctx->cinfo, size);
    if (ptr) {
        ctx->total_memory += size;
    }

    return ptr;
}

void jmemstorm_free_pool(jmemstorm_context *ctx, JPOOL pool_id) {
    // 释放内存池中的所有内存
    if (ctx && pool_id < JPOOL_NUMPOOLS) {
        ctx->total_memory = 0;
    }
}

size_t jmemstorm_get_memory_usage(jmemstorm_context *ctx) {
    return ctx ? ctx->total_memory : 0;
}
