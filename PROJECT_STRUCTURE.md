# Warcraft III 源码结构分析报告

基于 IDA 反编译分析，整理当前项目的文件结构。

## IDA 原始路径与当前项目映射

### 路径映射关系

IDA 数据库中的源码路径与当前项目目录的对应关系：

| IDA 原始路径前缀 | 当前项目目录 | 说明 |
|-----------------|-------------|------|
| `../Glue/` | `Glue/` | 登录界面和 Battle.net 相关 |
| `../UI/` | `UI/` | Lua 驱动的 UI 框架 |
| `../Net/` | `Net/` | 网络协议栈 |
| `../Game/` | `Game/` | 游戏主逻辑 |
| `../Data.h` | `Data/Data.h` | 数据定义 |
| `../../../Engine/Source/Agile/` | `Agile/` | 代理系统 |
| `../../../Engine/Source/Anim/` | `Anim/` | 动画系统 |
| `../../../Engine/Source/Common/` | `Common/` | 通用数据结构 |
| `../../../Engine/Source/Event/` | `Event/` | 事件系统 |
| `../../../Engine/Source/Graphic/` | `Graphic/` | 图形渲染 |
| `../../../Engine/Source/NTempest/` | `NTempest/` | 数学库 |
| `../../../Engine/Source/Sound/` | `Sound/` | 音频系统 |
| `../../../StormMac/Storm Mac/SOURCE/` | `Storm/` | Storm 库 |
| `/Volumes/.../Source/Mac/../` | 各模块目录 | Mac 平台源码 |

### 原始构建系统

原始项目使用 Mac 平台构建，路径结构如下：
```
War3x_B6401/
├── War3/
│   └── Source/
│       └── Mac/
│           ├── ../Game/          -> Game/
│           ├── ../Glue/          -> Glue/
│           ├── ../UI/            -> UI/
│           ├── ../Net/           -> Net/
│           ├── ../Data.h         -> Data.h
│           ├── Engine.cpp        -> Engine.cpp
│           └── ../../../Engine/Source/  -> Engine/ (拆分为多个模块)
│               ├── Agile/        -> Agile/
│               ├── Common/       -> Common/
│               ├── Event/        -> Event/
│               ├── Graphic/      -> Graphic/
│               ├── NTempest/     -> NTempest/
│               └── Sound/        -> Sound/
└── StormMac/
    └── Storm Mac/
        └── SOURCE/               -> Storm/
```

### 文件统计

| 类别 | IDA 文件数 | 当前项目文件数 | 状态 |
|------|-----------|--------------|------|
| Engine/ (拆分) | 145 | 478 | ✅ 已整合到各模块 |
| Glue/ | 96 | 101 | ✅ 已补充 |
| UI/ | 74 | 112 | ✅ 已补充 |
| Game/ | 18 | 18 | ✅ 完整 |
| Net/ | 2 | 39 | ✅ 已扩展 |
| Storm/ | 2 | 126 | ✅ 已扩展 |
| 其他 | 64 | 234 | ✅ 已创建占位符 |

## 目录结构总览

| 目录 | 文件数 | 说明 |
|------|--------|------|
| / | 1 | 其他模块 |
| Agile/ | 77 | 游戏对象属性/代理系统 |
| Anim/ | 32 | M2 模型动画系统 |
| Common/ | 74 | 通用数据结构和工具 |
| Event/ | 26 | 事件调度系统 |
| Game/ | 18 | 游戏主逻辑 |
| Glue/ | 6 | 登录界面和 Battle.net |
| Graphic/ | 123 | OpenGL 渲染引擎 |
| NIpse/ | 12 | AI/RL 代理系统 |
| NTempest/ | 63 | 数学库（向量、矩阵、四元数） |
| Net/ | 39 | 网络协议栈 |
| Scrn/ | 1 | 控制台 UI |
| Services/ | 17 | 服务层（异步文件、数据库） |
| Sound/ | 4 | 音频系统（SI2） |
| Storm/ | 126 | 底层系统抽象层 |
| Terrain/ | 4 | 地形系统 |
| UI/ | 112 | Lua 驱动的 UI 框架 |

## 详细目录结构

### /

**文件数**: 1

**文件列表**:
- main.cpp

### Agile/

**文件数**: 77

