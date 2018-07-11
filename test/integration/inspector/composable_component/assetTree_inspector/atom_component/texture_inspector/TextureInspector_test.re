open Wonder_jest;

open Expect;

open Expect.Operators;

open AssetNodeType;

open Sinon;

let _ =
  describe("TextureInspector", () => {
    let sandbox = getSandboxDefaultVal();
    beforeEach(() => {
      sandbox := createSandbox();
      MainEditorSceneTool.initStateAndGl(~sandbox, ());
      EventListenerTool.buildFakeDom()
      |> EventListenerTool.stubGetElementByIdReturnFakeDom;
    });
    afterEach(() => restoreSandbox(refJsObjToSandbox(sandbox^)));

    describe("prepare currentSelectSource", () => {
      let _clickAssetChildrenNodeToSetCurrentNode = index => {
        let component = BuildComponentTool.buildAssetComponent();
        BaseEventTool.triggerComponentEvent(
          component,
          AssetTreeEventTool.clickAssetTreeChildrenNode(index),
        );
      };
      beforeEach(() => {
        MainEditorSceneTool.createDefaultScene(
          sandbox,
          MainEditorAssetTool.initAssetTree,
        );
        /* MainEditorAssetTool.buildTwoLayerAssetTreeRoot, */
        CurrentSelectSourceEditorService.setCurrentSelectSource(
          EditorType.Asset,
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

      describe("test component snapshot", () =>
        test("test texture attribute default value", () => {
          _clickAssetChildrenNodeToSetCurrentNode(2);

          BuildComponentTool.buildInspectorComponent(
            TestTool.buildEmptyAppState(),
            InspectorTool.buildFakeAllShowComponentConfig(),
          )
          |> ReactTestTool.createSnapshotAndMatch;
        })
      );

      describe("test texture rename", () => {
        let _triggerInspectorRenameEvent = newName => {
          let inspectorComponent =
            BuildComponentTool.buildInspectorComponent(
              TestTool.buildEmptyAppState(),
              InspectorTool.buildFakeAllShowComponentConfig(),
            );
          BaseEventTool.triggerComponentEvent(
            inspectorComponent,
            TextureInspectorTool.triggerChangeRenameEvent(newName),
          );
          BaseEventTool.triggerComponentEvent(
            inspectorComponent,
            TextureInspectorTool.triggerBlurRenameEvent(newName),
          );
        };
        describe("test snapshot", () =>
          test("test rename to specific name", () => {
            _clickAssetChildrenNodeToSetCurrentNode(2);
            let newName = "newTextureName";

            _triggerInspectorRenameEvent(newName);

            BuildComponentTool.buildAssetComponent()
            |> ReactTestTool.createSnapshotAndMatch;
          })
        );

        describe("test logic", ()
          /* TODO all:rename to "test engine" */
          =>
            describe("test set engine", () =>
              testPromise(
                "upload texture;
                         rename texture;", () => {
                MainEditorAssetTool.buildFakeFileReader();
                MainEditorAssetTool.buildFakeImage();

                MainEditorAssetHeader.Method._fileLoad(
                  TestTool.getDispatch(),
                  BaseEventTool.buildFileEvent(),
                )
                |> Js.Promise.then_(() => {
                     _clickAssetChildrenNodeToSetCurrentNode(5);
                     let newName = "newTextureToEngine";

                     _triggerInspectorRenameEvent(newName);

                     /* TODO all: get textureIndex from textureNodeMap */
                     BasicSourceTextureEngineService.unsafeGetBasicSourceTextureName(
                       2,
                     )
                     |> StateLogicService.getEngineStateToGetData
                     |> expect == newName
                     |> Js.Promise.resolve;
                   });
              })
            )
          );
      });

      describe("test set engine", () => {
        describe("test texture change wrap", () => {
          let _triggerInspectorChangeWrapEvent = (wrapIndex, type_) => {
            let inspectorComponent =
              BuildComponentTool.buildInspectorComponent(
                TestTool.buildEmptyAppState(),
                InspectorTool.buildFakeAllShowComponentConfig(),
              );
            BaseEventTool.triggerComponentEvent(
              inspectorComponent,
              TextureInspectorTool.triggerChangeWrapEvent(
                wrapIndex,
                type_ |> string_of_int,
              ),
            );
          };
          describe("test set wrapS to REPEAT", () => {
            /* TODO move out from "test set engine" */
            test("test snapshot", () => {
              _clickAssetChildrenNodeToSetCurrentNode(2);

              /* TODO all: use function to mark
                 let getWrapSDomIndx = () => 3;
                 let getWrapRepeatType = () => Wonderjs.SourceTextureType.REPEAT ;

                 _triggerInspectorChangeWrapEvent(getWrapSDomIndx(), getWrapRepeatType ());
                 */
              _triggerInspectorChangeWrapEvent(3, 2);

              BuildComponentTool.buildInspectorComponent(
                TestTool.buildEmptyAppState(),
                InspectorTool.buildFakeAllShowComponentConfig(),
              )
              |> ReactTestTool.createSnapshotAndMatch;
            });
            test("test logic", () => {
              _clickAssetChildrenNodeToSetCurrentNode(2);
              let wrapType = 2;

              _triggerInspectorChangeWrapEvent(3, wrapType);

              let textureIndex =
                TextureInspectorTool.getTextureIndexFromCurrentNodeData();

              BasicSourceTextureEngineService.getWrapS(textureIndex)
              |> StateLogicService.getEngineStateToGetData
              |> TextureTypeUtils.convertWrapToInt
              |> expect == wrapType;
            });
          });
          describe("test set wrapT to MIRRORED_REPEAT", () => {
            test("test snapshot", () => {
              _clickAssetChildrenNodeToSetCurrentNode(2);

              _triggerInspectorChangeWrapEvent(4, 1);

              BuildComponentTool.buildInspectorComponent(
                TestTool.buildEmptyAppState(),
                InspectorTool.buildFakeAllShowComponentConfig(),
              )
              |> ReactTestTool.createSnapshotAndMatch;
            });
            test("test logic", () => {
              _clickAssetChildrenNodeToSetCurrentNode(2);
              let wrapType = 1;

              _triggerInspectorChangeWrapEvent(4, wrapType);

              let textureIndex =
                TextureInspectorTool.getTextureIndexFromCurrentNodeData();

              BasicSourceTextureEngineService.getWrapT(textureIndex)
              |> StateLogicService.getEngineStateToGetData
              |> TextureTypeUtils.convertWrapToInt
              |> expect == wrapType;
            });
          });
        });
        describe("test texture change filter", () => {
          let _triggerInspectorChangeWrapEvent = (index, type_) => {
            let inspectorComponent =
              BuildComponentTool.buildInspectorComponent(
                TestTool.buildEmptyAppState(),
                InspectorTool.buildFakeAllShowComponentConfig(),
              );
            BaseEventTool.triggerComponentEvent(
              inspectorComponent,
              TextureInspectorTool.triggerChangeFilterEvent(
                index,
                type_ |> string_of_int,
              ),
            );
          };
          describe("test set FilterMag to LINEARMIPMAPLINEAR", () => {
            test("test snapshot", () => {
              _clickAssetChildrenNodeToSetCurrentNode(2);

              _triggerInspectorChangeWrapEvent(5, 5);

              BuildComponentTool.buildInspectorComponent(
                TestTool.buildEmptyAppState(),
                InspectorTool.buildFakeAllShowComponentConfig(),
              )
              |> ReactTestTool.createSnapshotAndMatch;
            });
            test("test logic", () => {
              _clickAssetChildrenNodeToSetCurrentNode(2);
              let filterType = 5;

              _triggerInspectorChangeWrapEvent(5, filterType);

              let textureIndex =
                TextureInspectorTool.getTextureIndexFromCurrentNodeData();

              BasicSourceTextureEngineService.getMagFilter(textureIndex)
              |> StateLogicService.getEngineStateToGetData
              |> TextureTypeUtils.convertFilterToInt
              |> expect == filterType;
            });
          });
          describe("test set FilterMin to NEARESTMIPMAPLINEAR", () => {
            test("test snapshot", () => {
              _clickAssetChildrenNodeToSetCurrentNode(2);

              _triggerInspectorChangeWrapEvent(6, 4);

              BuildComponentTool.buildInspectorComponent(
                TestTool.buildEmptyAppState(),
                InspectorTool.buildFakeAllShowComponentConfig(),
              )
              |> ReactTestTool.createSnapshotAndMatch;
            });

            test("test logic", () => {
              _clickAssetChildrenNodeToSetCurrentNode(2);
              let filterType = 4;

              _triggerInspectorChangeWrapEvent(6, filterType);

              let textureIndex =
                TextureInspectorTool.getTextureIndexFromCurrentNodeData();

              BasicSourceTextureEngineService.getMinFilter(textureIndex)
              |> StateLogicService.getEngineStateToGetData
              |> TextureTypeUtils.convertFilterToInt
              |> expect == filterType;
            });
          });
        });
      });
    });
  });