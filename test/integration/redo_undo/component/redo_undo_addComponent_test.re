open Wonder_jest;

open Expect;

open Expect.Operators;

open Sinon;

let _ =
  describe("redo_undo: add component", () => {
    let sandbox = getSandboxDefaultVal();
    beforeEach(() => sandbox := createSandbox());
    afterEach(() => restoreSandbox(refJsObjToSandbox(sandbox^)));
    let _simulateAddSourceInstanceComponent = () => {
      let component =
        BuildComponentTool.buildInspectorComponent(
          TestTool.buildEmptyAppState(),
          InspectorTool.buildFakeAllShowComponentConfig(),
        );
      BaseEventTool.triggerComponentEvent(
        component,
        OperateComponentEventTool.triggerClickAddComponentEvent,
      );
      BaseEventTool.triggerComponentEvent(
        component,
        OperateComponentEventTool.triggerClickAddSourceInstanceEvent,
      );
    };
    let _beforeEach = () => {
      MainEditorSceneTool.initStateAndGl(~sandbox, ());
      MainEditorSceneTool.createDefaultScene(sandbox, () => ());

      CurrentSelectSourceEditorService.setCurrentSelectSource(
        EditorType.SceneTree,
      )
      |> StateLogicService.getAndSetEditorState;

      SceneTreeNodeDomTool.OperateTwoLayer.getFirstCubeDomIndex()
      |> SceneTreeTool.clearCurrentGameObjectAndSetTreeSpecificGameObject;
    };

    RedoUndoTool.testRedoUndoOneStep(
      sandbox,
      "prepare first step: set currentSceneTreeNode",
      (_simulateAddSourceInstanceComponent, _beforeEach),
      BuildComponentForRedoUndoTool.buildInspectorComponent,
    );
  });