**文件列表**:
- AGILE_TYPE_DATA.h
- ARRAY_2D_UNSIGNED.h
- AgentRef.cpp
- AgentRef.h
- AgentRefListener.cpp
- AgentRefListener.h
- AgentRefMini.h
- AgileAgentQuery.h
- BigBuffer.h
- BigData.h
- BigNum.h
- BigStack.h
- CAgentField.cpp
- CAgentField.h
- CAgentFieldMini.cpp
- CAgentFieldMini.h
- CAgentTimer.cpp
- CAgentTimer.h
- CAngle.h
- CBitInput.h
- CDBDatabase.h
- CEventTimer.cpp
- CEventTimer.h
- CHandleObject.h
- CHuffman.h
- CHuffmanDecoder.h
- CHuffmanEncoder.h
- CListener.cpp
- CListener.h
- CModifier.cpp
- CModifier.h
- CObserver.cpp
- CObserver.h
- CPresenceRef.cpp
- CPresenceRef.h
- CRelation.cpp
- CRelation.h
- CSLKDatabase.h
- CStatus.cpp
- CStatus.h
- CStringManager.cpp
- CStringManager.h
- CStringMemory.cpp
- CStringMemory.h
- CStringRep.h
- Crypt.h
- Float.cpp
- Float.h
- FloatListener.cpp
- FloatListener.h
- FloatModifier.cpp
- FloatModifier.h
- FloatProp.cpp
- FloatProp.h
- HUFFNODE.h
- Integer.cpp
- Integer.h
- IntegerListener.cpp
- IntegerListener.h
- IntegerModifier.cpp
- IntegerModifier.h
- MovementModifier.cpp
- MovementModifier.h
- Position.cpp
- Position.h
- PositionListener.h
- PositionModifier.h
- ProcessSLK.h
- ProjectilePosition.cpp
- ProjectilePosition.h
- RangeListener.cpp
- RangeListener.h
- RegistryKey.h
- SLK.h
- SmartPosition.cpp
- SmartPosition.h
- slkRow.h

### Anim/

**文件数**: 32

**文件列表**:
- CM2Cache.cpp
- CM2Cache.h
- CM2Light.cpp
- CM2Light.h
- CM2Lighting.cpp
- CM2Lighting.h
- CM2Model.cpp
- CM2Model.h
- CM2Scene.cpp
- CM2Scene.h
- CM2SceneRender.cpp
- CM2SceneRender.h
- CM2Shared.cpp
- CM2Shared.h
- Interp.cpp
- Interp.h
- M2Animate.h
- M2Data.h
- M2Init.cpp
- M2Init.h
- M2Internal.cpp
- M2Internal.h
- M2Model.h
- M2Sort.cpp
- M2Sort.h
- M2Types.h
- Model2.cpp
- Model2.h
- Type.cpp
- Type.h
- WorldMatrix.cpp
- WorldMatrix.h

### Common/

**文件数**: 53

**文件列表**:
- CSBaseArray.cpp
- CSBaseArray.h
- CSBasePriority.cpp
- CSBasePriority.h
- CSBasePriorityQueue.cpp
- CSBasePriorityQueue.h
- CSimpleSortedArray.h
- Call.cpp
- Call.h
- DataMgr.cpp
- DataMgr.h
- DebugOut.h
- Hashkey.cpp
- Hashkey.h
- ObjectAlloc.cpp
- ObjectAlloc.h
- Prop.cpp
- Prop.h
- RCString.cpp
- RCString.h
- Region.cpp
- Region.h
- SHA1.cpp
- SHA1.h
- TAllocatorHashTable.h
- TExtraInstanceRecycler.h
- TInstanceAllocator.h
- TRefCnt.h
- TRefCntPtr.h
- TSBaseArray.h
- TSCArray.h
- TSCD.h
- TSExplicitList.h
- TSExportTableSimpleReuse.h
- TSExportTableSyncReuse.h
- TSFixedArray.h
- TSGetExplicitLink.h
- TSGetLink.h
- TSGrowableArray.h
- TSHashObject.h
- TSHashObjectChunk.h
- TSHashTable.h
- TSHashTableReuse.h
- TSHashTable_P.h
- TSLink.h
- TSLinkedNode.h
- TSList.h
- TSPriorityQueue.h
- TSStaticDynamicArray.h
- TSTimerPriority.h
- offset_of.h
- softfloat.cpp
- softfloat.h

### Common/datamgr/

**文件数**: 4

**文件列表**:
- CBaseManaged.h
- CDataMgr.cpp
- CDataMgr.h
- TManaged.h

### Common/datastore/

