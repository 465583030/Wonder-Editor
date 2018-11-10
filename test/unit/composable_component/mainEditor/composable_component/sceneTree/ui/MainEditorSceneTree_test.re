open Wonder_jest;

open Expect;

open Expect.Operators;

open Sinon;

open MainEditorSceneTree;

open Js.Promise;

let _ =
  describe("MainEditorSceneTree", () => {
    let sandbox = getSandboxDefaultVal();

    let _getFromArray = (array, index) =>
      ArrayService.unsafeGetNth(index, array);

    beforeEach(() => {
      sandbox := createSandbox();

      MainEditorSceneTool.initState(~sandbox, ());

      EventListenerTool.buildFakeDom()
      |> EventListenerTool.stubGetElementByIdReturnFakeDom;
    });
    afterEach(() => restoreSandbox(refJsObjToSandbox(sandbox^)));

    describe("get sceneTree from engine", () => {
      describe("test should update", () => {
        test("if reatinedProps updateTypeArr include All, should update", () =>
          shouldUpdate(
            OldNewSelfTool.buildNewSelf({
              updateTypeArr: [|UpdateStore.All|] |> Obj.magic,
            }),
          )
          |> expect == true
        );
        test(
          "else if reatinedProps updateTypeArr include SceneTree, should update",
          () =>
          shouldUpdate(
            OldNewSelfTool.buildNewSelf({
              updateTypeArr: [|UpdateStore.SceneTree|] |> Obj.magic,
            }),
          )
          |> expect == true
        );
        test("else, should not update", () =>
          shouldUpdate(
            OldNewSelfTool.buildNewSelf({
              updateTypeArr:
                [|UpdateStore.Project, UpdateStore.Inspector|]
                |> Obj.magic,
            }),
          )
          |> expect == false
        );
      });

      describe("test simple scene graph data which haven't children case", () => {
        beforeEach(() =>
          MainEditorSceneTool.createDefaultScene(
            sandbox,
            MainEditorSceneTool.setFirstBoxToBeCurrentSceneTreeNode,
          )
        );
        afterEach(() => GameObjectTool.clearCurrentSceneTreeNode());
        test("no drag", () =>
          BuildComponentTool.buildSceneTree(
            TestTool.buildAppStateSceneGraphFromEngine(),
          )
          |> ReactTestTool.createSnapshotAndMatch
        );
        test("drag treeNode into target treeNode", () => {
          MainEditorSceneTreeTool.Drag.dragGameObjectIntoGameObject(
            ~sourceGameObject=
              MainEditorSceneTool.getFirstBox(
                StateEngineService.unsafeGetState(),
              ),
            ~targetGameObject=
              MainEditorSceneTool.getSecondBox(
                StateEngineService.unsafeGetState(),
              ),
            (),
          );

          BuildComponentTool.buildSceneTree(
            TestTool.buildAppStateSceneGraphFromEngine(),
          )
          |> ReactTestTool.createSnapshotAndMatch;
        });
      });

      describe("set current gameObject", () => {
        beforeEach(() =>
          MainEditorSceneTool.createDefaultScene(sandbox, () => ())
        );
        test("click treeNode to set it to be currentSceneTreeNode", () => {
          MainEditorSceneTreeTool.Select.selectGameObject(
            ~gameObject=
              MainEditorSceneTool.getFirstBox(
                StateEngineService.unsafeGetState(),
              ),
            (),
          );

          GameObjectTool.unsafeGetCurrentSceneTreeNode()
          |>
          expect == MainEditorSceneTool.getFirstBox(
                      StateEngineService.unsafeGetState(),
                    );
        });
      });

      describe("deal with the specific case", () => {
        test("if drag treeNode into itself, keep not change", () => {
          MainEditorSceneTool.createDefaultScene(
            sandbox,
            MainEditorSceneTool.setFirstBoxToBeCurrentSceneTreeNode,
          );

          MainEditorSceneTreeTool.Drag.isTriggerDragCurrentSceneTreeNode(
            GameObjectTool.unsafeGetCurrentSceneTreeNode(),
          )
          |> expect == false;
        });
        test(
          "if drag treeNode into it's first layer chidlren, keep not change",
          () => {
          let (scene, (box1, box4), box2, box3) =
            SceneTreeTool.buildThreeLayerSceneGraphToEngine(sandbox);

          box1 |> GameObjectTool.setCurrentSceneTreeNode;

          MainEditorSceneTreeTool.Drag.isTriggerDragCurrentSceneTreeNode(box4)
          |> expect == false;
        });
        describe("if drag treeNode into it's second layer chidlren", () =>
          test(
            "if drag treeNode into it's second layer chidlren, keep not change",
            () => {
            let (scene, (box1, box3, box4), box2) =
              SceneTreeTool.buildFourLayerSceneGraphToEngine(sandbox);

            box1 |> GameObjectTool.setCurrentSceneTreeNode;

            MainEditorSceneTreeTool.Drag.isTriggerDragCurrentSceneTreeNode(
              box4,
            )
            |> expect == false;
          })
        );
      });
    });
  });