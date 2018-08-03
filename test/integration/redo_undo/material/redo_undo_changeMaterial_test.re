open Wonder_jest;

open Expect;

open Expect.Operators;

open Sinon;

let _ =
  describe("redo_undo: change material", () => {
    let sandbox = getSandboxDefaultVal();

    let _getFromArray = (array, index) => ArrayService.getNth(index, array);

    beforeEach(() => {
      sandbox := createSandbox();

      MainEditorSceneTool.initState(~sandbox, ());

      EventListenerTool.buildFakeDom()
      |> EventListenerTool.stubGetElementByIdReturnFakeDom;
    });
    afterEach(() => restoreSandbox(refJsObjToSandbox(sandbox^)));
    let _simulateChangeMaterial = () =>
      MainEditorMaterialTool.setMaterialTypeToBeBaiscMaterial();

    let _beforeEach = () => {
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
    };

    RedoUndoTool.testRedoUndoOneStep(
      sandbox,
      "prepare first step: set currentSceneTreeNode",
      (_simulateChangeMaterial, _beforeEach),
      BuildComponentForRedoUndoTool.buildMaterial,
    );
  });