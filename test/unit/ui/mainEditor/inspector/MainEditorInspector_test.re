open Wonder_jest;

open Expect;

open Expect.Operators;

open Sinon;

/* TODO add engine test:
add gameObject
add component 
*/

/* TODO redo,undo:
add gameObject
add component  */

let _ =
  describe(
    "MainEditorInspector ui component",
    () => {
      let sandbox = getSandboxDefaultVal();
      let _buildInspectorComponent = (allShowComponentConfig) =>
        ReactTestRenderer.create(
          <MainEditorInspector
            store=(TestToolUI.buildEmptyAppState())
            dispatch=(TestToolUI.getDispatch())
            allShowComponentConfig
          />
        );
      beforeEach(
        () => {
          sandbox := createSandbox();
          TestToolEngine.prepare(sandbox);
          TestToolUI.initMainEditor(sandbox)
        }
      );
      afterEach(() => restoreSandbox(refJsObjToSandbox(sandbox^)));
      describe(
        "test snapshot",
        () => {
          describe(
            "test show component",
            () => {
              test(
                "if hasn't currentGameObject, show nothing",
                () =>
                  _buildInspectorComponent(InspectorToolUI.buildFakeAllShowComponentConfig())
                  |> ReactTestTool.createSnapshotAndMatch
              );
              describe(
                "else",
                () => {
                  test(
                    "if currentGameObject is camera, should show transform and cameraController",
                    () => {
                      /* TODO not init again(all) */
                      TestToolUI.initMainEditor(sandbox);

                      MainEditorSceneToolEditor.prepareDefaultScene(
                        MainEditorSceneToolEditor.setCameraTobeCurrentGameObject
                      );
                      _buildInspectorComponent(InspectorToolUI.buildFakeAllShowComponentConfig())
                      |> ReactTestTool.createSnapshotAndMatch
                    }
                  );
                  test(
                    "else if currentGameObject is box, should show transform and material",
                    () => {
                      TestToolUI.initMainEditor(sandbox);
                      MainEditorSceneToolEditor.prepareDefaultScene(
                        MainEditorSceneToolEditor.setFirstBoxTobeCurrentGameObject
                      );
                      _buildInspectorComponent(InspectorToolUI.buildFakeAllShowComponentConfig())
                      |> ReactTestTool.createSnapshotAndMatch
                    }
                  )
                }
              )
            }
          );
          describe(
            "test add component workflow",
            () => {
              let _triggerClickAddComponentEvent = (domChildren) => {
                let article = WonderCommonlib.ArraySystem.unsafeGet(domChildren, 2);
                let button = WonderCommonlib.ArraySystem.unsafeGet(article##children, 0);
                EventToolUI.triggerClickEvent(button)
              };
              let _triggerClickAddSourceInstanceEvent = (domChildren) => {
                let article = WonderCommonlib.ArraySystem.unsafeGet(domChildren, 2);
                let sourceInstanceDiv =
                  WonderCommonlib.ArraySystem.unsafeGet(article##children, 1);
                EventToolUI.triggerClickEvent(sourceInstanceDiv)
              };
              beforeEach(
                () => {
                      /* TODO not init again(all) */
                  TestToolUI.initMainEditor(sandbox);

                  MainEditorSceneToolEditor.prepareDefaultScene(
                    MainEditorSceneToolEditor.setFirstBoxTobeCurrentGameObject
                  )
                }
              );
              test(
                "click the add component button, show addableComponent list",
                () => {
                  let component =
                    _buildInspectorComponent(InspectorToolUI.buildFakeAllShowComponentConfig());
                  EventToolUI.triggerComponentEvent(component, _triggerClickAddComponentEvent);
                  component |> ReactTestTool.createSnapshotAndMatch
                }
              );
              test(
                "click sourceInstance component, add to inspector",
                () => {
                  let component =
                    _buildInspectorComponent(InspectorToolUI.buildFakeAllShowComponentConfig());
                  EventToolUI.triggerComponentEvent(component, _triggerClickAddComponentEvent);
                  EventToolUI.triggerComponentEvent(
                    component,
                    _triggerClickAddSourceInstanceEvent
                  );
                  let component2 =
                    _buildInspectorComponent(InspectorToolUI.buildFakeAllShowComponentConfig());
                  component2 |> ReactTestTool.createSnapshotAndMatch
                }
              )
            }
          )
        }
      );
      describe(
        "deal with specific case",
        () => {
          beforeEach(
            () => {
              TestToolUI.initMainEditor(sandbox);
              MainEditorSceneToolEditor.prepareDefaultScene(
                MainEditorSceneToolEditor.setCameraTobeCurrentGameObject
              )
            }
          );
          test(
            "test if specific component not exist, should throw error when parse config from json data",
            () =>
              expect(
                () =>
                  _buildInspectorComponent(InspectorToolUI.buildFakeErrorAllShowComponentConfig())
              )
              |> toThrowMessage("specific component:transformError is error")
          );
          test(
            "test if specific component not exist, should throw error when build component",
            () =>
              expect(
                () =>
                  InspectorToolUI.buildComponentUIComponent(
                    ("SceneTree", 0),
                    (TestToolUI.buildEmptyAppState(), TestToolUI.getDispatch())
                  )
              )
              |> toThrowMessage("the component: SceneTree not exist")
          )
        }
      )
    }
  );