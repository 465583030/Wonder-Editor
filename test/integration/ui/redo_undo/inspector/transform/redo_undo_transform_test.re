open Wonder_jest;

open Expect;

open Expect.Operators;

open Sinon;

let _ =
  describe(
    "redo_undo: transform",
    () => {
      let sandbox = getSandboxDefaultVal();
      let _simulateTwiceChangeEvent = (currentGameObjectTransform) => {
        let component =
          BuildComponentTool.buildMainEditorTransformComponent(
            TestToolUI.buildEmptyAppState(),
            currentGameObjectTransform
          );
        EventToolUI.triggerComponentEvent(
          component,
          TransformEventTool.triggerChangeXEvent("11.25")
        );
        EventToolUI.triggerComponentEvent(
          component,
          TransformEventTool.triggerBlurXEvent("11.25")
        );
        EventToolUI.triggerComponentEvent(component, TransformEventTool.triggerChangeYEvent("15"));
        EventToolUI.triggerComponentEvent(component, TransformEventTool.triggerBlurYEvent("15"))
      };
      beforeEach(
        () => {
          sandbox := createSandbox();
          TestToolEngine.prepare(sandbox);
          TestToolUI.initMainEditor(sandbox);
          StateHistoryToolEditor.clearAllState()
        }
      );
      afterEach(() => restoreSandbox(refJsObjToSandbox(sandbox^)));
      describe(
        "test simulate set currentGameObject",
        () => {
          let _setSpecificGameObject = (clickTreeNodeIndex) => {
            let component =
              BuildComponentTool.buildSceneTree(
                SceneTreeToolUI.buildAppStateSceneGraphFromEngine()
              );
            EventToolUI.triggerComponentEvent(
              component,
              SceneTreeEventTool.triggerClickEvent(clickTreeNodeIndex)
            );
            MainEditorSceneToolEditor.unsafeGetCurrentGameObject() |> ignore
          };
          beforeEach(
            () => {
              TestToolEditor.closeContractCheck();
              MainEditorSceneToolEditor.prepareDefaultScene(
                MainEditorSceneToolEditor.setFirstBoxTobeCurrentGameObject
              );
              _setSpecificGameObject(1)
            }
          );
          afterEach(() => TestToolEditor.openContractCheck());
          describe(
            "test snapshot",
            () => {
              describe(
                "test undo operate",
                () => {
                  test(
                    "test not undo",
                    () => {
                      let currentGameObjectTransform =
                        MainEditorSceneToolEditor.getCurrentGameObjectTransform();
                      _simulateTwiceChangeEvent(currentGameObjectTransform);
                      BuildComponentTool.buildMainEditorTransformComponent(
                        TestToolUI.buildEmptyAppState(),
                        currentGameObjectTransform
                      )
                      |> ReactTestTool.createSnapshotAndMatch
                    }
                  );
                  describe(
                    "test undo one step",
                    () =>
                      test(
                        "step from second to first",
                        () => {
                          let currentGameObjectTransform =
                            MainEditorSceneToolEditor.getCurrentGameObjectTransform();
                          _simulateTwiceChangeEvent(currentGameObjectTransform);
                          StateHistoryToolEditor.undo();
                          BuildComponentTool.buildMainEditorTransformComponent(
                            TestToolUI.buildEmptyAppState(),
                            currentGameObjectTransform
                          )
                          |> ReactTestTool.createSnapshotAndMatch
                        }
                      )
                  );
                  describe(
                    "test undo two step",
                    () =>
                      test(
                        "step from second to zero",
                        () => {
                          let currentGameObjectTransform =
                            MainEditorSceneToolEditor.getCurrentGameObjectTransform();
                          _simulateTwiceChangeEvent(currentGameObjectTransform);
                          StateHistoryToolEditor.undo();
                          StateHistoryToolEditor.undo();
                          BuildComponentTool.buildMainEditorTransformComponent(
                            TestToolUI.buildEmptyAppState(),
                            currentGameObjectTransform
                          )
                          |> ReactTestTool.createSnapshotAndMatch
                        }
                      )
                  )
                }
              );
              describe(
                "test redo operate",
                () => {
                  describe(
                    "test redo one step",
                    () => {
                      test(
                        "if not exec undo, redo one step, not change",
                        () => {
                          let currentGameObjectTransform =
                            MainEditorSceneToolEditor.getCurrentGameObjectTransform();
                          _simulateTwiceChangeEvent(currentGameObjectTransform);
                          StateHistoryToolEditor.redo();
                          BuildComponentTool.buildMainEditorTransformComponent(
                            TestToolUI.buildEmptyAppState(),
                            currentGameObjectTransform
                          )
                          |> ReactTestTool.createSnapshotAndMatch
                        }
                      );
                      test(
                        "undo step from second to zero, redo step from zero to first",
                        () => {
                          let currentGameObjectTransform =
                            MainEditorSceneToolEditor.getCurrentGameObjectTransform();
                          _simulateTwiceChangeEvent(currentGameObjectTransform);
                          StateHistoryToolEditor.undo();
                          StateHistoryToolEditor.undo();
                          StateHistoryToolEditor.redo();
                          BuildComponentTool.buildMainEditorTransformComponent(
                            TestToolUI.buildEmptyAppState(),
                            currentGameObjectTransform
                          )
                          |> ReactTestTool.createSnapshotAndMatch
                        }
                      )
                    }
                  );
                  describe(
                    "test redo two step",
                    () =>
                      test(
                        "undo step from second to zero, redo step from zero to second",
                        () => {
                          let currentGameObjectTransform =
                            MainEditorSceneToolEditor.getCurrentGameObjectTransform();
                          _simulateTwiceChangeEvent(currentGameObjectTransform);
                          StateHistoryToolEditor.undo();
                          StateHistoryToolEditor.undo();
                          StateHistoryToolEditor.redo();
                          StateHistoryToolEditor.redo();
                          BuildComponentTool.buildMainEditorTransformComponent(
                            TestToolUI.buildEmptyAppState(),
                            currentGameObjectTransform
                          )
                          |> ReactTestTool.createSnapshotAndMatch
                        }
                      )
                  );
                  describe(
                    "test redo three step",
                    () =>
                      test(
                        "test if current step is last step, execute redo, not change",
                        () => {
                          let currentGameObjectTransform =
                            MainEditorSceneToolEditor.getCurrentGameObjectTransform();
                          _simulateTwiceChangeEvent(currentGameObjectTransform);
                          StateHistoryToolEditor.undo();
                          StateHistoryToolEditor.undo();
                          StateHistoryToolEditor.redo();
                          StateHistoryToolEditor.redo();
                          StateHistoryToolEditor.redo();
                          BuildComponentTool.buildMainEditorTransformComponent(
                            TestToolUI.buildEmptyAppState(),
                            currentGameObjectTransform
                          )
                          |> ReactTestTool.createSnapshotAndMatch
                        }
                      )
                  )
                }
              )
            }
          )
        }
      )
    }
  );