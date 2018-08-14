<a name="0.13.0"></a>
# [0.13.0](https://github.com/Wonder-Technology/Wonder-Editor/compare/v0.10.0...v0.13.0) (2018-08-14)


### Bug Fixes

* **gameObject:** fix bug:add deep dispose gameObject ([ce2461b](https://github.com/Wonder-Technology/Wonder-Editor/commit/ce2461b))


### Features

* **addGameObject:** extract AddGameObjectType manage gameObject type ([0f9cd42](https://github.com/Wonder-Technology/Wonder-Editor/commit/0f9cd42))
* **assetState:** remove AssetState, change to editorState-> assetRecord ([ee4f41b](https://github.com/Wonder-Technology/Wonder-Editor/commit/ee4f41b))
* **blurEvent:** add check blur value is equal origin value ([9dc80b8](https://github.com/Wonder-Technology/Wonder-Editor/commit/9dc80b8))
* **camera:** add cameraGroup and remove cameraGroup is run, bind and unbind event ([2dc2873](https://github.com/Wonder-Technology/Wonder-Editor/commit/2dc2873))
* **camera:** add cameraGroup cameraView component ([4815161](https://github.com/Wonder-Technology/Wonder-Editor/commit/4815161))
* **camera:** finish camera view component ([a706693](https://github.com/Wonder-Technology/Wonder-Editor/commit/a706693))
* **camera:** finish remove currentCamera feature ([05f0b87](https://github.com/Wonder-Technology/Wonder-Editor/commit/05f0b87))
* **camera:** pass ee engine state->arcball cameraController ([f4d3046](https://github.com/Wonder-Technology/Wonder-Editor/commit/f4d3046))
* **camera:** use camera component instead of basicCameraView and perspectiveCamera ([2d28e00](https://github.com/Wonder-Technology/Wonder-Editor/commit/2d28e00))
* **cameraGroup:** finish mainEditorPerspectiveCamera feature and test ([1affa54](https://github.com/Wonder-Technology/Wonder-Editor/commit/1affa54))
* **cameraView:** add cameraview redo/undo ([15949b4](https://github.com/Wonder-Technology/Wonder-Editor/commit/15949b4))
* **color:** select color show color pick such as unity ([67d972a](https://github.com/Wonder-Technology/Wonder-Editor/commit/67d972a))
* **colorPick:** import colorPick ui component, and finish test ([eb5eeab](https://github.com/Wonder-Technology/Wonder-Editor/commit/eb5eeab))
* **component:** add addableComponent list to add component ([4a5e89c](https://github.com/Wonder-Technology/Wonder-Editor/commit/4a5e89c))
* **component:** add addableComponentBox and add component in gameObject ([468d6a3](https://github.com/Wonder-Technology/Wonder-Editor/commit/468d6a3))
* **component:** add inspectorComponentTypeMap store gameObject's components ([0338039](https://github.com/Wonder-Technology/Wonder-Editor/commit/0338039))
* **component:** finish add component feature ([337454d](https://github.com/Wonder-Technology/Wonder-Editor/commit/337454d))
* **component:** finish remove component feature ([a293dba](https://github.com/Wonder-Technology/Wonder-Editor/commit/a293dba))
* **component:** fix "add component"->init gameObject: now with diff ([e513341](https://github.com/Wonder-Technology/Wonder-Editor/commit/e513341))
* **component:** remove BoxGeometry; rename CustomGeometry to Geometry; ([dc6acad](https://github.com/Wonder-Technology/Wonder-Editor/commit/dc6acad))
* **css:** extract public/css ([c941329](https://github.com/Wonder-Technology/Wonder-Editor/commit/c941329))
* **emptyGameObject:** add empty gameObject ([aea09ee](https://github.com/Wonder-Technology/Wonder-Editor/commit/aea09ee))
* **engine:** add ScreenEngineService->setScreenSize ([c777ea4](https://github.com/Wonder-Technology/Wonder-Editor/commit/c777ea4))
* **engine:** fix engine bug; arcballCameraController not bind event when init, initGameObject ([c0e2258](https://github.com/Wonder-Technology/Wonder-Editor/commit/c0e2258))
* **engine:** update version ([e17ffd0](https://github.com/Wonder-Technology/Wonder-Editor/commit/e17ffd0))
* **engine:** update wonder.js ([ec493ae](https://github.com/Wonder-Technology/Wonder-Editor/commit/ec493ae))
* **engine:** update wonder.js version ([bfbebf6](https://github.com/Wonder-Technology/Wonder-Editor/commit/bfbebf6))
* **engine:** upgrade to 1.0.0-alpha.23 ([7f41102](https://github.com/Wonder-Technology/Wonder-Editor/commit/7f41102))
* **engine:** use GameObjectAPI->getAllXXXComponents api ([edaf617](https://github.com/Wonder-Technology/Wonder-Editor/commit/edaf617))
* **event:** add change currentCamera arcballCameraContollerEvent ([9e22eec](https://github.com/Wonder-Technology/Wonder-Editor/commit/9e22eec))
* **event:** add mouse event into ee and re canvas;remove engine->initEventJob ([e78b1e1](https://github.com/Wonder-Technology/Wonder-Editor/commit/e78b1e1))
* **event:** fix MainUtils->set unsafeGetStateFunc and setStateFunc for event: if is run, not loopBody ([41f7567](https://github.com/Wonder-Technology/Wonder-Editor/commit/41f7567))
* **event:** if is stop, ee should loopBody but re not ([1fd5fd6](https://github.com/Wonder-Technology/Wonder-Editor/commit/1fd5fd6))
* **imgui:** change imguiFunc to pure func ([0f6f64b](https://github.com/Wonder-Technology/Wonder-Editor/commit/0f6f64b))
* **imgui:** each direction light gameObject show one imgui ([2855f8f](https://github.com/Wonder-Technology/Wonder-Editor/commit/2855f8f))
* **imgui:** fix coordinate bug ([ddd7005](https://github.com/Wonder-Technology/Wonder-Editor/commit/ddd7005))
* **imgui:** fix direction light imgui->image x,y ([7438d7f](https://github.com/Wonder-Technology/Wonder-Editor/commit/7438d7f))
* **imgui:** fix imgui->image control->size bug ([4e7851e](https://github.com/Wonder-Technology/Wonder-Editor/commit/4e7851e))
* **imgui:** fix setIMGUIFunc: now get canvas in func ([468ee81](https://github.com/Wonder-Technology/Wonder-Editor/commit/468ee81))
* **imgui:** not serialize/deserialize customData ([872bcdf](https://github.com/Wonder-Technology/Wonder-Editor/commit/872bcdf))
* **imgui:** refactor MainUtils->setIMGUIFunc ([39ea458](https://github.com/Wonder-Technology/Wonder-Editor/commit/39ea458))
* **IMGUI:** add draw directionLight icon ([ab97d88](https://github.com/Wonder-Technology/Wonder-Editor/commit/ab97d88))
* **light:** add directionLight change color and change intensity, add those test ([0db1676](https://github.com/Wonder-Technology/Wonder-Editor/commit/0db1676))
* **light:** add MainEditorLightMaterial ([0e6db9f](https://github.com/Wonder-Technology/Wonder-Editor/commit/0e6db9f))
* **light:** add point light feature and test ([00e0119](https://github.com/Wonder-Technology/Wonder-Editor/commit/00e0119))
* **light:** finish all point light components ([308af0a](https://github.com/Wonder-Technology/Wonder-Editor/commit/308af0a))
* **lightMaterial:** add light material color, map, shininess feature ([594020b](https://github.com/Wonder-Technology/Wonder-Editor/commit/594020b))
* **lightMaterial:** fix change color ([5c266b2](https://github.com/Wonder-Technology/Wonder-Editor/commit/5c266b2))
* **lightMaterial:** fix: add direction light component that should re-init all light material components in the scene ([e1c51ae](https://github.com/Wonder-Technology/Wonder-Editor/commit/e1c51ae))
* **lightMaterial:** fix: dispose gameObject which has light component should re-init all light material components in the scene ([fb5e9c6](https://github.com/Wonder-Technology/Wonder-Editor/commit/fb5e9c6))
* **lightMaterial:** use lightMaterial instead of basicMaterial ([d169f3d](https://github.com/Wonder-Technology/Wonder-Editor/commit/d169f3d))
* **meshRenderer:** add meshRenderer drawMode feature and test ([b485890](https://github.com/Wonder-Technology/Wonder-Editor/commit/b485890))
* **redo/undo:** add select gameObject redo/undo check ([47ef550](https://github.com/Wonder-Technology/Wonder-Editor/commit/47ef550))
* **rename:** stringInput component add isNull field ([25e62c0](https://github.com/Wonder-Technology/Wonder-Editor/commit/25e62c0))
* **renderGroup:** add renderGroup add and show ([77974f5](https://github.com/Wonder-Technology/Wonder-Editor/commit/77974f5))
* **scale:** add transform -> scale ([ddf4994](https://github.com/Wonder-Technology/Wonder-Editor/commit/ddf4994))
* **scene:** use engine sceneGameObject instead of editorState ([5f64e16](https://github.com/Wonder-Technology/Wonder-Editor/commit/5f64e16))
* **state:** rewrite stateLogicService->getAndRefreshEngineStateWithDiff ([ad2d878](https://github.com/Wonder-Technology/Wonder-Editor/commit/ad2d878))
* **texture:** add handleBoxGeometryAddMap and handleCustomGeometryAddMap function ([8c1a76b](https://github.com/Wonder-Technology/Wonder-Editor/commit/8c1a76b))
* **texture:** add texture into MainEditorBasicMaterial ([8472a78](https://github.com/Wonder-Technology/Wonder-Editor/commit/8472a78))
* **texture:** add textureMapData retainedProps in MainEditorInspector ([94c00b0](https://github.com/Wonder-Technology/Wonder-Editor/commit/94c00b0))
* **texture:** change texture name in nodeMap and engineState ([1f58fb8](https://github.com/Wonder-Technology/Wonder-Editor/commit/1f58fb8))
* **texture:** finish add texture and set texture is null redo/undo ([4fd2a50](https://github.com/Wonder-Technology/Wonder-Editor/commit/4fd2a50))
* **texture:** finish add texture into material ([5ade75d](https://github.com/Wonder-Technology/Wonder-Editor/commit/5ade75d))
* **texture:** finish convert image to texture ([84eb435](https://github.com/Wonder-Technology/Wonder-Editor/commit/84eb435))
* **texture:** finish MainEditorBasicMaterial texture component drag event ([f7bd9fc](https://github.com/Wonder-Technology/Wonder-Editor/commit/f7bd9fc))
* **texture:** finish textureInspector show texture props ([f460ea1](https://github.com/Wonder-Technology/Wonder-Editor/commit/f460ea1))
* **texture:** use getAndRefreshEngineStateWithDiff instead of getAndRefreshEngineState ([03e35a5](https://github.com/Wonder-Technology/Wonder-Editor/commit/03e35a5))
* **transform:** add localEulerAngles, eulerAngles api ([6b5beb5](https://github.com/Wonder-Technology/Wonder-Editor/commit/6b5beb5))
* **update:** refactor all shouldUpdate and dispatchFunc ([583f9e8](https://github.com/Wonder-Technology/Wonder-Editor/commit/583f9e8))
* **viewport:** set canvas viewport and resize ([e183b20](https://github.com/Wonder-Technology/Wonder-Editor/commit/e183b20))
* add grid plane gameObject to ee engine state ([d759329](https://github.com/Wonder-Technology/Wonder-Editor/commit/d759329))
* adjust show effect ([eea702e](https://github.com/Wonder-Technology/Wonder-Editor/commit/eea702e))
* extract assetState, redo/undo don't use it ([ece1ae5](https://github.com/Wonder-Technology/Wonder-Editor/commit/ece1ae5))



<a name="0.11.0"></a>
# [0.11.0](https://github.com/Wonder-Technology/Wonder-Editor/compare/v0.10.0...v0.11.0) (2018-07-18)


### Bug Fixes

* **gameObject:** fix bug:add deep dispose gameObject ([ce2461b](https://github.com/Wonder-Technology/Wonder-Editor/commit/ce2461b))


### Features

* **colorPick:** import colorPick ui component, and finish test ([eb5eeab](https://github.com/Wonder-Technology/Wonder-Editor/commit/eb5eeab))
* **redo/undo:** add select gameObject redo/undo check ([47ef550](https://github.com/Wonder-Technology/Wonder-Editor/commit/47ef550))
* **rename:** stringInput component add isNull field ([25e62c0](https://github.com/Wonder-Technology/Wonder-Editor/commit/25e62c0))
* **state:** rewrite stateLogicService->getAndRefreshEngineStateWithDiff ([ad2d878](https://github.com/Wonder-Technology/Wonder-Editor/commit/ad2d878))
* **texture:** add handleBoxGeometryAddMap and handleCustomGeometryAddMap function ([8c1a76b](https://github.com/Wonder-Technology/Wonder-Editor/commit/8c1a76b))
* **texture:** add texture into MainEditorBasicMaterial ([8472a78](https://github.com/Wonder-Technology/Wonder-Editor/commit/8472a78))
* **texture:** add textureMapData retainedProps in MainEditorInspector ([94c00b0](https://github.com/Wonder-Technology/Wonder-Editor/commit/94c00b0))
* extract assetState, redo/undo don't use it ([ece1ae5](https://github.com/Wonder-Technology/Wonder-Editor/commit/ece1ae5))
* **texture:** change texture name in nodeMap and engineState ([1f58fb8](https://github.com/Wonder-Technology/Wonder-Editor/commit/1f58fb8))
* **texture:** finish add texture and set texture is null redo/undo ([4fd2a50](https://github.com/Wonder-Technology/Wonder-Editor/commit/4fd2a50))
* **texture:** finish add texture into material ([5ade75d](https://github.com/Wonder-Technology/Wonder-Editor/commit/5ade75d))
* **texture:** finish convert image to texture ([84eb435](https://github.com/Wonder-Technology/Wonder-Editor/commit/84eb435))
* **texture:** finish MainEditorBasicMaterial texture component drag event ([f7bd9fc](https://github.com/Wonder-Technology/Wonder-Editor/commit/f7bd9fc))
* **texture:** finish textureInspector show texture props ([f460ea1](https://github.com/Wonder-Technology/Wonder-Editor/commit/f460ea1))
* **texture:** use getAndRefreshEngineStateWithDiff instead of getAndRefreshEngineState ([03e35a5](https://github.com/Wonder-Technology/Wonder-Editor/commit/03e35a5))



<a name="0.10.0"></a>
# [0.10.0](https://github.com/Wonder-Technology/Wonder-Editor/compare/v0.9.0...v0.10.0) (2018-06-13)


### Features

* **asset:** add assetTree and finish two tree drag event ([0e1576a](https://github.com/Wonder-Technology/Wonder-Editor/commit/0e1576a))
* **asset:** add drag event check div ([def6454](https://github.com/Wonder-Technology/Wonder-Editor/commit/def6454))
* **asset:** finish add file into assetTree and fileMap ([84d6e20](https://github.com/Wonder-Technology/Wonder-Editor/commit/84d6e20))
* **asset:** finish addFolder feature ([7806e37](https://github.com/Wonder-Technology/Wonder-Editor/commit/7806e37))
* **asset:** finish all drag event relation handle ([a0bf9c0](https://github.com/Wonder-Technology/Wonder-Editor/commit/a0bf9c0))
* **asset:** finish assetType and record operate ([9e9bd27](https://github.com/Wonder-Technology/Wonder-Editor/commit/9e9bd27))
* **asset:** finish drag folder and remove folder ([0d99cb9](https://github.com/Wonder-Technology/Wonder-Editor/commit/0d99cb9))
* **asset:** finish fileInspector rename ([f5006f8](https://github.com/Wonder-Technology/Wonder-Editor/commit/f5006f8))
* **asset:** finish move file to folder ([898ff07](https://github.com/Wonder-Technology/Wonder-Editor/commit/898ff07))
* **asset:** finish readFile and deal with it ([05f5121](https://github.com/Wonder-Technology/Wonder-Editor/commit/05f5121))
* **asset:** finish remove asset node form nodeMap ([05c7650](https://github.com/Wonder-Technology/Wonder-Editor/commit/05c7650))
* **asset:** finish remove file ([60923ee](https://github.com/Wonder-Technology/Wonder-Editor/commit/60923ee))
* **asset:** finish showImg in the specific folder ([fad6708](https://github.com/Wonder-Technology/Wonder-Editor/commit/fad6708))
* **asset:** finish upload json file ([90a778a](https://github.com/Wonder-Technology/Wonder-Editor/commit/90a778a))
* **asset:** show folder in file content ([3c80474](https://github.com/Wonder-Technology/Wonder-Editor/commit/3c80474))
* **engine:** upgrade engine to v1.0.0-alpha.18.3 version ([252bc00](https://github.com/Wonder-Technology/Wonder-Editor/commit/252bc00))
* **engine:** upgrade to v1.0.0-alpha.18.5 ([eb628f2](https://github.com/Wonder-Technology/Wonder-Editor/commit/eb628f2))
* **engine:** upgrade to v1.0.0-alpha.19 ([d1006af](https://github.com/Wonder-Technology/Wonder-Editor/commit/d1006af))
* **redo-undo:** optimize redo: not deep copy current state ([5463e2e](https://github.com/Wonder-Technology/Wonder-Editor/commit/5463e2e))


### Performance Improvements

* **asset:** optimize async test:reduce debounce time to 10ms ([ebf1b6f](https://github.com/Wonder-Technology/Wonder-Editor/commit/ebf1b6f))



<a name="0.9.0"></a>
# [0.9.0](https://github.com/Wonder-Technology/Wonder-Editor/compare/v0.8.0...v0.9.0) (2018-04-19)


### Bug Fixes

* fix "dispose gameObject cause order wrong(scene tree)" bug ([8cecb32](https://github.com/Wonder-Technology/Wonder-Editor/commit/8cecb32))
* need to fix some bug ([bb1e406](https://github.com/Wonder-Technology/Wonder-Editor/commit/bb1e406))
* **engine:** update engine version ([7ad68ee](https://github.com/Wonder-Technology/Wonder-Editor/commit/7ad68ee))
* **redo/undo:** fix bug: change material color and change transform, exec undo throw error ([e6376cd](https://github.com/Wonder-Technology/Wonder-Editor/commit/e6376cd))


### Features

* **controller:** add run and stop check ([b163183](https://github.com/Wonder-Technology/Wonder-Editor/commit/b163183))
* **controller:** can't remove last camera ([d3f6a13](https://github.com/Wonder-Technology/Wonder-Editor/commit/d3f6a13))
* **controller:** finish controller stack redo undo ([3f08b1c](https://github.com/Wonder-Technology/Wonder-Editor/commit/3f08b1c))
* **controller:** finish run and stop undo/redo stack manager ([cd7489f](https://github.com/Wonder-Technology/Wonder-Editor/commit/cd7489f))
* **controller:** finish two engine state init default scene ([ec7e6f8](https://github.com/Wonder-Technology/Wonder-Editor/commit/ec7e6f8))
* **engine:** update version ([bcd54a3](https://github.com/Wonder-Technology/Wonder-Editor/commit/bcd54a3))
* **engine:** update wonder.js to 1.0.0-alpha.17.1; update wonder-commonlib to 0.2.20 ([4f1245f](https://github.com/Wonder-Technology/Wonder-Editor/commit/4f1245f))
* finish stop function cancelAnimationFrame ([c0e6494](https://github.com/Wonder-Technology/Wonder-Editor/commit/c0e6494))
* **run/stop:** add getAndRefreshEngineState function ([a7d29a3](https://github.com/Wonder-Technology/Wonder-Editor/commit/a7d29a3))
* **run/stop:** add two engineState and two canvas ([26c8c41](https://github.com/Wonder-Technology/Wonder-Editor/commit/26c8c41))
* **run/stop:** finish two engineState ([57b663c](https://github.com/Wonder-Technology/Wonder-Editor/commit/57b663c))



<a name="0.8.0"></a>
# [0.8.0](https://github.com/Wonder-Technology/Wonder-Editor/compare/v0.6.0...v0.8.0) (2018-03-15)


### Features

* **addComponent:** finish add component by current GameObject is exist component by json data ([9e7b221](https://github.com/Wonder-Technology/Wonder-Editor/commit/9e7b221))
* **addComponent:** finish add sourceInstance component ([6a399bd](https://github.com/Wonder-Technology/Wonder-Editor/commit/6a399bd))
* **addMaterial:** add material ui component ([0976a40](https://github.com/Wonder-Technology/Wonder-Editor/commit/0976a40))
* **addMaterial:** set current gameObject material color ([73bf6e0](https://github.com/Wonder-Technology/Wonder-Editor/commit/73bf6e0))
* **service:** extract basicMaterial engineState logicService and commonService ([297e972](https://github.com/Wonder-Technology/Wonder-Editor/commit/297e972))
* **service:** extract editorStateData ([c24d87c](https://github.com/Wonder-Technology/Wonder-Editor/commit/c24d87c))
* **service:** extract EditorStateLogicService and EditorStateCommonService and EditorStateFacade ([499a5d2](https://github.com/Wonder-Technology/Wonder-Editor/commit/499a5d2))
* **service:** extract floatService and rename uiState to store ([f3a91aa](https://github.com/Wonder-Technology/Wonder-Editor/commit/f3a91aa))
* **service:** extract GameObjectComposite and GameObjectLogicSingleService ([66ca7a2](https://github.com/Wonder-Technology/Wonder-Editor/commit/66ca7a2))
* **service:** extract GameObjectService and currentGameObjectService ([e2cccfa](https://github.com/Wonder-Technology/Wonder-Editor/commit/e2cccfa))
* **service:** extract GameObjectUtils and SceneTreeUtils ([679dbf4](https://github.com/Wonder-Technology/Wonder-Editor/commit/679dbf4))
* **service:** extract HistoryLogicService and allStateData ([ae8cda7](https://github.com/Wonder-Technology/Wonder-Editor/commit/ae8cda7))
* **service:** extract historyLogicService and finish TODO ([f7e9a7b](https://github.com/Wonder-Technology/Wonder-Editor/commit/f7e9a7b))
* **service:** extract logicComposite service and singleService and facade ([f25d348](https://github.com/Wonder-Technology/Wonder-Editor/commit/f25d348))
* **service:** extract primitive/sceneService and CurrentGameObjectService ([9b41c40](https://github.com/Wonder-Technology/Wonder-Editor/commit/9b41c40))
* **service:** extract state stateTuple record primitive atom service ([3071e3c](https://github.com/Wonder-Technology/Wonder-Editor/commit/3071e3c))
* **service:** extract ui inspector and scenetree ([2580790](https://github.com/Wonder-Technology/Wonder-Editor/commit/2580790))
* **service:** remove AppExtensionView and extract AppExtensionUtils ([3f385c4](https://github.com/Wonder-Technology/Wonder-Editor/commit/3f385c4))
* **service:** remove MainEditorStateView.re and add service in cz.config ([401dd42](https://github.com/Wonder-Technology/Wonder-Editor/commit/401dd42))



<a name="0.7.0"></a>
# [0.7.0](https://github.com/Wonder-Technology/Wonder-Editor/compare/v0.6.0...v0.7.0) (2018-03-02)


### Features

* **addComponent:** finish add component by current GameObject is exist component by json data ([9e7b221](https://github.com/Wonder-Technology/Wonder-Editor/commit/9e7b221))
* **addComponent:** finish add sourceInstance component ([6a399bd](https://github.com/Wonder-Technology/Wonder-Editor/commit/6a399bd))
* **addMaterial:** add material ui component ([0976a40](https://github.com/Wonder-Technology/Wonder-Editor/commit/0976a40))
* **addMaterial:** set current gameObject material color ([73bf6e0](https://github.com/Wonder-Technology/Wonder-Editor/commit/73bf6e0))



<a name="0.6.0"></a>
# [0.6.0](https://github.com/Wonder-Technology/Wonder-Editor/compare/v0.5.0...v0.6.0) (2018-01-29)


### Features

* **main:** use statelessComponentWithRetainedProps instead of statelessComponent ([b8fcda1](https://github.com/Wonder-Technology/Wonder-Editor/commit/b8fcda1))
* **redo/undo:** extract allStateData manage uiState,editorState,engineState ([e4ec871](https://github.com/Wonder-Technology/Wonder-Editor/commit/e4ec871))
* **redo/undo:** extract markRedoUndoChangeXXX module ([6ed0898](https://github.com/Wonder-Technology/Wonder-Editor/commit/6ed0898))
* **redo/undo:** finish redo/undo structure ([145e771](https://github.com/Wonder-Technology/Wonder-Editor/commit/145e771))
* **redo/undo:** import most.js ([baa9cb0](https://github.com/Wonder-Technology/Wonder-Editor/commit/baa9cb0))
* **redo/undo:** use allStateData.history instead of markRedoUndoStack ([bce3282](https://github.com/Wonder-Technology/Wonder-Editor/commit/bce3282))



<a name="0.5.0"></a>
# [0.5.0](https://github.com/Wonder-Technology/Wonder-Editor/compare/v0.4.1...v0.5.0) (2018-01-17)


### Bug Fixes

* **defaultScene:** now have three gameObject but test is 2 ([4b76f72](https://github.com/Wonder-Technology/Wonder-Editor/commit/4b76f72))
* change "DreamForeast" to "Wonder-Technology" ([ef1769e](https://github.com/Wonder-Technology/Wonder-Editor/commit/ef1769e))
* **mainView:** mainEditorMainView.re loop method set editor every frame ([a3d180a](https://github.com/Wonder-Technology/Wonder-Editor/commit/a3d180a))
* **scene-tree:** add drag end event to treeNode ([cf8dd07](https://github.com/Wonder-Technology/Wonder-Editor/commit/cf8dd07))
* **scene-tree:** forget add onDragEnd to treeNode.re ([585bfd0](https://github.com/Wonder-Technology/Wonder-Editor/commit/585bfd0))
* **scenetree:** the move ui component method make the recursion ([f7031e8](https://github.com/Wonder-Technology/Wonder-Editor/commit/f7031e8))
* **sceneTree:** insert to target treeNode is error ([78b58bc](https://github.com/Wonder-Technology/Wonder-Editor/commit/78b58bc))
* **sceneTree:** use makeStringToNumber instead of int_of_string ([3cdc021](https://github.com/Wonder-Technology/Wonder-Editor/commit/3cdc021))


### Features

* **config:** add .cz-config.js ([5e17463](https://github.com/Wonder-Technology/Wonder-Editor/commit/5e17463))
* **disposeGameObject:** add disposeGameObject method in adaptor and operator ([96f1ddd](https://github.com/Wonder-Technology/Wonder-Editor/commit/96f1ddd))
* **engine:** upgrade to v1.0.0-alpha.12 ([22e8f2d](https://github.com/Wonder-Technology/Wonder-Editor/commit/22e8f2d))
* **gameObject:** finish get/set current gameObject ([4af7f7c](https://github.com/Wonder-Technology/Wonder-Editor/commit/4af7f7c))
* **inspector:** add build current gameObject component by json data ([7abfc83](https://github.com/Wonder-Technology/Wonder-Editor/commit/7abfc83))
* **inspector:** extract buildGameObjectComponent method by json data ([35959c1](https://github.com/Wonder-Technology/Wonder-Editor/commit/35959c1))
* **inspector:** import wonder.js setParentKeepOrder ([2284069](https://github.com/Wonder-Technology/Wonder-Editor/commit/2284069))
* **scene-tree:** extract utils/ and external/ ([b2f16b6](https://github.com/Wonder-Technology/Wonder-Editor/commit/b2f16b6))
* **scenetree:** add check objects associate is right ([78b2eab](https://github.com/Wonder-Technology/Wonder-Editor/commit/78b2eab))
* **sceneTree:** add clearGameObjectChildren method and test ([98ef995](https://github.com/Wonder-Technology/Wonder-Editor/commit/98ef995))


### Performance Improvements

* add .rei file to increase test coverage ([ad9783f](https://github.com/Wonder-Technology/Wonder-Editor/commit/ad9783f))
* **scene-tree:** improve isGameObjectRelationError method perf ([cfe246c](https://github.com/Wonder-Technology/Wonder-Editor/commit/cfe246c))



<a name="0.4.0"></a>
# [0.4.0](https://github.com/DreamForeast/Wonder-Editor/compare/v0.3.0...v0.4.0) (2017-12-02)


### Bug Fixes

* "npm run test:coverage": add "|| true" ([9597569](https://github.com/DreamForeast/Wonder-Editor/commit/9597569))
* mainEditor.re: add canvas ([1734b31](https://github.com/DreamForeast/Wonder-Editor/commit/1734b31))
* pass run test: update rollup, rollup-plugin-commonjs version to newest ([8811ea5](https://github.com/DreamForeast/Wonder-Editor/commit/8811ea5))
* re-generate editor index to fix conflicts ([88b23a0](https://github.com/DreamForeast/Wonder-Editor/commit/88b23a0))


### Features

* add GameObjectAdaptor,GameObjectOper->"getMaterial" function ([26a1aa6](https://github.com/DreamForeast/Wonder-Editor/commit/26a1aa6))
* add get engine state, set engine state ([aef3bd7](https://github.com/DreamForeast/Wonder-Editor/commit/aef3bd7))
* add sceneTree and inspector component ([ede6c5f](https://github.com/DreamForeast/Wonder-Editor/commit/ede6c5f))
* begin "move component data to componentData_config.ts"(not finish) ([b804260](https://github.com/DreamForeast/Wonder-Editor/commit/b804260))
* begine "import engine": ([2a9e8ab](https://github.com/DreamForeast/Wonder-Editor/commit/2a9e8ab))
* GameObjectOper add "getAllComponents" function ([a833e5e](https://github.com/DreamForeast/Wonder-Editor/commit/a833e5e))
* implement "show box" ([c989789](https://github.com/DreamForeast/Wonder-Editor/commit/c989789))
* import wonder-commonlib ([b1098b6](https://github.com/DreamForeast/Wonder-Editor/commit/b1098b6))
* package.json: remove node-sass and its dependences ([69fde8f](https://github.com/DreamForeast/Wonder-Editor/commit/69fde8f))
* package.json: remove node-sass and its dependences ([26517f9](https://github.com/DreamForeast/Wonder-Editor/commit/26517f9))



<a name="0.2.0"></a>
# [0.2.0](https://github.com/DreamForeast/Wonder-Editor/compare/v0.1.0...v0.2.0) (2017-09-18)


### Bug Fixes

* directory mistake ([41981a1](https://github.com/DreamForeast/Wonder-Editor/commit/41981a1))
* fix gulp task "generateEditorIndex" ([d9577fa](https://github.com/DreamForeast/Wonder-Editor/commit/d9577fa))
* fix parent and child gameObject only show parent gameObject bug ([a08f764](https://github.com/DreamForeast/Wonder-Editor/commit/a08f764))
* fix rollup->namedExports->cnpm install: ([5ccc6af](https://github.com/DreamForeast/Wonder-Editor/commit/5ccc6af))
* gulp task "watchForRunTest" add "generateEditorIndex" task ([f37d00e](https://github.com/DreamForeast/Wonder-Editor/commit/f37d00e))
* gulp task "watchForRunTest" add "generateEditorIndex" task ([4d03835](https://github.com/DreamForeast/Wonder-Editor/commit/4d03835))
* gulp task "watchForRunTest" remove "generateEditorIndex" task ([db20609](https://github.com/DreamForeast/Wonder-Editor/commit/db20609))
* jest.json: pass testUI ([193f1ae](https://github.com/DreamForeast/Wonder-Editor/commit/193f1ae))
* remove component->asset related code ([e266501](https://github.com/DreamForeast/Wonder-Editor/commit/e266501))
* rollup->namedExports: react-dom add "findDOMNode" ([1c3f65f](https://github.com/DreamForeast/Wonder-Editor/commit/1c3f65f))
* rollup.config.xxx.js: "namedExports" now define xxx@xxx(add version to handle the package installed by cnpm case) ([60273d6](https://github.com/DreamForeast/Wonder-Editor/commit/60273d6))
* rollup.config.xxx.js: "namedExports" now define xxx@xxx(add version to handle the package installed by cnpm case) ([3d71e90](https://github.com/DreamForeast/Wonder-Editor/commit/3d71e90))
* run test: use hack to pass run test, but run test still has bug(e.g. can't set current gameObject's material) ([903fc81](https://github.com/DreamForeast/Wonder-Editor/commit/903fc81))
* SceneBuss.ts import "it" from contract.ts ([595758c](https://github.com/DreamForeast/Wonder-Editor/commit/595758c))


### Features

* adaptor add "getViewport", resize canvas functions ([fe35a6b](https://github.com/DreamForeast/Wonder-Editor/commit/fe35a6b))
* add BasicMaterial component ([842bf4e](https://github.com/DreamForeast/Wonder-Editor/commit/842bf4e))
* add BasicMaterial component->get color ([b044216](https://github.com/DreamForeast/Wonder-Editor/commit/b044216))
* ci: add "test ui" ([a61b404](https://github.com/DreamForeast/Wonder-Editor/commit/a61b404))
* ci: update node version ([509e996](https://github.com/DreamForeast/Wonder-Editor/commit/509e996))
* commit dist files ([d44f075](https://github.com/DreamForeast/Wonder-Editor/commit/d44f075))
* DeviceAdaptor add "setViewport" function ([3c74192](https://github.com/DreamForeast/Wonder-Editor/commit/3c74192))
* fill BasicMaterial and show it on MainEditor ([f833763](https://github.com/DreamForeast/Wonder-Editor/commit/f833763))
* GameObjectAdaptor: add "getParent","setParent" functions ([ec9ba20](https://github.com/DreamForeast/Wonder-Editor/commit/ec9ba20))
* move getSceneData to redux and epic ([eb7875a](https://github.com/DreamForeast/Wonder-Editor/commit/eb7875a))
* update version to 0.2.0 ([6782836](https://github.com/DreamForeast/Wonder-Editor/commit/6782836))
* update wonder-expect.js version ([6867e2d](https://github.com/DreamForeast/Wonder-Editor/commit/6867e2d))
* update wonder.js version ([2086aef](https://github.com/DreamForeast/Wonder-Editor/commit/2086aef))



<a name="0.1.0"></a>
# [0.1.0](https://github.com/DreamForeast/Wonder-Editor/compare/d13acc2...v0.1.0) (2017-08-28)


### Bug Fixes

* canvas width and style width ([d13acc2](https://github.com/DreamForeast/Wonder-Editor/commit/d13acc2))
* ci: add "gulp rollupTest" before "gulp testInCI" ([9269659](https://github.com/DreamForeast/Wonder-Editor/commit/9269659))
* fix README->ci,codecov icon ([33851aa](https://github.com/DreamForeast/Wonder-Editor/commit/33851aa))
* fix TransformAdaptor->translate bug:now can translate instead of only set position ([f0f70d3](https://github.com/DreamForeast/Wonder-Editor/commit/f0f70d3))
* now will only set clear color once ([9423686](https://github.com/DreamForeast/Wonder-Editor/commit/9423686))
* package.json: add install "electron" ([aea1dda](https://github.com/DreamForeast/Wonder-Editor/commit/aea1dda))
* package.json: not install electron ([df8ecca](https://github.com/DreamForeast/Wonder-Editor/commit/df8ecca))
* pass run test: ([53f744d](https://github.com/DreamForeast/Wonder-Editor/commit/53f744d))
* try solve ci->npm install->The package jest@20.0.4 does not satisfy its siblings' peerDependencies requirements!: update ts-ject version ([464febd](https://github.com/DreamForeast/Wonder-Editor/commit/464febd))


### Features

* add .travis.yml(commit id:8551e need commit it, but forget!) ([b4471fa](https://github.com/DreamForeast/Wonder-Editor/commit/b4471fa))
* add ci ([8551e0f](https://github.com/DreamForeast/Wonder-Editor/commit/8551e0f))
* add core ui and wordEditor ([66f3694](https://github.com/DreamForeast/Wonder-Editor/commit/66f3694))
* add node server ([350322b](https://github.com/DreamForeast/Wonder-Editor/commit/350322b))
* commit .idea files ([0a97f5c](https://github.com/DreamForeast/Wonder-Editor/commit/0a97f5c))
* commit dist ([6225ea9](https://github.com/DreamForeast/Wonder-Editor/commit/6225ea9))
* editor architecture ([93d37b5](https://github.com/DreamForeast/Wonder-Editor/commit/93d37b5))
* try pass ci: update node version ([3940569](https://github.com/DreamForeast/Wonder-Editor/commit/3940569))
* update author to "DreamForest" ([9da3ff4](https://github.com/DreamForeast/Wonder-Editor/commit/9da3ff4))
* use wonder.js as engine instead of amyjs: pass ts compile and rollup ([03d39ed](https://github.com/DreamForeast/Wonder-Editor/commit/03d39ed))