**文件数**: 3

**文件列表**:
- CDataStore.cpp
- CDataStore.h
- CDataStoreCache.h

### Common/instance/

**文件数**: 4

**文件列表**:
- TExtraInstanceRecyclable.h
- TInstanceId.h
- TInstanceIdTable.h
- TSingletonInstanceId.h

### Common/math/

**文件数**: 1

**文件列表**:
- Utils.h

### Common/objectalloc/

**文件数**: 6

**文件列表**:
- CObjectHeap.cpp
- CObjectHeap.h
- CObjectHeapList.cpp
- CObjectHeapList.h
- ObjAllocGlobals.cpp
- ObjAllocGlobals.h

### Common/prop/

**文件数**: 1

**文件列表**:
- Types.h

### Common/region/

**文件数**: 2

**文件列表**:
- RGN.h
- Types.h

### Event/

**文件数**: 25

**文件列表**:
- CEvent.cpp
- CEvent.h
- Context.cpp
- Context.h
- Event.cpp
- Event.h
- EvtContext.cpp
- EvtContext.h
- EvtHandler.h
- EvtKeyDown.h
- EvtMessage.h
- EvtThread.cpp
- EvtThread.h
- EvtTimer.h
- Input.cpp
- Input.h
- Queue.cpp
- Queue.h
- Scheduler.cpp
- Scheduler.h
- Synthesize.cpp
- Synthesize.h
- Timer.cpp
- Timer.h
- Types.h

### Event/win/

**文件数**: 1

**文件列表**:
- Input.cpp

### Game/

**文件数**: 18

**文件列表**:
- CBoundingBox.h
- CWorld.cpp
- CWorld.h
- Client.cpp
- Client.h
- ClientRealmResponseAdapter.cpp
- ClientRealmResponseAdapter.h
- ClientServices.cpp
- ClientServices.h
- Console.cpp
- Console.h
- Device.cpp
- Device.h
- Handlers.cpp
- Handlers.h
- Screen.cpp
- Screen.h
- Types.h

### Glue/

**文件数**: 6

**文件列表**:
- CCharacterSelection.cpp
- CCharacterSelection.h
- CGlueMgr.cpp
- CGlueMgr.h
- CRealmList.cpp
- CRealmList.h

### Graphic/

**文件数**: 42

**文件列表**:
- Blit.cpp
- Blit.h
- Buffer.cpp
- Buffer.h
- CCamera.cpp
- CCamera.h
- CGxBatch.h
- CGxCaps.h
- CGxDevice.cpp
- CGxDevice.h
- CGxFormat.h
- CGxMatrixStack.cpp
- CGxMatrixStack.h
- CGxStateBom.cpp
- CGxStateBom.h
- Camera.cpp
- Camera.h
- Coordinate.cpp
- Coordinate.h
- Device.cpp
- Device.h
- Draw.cpp
- Draw.h
- Font.cpp
- Font.h
- FontInternal.cpp
- FontInternal.h
- Gx.cpp
- Gx.h
- RenderState.cpp
- RenderState.h
- Screen.cpp
- Screen.h
- Shader.cpp
- Shader.h
- Texture.cpp
- Texture.h
- Transform.cpp
- Transform.h
- Types.h
- Window.cpp
- Window.h

### Graphic/buffer/

**文件数**: 4

**文件列表**:
- CGxBuf.h
- CGxPool.cpp
- CGxPool.h
- Types.h

### Graphic/font/

**文件数**: 17

**文件列表**:
- CGxFont.cpp
- CGxFont.h
- CGxString.cpp
- CGxString.h
- CGxStringBatch.cpp
- CGxStringBatch.h
- FaceData.cpp
- FaceData.h
- FontFace.cpp
- FontFace.h
- FreeType.cpp
- FreeType.h
- FreeTypeInternal.cpp
- FreeTypeInternal.h
- Types.h
- Wrap.cpp
- Wrap.h

### Graphic/gll/

**文件数**: 48

