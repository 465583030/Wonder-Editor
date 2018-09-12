open Wonder_jest;

open Expect;

open Expect.Operators;

open Sinon;

open MainEditorTransform;

let _ =
  describe("controller inspector arcballCameraController", () => {
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
          MainEditorSceneTool.setFirstCameraTobeCurrentSceneTreeNode,
        );

        CurrentSelectSourceEditorService.setCurrentSelectSource(
          EditorType.SceneTree,
        )
        |> StateLogicService.getAndSetEditorState;
      });

      describe("test set value into engineState", () => {
        describe("test change arcballCameraController distance", () => {
          let _getArcballCameraDistance = (component, engineState) =>
            engineState
            |> ArcballCameraEngineService.unsafeGetArcballCameraControllerDistance(
                 component,
               )
            |. FloatService.truncateFloatValue(5);
          test("test change distance should set into engine", () => {
            AddableComponentTool.addArcballCameraInCamera();

            let currentGameObjectArcballCamera =
              GameObjectTool.getCurrentGameObjectArcballCamera();

            let component =
              BuildComponentTool.buildInspectorComponent(
                TestTool.buildEmptyAppState(),
                InspectorTool.buildFakeAllShowComponentConfig(),
              );
            let value = 21.1;

            BaseEventTool.triggerComponentEvent(
              component,
              MainEditorCameraTool.triggerChangeArcballDistance(value),
            );

            BaseEventTool.triggerComponentEvent(
              component,
              MainEditorCameraTool.triggerBlurArcballDistance(value),
            );

            StateEngineService.unsafeGetState()
            |> _getArcballCameraDistance(currentGameObjectArcballCamera)
            |> expect == value;
          });
        });

        describe("test change arcballCameraController minDistance", () => {
          let _getArcballCameraMinDistance = (component, engineState) =>
            engineState
            |> ArcballCameraEngineService.unsafeGetArcballCameraControllerMinDistance(
                 component,
               )
            |. FloatService.truncateFloatValue(5);

          test("test change minDistance should set into engine", () => {
            AddableComponentTool.addArcballCameraInCamera();

            let currentGameObjectArcballCamera =
              GameObjectTool.getCurrentGameObjectArcballCamera();

            let component =
              BuildComponentTool.buildInspectorComponent(
                TestTool.buildEmptyAppState(),
                InspectorTool.buildFakeAllShowComponentConfig(),
              );
            let value = 11.1;

            BaseEventTool.triggerComponentEvent(
              component,
              MainEditorCameraTool.triggerChangeArcballMinDistance(value),
            );

            BaseEventTool.triggerComponentEvent(
              component,
              MainEditorCameraTool.triggerBlurArcballMinDistance(value),
            );

            StateEngineService.unsafeGetState()
            |> _getArcballCameraMinDistance(currentGameObjectArcballCamera)
            |> expect == value;
          });
        });
      });
    });
  });