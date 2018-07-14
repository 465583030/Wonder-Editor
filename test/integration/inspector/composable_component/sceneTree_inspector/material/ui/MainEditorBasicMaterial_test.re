open Wonder_jest;

open Expect;

open Expect.Operators;

open Sinon;

type retainedProps = {
  color: string,
  map: option(int),
};

let _ =
  describe("MainEditorBasicMaterial", () => {
    let sandbox = getSandboxDefaultVal();
    beforeEach(() => {
      sandbox := createSandbox();
      MainEditorSceneTool.initStateAndGl(~sandbox, ());
      EventListenerTool.buildFakeDom()
      |> EventListenerTool.stubGetElementByIdReturnFakeDom;
    });
    afterEach(() => restoreSandbox(refJsObjToSandbox(sandbox^)));
    describe("test should update", () => {
      test("if ( color, map ) not change, should not update", () =>
        MainEditorBasicMaterial.shouldUpdate(
          OldNewSelfTool.buildOldNewSelf(
            {color: "#ffffff", map: Some(1)},
            {color: "#ffffff", map: Some(1)},
          ),
        )
        |> expect == false
      );
      test("else if color change, should update", () =>
        MainEditorBasicMaterial.shouldUpdate(
          OldNewSelfTool.buildOldNewSelf(
            {color: "#ffffff", map: Some(1)},
            {color: "#c0c0c0", map: Some(1)},
          ),
        )
        |> expect == true
      );
      test("else if map change, should update", () =>
        MainEditorBasicMaterial.shouldUpdate(
          OldNewSelfTool.buildOldNewSelf(
            {color: "#ffffff", map: Some(1)},
            {color: "#ffffff", map: Some(2)},
          ),
        )
        |> expect == true
      );
    });
    describe("test set currentSceneTreeNode", () => {
      beforeEach(() =>
        MainEditorSceneTool.createDefaultScene(
          sandbox,
          MainEditorSceneTool.setFirstBoxTobeCurrentSceneTreeNode,
        )
      );
      describe("test change color should set current gameObject color", () =>
        /* TODO rename to "test set color value" */
        test("set color value to stringInput", () => {
          let currentGameObjectMaterial =
            GameObjectTool.getCurrentSceneTreeNodeMaterial();
          let value = "#c0c0c0";
          let component =
            BuildComponentTool.buildMaterialComponent(
              currentGameObjectMaterial,
            );
          MaterialEventTool.triggerChangeAndBlurMaterialEvent(
            component,
            value,
          );
          component |> ReactTestTool.createSnapshotAndMatch;
        })
      );
    });
    describe("test gameObject basic material texture", () => {
      beforeEach(() => {
        MainEditorSceneTool.createDefaultScene(
          sandbox,
          () => {
            MainEditorAssetTool.initAssetTree();
            MainEditorSceneTool.setFirstBoxTobeCurrentSceneTreeNode();
          },
        );
        CurrentSelectSourceEditorService.setCurrentSelectSource(
          EditorType.SceneTree,
        )
        |> StateLogicService.getAndSetEditorState;
      });
      afterEach(() =>
        StateAssetService.getState()
        |> CurrentNodeDataAssetService.clearCurrentNodeData
        |> CurrentNodeParentIdAssetService.clearCurrentNodeParentId
        |> StateAssetService.setState
        |> ignore
      );

      describe("test drag texture to set gameObject material map", () => {
        describe("test snapshot", () => {
          test("test no drag", () => {
            MainEditorAssetTool.buildTwoLayerAssetTreeRoot() |> ignore;

            BuildComponentTool.buildInspectorComponent(
              TestTool.buildEmptyAppState(),
              InspectorTool.buildFakeAllShowComponentConfig(),
            )
            |> ReactTestTool.createSnapshotAndMatch;
          });

          /* TODO rename to "test drag texture asset into gameObject material map zone, the zone should show the texture source" */
          test("test drag texture file into gameObject material texture", () => {
            let assetTreeDomRecord =
              MainEditorAssetTool.buildTwoLayerAssetTreeRoot();

            assetTreeDomRecord
            |> MainEditorAssetNodeTool.OperateTwoLayer.getFirstTextureDomIndex
            |> MainEditorBasicMaterialTool.triggerFileDragStartEvent;

            MainEditorBasicMaterialTool.triggerDragTextureToGameObjectMaterial();

            BuildComponentTool.buildInspectorComponent(
              TestTool.buildEmptyAppState(),
              InspectorTool.buildFakeAllShowComponentConfig(),
            )
            |> ReactTestTool.createSnapshotAndMatch;
          });
          /* TODO rename: test set map when already has map, material's map should be the new one */
          test("test if have already set map, set map again", () => {
            let assetTreeDomRecord =
              MainEditorAssetTool.buildTwoLayerAssetTreeRoot();
            let firstTextureDomIndex =
              assetTreeDomRecord
              |> MainEditorAssetNodeTool.OperateTwoLayer.getFirstTextureDomIndex;
            let secondTextureDomIndex =
              assetTreeDomRecord
              |> MainEditorAssetNodeTool.OperateTwoLayer.getSecondTextureDomIndex;

            MainEditorBasicMaterialTool.triggerFileDragStartEvent(
              firstTextureDomIndex,
            );
            MainEditorBasicMaterialTool.triggerDragTextureToGameObjectMaterial();

            MainEditorBasicMaterialTool.triggerFileDragStartEvent(
              secondTextureDomIndex,
            );
            MainEditorBasicMaterialTool.triggerDragTextureToGameObjectMaterial();

            BuildComponentTool.buildInspectorComponent(
              TestTool.buildEmptyAppState(),
              InspectorTool.buildFakeAllShowComponentConfig(),
            )
            |> ReactTestTool.createSnapshotAndMatch;
          });
        });
        describe("test logic", () =>
          describe("test engine ", () => {
            beforeEach(() => {
              MainEditorAssetTool.buildFakeFileReader();
              MainEditorAssetTool.buildFakeImage();
            });

            testPromise(
              "test upload texture;
               drag texture to set gameObject material texture;",
              () => {
                let assetTreeDomRecord =
                  MainEditorAssetTool.buildTwoLayerAssetTreeRoot();

                MainEditorAssetHeader.Method._fileLoad(
                  TestTool.getDispatch(),
                  BaseEventTool.buildFileEvent(),
                )
                |> Js.Promise.then_(() => {
                     assetTreeDomRecord
                     |> MainEditorAssetNodeTool.OperateTwoLayer.getUploadedeTextureNodeDomIndex
                     |> MainEditorBasicMaterialTool.triggerFileDragStartEvent;

                     MainEditorBasicMaterialTool.triggerDragTextureToGameObjectMaterial();

                     let currentGameObject =
                       SceneEditorService.unsafeGetCurrentSceneTreeNode
                       |> StateLogicService.getEditorState;
                     let engineStateToGetData =
                       StateLogicService.getRunEngineState();

                     let mapId =
                       engineStateToGetData
                       |> GameObjectComponentEngineService.getBasicMaterialComponent(
                            currentGameObject,
                          )
                       |. BasicMaterialEngineService.unsafeGetMap(
                            engineStateToGetData,
                          )
                       |> Uint.convertUint32ToInt;

                     mapId
                     |>
                     expect == MainEditorAssetNodeTool.OperateTwoLayer.getUploadedTextureIndex(
                                 assetTreeDomRecord,
                               )
                     |> Js.Promise.resolve;
                   });
              },
            );
          })
        );

        describe("deal with specific case", () => {
          /* TODO rename: if drag-texture-asset dragLeave gameObject material texture, should change nothing */
          test(
            "if drag texture file dragLeave gameObject material texture, should change nothing",
            () => {
            let assetTreeDomRecord =
              MainEditorAssetTool.buildTwoLayerAssetTreeRoot();

            assetTreeDomRecord
            |> MainEditorAssetNodeTool.OperateTwoLayer.getFirstTextureDomIndex
            |> MainEditorBasicMaterialTool.triggerFileDragStartEvent;

            MainEditorBasicMaterialTool.triggerDragTextureLeaveGameObjectMaterial();

            BuildComponentTool.buildInspectorComponent(
              TestTool.buildEmptyAppState(),
              InspectorTool.buildFakeAllShowComponentConfig(),
            )
            |> ReactTestTool.createSnapshotAndMatch;
          });
          /* TODO all: rename: should change nothing */
          test(
            "if drag folder into gameObject material texture, change nothing",
            () => {
            let assetTreeDomRecord =
              MainEditorAssetTool.buildTwoLayerAssetTreeRoot();

            assetTreeDomRecord
            |> MainEditorAssetNodeTool.OperateTwoLayer.getFirstFolderDomIndexForAssetTree
            |> MainEditorBasicMaterialTool.triggerFileDragStartEvent;

            MainEditorBasicMaterialTool.triggerTextureDragEvent();

            BuildComponentTool.buildInspectorComponent(
              TestTool.buildEmptyAppState(),
              InspectorTool.buildFakeAllShowComponentConfig(),
            )
            |> ReactTestTool.createSnapshotAndMatch;
          });
        });
      });

      /* TODO add controller case */

      /* TODO add "show image base64" case as "show texture"->image base64 case */

      /* TODO add engine cases */
      /* TODO rename: test remove texture */
      describe("test set texture is null", () => {
        test("test if not set map, change nothing", () => {
          MainEditorBasicMaterialTool.triggerTextureRemoveClickEvent();

          BuildComponentTool.buildInspectorComponent(
            TestTool.buildEmptyAppState(),
            InspectorTool.buildFakeAllShowComponentConfig(),
          )
          |> ReactTestTool.createSnapshotAndMatch;
        });

        /* TODO rename: should remove map */
        test("test if have already set map, set map is null", () => {
          let assetTreeDomRecord =
            MainEditorAssetTool.buildTwoLayerAssetTreeRoot();

          assetTreeDomRecord
          |> MainEditorAssetNodeTool.OperateTwoLayer.getFirstTextureDomIndex
          |> MainEditorBasicMaterialTool.triggerFileDragStartEvent;
          MainEditorBasicMaterialTool.triggerDragTextureToGameObjectMaterial();
          MainEditorBasicMaterialTool.triggerTextureRemoveClickEvent();

          BuildComponentTool.buildInspectorComponent(
            TestTool.buildEmptyAppState(),
            InspectorTool.buildFakeAllShowComponentConfig(),
          )
          |> ReactTestTool.createSnapshotAndMatch;
        });
      });
    });
  });