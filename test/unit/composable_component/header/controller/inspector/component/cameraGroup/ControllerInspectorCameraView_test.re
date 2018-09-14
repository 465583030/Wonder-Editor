open Wonder_jest;

open Expect;

open Expect.Operators;

open Sinon;

let _ =
  describe("controller cameraView", () => {
    let sandbox = getSandboxDefaultVal();

    beforeEach(() => sandbox := createSandbox());
    afterEach(() => restoreSandbox(refJsObjToSandbox(sandbox^)));

    describe("test camera bind arcballCameraController event", () =>
      describe(
        "test has two cameras with arcballCameraController component", () => {
        beforeEach(() => {
          MainEditorSceneTool.initState(~sandbox, ());

          ControllerTool.stubRequestAnimationFrame(
            createEmptyStubWithJsObjSandbox(sandbox),
          );
          ControllerTool.stubCancelAnimationFrame(
            createEmptyStubWithJsObjSandbox(sandbox),
          );
        });
        test(
          "test click run, the current camera arcballCameraController should bind event, the other camera shouldn't bind event",
          () => {
            let (camera1, camera2) =
              AddableComponentTool.buildTwoAddedArcballCameraControllerCamera(
                sandbox,
              );
            SceneTreeNodeDomTool.OperateTwoCamera.getSecondCameraDomIndex()
            |> SceneTreeTool.clearCurrentGameObjectAndSetTreeSpecificGameObject;
            MainEditorCameraViewTool.triggerClickSetCurrentCameraEvent();

            ControllerTool.run();

            let engineState = StateEngineService.unsafeGetState();
            (
              engineState
              |> GameObjectComponentEngineService.getArcballCameraControllerComponent(
                   camera1,
                 )
              |. ArcballCameraEngineService.isBindArcballCameraControllerEventForGameView(
                   engineState,
                 ),
              engineState
              |> GameObjectComponentEngineService.getArcballCameraControllerComponent(
                   camera2,
                 )
              |. ArcballCameraEngineService.isBindArcballCameraControllerEventForGameView(
                   engineState,
                 ),
            )
            |> expect == (false, true);
          },
        );
        test(
          "test click stop, the two camera arcballCameraController shouldn't bind event",
          () => {
          let (camera1, camera2) =
            AddableComponentTool.buildTwoAddedArcballCameraControllerCamera(
              sandbox,
            );

          ControllerTool.run();
          ControllerTool.stop();

          let engineState = StateEngineService.unsafeGetState();

          (
            engineState
            |> GameObjectComponentEngineService.getArcballCameraControllerComponent(
                 camera1,
               )
            |. ArcballCameraEngineService.isBindArcballCameraControllerEventForGameView(
                 engineState,
               ),
            engineState
            |> GameObjectComponentEngineService.getArcballCameraControllerComponent(
                 camera2,
               )
            |. ArcballCameraEngineService.isBindArcballCameraControllerEventForGameView(
                 engineState,
               ),
          )
          |> expect == (false, false);
        });

        describe("test click run and change current camera", () => {
          let _prepareAndExec = () => {
            let (camera1, camera2) =
              AddableComponentTool.buildTwoAddedArcballCameraControllerCamera(
                sandbox,
              );
            GameObjectComponentEngineService.getArcballCameraControllerComponent(
              camera2,
              StateEngineService.unsafeGetState(),
            )
            |> ArcballCameraEngineService.bindArcballCameraControllerEventForGameView(
                 _,
                 StateEngineService.unsafeGetState(),
               )
            |> StateEngineService.setState
            |> ignore;

            ControllerTool.run();
            SceneTreeNodeDomTool.OperateTwoCamera.getFirstCameraDomIndex()
            |> SceneTreeTool.clearCurrentGameObjectAndSetTreeSpecificGameObject;

            MainEditorCameraViewTool.triggerClickSetCurrentCameraEvent();

            (camera1, camera2);
          };

          test(
            "the target camera should bind event, and the source camera shouldn't bind event",
            () => {
              let (camera1, camera2) = _prepareAndExec();

              let engineState = StateEngineService.unsafeGetState();
              (
                engineState
                |> GameObjectComponentEngineService.getArcballCameraControllerComponent(
                     camera1,
                   )
                |. ArcballCameraEngineService.isBindArcballCameraControllerEventForGameView(
                     engineState,
                   ),
                engineState
                |> GameObjectComponentEngineService.getArcballCameraControllerComponent(
                     camera2,
                   )
                |. ArcballCameraEngineService.isBindArcballCameraControllerEventForGameView(
                     engineState,
                   ),
              )
              |> expect == (true, false);
            },
          );
          test("active source camera->basicCameraView", () => {
            let (camera1, camera2) = _prepareAndExec();

            let editorState = StateEditorService.getState();
            let engineState = StateEngineService.unsafeGetState();
            GameViewEditorService.getActivedBasicCameraView(editorState)
            |>
            expect == Some(
                        engineState
                        |> GameObjectComponentEngineService.getArcballCameraControllerComponent(
                             camera1,
                           ),
                      );
          });
        });
      })
    );
  });