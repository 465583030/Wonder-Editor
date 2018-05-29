/* open Wonder_jest;

open Expect;

open Expect.Operators;

open Sinon;

let _ =
  describe(
    "AssetTreeInspector",
    () => {
      let sandbox = getSandboxDefaultVal();
      let _getFromArray = (array, index) => ArrayService.getNth(index, array);
      beforeEach(
        () => {
          sandbox := createSandbox();
          MainEditorSceneTool.initStateAndGl(~sandbox, ());
          MainEditorSceneTool.createDefaultScene(
            sandbox,
            MainEditorAssetTool.initAssetTree(MainEditorAssetTool.buildTwoLayerAssetTree)
          )
        }
      );
      afterEach(() => restoreSandbox(refJsObjToSandbox(sandbox^)));
      describe(
        "prepare currentSelectSource",
        () => {
          beforeEach(
            () =>
              CurrentSelectSourceEditorService.setCurrentSelectSource(EditorType.AssetTree)
              |> StateLogicService.getAndSetEditorState
          );
          describe(
            "test component snapshot",
            () => {
              test(
                "if hasn't currentAssetChildrenNodeParent, show nothing",
                () =>
                  BuildComponentTool.buildInspectorComponent(
                    TestTool.buildEmptyAppState(),
                    InspectorTool.buildFakeAllShowComponentConfig()
                  )
                  |> ReactTestTool.createSnapshotAndMatch
              );
              test(
                "else",
                () => {
                  MainEditorAssetTool.setFolder1ToBeCurrentAssetChildrenNodeParent();
                  BuildComponentTool.buildInspectorComponent(
                    TestTool.buildEmptyAppState(),
                    InspectorTool.buildFakeAllShowComponentConfig()
                  )
                  |> ReactTestTool.createSnapshotAndMatch
                }
              )
            }
          );
          describe(
            "test rename treeNode",
            () => {
              let triggerChangeEvent = (value, domChildren) => {
                let article = _getFromArray(domChildren, 0);
                let input = _getFromArray(article##children, 3);
                BaseEventTool.triggerChangeEvent(input, BaseEventTool.buildFormEvent(value))
              };
              let triggerBlurEvent = (value, domChildren) => {
                let article = _getFromArray(domChildren, 0);
                let input = _getFromArray(article##children, 3);
                BaseEventTool.triggerBlurEvent(input, BaseEventTool.buildFormEvent(value))
              };
              test(
                "test not rename",
                () =>
                  BuildComponentTool.buildAssetTreeComponent()
                  |> ReactTestTool.createSnapshotAndMatch
              );
              test(
                "test rename to specific name",
                () => {
                  MainEditorAssetTool.setFolder2ToBeCurrentAssetChildrenNodeParent();
                  let folderId = MainEditorAssetTool.folderId2;
                  let newName = "mickeyFolder";
                  let component =
                    BuildComponentTool.buildAssetTreeInspector(
                      folderId,
                      StateEditorService.getState()
                      |> AssetUtils.getRootTreeNode
                      |> AssetUtils.getSpecificTreeNodeById(folderId)
                      |> OptionService.unsafeGet
                    );
                  BaseEventTool.triggerComponentEvent(component, triggerChangeEvent(newName));
                  BaseEventTool.triggerComponentEvent(component, triggerBlurEvent(newName));
                  BuildComponentTool.buildAssetTreeComponent()
                  |> ReactTestTool.createSnapshotAndMatch
                }
              );
              describe(
                "test the root folder can't be rename",
                () =>
                  test(
                    "the root treeNode rename-input disabled should be true",
                    () => {
                      MainEditorAssetTool.setRootToBeCurrentAssetChildrenNodeParent();
                      let folderId = MainEditorAssetTool.assetTreeRootId;
                      BuildComponentTool.buildAssetTreeInspector(
                        folderId,
                        StateEditorService.getState()
                        |> AssetUtils.getRootTreeNode
                        |> AssetUtils.getSpecificTreeNodeById(folderId)
                        |> OptionService.unsafeGet
                      )
                      |> ReactTestTool.createSnapshotAndMatch
                    }
                  )
              );
              describe(
                "deal with specific case",
                () =>
                  test(
                    "key in '', trigger onBlur, the input value should be primitive name",
                    () => {
                      MainEditorAssetTool.setFolder2ToBeCurrentAssetChildrenNodeParent();
                      let folderId = MainEditorAssetTool.folderId2;
                      let newName = "";
                      let component =
                        BuildComponentTool.buildAssetTreeInspector(
                          folderId,
                          StateEditorService.getState()
                          |> AssetUtils.getRootTreeNode
                          |> AssetUtils.getSpecificTreeNodeById(folderId)
                          |> OptionService.unsafeGet
                        );
                      BaseEventTool.triggerComponentEvent(component, triggerChangeEvent(newName));
                      BaseEventTool.triggerComponentEvent(component, triggerBlurEvent(newName));
                      component
                      |> ReactTestTool.createSnapshotAndMatch
                    }
                  )
              )
            }
          )
        }
      )
    }
  ); */