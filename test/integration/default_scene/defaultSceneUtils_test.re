open Wonder_jest;

open Expect;

open Expect.Operators;

open Sinon;

let _ =
  describe(
    "defaultScene: compute diff value ",
    () => {
      let sandbox = getSandboxDefaultVal();
      beforeEach(
        () => {
          sandbox := createSandbox();
          TestTool.closeContractCheck();
          MainEditorSceneTool.initStateAndGl(~sandbox, ());
          MainEditorSceneTool.createDefaultScene(
            sandbox,
            MainEditorSceneTool.setFirstBoxTobeCurrentSceneTreeNode
          )
        }
      );
      afterEach(
        () => {
          TestTool.openContractCheck();
          restoreSandbox(refJsObjToSandbox(sandbox^))
        }
      );
      describe(
        "test change currentSceneTreeNode color",
        () =>
          test(
            "change currentSceneTreeNode material color shouldn't change editCamera box material color",
            () => {
              let editEngineState = StateLogicService.getEditEngineState();
              let editCamera =
                MainEditorSceneTool.unsafeGetScene()
                |> GameObjectTool.getEditEngineChildren
                |> Js.Array.filter(
                     (gameObject) => CameraEngineService.isCamera(gameObject, editEngineState)
                   )
                |> ArrayService.getNth(1)
                |> GameObjectTool.getEditEngineChildren
                |> ArrayService.getFirst;
              let material =
                editEngineState
                |> GameObjectComponentEngineService.getBasicMaterialComponent(editCamera);
              let color = editEngineState |> BasicMaterialEngineService.getColor(material);
              let currentGameObjectMaterial = GameObjectTool.getCurrentSceneTreeNodeMaterial();
              let value = "#c0c0c0";
              let component = BuildComponentTool.buildMaterialComponent(currentGameObjectMaterial);
              MaterialEventTool.triggerChangeAndBlurMaterialEvent(component, value);
              editEngineState |> BasicMaterialEngineService.getColor(material) |> expect == color
            }
          )
      )
    }
  );