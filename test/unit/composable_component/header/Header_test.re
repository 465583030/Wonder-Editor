open Wonder_jest;

open Expect;

open Expect.Operators;

open Sinon;

open Header;

open Js.Promise;

let _ =
  describe("Header", () => {
    let sandbox = getSandboxDefaultVal();
    beforeEach(() => sandbox := createSandbox());
    afterEach(() => restoreSandbox(refJsObjToSandbox(sandbox^)));

    describe("test operate gameObject", () => {
      beforeEach(() =>
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
        )
      );

      describe("test add gameObject", () => {
        beforeEach(() =>
          MainEditorSceneTool.createDefaultScene(
            sandbox,
            MainEditorSceneTool.setFirstBoxToBeCurrentSceneTreeNode,
          )
        );
        describe("test add emptyGameObject", () =>
          test(
            "the added emptyGameObject should only has transform component", () => {
            let engineState = StateEngineService.unsafeGetState();

            HeaderTool.triggerAddEmptyGameObject();

            SceneTreeNodeDomTool.OperateDefaultScene.getNewGameObjectDomIndex()
            |> SceneTreeTool.clearCurrentGameObjectAndSetTreeSpecificGameObject;

            (
              engineState
              |> GameObjectComponentEngineService.hasTransformComponent(
                   GameObjectTool.unsafeGetCurrentSceneTreeNode(),
                 ),
              engineState
              |> GameObjectComponentEngineService.hasMeshRendererComponent(
                   GameObjectTool.unsafeGetCurrentSceneTreeNode(),
                 ),
            )
            |> expect == (true, false);
          })
        );
      });
      describe("test dispose gameObject", () => {
        beforeEach(() =>
          MainEditorSceneTool.createDefaultScene(
            sandbox,
            MainEditorSceneTool.setFirstBoxToBeCurrentSceneTreeNode,
          )
        );
        test(
          "if not set current gameObject, log error message and continue", () => {
          let error =
            createMethodStubWithJsObjSandbox(
              sandbox,
              ConsoleTool.console,
              "error",
            );
          GameObjectTool.clearCurrentSceneTreeNode();
          let component =
            BuildComponentTool.buildHeader(
              TestTool.buildAppStateSceneGraphFromEngine(),
            );
          BaseEventTool.triggerComponentEvent(
            component,
            OperateGameObjectEventTool.triggerClickDisposeAndExecDisposeJob,
          );
          ConsoleTool.getMessage(error)
          |> expect
          |> toContain("current gameObject should exist, but actual is None");
        });

        describe("else", () =>
          test("remove current gameObject from editorState", () => {
            let component =
              BuildComponentTool.buildHeader(
                TestTool.buildAppStateSceneGraphFromEngine(),
              );
            BaseEventTool.triggerComponentEvent(
              component,
              OperateGameObjectEventTool.triggerClickDisposeAndExecDisposeJob,
            );
            GameObjectTool.getCurrentSceneTreeNode()
            |> Js.Option.isNone
            |> expect == true;
          })
        );
      });

      describe("fix bug", () =>
        test(
          "remove gameObject has children;
            the children should be removed together;",
          () => {
            let (box1, box2, box3, box4) =
              SceneTreeTool.buildFourLayerSceneAndGetBox(sandbox);

            let engineState = StateEngineService.unsafeGetState();

            let component =
              BuildComponentTool.buildHeader(
                TestTool.buildAppStateSceneGraphFromEngine(),
              );
            BaseEventTool.triggerComponentEvent(
              component,
              OperateGameObjectEventTool.triggerClickDisposeAndExecDisposeJob,
            );

            (
              engineState |> GameObjectTool.isAlive(box1),
              engineState |> GameObjectTool.isAlive(box3),
              engineState |> GameObjectTool.isAlive(box4),
            )
            |> expect == (false, false, false);
          },
        )
      );
    });

    describe("test ambient light", () => {
      beforeEach(() => {
        MainEditorSceneTool.initState(~sandbox, ());

        MainEditorSceneTool.createDefaultScene(
          sandbox,
          MainEditorSceneTool.setFirstBoxToBeCurrentSceneTreeNode,
        );
      });
      describe("test snapshot", () =>
        test("show color picker component for change color", () => {
          BuildCanvasTool.buildFakeCanvas(sandbox);

          let component =
            BuildComponentTool.buildHeader(
              TestTool.buildAppStateSceneGraphFromEngine(),
            );

          BaseEventTool.triggerComponentEvent(
            component,
            OperateComponentEventTool.triggerShowColorPickEvent,
          );

          component |> ReactTestTool.createSnapshotAndMatch;
        })
      );
      test("test change color should set into engine", () => {
        let newColor = {
          "hex": "#7df1e8",
          "rgb": {
            "r": 125,
            "g": 241,
            "b": 232,
          },
        };

        Header.Method.changeColor(newColor);

        SceneEngineService.getAmbientLightColor
        |> StateLogicService.getEngineStateToGetData
        |> Color.getHexString
        |> expect == newColor##hex;
      });
    });

    describe("test export zip", () => {
      beforeEach(() => {
        MainEditorSceneTool.initState(~sandbox, ());

        MainEditorSceneTool.createDefaultScene(
          sandbox,
          MainEditorSceneTool.setFirstBoxToBeCurrentSceneTreeNode,
        );

        MainEditorAssetHeaderWDBTool.buildFakeTextEncoder();
        MainEditorAssetHeaderWDBTool.buildFakeURL(sandbox^);

        MainEditorAssetHeaderWDBTool.buildFakeLoadImage(.);
      });

      testPromise(
        "export assets folder's all node;
        first node is folder;
        second node is json;
      ",
        () => {
          MainEditorAssetTool.buildTwoLayerAssetTreeRootTest() |> ignore;

          let fakeFetchFunc =
            BuildFetchTool.buildFakeFetch(
              sandbox,
              "fake html text",
              "fake js text",
            );

          let obj = HeaderTool.buildExportFakeJsZipCreateFunc(sandbox^);

          HeaderExportUtils.exportPackage(() => obj, fakeFetchFunc)
          |> then_(_ => {
               let file = obj##file;

               (
                 file |> getCall(2) |> getArgs,
                 file |> getCall(3) |> getArgs,
               )
               |>
               expect == (
                           [
                             "Assets/newFolder",
                             0 |> Obj.magic,
                             {"dir": true} |> Obj.magic,
                           ],
                           [
                             "Assets/newJson.json",
                             "json result",
                             {"binary": true} |> Obj.magic,
                           ],
                         )
               |> resolve;
             });
        },
      );
      testPromise("export Index.html;", () => {
        let assetTreeDomRecord =
          MainEditorAssetTool.buildTwoLayerAssetTreeRootTest();

        let fakeFetchFunc =
          BuildFetchTool.buildFakeFetch(
            sandbox,
            "fake html text",
            "fake js text",
          );

        let component =
          BuildComponentTool.buildHeader(
            TestTool.buildAppStateSceneGraphFromEngine(),
          );

        let obj = HeaderTool.buildExportFakeJsZipCreateFunc(sandbox^);

        HeaderExportUtils.exportPackage(() => obj, fakeFetchFunc)
        |> then_(_ => {
             let file = obj##file;

             file
             |> getCall(0)
             |> getArgs
             |> Js.List.hd
             |> OptionService.unsafeGet
             |> expect == "Index.html"
             |> resolve;
           });
      });
      testPromise("export Index.min.js;", () => {
        let assetTreeDomRecord =
          MainEditorAssetTool.buildTwoLayerAssetTreeRootTest();

        let fakeFetchFunc =
          BuildFetchTool.buildFakeFetch(
            sandbox,
            "fake html text",
            "fake js text",
          );

        let component =
          BuildComponentTool.buildHeader(
            TestTool.buildAppStateSceneGraphFromEngine(),
          );

        let obj = HeaderTool.buildExportFakeJsZipCreateFunc(sandbox^);

        HeaderExportUtils.exportPackage(() => obj, fakeFetchFunc)
        |> then_(_ => {
             let file = obj##file;

             file
             |> getCall(1)
             |> getArgs
             |> Js.List.hd
             |> OptionService.unsafeGet
             |> expect == "Index.min.js"
             |> resolve;
           });
      });
      testPromise("export Scene.wdb;", () => {
        let assetTreeDomRecord =
          MainEditorAssetTool.buildTwoLayerAssetTreeRootTest();

        let fakeFetchFunc =
          BuildFetchTool.buildFakeFetch(
            sandbox,
            "fake html text",
            "fake js text",
          );

        let component =
          BuildComponentTool.buildHeader(
            TestTool.buildAppStateSceneGraphFromEngine(),
          );

        let obj = HeaderTool.buildExportFakeJsZipCreateFunc(sandbox^);

        HeaderExportUtils.exportPackage(() => obj, fakeFetchFunc)
        |> then_(_ => {
             let file = obj##file;

             file
             |> getCall(4)
             |> getArgs
             |> Js.List.hd
             |> OptionService.unsafeGet
             |> expect == "Scene.wdb"
             |> resolve;
           });
      });
      testPromise("export Assets.json;", () => {
        let assetTreeDomRecord =
          MainEditorAssetTool.buildTwoLayerAssetTreeRootTest();

        let fakeFetchFunc =
          BuildFetchTool.buildFakeFetch(
            sandbox,
            "fake html text",
            "fake js text",
          );

        let component =
          BuildComponentTool.buildHeader(
            TestTool.buildAppStateSceneGraphFromEngine(),
          );

        let obj = HeaderTool.buildExportFakeJsZipCreateFunc(sandbox^);

        HeaderExportUtils.exportPackage(() => obj, fakeFetchFunc)
        |> then_(_ => {
             let file = obj##file;

             file
             |> getCall(5)
             |> getArgs
             |> Js.List.hd
             |> OptionService.unsafeGet
             |> expect == "Assets.json"
             |> resolve;
           });
      });
    });
  });