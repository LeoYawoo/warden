#!/usr/bin/env python3
"""
MDX 文件解析验证脚本
用于快速验证 MDX 文件结构和解析逻辑
"""

import struct
import os
from dataclasses import dataclass
from typing import List, Optional, Dict, Any
from pathlib import Path

# ============================================================================
# 数据结构
# ============================================================================

@dataclass
class MDLChunk:
    """MDL Chunk 数据"""
    tag: str
    size: int
    data: bytes
    offset: int

@dataclass
class MDLSequence:
    """动画序列"""
    name: str
    interval: tuple
    move_speed: float
    flags: int
    frequency: int
    replay: tuple
    blend_time: int

@dataclass
class MDLTexture:
    """纹理"""
    replaceable_id: int
    filename: str
    flags: int

@dataclass
class MDLMaterial:
    """材质"""
    flags: int
    blend_mode: int

@dataclass
class MDLBone:
    """骨骼"""
    name: str
    node_id: int
    flags: int
    parent_bone: int

# ============================================================================
# MDX 解析器
# ============================================================================

class MDXParser:
    """MDX 文件解析器"""

    def __init__(self):
        self.chunks: List[MDLChunk] = []
        self.sequences: List[MDLSequence] = []
        self.textures: List[MDLTexture] = []
        self.materials: List[MDLMaterial] = []
        self.bones: List[MDLBone] = []
        self.header: Optional[Dict[str, Any]] = None
        self.version: int = 0

    def parse_file(self, filepath: str) -> bool:
        """解析 MDX 文件"""
        if not os.path.exists(filepath):
            print(f"Error: File not found: {filepath}")
            return False

        with open(filepath, 'rb') as f:
            data = f.read()

        return self.parse_data(data)

    def parse_data(self, data: bytes) -> bool:
        """解析 MDX 数据"""
        if len(data) < 12:
            print("Error: File too small")
            return False

        # 检查签名
        signature = data[0:4]
        if signature != b'MDLX':
            print(f"Error: Invalid signature: {signature}")
            return False

        print(f"MDX Signature: {signature.decode('ascii')}")

        # 解析 VERS chunk (版本)
        offset = 4
        if data[offset:offset+4] == b'VERS':
            self.version = struct.unpack('<I', data[offset+8:offset+12])[0]
            print(f"MDX Version: {self.version}")
            offset += 12  # 跳过 VERS chunk

        # 解析其他 chunks
        while offset < len(data) - 8:
            # 读取 chunk 标签
            tag = data[offset:offset+4]

            # 读取 chunk 大小
            size = struct.unpack('<I', data[offset+4:offset+8])[0]

            # 检查大小是否合理
            if size < 8 or offset + size > len(data):
                print(f"Warning: Invalid chunk size {size} at offset {offset}")
                break

            # 读取 chunk 数据
            chunk_data = data[offset+8:offset+size]

            chunk = MDLChunk(
                tag=tag.decode('ascii', errors='replace'),
                size=size,
                data=chunk_data,
                offset=offset
            )
            self.chunks.append(chunk)

            # 解析 chunk 内容
            self._parse_chunk(chunk)

            offset += size

        return True

    def _parse_chunk(self, chunk: MDLChunk):
        """解析单个 chunk"""
        if chunk.tag == 'MODL':
            self._parse_model(chunk)
        elif chunk.tag == 'SEQS':
            self._parse_sequences(chunk)
        elif chunk.tag == 'TEXS':
            self._parse_textures(chunk)
        elif chunk.tag == 'MATS':
            self._parse_materials(chunk)
        elif chunk.tag == 'BONE':
            self._parse_bones(chunk)

    def _parse_model(self, chunk: MDLChunk):
        """解析模型信息"""
        data = chunk.data
        if len(data) > 80:
            name = data[0:80].split(b'\x00')[0].decode('ascii', errors='replace')
            print(f"Model name: {name}")

    def _parse_sequences(self, chunk: MDLChunk):
        """解析动画序列"""
        offset = 0
        data = chunk.data

        # 先读取序列数量
        if len(data) >= 4:
            count = struct.unpack('<I', data[0:4])[0]
            print(f"Sequence count: {count}")
            offset = 4

            # 每个序列 132 字节
            while offset + 132 <= len(data) and len(self.sequences) < count:
                name = data[offset:offset+80].split(b'\x00')[0].decode('ascii', errors='replace')
                interval = struct.unpack('<II', data[offset+80:offset+88])
                move_speed = struct.unpack('<f', data[offset+88:offset+92])[0]
                flags = struct.unpack('<I', data[offset+92:offset+96])[0]
                frequency = struct.unpack('<i', data[offset+96:offset+100])[0]
                replay = struct.unpack('<ii', data[offset+100:offset+108])
                blend_time = struct.unpack('<i', data[offset+108:offset+112])[0]

                seq = MDLSequence(
                    name=name,
                    interval=interval,
                    move_speed=move_speed,
                    flags=flags,
                    frequency=frequency,
                    replay=replay,
                    blend_time=blend_time
                )
                self.sequences.append(seq)

                offset += 132

    def _parse_textures(self, chunk: MDLChunk):
        """解析纹理"""
        offset = 0
        data = chunk.data

        # 先读取纹理数量
        if len(data) >= 4:
            count = struct.unpack('<I', data[0:4])[0]
            print(f"Texture count: {count}")
            offset = 4

            # 每个纹理 268 字节
            while offset + 268 <= len(data) and len(self.textures) < count:
                replaceable_id = struct.unpack('<I', data[offset:offset+4])[0]
                filename = data[offset+4:offset+264].split(b'\x00')[0].decode('ascii', errors='replace')
                flags = struct.unpack('<I', data[offset+264:offset+268])[0]

                tex = MDLTexture(
                    replaceable_id=replaceable_id,
                    filename=filename,
                    flags=flags
                )
                self.textures.append(tex)

                offset += 268

    def _parse_materials(self, chunk: MDLChunk):
        """解析材质"""
        offset = 0
        data = chunk.data

        # 先读取材质数量
        if len(data) >= 4:
            count = struct.unpack('<I', data[0:4])[0]
            print(f"Material count: {count}")
            offset = 4

            # 每个材质 16 字节
            while offset + 16 <= len(data) and len(self.materials) < count:
                flags = struct.unpack('<I', data[offset:offset+4])[0]
                blend_mode = struct.unpack('<i', data[offset+4:offset+8])[0]

                mat = MDLMaterial(
                    flags=flags,
                    blend_mode=blend_mode
                )
                self.materials.append(mat)

                offset += 16

    def _parse_bones(self, chunk: MDLChunk):
        """解析骨骼"""
        offset = 0
        data = chunk.data

        # 先读取骨骼数量
        if len(data) >= 4:
            count = struct.unpack('<I', data[0:4])[0]
            print(f"Bone count: {count}")
            offset = 4

            # 骨骼结构比较复杂，这里简化处理
            while offset + 80 <= len(data) and len(self.bones) < count:
                name = data[offset:offset+80].split(b'\x00')[0].decode('ascii', errors='replace')
                if name:
                    bone = MDLBone(
                        name=name,
                        node_id=0,
                        flags=0,
                        parent_bone=-1
                    )
                    self.bones.append(bone)

                offset += 80

    def print_info(self):
        """打印解析信息"""
        print(f"\n{'='*60}")
        print(f"MDX File Information")
        print(f"{'='*60}")

        print(f"\nChunks found: {len(self.chunks)}")
        for chunk in self.chunks:
            print(f"  - {chunk.tag}: {chunk.size} bytes at offset {chunk.offset}")

        print(f"\nSequences: {len(self.sequences)}")
        for i, seq in enumerate(self.sequences[:5]):  # 只显示前5个
            print(f"  [{i}] {seq.name}: {seq.interval[0]}-{seq.interval[1]} ms")

        print(f"\nTextures: {len(self.textures)}")
        for i, tex in enumerate(self.textures[:5]):
            print(f"  [{i}] {tex.filename or f'Replaceable {tex.replaceable_id}'}")

        print(f"\nMaterials: {len(self.materials)}")
        print(f"Bones: {len(self.bones)}")

# ============================================================================
# 测试函数
# ============================================================================

def test_mdx_file(filepath: str):
    """测试 MDX 文件解析"""
    print(f"\nTesting: {filepath}")
    print(f"File size: {os.path.getsize(filepath)} bytes")

    parser = MDXParser()
    if parser.parse_file(filepath):
        parser.print_info()
        return True
    return False

def main():
    """主函数"""
    # 测试文件路径
    test_files = [
        "data/mpq/war3.mpq.unpack/Units/Human/Footman/Footman.mdx",
        "data/mpq/war3.mpq.unpack/Abilities/Spells/Human/Heal/HealTarget.mdx",
    ]

    success_count = 0
    total_count = 0

    for filepath in test_files:
        if os.path.exists(filepath):
            total_count += 1
            if test_mdx_file(filepath):
                success_count += 1
        else:
            print(f"Skipping: {filepath} (not found)")

    print(f"\n{'='*60}")
    print(f"Results: {success_count}/{total_count} files parsed successfully")
    print(f"{'='*60}")

    return 0 if success_count == total_count else 1

if __name__ == '__main__':
    exit(main())
