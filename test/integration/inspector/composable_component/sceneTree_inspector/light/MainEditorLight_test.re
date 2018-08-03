open Wonder_jest;

open Expect;

open Expect.Operators;

open Sinon;

let _ =
  describe("MainEditorLight component", () => {
    let sandbox = getSandboxDefaultVal();
    beforeEach(() => {
      sandbox := createSandbox();
      MainEditorSceneTool.initStateWithJob(
        ~sandbox,
        ~noWorkerJobRecord=
          NoWorkerJobConfigToolEngine.buildNoWorkerJobConfig(
            ~loopPipelines=
              {|
                   [
                       {
                           "name": "default",
                           "jobs": [
                               {
                                   "name": "dispose"
                               }
                           ]
                       }
                   ]
               |},
            (),
          ),
        (),
      );

      EventListenerTool.buildFakeDom()
      |> EventListenerTool.stubGetElementByIdReturnFakeDom;
    });
    afterEach(() => restoreSandbox(refJsObjToSandbox(sandbox^)));

    describe("test set currentSceneTreeNode", () => {
      beforeEach(() =>
        MainEditorSceneTool.createDefaultScene(
          sandbox,
          MainEditorSceneTool.setDirectionLightGameObjectTobeCurrentSceneTreeNode,
        )
      );
      describe("test change light type", () => {
        test(
          "test the original type is direction light, should show direction light component ",
          () =>
          BuildComponentTool.buildLight()
          |> ReactTestTool.createSnapshotAndMatch
        );
        test(
          "test change type to be point light, should show point light component",
          () => {
          MainEditorLightTool.setLightTypeToBePointLight();

          BuildComponentTool.buildLight()
          |> ReactTestTool.createSnapshotAndMatch;
        });

        describe(
          "should re-init all light material components in the scene", () =>
          describe("test change direction light to be point light", () =>
            test(
              "test
               glsl->DIRECTION_LIGHTS_COUNT should - 1;
               glsl->POINT_LIGHTS_COUNT should + 1;",
              () => {
                let (editGl, runGl) =
                  FakeGlToolEngine.getEditEngineStateGlAndRunEngineStateGl();
                let editGlShaderSource = editGl##shaderSource;
                let runGlShaderSource = runGl##shaderSource;

                MainEditorLightTool.setLightTypeToBePointLight();

                (
                  GLSLToolEngine.contain(
                    GLSLToolEngine.getVsSource(editGlShaderSource),
                    {|#define DIRECTION_LIGHTS_COUNT 0|},
                  ),
                  GLSLToolEngine.contain(
                    GLSLToolEngine.getFsSource(runGlShaderSource),
                    {|#define DIRECTION_LIGHTS_COUNT 0|},
                  ),
                  GLSLToolEngine.contain(
                    GLSLToolEngine.getVsSource(editGlShaderSource),
                    {|#define POINT_LIGHTS_COUNT 1|},
                  ),
                  GLSLToolEngine.contain(
                    GLSLToolEngine.getFsSource(runGlShaderSource),
                    {|#define POINT_LIGHTS_COUNT 1|},
                  ),
                )
                |> expect == (true, true, true, true);
              },
            )
          )
        );
      });
    });
  });