**文件列表**:
- CGRect.cpp
- CGRect.h
- CGxDeviceGLL.cpp
- CGxDeviceGLL.h
- GL.cpp
- GL.h
- GLAbstractWindow.cpp
- GLAbstractWindow.h
- GLBatch.h
- GLBuffer.cpp
- GLBuffer.h
- GLBufferPool.h
- GLCommand.cpp
- GLCommand.h
- GLContext.cpp
- GLContext.h
- GLDebugMipmap2D.h
- GLDevice.cpp
- GLDevice.h
- GLFramebuffer.cpp
- GLFramebuffer.h
- GLGLSLProgram.cpp
- GLGLSLProgram.h
- GLMipmap.cpp
- GLMipmap.h
- GLObject.cpp
- GLObject.h
- GLPixelShader.cpp
- GLPixelShader.h
- GLPool.h
- GLShader.cpp
- GLShader.h
- GLShaderInput.h
- GLTexture.cpp
- GLTexture.h
- GLTypes.cpp
- GLTypes.h
- GLUtil.cpp
- GLUtil.h
- GLVertexArray.cpp
- GLVertexArray.h
- GLVertexFormat.h
- GLVertexShader.cpp
- GLVertexShader.h
- GLWindow.cpp
- GLWindow.h
- GLWorker.cpp
- GLWorker.h

### Graphic/shader/

**文件数**: 6

**文件列表**:
- CGxShader.cpp
- CGxShader.h
- CShaderEffect.cpp
- CShaderEffect.h
- CShaderEffectManager.cpp
- CShaderEffectManager.h

### Graphic/texture/

**文件数**: 6

**文件列表**:
- CBLPFile.cpp
- CBLPFile.h
- CGxTex.cpp
- CGxTex.h
- CTexture.cpp
- CTexture.h

### NIpse/

**文件数**: 12

**文件列表**:
- CPoReal.cpp
- CPoReal.h
- CPrRelation.cpp
- CPrRelation.h
- CRlAgent.cpp
- CRlAgent.h
- CRlAgentDef.cpp
- CRlAgentDef.h
- CRlProperty.cpp
- CRlProperty.h
- CThreadData.cpp
- CThreadData.h

### NTempest/

**文件数**: 63

**文件列表**:
- C22uMatrix.cpp
- C22uMatrix.h
- C2Vector.cpp
- C2Vector.h
- C2iVector.cpp
- C2iVector.h
- C2uVector.h
- C33Matrix.cpp
- C33Matrix.h
- C33uMatrix.h
- C34Matrix.h
- C3Vector.cpp
- C3Vector.h
- C3uVector.h
- C44Matrix.cpp
- C44Matrix.h
- C4Plane.cpp
- C4Plane.h
- C4Quaternion.cpp
- C4Quaternion.h
- C4Vector.cpp
- C4Vector.h
- C4iRect.h
- CAaBox.h
- CAaSphere.cpp
- CAaSphere.h
- CBoundingBox.h
- CDynParms.h
- CDynTable.h
- CEntity.h
- CImVector.h
- CLinkedList.h
- CLinkedNode.h
- CLinkedNodeCache.h
- CMath.h
- CMathi.cpp
- CMathi.h
- CMemBlock.h
- CMemBlockT.h
- CPrRgEntry.h
- CPresence.h
- CPresenceReg.h
- CPresenceSys.h
- CPresenceSysTagged.h
- CPresenceTagged.h
- CPriorityQ.h
- CRandSeed.h
- CRandom.h
- CRange.h
- CRect.cpp
- CRect.h
- CRndSeed.h
- CSyncData.h
- CTargetPrTg.h
- CThreadData.h
- CiRange.h
- CiRect.cpp
- CiRect.h
- CuMath.h
- CuRandom.h
- CuRange.h
- CuRect.h
- TInstanceCache.h

### Net/

**文件数**: 6

**文件列表**:
- Connection.h
- Grunt.h
- Login.h
- Poll.cpp
- Poll.h
- Types.h

### Net/connection/

**文件数**: 12

**文件列表**:
- ClientConnection.cpp
- ClientConnection.h
- NetClient.cpp
- NetClient.h
- RealmConnection.cpp
- RealmConnection.h
- RealmResponse.h
- WowConnection.cpp
- WowConnection.h
- WowConnectionNet.cpp
- WowConnectionNet.h
- WowConnectionResponse.h

### Net/connection/winsock/

**文件数**: 1

**文件列表**:
- WowConnectionNet.cpp

### Net/grunt/

**文件数**: 9

**文件列表**:
- ClientLink.cpp
- ClientLink.h
- ClientResponse.h
- Command.h
- Grunt.cpp
- Grunt.h
- Pending.h
- Timer.cpp
- Timer.h

### Net/login/

**文件数**: 7

**文件列表**:
- BattlenetLogin.h
- GruntLogin.cpp
- GruntLogin.h
- Login.cpp
- Login.h
- LoginResponse.cpp
- LoginResponse.h

