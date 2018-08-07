open Wonder_jest;

open Expect;

open Expect.Operators;

open Sinon;

let _ =
  describe("redo_undo: add renderGroup component", () => {
    let sandbox = getSandboxDefaultVal();
    beforeEach(() => sandbox := createSandbox());
    afterEach(() => restoreSandbox(refJsObjToSandbox(sandbox^)));
    let _simulateAddSpecificComponent = () => {
      let cameraComponentCount = ComponentDomTool.getCameraComponentCount();
      let renderingCategoryDomIndex =
        ComponentDomTool.getRenderingCategoryDomIndex();
      let renderGroupTypeDomIndex =
        ComponentDomTool.getRenderGroupTypeDomIndex();

      OperateComponentEventTool.addComponentIntoCurrentGameObject(
        cameraComponentCount,
        renderingCategoryDomIndex,
        renderGroupTypeDomIndex,
      );
    };
    let _beforeEach = () => {
      MainEditorSceneTool.initState(~sandbox, ());
      MainEditorSceneTool.createDefaultScene(
        sandbox,
        MainEditorSceneTool.setFirstCameraTobeCurrentSceneTreeNode,
      );

      CurrentSelectSourceEditorService.setCurrentSelectSource(
        EditorType.SceneTree,
      )
      |> StateLogicService.getAndSetEditorState;
    };
    let _afterEach = () => ();

    RedoUndoTool.testRedoUndoOneStep(
      sandbox,
      "prepare first step: set currentSceneTreeNode",
      (_simulateAddSpecificComponent, _beforeEach, _afterEach),
      BuildComponentForRedoUndoTool.buildInspectorComponent,
    );
  });