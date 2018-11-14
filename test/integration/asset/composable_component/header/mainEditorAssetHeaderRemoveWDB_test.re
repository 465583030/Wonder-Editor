open Wonder_jest;

let _ =
  describe("MainEditorAssetHeader->remove wdb", () => {
    open Expect;
    open Expect.Operators;
    open Sinon;
    open Js.Promise;

    let sandbox = getSandboxDefaultVal();
    let boxTexturedWDBArrayBuffer = ref(Obj.magic(1));
    let sceneWDBArrayBuffer = ref(Obj.magic(1));

    beforeAll(() => {
      boxTexturedWDBArrayBuffer := WDBTool.convertGLBToWDB("BoxTextured");
      sceneWDBArrayBuffer := WDBTool.generateSceneWDB();
    });

    beforeEach(() => {
      sandbox := createSandbox();

      MainEditorSceneTool.initStateWithJob(
        ~sandbox,
        ~isBuildFakeDom=false,
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

      MainEditorAssetTool.buildFakeFileReader();
      MainEditorAssetTool.buildFakeImage();

      LoadTool.buildFakeTextDecoder(LoadTool.convertUint8ArrayToBuffer);

      LoadTool.buildFakeURL(sandbox^);

      LoadTool.buildFakeLoadImage(.);

      EventListenerTool.buildFakeDom()
      |> EventListenerTool.stubGetElementByIdReturnFakeDom;

      MainEditorAssetTreeTool.BuildAssetTree.buildEmptyAssetTree() |> ignore;
    });
    afterEach(() => restoreSandbox(refJsObjToSandbox(sandbox^)));

    describe(
      {|drag wdb asset into scene;
              select wdb to be currentNode;
              click remove-button;
              |},
      () => {
        describe("test cloned gameObjects of the wdb asset", () => {
          testPromise("cloned gameObjects shouldn't be removed", () => {
            MainEditorSceneTool.prepareScene(sandbox);

            MainEditorAssetUploadTool.loadOneWDB(
              ~arrayBuffer=boxTexturedWDBArrayBuffer^,
              (),
            )
            |> then_(uploadedWDBNodeId => {
                 MainEditorSceneTreeTool.Drag.dragWDBAssetToSceneTree(
                   ~wdbNodeId=uploadedWDBNodeId,
                   (),
                 );

                 MainEditorAssetHeaderOperateNodeTool.removeWDBNode(
                   ~wdbNodeId=uploadedWDBNodeId,
                   (),
                 );

                 BuildComponentTool.buildSceneTree(
                   TestTool.buildAppStateSceneGraphFromEngine(),
                 )
                 |> ReactTestTool.createSnapshotAndMatch
                 |> resolve;
               });
          });

          describe("cloned gameObjects->geometrys should be disposed", () => {
            let _prepare = testFunc => {
              MainEditorSceneTool.prepareScene(sandbox);

              MainEditorAssetUploadTool.loadOneWDB(
                ~arrayBuffer=boxTexturedWDBArrayBuffer^,
                (),
              )
              |> then_(uploadedWDBNodeId => {
                   MainEditorSceneTreeTool.Drag.dragWDBAssetToSceneTree(
                     ~wdbNodeId=uploadedWDBNodeId,
                     (),
                   );
                   MainEditorSceneTreeTool.Drag.dragWDBAssetToSceneTree(
                     ~wdbNodeId=uploadedWDBNodeId,
                     (),
                   );

                   MainEditorAssetHeaderOperateNodeTool.removeWDBNode(
                     ~wdbNodeId=uploadedWDBNodeId,
                     (),
                   );

                   let engineState = StateEngineService.unsafeGetState();

                   let clonedGameObjectsWhoHasGeometryWhenCloned =
                     LoadWDBTool.getBoxTexturedMeshGameObjects(engineState);

                   engineState |> StateEngineService.setState |> ignore;

                   testFunc(
                     clonedGameObjectsWhoHasGeometryWhenCloned,
                     engineState,
                   );
                 });
            };

            testPromise("test engine", () =>
              _prepare(
                (clonedGameObjectsWhoHasGeometryWhenCloned, engineState) =>
                clonedGameObjectsWhoHasGeometryWhenCloned
                |> Js.Array.map(gameObject =>
                     GameObjectComponentEngineService.hasGeometryComponent(
                       gameObject,
                       engineState,
                     )
                   )
                |> expect == [|false, false|]
                |> resolve
              )
            );
            testPromise("test snapshot", () =>
              _prepare(
                (clonedGameObjectsWhoHasGeometryWhenCloned, engineState) => {
                MainEditorSceneTreeTool.Select.selectGameObject(
                  ~gameObject=
                    clonedGameObjectsWhoHasGeometryWhenCloned
                    |> ArrayService.unsafeGetFirst,
                  (),
                );

                BuildComponentTool.buildInspectorComponent(
                  TestTool.buildEmptyAppState(),
                  InspectorTool.buildFakeAllShowComponentConfig(),
                )
                |> ReactTestTool.createSnapshotAndMatch
                |> resolve;
              })
            );
          });
        });

        describe("dispose wdb asset gameObject", () => {
          testPromise("it's geometry should be disposed", () => {
            MainEditorSceneTool.createDefaultSceneAndNotInit(sandbox);

            MainEditorAssetUploadTool.loadOneWDB(
              ~arrayBuffer=boxTexturedWDBArrayBuffer^,
              (),
            )
            |> then_(uploadedWDBNodeId => {
                 MainEditorSceneTreeTool.Drag.dragWDBAssetToSceneTree(
                   ~wdbNodeId=uploadedWDBNodeId,
                   (),
                 );

                 MainEditorAssetHeaderOperateNodeTool.removeWDBNode(
                   ~wdbNodeId=uploadedWDBNodeId,
                   (),
                 );

                 MainEditorSceneTool.setFirstBoxToBeCurrentSceneTreeNode();

                 let component =
                   BuildComponentTool.buildGeometry(
                     ~geometryComponent=
                       GameObjectTool.getCurrentGameObjectGeometry(),
                     ~isShowGeometryGroup=true,
                     (),
                   );

                 component |> ReactTestTool.createSnapshotAndMatch |> resolve;
               });
          });

          describe("it's material should be removed", () =>
            testPromise(
              "the material asset related with the material component should exist",
              () => {
              MainEditorSceneTool.createDefaultSceneAndNotInit(sandbox);

              MainEditorAssetUploadTool.loadOneWDB(
                ~arrayBuffer=boxTexturedWDBArrayBuffer^,
                (),
              )
              |> then_(uploadedWDBNodeId => {
                   MainEditorSceneTreeTool.Drag.dragWDBAssetToSceneTree(
                     ~wdbNodeId=uploadedWDBNodeId,
                     (),
                   );

                   MainEditorAssetHeaderOperateNodeTool.removeWDBNode(
                     ~wdbNodeId=uploadedWDBNodeId,
                     (),
                   );

                   let editorState = StateEditorService.getState();

                   MainEditorAssetTreeTool.Select.selectFolderNode(
                     ~nodeId=
                       MainEditorAssetFolderNodeTool.getNodeIdByName(
                         "Materials",
                         editorState,
                       )
                       |> OptionService.unsafeGet,
                     (),
                   );

                   BuildComponentTool.buildAssetChildrenNode()
                   |> ReactTestTool.createSnapshotAndMatch
                   |> resolve;
                 });
            })
          );
          testPromise("it should be disposed", () => {
            MainEditorSceneTool.createDefaultSceneAndNotInit(sandbox);

            MainEditorAssetUploadTool.loadOneWDB(
              ~arrayBuffer=boxTexturedWDBArrayBuffer^,
              (),
            )
            |> then_(uploadedWDBNodeId => {
                 MainEditorSceneTreeTool.Drag.dragWDBAssetToSceneTree(
                   ~wdbNodeId=uploadedWDBNodeId,
                   (),
                 );

                 let editorState = StateEditorService.getState();
                 let engineState = StateEngineService.unsafeGetState();

                 let wdbGameObject =
                   LoadWDBTool.getBoxTexturedMeshGameObjectFromAssetNode(
                     uploadedWDBNodeId,
                     (editorState, engineState),
                   );

                 MainEditorAssetHeaderOperateNodeTool.removeWDBNode(
                   ~wdbNodeId=uploadedWDBNodeId,
                   (),
                 );

                 GameObjectTool.isAlive(wdbGameObject, engineState)
                 |> expect == false
                 |> resolve;
               });
          });
        });
      },
    );

    testPromise(
      {|load BoxTextured.wdb;
              remove BoxTextured.wdb;
              load Scene.wdb;
              load BoxTextured.wdb;

              the MainEditorAssetChildrenNode panel should show "Scene","Boxtextured"
                |},
      () => {
        MainEditorSceneTool.prepareScene(sandbox);

        MainEditorAssetUploadTool.loadOneWDB(
          ~arrayBuffer=boxTexturedWDBArrayBuffer^,
          (),
        )
        |> then_(uploadedWDBNodeId => {
             MainEditorAssetHeaderOperateNodeTool.removeWDBNode(
               ~wdbNodeId=uploadedWDBNodeId,
               (),
             );

             MainEditorAssetUploadTool.loadOneWDB(
               ~arrayBuffer=sceneWDBArrayBuffer^,
               (),
             )
             |> then_(_ =>
                  MainEditorAssetUploadTool.loadOneWDB(
                    ~arrayBuffer=boxTexturedWDBArrayBuffer^,
                    (),
                  )
                  |> then_(_ =>
                       BuildComponentTool.buildAssetComponent()
                       |> ReactTestTool.createSnapshotAndMatch
                       |> resolve
                     )
                );
           });
      },
    );

    describe("fix bug", () =>
      describe(
        "the default geometry with wdb asset should be remove instead of dispose when remove wdb asset",
        () => {
          let wdbArrayBuffer = ref(Obj.magic(1));

          let _generateWDB = () =>
            WDBTool.generateWDB((editorState, engineState) => {
              let (engineState, rootGameObject) =
                GameObjectEngineService.create(engineState);

              let geometry =
                GeometryDataAssetEditorService.unsafeGetDefaultCubeGeometryComponent(
                  editorState,
                );

              let (engineState, lightMaterial) =
                LightMaterialEngineService.create(engineState);

              let (editorState, engineState, box1) =
                PrimitiveEngineService.createCube(
                  (geometry, lightMaterial),
                  editorState,
                  engineState,
                );

              let engineState =
                GameObjectEngineService.setGameObjectName(
                  "Box1",
                  box1,
                  engineState,
                );

              let engineState =
                engineState |> GameObjectUtils.addChild(rootGameObject, box1);

              (rootGameObject, (editorState, engineState));
            });

          beforeAll(() => wdbArrayBuffer := _generateWDB());

          testPromise(
            {|
        1.create gameObject g1 with default cube geometry in scene;
        2.load wdb asset w1(has one box gameObject with default cube geometry);
        3.drag wdb asset to scene tree to be c1;
        4.remove w1;

        c1's and g1's geometry shouldn't be changed
        |},
            () => {
              MainEditorSceneTool.prepareScene(sandbox);
              MainEditorSceneTool.createDefaultScene(
                sandbox,
                MainEditorAssetTool.initAssetTree,
              );

              let engineState = StateEngineService.unsafeGetState();

              let firstBoxGameObject =
                MainEditorSceneTool.getFirstBox(engineState);

              MainEditorAssetUploadTool.loadOneWDB(
                ~arrayBuffer=wdbArrayBuffer^,
                (),
              )
              |> then_(uploadedWDBNodeId => {
                   MainEditorSceneTreeTool.Drag.dragWDBAssetToSceneTree(
                     ~wdbNodeId=uploadedWDBNodeId,
                     (),
                   );

                   let editorState = StateEditorService.getState();
                   let engineState = StateEngineService.unsafeGetState();

                   let clonedGameObject =
                     LoadWDBTool.findGameObjectByName("Box1", engineState);

                   MainEditorAssetHeaderOperateNodeTool.removeWDBNode(
                     ~wdbNodeId=uploadedWDBNodeId,
                     (),
                   );

                   let engineState = StateEngineService.unsafeGetState();

                   (
                     clonedGameObject
                     |> GameObjectComponentEngineService.hasGeometryComponent(
                          _,
                          engineState,
                        ),
                     firstBoxGameObject
                     |> GameObjectComponentEngineService.hasGeometryComponent(
                          _,
                          engineState,
                        ),
                   )
                   |> expect == (true, true)
                   |> resolve;
                 });
            },
          );
        },
      )
    );
  });