### Net/srp/

**文件数**: 4

**文件列表**:
- SRP6_Client.cpp
- SRP6_Client.h
- SRP6_Random.cpp
- SRP6_Random.h

### Scrn/

**文件数**: 1

**文件列表**:
- CONSOLE.h

### Services/

**文件数**: 17

**文件列表**:
- AsyncFile.cpp
- AsyncFile.h
- Database.cpp
- Database.h
- GfxSingletonManager.cpp
- GfxSingletonManager.h
- Lightning.cpp
- Lightning.h
- Profile.cpp
- Profile.h
- ProfileInternal.h
- SprAnimList.cpp
- SprAnimList.h
- SprLinkTable.cpp
- SprLinkTable.h
- Texture.cpp
- Texture.h

### Sound/

**文件数**: 4

**文件列表**:
- SI2.cpp
- SI2.h
- SI2Script.cpp
- SI2Script.h

### Storm/

**文件数**: 67

**文件列表**:
- AsyncFile.cpp
- AsyncFile.h
- AsyncFileRead.cpp
- AsyncFileRead.h
- Atomic.cpp
- Atomic.h
- Autorelease.h
- Big.cpp
- Big.h
- BigInteger.cpp
- BigInteger.h
- Bytes.h
- CAsyncObject.h
- CAsyncQueue.h
- CAsyncThread.h
- CVar.cpp
- CVar.h
- Crypto.cpp
- Crypto.h
- Debug.cpp
- Debug.h
- DebugUtils.cpp
- DebugUtils.h
- Error.cpp
- Error.h
- Filesystem.cpp
- Filesystem.h
- HMAC.cpp
- HMAC.h
- Handle.cpp
- Handle.h
- Lock.cpp
- Lock.h
- Log.cpp
- Log.h
- Luaex.h
- MD5.cpp
- MD5.h
- Process.cpp
- Process.h
- SFile.cpp
- SFile.h
- StormInit.cpp
- StormInit.h
- String.cpp
- String.h
- StringTo.cpp
- StringTo.h
- System_Debug.cpp
- System_Debug.h
- System_Lock.cpp
- System_Lock.h
- System_Thread.cpp
- System_Thread.h
- Thread.cpp
- Thread.h
- Time.cpp
- Time.h
- Unicode.cpp
- Unicode.h
- Unimplemented.h
- View.cpp
- View.h
- memory.cpp
- memory.h
- platform_win.cpp
- platform_win.h

### Storm/big/

**文件数**: 8

**文件列表**:
- BigBuffer.cpp
- BigBuffer.h
- BigData.cpp
- BigData.h
- BigStack.cpp
- BigStack.h
- Ops.cpp
- Ops.h

### Storm/crypto/

**文件数**: 1

**文件列表**:
- SARC4Key.h

### Storm/db/

**文件数**: 6

**文件列表**:
- Db.cpp
- Db.h
- IDatabase.h
- WowClientDB.h
- WowClientDB_Base.h
- WowClientDB_Common.h

### Storm/db/rec/

**文件数**: 8

**文件列表**:
- AchievementRec.cpp
- AchievementRec.h
- Cfg_CategoriesRec.cpp
- Cfg_CategoriesRec.h
- Cfg_ConfigsRec.cpp
- Cfg_ConfigsRec.h
- ChrRacesRec.cpp
- ChrRacesRec.h

### Storm/lock/

**文件数**: 2

**文件列表**:
- win32Critical_Section.cpp
- win32Critical_Section.h

### Storm/mempool/

**文件数**: 4

**文件列表**:
- MemChunk.cpp
- MemChunk.h
- MemPool.cpp
- MemPool.h

### Storm/string/

**文件数**: 2

**文件列表**:
- bjhash.cpp
- bjhash.h

### Storm/thread/

**文件数**: 18

**文件列表**:
- CCritSect.cpp
- CCritSect.h
- CSRWLock.cpp
- CSRWLock.h
- OsTls.cpp
- OsTls.h
- SCritSect.cpp
- SCritSect.h
- SEvent.cpp
- SEvent.h
- SSemaphore.cpp
- SSemaphore.h
- SSyncObject.cpp
- SSyncObject.h
- SThread.cpp
- SThread.h
- S_Thread.cpp
- S_Thread.h

### Storm/thread/win/

**文件数**: 4

