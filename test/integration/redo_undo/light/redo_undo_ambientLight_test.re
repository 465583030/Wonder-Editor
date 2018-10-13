open Wonder_jest;

open Expect;

open Expect.Operators;

open Sinon;

let _ =
  describe("redo_undo: ambientLight", () => {
    let sandbox = getSandboxDefaultVal();

    let _changeColorAndPushUndoStack = value => {
      let sourceColor = ControllerTool.getColor();

      ControllerTool.changeColor(value);

      ControllerTool.closeColorPicker(~color=sourceColor, ());
    };

    let _simulateTwiceChangeAmbientLight = () => {
      BuildCanvasTool.buildFakeCanvas(sandbox);

      let color1 = {
        "hex": "#7df1e8",
        "rgb": {
          "r": 125,
          "g": 241,
          "b": 232,
        },
      };
      let color2 = {
        "hex": "#1918e8",
        "rgb": {
          "r": 25,
          "g": 24,
          "b": 232,
        },
      };

      _changeColorAndPushUndoStack(color1);
      _changeColorAndPushUndoStack(color2);
    };

    let _beforeEach = () =>
      MainEditorSceneTool.createDefaultScene(sandbox, () => ());

    beforeEach(() => {
      sandbox := createSandbox();

      MainEditorSceneTool.initState(~sandbox, ());

      EventListenerTool.buildFakeDom()
      |> EventListenerTool.stubGetElementByIdReturnFakeDom;
    });
    afterEach(() => restoreSandbox(refJsObjToSandbox(sandbox^)));

    RedoUndoTool.testRedoUndoTwoStep(
      sandbox,
      "prepare first step: set currentSceneTreeNode",
      (_simulateTwiceChangeAmbientLight, _beforeEach, () => ()),
      BuildComponentForCurryTool.buildHeader,
    );
  });