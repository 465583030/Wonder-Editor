open Wonder_jest;

open Expect;

open Expect.Operators;

open Sinon;

let _ =
  describe("redo_undo: sceneTree", () => {
    let sandbox = getSandboxDefaultVal();
    beforeEach(() => sandbox := createSandbox());
    afterEach(() => restoreSandbox(refJsObjToSandbox(sandbox^)));

    let _simulateTwiceDragEvent = () => {
      let firstCameraDomIndex =
        SceneTreeNodeDomTool.OperateDefaultScene.getFirstCameraDomIndex();
      let firstCubeDomIndex =
        SceneTreeNodeDomTool.OperateDefaultScene.getFirstCubeDomIndex();
      let secondCubeDomIndex =
        SceneTreeNodeDomTool.OperateDefaultScene.getSecondCubeDomIndex();

      let component =
        BuildComponentTool.buildSceneTree(
          TestTool.buildAppStateSceneGraphFromEngine(),
        );
      BaseEventTool.triggerComponentEvent(
        component,
        SceneTreeEventTool.triggerDragStart(secondCubeDomIndex),
      );
      BaseEventTool.triggerComponentEvent(
        component,
        SceneTreeEventTool.triggerDragEnter(firstCameraDomIndex),
      );
      BaseEventTool.triggerComponentEvent(
        component,
        SceneTreeEventTool.triggerDragDrop(firstCameraDomIndex),
      );

      let component2 =
        BuildComponentTool.buildSceneTree(
          TestTool.buildAppStateSceneGraphFromEngine(),
        );
      BaseEventTool.triggerComponentEvent(
        component2,
        SceneTreeEventTool.triggerDragStart(firstCubeDomIndex),
      );
      BaseEventTool.triggerComponentEvent(
        component2,
        SceneTreeEventTool.triggerDragEnter(firstCameraDomIndex),
      );
      BaseEventTool.triggerComponentEvent(
        component2,
        SceneTreeEventTool.triggerDragDrop(firstCameraDomIndex),
      );
    };
    let _beforeEach = () => {
      MainEditorSceneTool.initState(~sandbox, ());
      MainEditorSceneTool.createDefaultScene(
        sandbox,
        MainEditorSceneTool.setFirstBoxToBeCurrentSceneTreeNode,
      );
    };

    RedoUndoTool.testRedoUndoTwoStep(
      sandbox,
      "get scene tree from engine",
      (_simulateTwiceDragEvent, _beforeEach, () => ()),
      BuildComponentForCurryTool.buildSceneTree,
    );

    describe("fix bug", () => {
      let execChangeMaterialColorWork = (currentGameObjectMaterial, newColor) =>
        PickColorEventTool.triggerChangeLightMaterialColor(
          currentGameObjectMaterial,
          newColor,
        );

      let execChangeTransformWork = () => {
        let currentGameObjectTransform =
          GameObjectTool.getCurrentSceneTreeNodeTransform();
        let transformComponent =
          BuildComponentTool.buildMainEditorTransformComponent(
            TestTool.buildEmptyAppState(),
            currentGameObjectTransform,
          );
        BaseEventTool.triggerComponentEvent(
          transformComponent,
          TransformEventTool.triggerChangePositionX("11.25"),
        );
        BaseEventTool.triggerComponentEvent(
          transformComponent,
          TransformEventTool.triggerBlurPositionX("11.25"),
        );
      };

      beforeEach(() => {
        MainEditorSceneTool.initState(~sandbox, ());
        MainEditorSceneTool.createDefaultScene(
          sandbox,
          MainEditorSceneTool.setFirstBoxToBeCurrentSceneTreeNode,
        );
      });
      test(
        "the workflow:
        click treeNote set currentSceneTreeNode;
        change material color;
        change transform x value;
        click undo, engineState is error",
        () => {
          let currentGameObjectMaterial =
            GameObjectTool.getCurrentGameObjectLightMaterial();
          let newColor = {
            "hex": "#7df1e8",
            "rgb": {
              "r": 125,
              "g": 241,
              "b": 232,
            },
          };

          execChangeMaterialColorWork(currentGameObjectMaterial, newColor);
          execChangeTransformWork();

          StateHistoryToolEditor.undo();

          LightMaterialEngineService.getLightMaterialDiffuseColor(
            currentGameObjectMaterial,
          )
          |> StateLogicService.getEngineStateToGetData
          |> Color.getHexString
          |> expect == newColor##hex;
        },
      );
    });
  });