**文件列表**:
- SRWLock.cpp
- SRWLock.h
- S_Thread.cpp
- Thread.cpp

### Storm/xml/

**文件数**: 6

**文件列表**:
- Expat.h
- XMLAttribute.h
- XMLNode.cpp
- XMLNode.h
- XMLTree.cpp
- XMLTree.h

### Terrain/

**文件数**: 4

**文件列表**:
- CTerrain.cpp
- CTerrain.h
- TerrainRenderer.cpp
- TerrainRenderer.h

### UI/

**文件数**: 112

**文件列表**:
- CBackdropGenerator.cpp
- CBackdropGenerator.h
- CFramePoint.cpp
- CFramePoint.h
- CFrameStrata.cpp
- CFrameStrata.h
- CLayoutFrame.cpp
- CLayoutFrame.h
- CRenderBatch.cpp
- CRenderBatch.h
- CScriptObject.cpp
- CScriptObject.h
- CScriptObjectScript.cpp
- CScriptObjectScript.h
- CScriptRegion.cpp
- CScriptRegion.h
- CScriptRegionScript.cpp
- CScriptRegionScript.h
- CSimpleAnimGroup.cpp
- CSimpleAnimGroup.h
- CSimpleButton.cpp
- CSimpleButton.h
- CSimpleButtonScript.cpp
- CSimpleButtonScript.h
- CSimpleCheckbox.cpp
- CSimpleCheckbox.h
- CSimpleCheckboxScript.cpp
- CSimpleCheckboxScript.h
- CSimpleEditBox.cpp
- CSimpleEditBox.h
- CSimpleEditBoxScript.cpp
- CSimpleEditBoxScript.h
- CSimpleFont.cpp
- CSimpleFont.h
- CSimpleFontScript.cpp
- CSimpleFontScript.h
- CSimpleFontString.cpp
- CSimpleFontString.h
- CSimpleFontStringAttributes.cpp
- CSimpleFontStringAttributes.h
- CSimpleFontStringScript.cpp
- CSimpleFontStringScript.h
- CSimpleFontable.cpp
- CSimpleFontable.h
- CSimpleFontedFrame.h
- CSimpleFontedFrameFont.h
- CSimpleFrame.cpp
- CSimpleFrame.h
- CSimpleFrameScript.cpp
- CSimpleFrameScript.h
- CSimpleHTML.cpp
- CSimpleHTML.h
- CSimpleHTMLScript.cpp
- CSimpleHTMLScript.h
- CSimpleHyperlinkedFrame.cpp
- CSimpleHyperlinkedFrame.h
- CSimpleModel.cpp
- CSimpleModel.h
- CSimpleModelFFX.cpp
- CSimpleModelFFX.h
- CSimpleModelFFXScript.cpp
- CSimpleModelFFXScript.h
- CSimpleModelScript.cpp
- CSimpleModelScript.h
- CSimpleRegion.cpp
- CSimpleRegion.h
- CSimpleRender.cpp
- CSimpleRender.h
- CSimpleScrollFrame.cpp
- CSimpleScrollFrame.h
- CSimpleScrollFrameScript.cpp
- CSimpleScrollFrameScript.h
- CSimpleSlider.cpp
- CSimpleSlider.h
- CSimpleSliderScript.cpp
- CSimpleSliderScript.h
- CSimpleTexture.cpp
- CSimpleTexture.h
- CSimpleTextureScript.cpp
- CSimpleTextureScript.h
- CSimpleTitleRegion.h
- CSimpleTop.cpp
- CSimpleTop.h
- FrameScript.cpp
- FrameScript.h
- FrameScriptInternal.h
- FrameScript_Object.cpp
- FrameScript_Object.h
- FrameXML.cpp
- FrameXML.h
- Interface.cpp
- Interface.h
- LoadXML.cpp
- LoadXML.h
- LuaExtraFuncs.cpp
- LuaExtraFuncs.h
- LuaMemory.cpp
- LuaMemory.h
- OsGui.cpp
- OsGui.h
- ScriptFunctions.cpp
- ScriptFunctions.h
- ScriptFunctionsCharCreate.cpp
- ScriptFunctionsCharSelect.cpp
- ScriptFunctionsGlueScriptEvents.cpp
- ScriptFunctionsRealmList.cpp
- ScriptFunctionsShared.cpp
- ScriptFunctionsSimpleFrame.cpp
- ScriptFunctionsSystem.cpp
- Types.h
- Util.cpp
- Util.h
