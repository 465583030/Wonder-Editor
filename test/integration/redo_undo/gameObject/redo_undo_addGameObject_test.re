open Wonder_jest;

open Expect;

open Expect.Operators;

open Sinon;

let _ =
  describe("redo_undo: add gameObject", () => {
    let sandbox = getSandboxDefaultVal();
    beforeEach(() => sandbox := createSandbox());
    afterEach(() => restoreSandbox(refJsObjToSandbox(sandbox^)));
    let _simulateAddGameObjectTwice = () => {
      HeaderTool.triggerAddBox();
      HeaderTool.triggerAddEmptyGameObject();
    };
    let _beforeEach = () => {
      MainEditorSceneTool.initState(~sandbox, ());
      MainEditorSceneTool.createDefaultScene(sandbox, () => ());

      SceneTreeNodeDomTool.OperateDefaultScene.getFirstCubeDomIndex()
      |> SceneTreeTool.clearCurrentGameObjectAndSetTreeSpecificGameObject;
    };

    RedoUndoTool.testRedoUndoTwoStep(
      sandbox,
      "prepare first step: set currentSceneTreeNode",
      (_simulateAddGameObjectTwice, _beforeEach, () => ()),
      BuildComponentForCurryTool.buildSceneTree,
    );
  });