open Wonder_jest;

open Expect;

open Expect.Operators;

open Sinon;

let _ =
  describe(
    "engine: mainEditor inspector",
    () => {
      let sandbox = getSandboxDefaultVal();
      beforeEach(
        () => {
          sandbox := createSandbox();
          TestToolEngine.prepare(sandbox)
        }
      );
      afterEach(() => restoreSandbox(refJsObjToSandbox(sandbox^)));
      describe(
        "test current gameObject",
        () => {
          test(
            "if not set currentGameObject, there hasn't currentGameObject",
            () => {
              TestTool.initMainEditor(sandbox);
              MainEditorSceneTool.hasCurrentGameObject() |> expect == false
            }
          );
          describe(
            "else can get currentGameObject",
            () => {
              let gameObject = 2;
              beforeEach(
                () => {
                  TestTool.initMainEditor(sandbox);
                  MainEditorSceneTool.setCurrentGameObject(gameObject)
                }
              );
              test(
                "the hasCurrentGameObject should == true",
                () => MainEditorSceneTool.hasCurrentGameObject() |> expect == true
              );
              test(
                "the currentGameObject should == the set one",
                () =>
                  MainEditorSceneTool.unsafeGetCurrentGameObject()
                  |> expect == gameObject
              )
            }
          )
          /* todo test gameObject components */
        }
      )
    }
  );