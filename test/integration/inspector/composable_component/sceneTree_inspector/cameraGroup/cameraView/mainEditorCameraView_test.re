open Wonder_jest;

open Expect;

open Expect.Operators;

open Sinon;

open MainEditorTransform;

let _ =
  describe("MainEditor CameraView", () => {
    let sandbox = getSandboxDefaultVal();
    beforeEach(() => {
      sandbox := createSandbox();

      MainEditorSceneTool.initState(~sandbox, ());
    });
    afterEach(() => restoreSandbox(refJsObjToSandbox(sandbox^)));

    describe("test set currentSceneTreeNode to be camera", () => {
      beforeEach(() => {
        MainEditorSceneTool.createDefaultScene(
          sandbox,
          MainEditorSceneTool.setSceneFirstCameraToBeCurrentSceneTreeNode,
        );

        HeaderTool.triggerAddBox();

        SceneTreeNodeDomTool.OperateDefaultScene.getNewGameObjectDomIndex()
        |> SceneTreeTool.clearCurrentGameObjectAndSetTreeSpecificGameObject;

        AddableComponentTool.addCameraGroupInBox();
      });

      describe("test set current camera", () => {
        describe("test snapshot", () => {
          test(
            "test if camera is currentCamera, the cameraView checkBox checked should == true and disabled should == true ",
            () => {
              MainEditorSceneTool.setSceneFirstCameraToBeCurrentSceneTreeNode();

              BuildComponentTool.buildCameraView(
                TestTool.buildEmptyAppState(),
              )
              |> ReactTestTool.createSnapshotAndMatch;
            },
          );
          test(
            "test if camera isn't currentCamera, the cameraView checkBox checked should == false and disabled should == false ",
            () =>
            BuildComponentTool.buildCameraView(TestTool.buildEmptyAppState())
            |> ReactTestTool.createSnapshotAndMatch
          );
          test(
            "test set unactive camera to be currentCamera, the currentCamera->cameraView checkBox checked should == true and disabled should == true",
            () => {
              MainEditorCameraViewTool.triggerClickSetCurrentCameraEvent();

              BuildComponentTool.buildCameraView(
                TestTool.buildEmptyAppState(),
              )
              |> ReactTestTool.createSnapshotAndMatch;
            },
          );
        });
        describe("test logic", () =>
          test(
            "test set unactive camera to be currentCamera, the unactive one should be marked active",
            () => {
              MainEditorCameraViewTool.triggerClickSetCurrentCameraEvent();

              let firstCamera = GameObjectTool.unsafeGetCurrentSceneTreeNode();

              let engineState = StateEngineService.unsafeGetState();
              StateEditorService.getState()
              |> GameViewEditorService.getActivedBasicCameraView
              |> OptionService.unsafeGet
              |>
              expect == GameObjectComponentEngineService.unsafeGetBasicCameraViewComponent(
                          firstCamera,
                          engineState,
                        );
            },
          )
        );
      });
    });
  });