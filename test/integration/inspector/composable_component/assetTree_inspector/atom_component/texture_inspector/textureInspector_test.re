open Wonder_jest;

open Expect;

open Expect.Operators;

open AssetNodeType;

open Sinon;

open Js.Promise;

let _ =
  describe("texture inspector", () => {
    let sandbox = getSandboxDefaultVal();

    beforeEach(() => {
      sandbox := createSandbox();
      MainEditorSceneTool.initState(~sandbox, ());
    });
    afterEach(() => restoreSandbox(refJsObjToSandbox(sandbox^)));

    describe("prepare currentSelectSource", () => {
      beforeEach(() => {
        MainEditorSceneTool.createDefaultScene(
          sandbox,
          MainEditorAssetTool.initAssetTree,
        );
        CurrentSelectSourceEditorService.setCurrentSelectSource(
          EditorType.Asset,
        )
        |> StateLogicService.getAndSetEditorState;
      });

      describe("test texture inspector->show default value", () =>
        test("test snapshot", () => {
          let assetTreeData =
            MainEditorAssetTreeTool.BuildAssetTree.Texture.buildOneTextureAssetTree();

          MainEditorAssetChildrenNodeTool.selectTextureNode(
            ~nodeId=
              MainEditorAssetTreeTool.BuildAssetTree.Texture.getFirstTextureNodeId(
                assetTreeData,
              ),
            (),
          );

          BuildComponentTool.buildInspectorComponent(
            TestTool.buildEmptyAppState(),
            InspectorTool.buildFakeAllShowComponentConfig(),
          )
          |> ReactTestTool.createSnapshotAndMatch;
        })
      );

      describe("test texture rename", () => {
        describe("test rename to specific name", () =>
          test("test snapshot", () => {
            let assetTreeData =
              MainEditorAssetTreeTool.BuildAssetTree.Texture.buildOneTextureAssetTree();
            let newName = "newTextureName";

            AssetTreeInspectorTool.Rename.renameAssetTextureNode(
              ~nodeId=
                MainEditorAssetTreeTool.BuildAssetTree.Texture.getFirstTextureNodeId(
                  assetTreeData,
                ),
              ~name=newName,
              (),
            );

            BuildComponentTool.buildAssetComponent()
            |> ReactTestTool.createSnapshotAndMatch;
          })
        );

        testPromise(
          {|upload texture;
            rename texture;

            texture name should be renamed
              |},
          () => {
            MainEditorAssetTool.buildFakeFileReader();
            MainEditorAssetTool.buildFakeImage();

            let assetTreeData =
              MainEditorAssetTreeTool.BuildAssetTree.Texture.buildOneTextureAssetTree();
            let newName = "newTextureToEngine";

            MainEditorAssetUploadTool.loadOneTexture()
            |> then_(uploadedTextureNodeId => {
                 AssetTreeInspectorTool.Rename.renameAssetTextureNode(
                   ~nodeId=uploadedTextureNodeId,
                   ~name=newName,
                   (),
                 );
                 MainEditorAssetChildrenNodeTool.selectTextureNode(
                   ~nodeId=uploadedTextureNodeId,
                   (),
                 );

                 MainEditorAssetNodeTool.getTextureComponentFromCurrentNodeId()
                 |> BasicSourceTextureEngineService.unsafeGetBasicSourceTextureName
                 |> StateLogicService.getEngineStateToGetData
                 |> expect == newName
                 |> Js.Promise.resolve;
               });
          },
        );
      });

      describe("test texture change wrap", () =>
        describe("test set wrapS to Repeat", () => {
          let _prepareAndExec = () => {
            let assetTreeData =
              MainEditorAssetTreeTool.BuildAssetTree.Texture.buildOneTextureAssetTree();
            let wrapRepeatType = TextureInspectorTool.getWrapRepeatType();
            let nodeId =
              MainEditorAssetTreeTool.BuildAssetTree.Texture.getFirstTextureNodeId(
                assetTreeData,
              );

            TextureInspectorTool.changeWrapS(
              MainEditorAssetNodeTool.getTextureComponentFromNodeId(
                MainEditorAssetTreeTool.BuildAssetTree.Texture.getFirstTextureNodeId(
                  assetTreeData,
                ),
              ),
              wrapRepeatType,
            );

            (
              MainEditorAssetNodeTool.getTextureComponentFromNodeId(nodeId),
              wrapRepeatType,
            );
          };

          test("test snapshot", () => {
            let _ = _prepareAndExec();

            BuildComponentTool.buildInspectorComponent(
              TestTool.buildEmptyAppState(),
              InspectorTool.buildFakeAllShowComponentConfig(),
            )
            |> ReactTestTool.createSnapshotAndMatch;
          });
          test("set wrapS", () => {
            let (textureComponent, wrapRepeatType) = _prepareAndExec();

            BasicSourceTextureEngineService.getWrapS(textureComponent)
            |> StateLogicService.getEngineStateToGetData
            |> TextureTypeUtils.convertWrapToInt
            |> expect == wrapRepeatType;
          });
          test("mark need update", () => {
            let (textureComponent, wrapRepeatType) = _prepareAndExec();

            let engineState = StateEngineService.unsafeGetState();
            BasicSourceTextureToolEngine.getIsNeedUpdate(
              textureComponent,
              engineState,
            )
            |> expect == true;
          });
        })
      );

      describe("test texture change filter", () => {
        describe("test set MagFilter to Nearest", () => {
          let _prepareAndExec = () => {
            let assetTreeData =
              MainEditorAssetTreeTool.BuildAssetTree.Texture.buildOneTextureAssetTree();
            let filterNearestType =
              TextureInspectorTool.getFilterNearestType();
            let nodeId =
              MainEditorAssetTreeTool.BuildAssetTree.Texture.getFirstTextureNodeId(
                assetTreeData,
              );

            TextureInspectorTool.changeMagFilter(
              MainEditorAssetNodeTool.getTextureNode(nodeId).textureComponent,
              filterNearestType,
            );

            (
              MainEditorAssetNodeTool.getTextureComponentFromNodeId(nodeId),
              filterNearestType,
            );
          };

          test("test snapshot", () => {
            let _ = _prepareAndExec();

            BuildComponentTool.buildInspectorComponent(
              TestTool.buildEmptyAppState(),
              InspectorTool.buildFakeAllShowComponentConfig(),
            )
            |> ReactTestTool.createSnapshotAndMatch;
          });

          test("set magFilter", () => {
            let (textureComponent, filterNearestType) = _prepareAndExec();

            BasicSourceTextureEngineService.getMagFilter(textureComponent)
            |> StateLogicService.getEngineStateToGetData
            |> TextureTypeUtils.convertFilterToInt
            |> expect == filterNearestType;
          });
          test("mark need update", () => {
            let (textureComponent, _) = _prepareAndExec();

            let engineState = StateEngineService.unsafeGetState();
            BasicSourceTextureToolEngine.getIsNeedUpdate(
              textureComponent,
              engineState,
            )
            |> expect == true;
          });
        });

        describe("test set MinFilter to Nearest_mipmap_linear", () => {
          let _prepareAndExec = () => {
            let assetTreeData =
              MainEditorAssetTreeTool.BuildAssetTree.Texture.buildOneTextureAssetTree();
            let filterLinearMipmapLinearType =
              TextureInspectorTool.getFilterLinearMipmapLinearType();

            let nodeId =
              MainEditorAssetTreeTool.BuildAssetTree.Texture.getFirstTextureNodeId(
                assetTreeData,
              );

            TextureInspectorTool.changeMinFilter(
              MainEditorAssetNodeTool.getTextureComponentFromNodeId(
                MainEditorAssetTreeTool.BuildAssetTree.Texture.getFirstTextureNodeId(
                  assetTreeData,
                ),
              ),
              filterLinearMipmapLinearType,
            );

            (
              MainEditorAssetNodeTool.getTextureComponentFromNodeId(nodeId),
              filterLinearMipmapLinearType,
            );
          };

          test("test snapshot", () => {
            let _ = _prepareAndExec();

            BuildComponentTool.buildInspectorComponent(
              TestTool.buildEmptyAppState(),
              InspectorTool.buildFakeAllShowComponentConfig(),
            )
            |> ReactTestTool.createSnapshotAndMatch;
          });

          test("set minFilter", () => {
            let (textureComponent, filterNearestType) = _prepareAndExec();

            BasicSourceTextureEngineService.getMinFilter(textureComponent)
            |> StateLogicService.getEngineStateToGetData
            |> TextureTypeUtils.convertFilterToInt
            |> expect == filterNearestType;
          });
          test("mark need update", () => {
            let (textureComponent, _) = _prepareAndExec();

            let engineState = StateEngineService.unsafeGetState();
            BasicSourceTextureToolEngine.getIsNeedUpdate(
              textureComponent,
              engineState,
            )
            |> expect == true;
          });
        });
      });
    });
  });