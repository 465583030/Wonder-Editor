open Wonder_jest;

open Expect;

open Expect.Operators;

open Sinon;

let _ =
  describe("init picking job", () => {
    let sandbox = getSandboxDefaultVal();

    beforeEach(() => sandbox := createSandbox());
    afterEach(() => restoreSandbox(refJsObjToSandbox(sandbox^)));

    describe("test find picked one", () => {
      describe("should set finded one to current scene tree node", () => {
        describe("if pointtap->mouse button isn't left button", () => {
          let _prepare = () =>
            InitPickingJobTool.prepareOneGameObject(
              ~sandbox,
              ~viewWidth=510,
              ~viewHeight=200,
              ~offsetLeft=10,
              ~offsetTop=20,
              ~cameraPos=(
                6.986046314239502,
                0.43706008791923523,
                (-0.06429910659790039),
              ),
              ~gameObjectPos=(3., 0., 0.),
              ~gameObjectEulerAngles=(45., 0., 0.),
              ~createGameObjectFunc=InitPickingJobTool.createCube,
              (),
            );

          test("not trigger pick", () => {
            let gameObject1 = _prepare();

            InitPickingJobTool.triggerPickingAndRestore(
              ~sandbox,
              ~pageX=233 + 10,
              ~pageY=119 + 20,
              ~eventButton=3,
              (),
            );

            InitPickingJobTool.notPick();
          });
        });

        describe("test only pick one", () =>
          describe("test cube", () => {
            let _prepare = () =>
              InitPickingJobTool.prepareOneGameObject(
                ~sandbox,
                ~viewWidth=510,
                ~viewHeight=200,
                ~offsetLeft=10,
                ~offsetTop=20,
                ~cameraPos=(
                  6.986046314239502,
                  0.43706008791923523,
                  (-0.06429910659790039),
                ),
                ~gameObjectPos=(3., 0., 0.),
                ~gameObjectEulerAngles=(45., 0., 0.),
                ~createGameObjectFunc=InitPickingJobTool.createCube,
                (),
              );

            test("test find", () => {
              let gameObject1 = _prepare();

              InitPickingJobTool.triggerPickingAndRestore(
                ~sandbox,
                ~pageX=233 + 10,
                ~pageY=119 + 20,
                (),
              );

              InitPickingJobTool.pickOne(gameObject1);
            });
            test("test not find", () => {
              let gameObject1 = _prepare();

              InitPickingJobTool.triggerPickingAndRestore(
                ~sandbox,
                ~pageX=225 + 10,
                ~pageY=124 + 20,
                (),
              );

              InitPickingJobTool.notPick();
            });
          })
        );

        describe("test pick multi ones", () =>
          describe(
            "find the top one whose distance between intersected point and the camera position is nearest",
            () => {
              describe("test cube", () => {
                let _prepare = () =>
                  InitPickingJobTool.prepareTwoGameObjects(
                    ~sandbox,
                    ~viewWidth=510,
                    ~viewHeight=200,
                    ~offsetLeft=10,
                    ~offsetTop=20,
                    ~cameraPos=(
                      2.2987656593322754,
                      8.099184036254883,
                      1.1699984073638916,
                    ),
                    ~gameObject1Pos=(0., 0., 0.),
                    ~gameObject1EulerAngles=(0., 0., 0.),
                    ~gameObject2Pos=(1., 2., 0.),
                    ~gameObject2EulerAngles=(0., 0., 0.),
                    ~createGameObjectFunc1=InitPickingJobTool.createCube,
                    ~createGameObjectFunc2=InitPickingJobTool.createCube,
                    (),
                  );

                test("test find gameObject1", () => {
                  let (gameObject1, gameObject2) = _prepare();

                  InitPickingJobTool.triggerPickingAndRestore(
                    ~sandbox,
                    ~pageX=251 + 10,
                    ~pageY=91 + 20,
                    (),
                  );

                  InitPickingJobTool.pickOne(gameObject1);
                });
                test("test find gameObject2", () => {
                  let (gameObject1, gameObject2) = _prepare();

                  InitPickingJobTool.triggerPickingAndRestore(
                    ~sandbox,
                    ~pageX=257 + 10,
                    ~pageY=100 + 20,
                    (),
                  );

                  InitPickingJobTool.pickOne(gameObject2);
                });
                test("test not find", () => {
                  let (gameObject1, gameObject2) = _prepare();

                  InitPickingJobTool.triggerPickingAndRestore(
                    ~sandbox,
                    ~pageX=241 + 10,
                    ~pageY=120 + 20,
                    (),
                  );

                  InitPickingJobTool.notPick();
                });
              });

              describe("test triangle", () => {
                let _createTriangleInPositiveYAxis = engineState => {
                  open Js.Typed_array;

                  let (engineState, geometry) =
                    GeometryEngineService.create(engineState);

                  let vertices1 =
                    Float32Array.make([|
                      1.,
                      0.,
                      3.,
                      0.,
                      1.,
                      3.,
                      (-1.),
                      0.,
                      3.,
                    |]);
                  let indices1 = Uint16Array.make([|0, 1, 2|]);

                  let engineState =
                    engineState
                    |> GeometryEngineService.setGeometryVertices(
                         geometry,
                         vertices1,
                       )
                    |> GeometryEngineService.setGeometryIndices(
                         geometry,
                         indices1,
                       );

                  InitPickingJobTool.createGameObject(geometry, engineState);
                };

                let _prepare = (gameObject1Pos, gameObject2Pos) =>
                  InitPickingJobTool.prepareTwoGameObjects(
                    ~sandbox,
                    ~viewWidth=500,
                    ~viewHeight=200,
                    ~offsetLeft=0,
                    ~offsetTop=0,
                    ~cameraPos=(0., 0., 5.),
                    ~gameObject1Pos,
                    ~gameObject1EulerAngles=(0., 0., 0.),
                    ~gameObject2Pos,
                    ~gameObject2EulerAngles=(0., 0., 0.),
                    ~createGameObjectFunc1=InitPickingJobTool.createCube,
                    ~createGameObjectFunc2=_createTriangleInPositiveYAxis,
                    (),
                  );

                test("test find", () => {
                  let (gameObject1, gameObject2) =
                    _prepare((0., 0., 3.), (0., 0., 1.));

                  InitPickingJobTool.triggerPickingAndRestore(
                    ~sandbox,
                    ~pageX=250,
                    ~pageY=100,
                    (),
                  );

                  InitPickingJobTool.pickOne(gameObject2);
                });
                test("test not find", () => {
                  let (gameObject1, gameObject2) =
                    _prepare((0., 0., 4.1), (0., 0., 1.));

                  InitPickingJobTool.triggerPickingAndRestore(
                    ~sandbox,
                    ~pageX=250,
                    ~pageY=100,
                    (),
                  );

                  InitPickingJobTool.pickOne(gameObject1);
                });
              });
            },
          )
        );

        describe("test sphere shape cache", () => {
          let _changePoints = gameObject => {
            let editorState = StateEditorService.getState();
            let engineState = StateEngineService.unsafeGetState();

            let geometry =
              GameObjectComponentEngineService.unsafeGetGeometryComponent(
                gameObject,
                engineState,
              );

            let (editorState, engineState) =
              (editorState, engineState)
              |> GeometryLogicService.setGeometryPoints(
                   geometry,
                   Js.Typed_array.Float32Array.make([|
                     2.5,
                     0.,
                     0.,
                     0.,
                     0.5,
                     0.,
                     1.5,
                     0.,
                     0.,
                   |]),
                   GeometryEngineService.setGeometryVertices,
                 )
              |> GeometryLogicService.setGeometryPoints(
                   geometry,
                   Js.Typed_array.Uint16Array.make([|0, 1, 2|]),
                   GeometryEngineService.setGeometryIndices,
                 );

            editorState |> StateEditorService.setState |> ignore;
            engineState |> StateEngineService.setState |> ignore;
          };

          test(
            "if change geometry points, the intersect should be correct", () => {
            let gameObject =
              InitPickingJobTool.prepareOneGameObject(
                ~sandbox,
                ~viewWidth=510,
                ~viewHeight=200,
                ~offsetLeft=10,
                ~offsetTop=20,
                ~cameraPos=(0., 0., 2.5),
                ~gameObjectPos=(0., 0., 0.),
                ~gameObjectEulerAngles=(0., 0., 0.),
                ~createGameObjectFunc=InitPickingJobTool.createCube,
                (),
              );

            InitPickingJobTool.triggerPicking(
              sandbox,
              255 + 10,
              100 + 20,
              1,
            );

            SceneTreeEditorService.clearCurrentSceneTreeNode
            |> StateLogicService.getAndSetEditorState;

            _changePoints(gameObject);

            InitPickingJobTool.triggerPickingAndRestore(
              ~sandbox,
              ~pageX=255 + 10,
              ~pageY=100 + 20,
              (),
            );

            InitPickingJobTool.notPick();
          });
        });
      });

      describe("if find one", () => {
        let _prepare = () =>
          InitPickingJobTool.prepareOneGameObject(
            ~sandbox,
            ~viewWidth=500,
            ~viewHeight=200,
            ~offsetLeft=10,
            ~offsetTop=20,
            ~cameraPos=(0., 0., 2.),
            ~gameObjectPos=(0., 0., 0.),
            ~gameObjectEulerAngles=(0., 0., 0.),
            ~createGameObjectFunc=InitPickingJobTool.createCube,
            (),
          );

        let _triggerPicking = () =>
          InitPickingJobTool.triggerPickingAndRestore(
            ~sandbox,
            ~pageX=250 + 10,
            ~pageY=100 + 20,
            (),
          );

        test("set current select source to scene tree", () => {
          let _ = _prepare();

          CurrentSelectSourceEditorService.clearCurrentSelectSource
          |> StateLogicService.getAndSetEditorState;

          _triggerPicking();

          let editorState = StateEditorService.getState();

          CurrentSelectSourceEditorService.getCurrentSelectSource(editorState)
          |> expect == Some(SceneTreeWidgetService.getWidget());
        });

        describe("trigger pickSuccess event", () => {
          test("test trigger", () => {
            let _ = _prepare();
            let a = ref(0);
            ManageEventEngineService.onCustomGlobalEvent(
              ~eventName=EventEditorService.getPickSuccessEventName(),
              ~handleFunc=
                (. event, engineState) => {
                  a := 1;

                  (engineState, event);
                },
              ~state=StateEngineService.unsafeGetState(),
              (),
            )
            |> StateEngineService.setState
            |> ignore;

            _triggerPicking();

            a^ |> expect == 1;
          });
          /* test("can get picked gameObject in event handle func", () => {
               let gameObject = _prepare();
               let pickedGameObject = ref(0);
               ManageEventEngineService.onCustomGlobalEvent(
                 ~eventName=EventEditorService.getPickSuccessEventName(),
                 ~handleFunc=
                   (. event, engineState) => {
                     let editorState = StateEditorService.getState();

                     pickedGameObject :=
                       SceneTreeEditorService.unsafeGetCurrentSceneTreeNode(
                         editorState,
                       );

                     (engineState, event);
                   },
                 ~state=StateEngineService.unsafeGetState(),
                 (),
               )
               |> StateEngineService.setState
               |> ignore;

               _triggerPicking();

               pickedGameObject^ |> expect == gameObject;
             }); */
          test("the picked gameObject's all parents should show children", () => {
            let _createParentGameObject = engineState => {
              let (engineState, parent) =
                engineState |> GameObjectEngineService.create;
              let engineState =
                engineState
                |> GameObjectEngineService.setGameObjectName("parent", parent);

              (engineState, parent);
            };

            let gameObject = _prepare();
            let engineState = StateEngineService.unsafeGetState();
            let (engineState, parent1) =
              _createParentGameObject(engineState);
            let (engineState, parent2) =
              _createParentGameObject(engineState);
            let engineState =
              engineState
              |> SceneEngineService.addSceneChild(parent1)
              |> HierarchyGameObjectEngineService.addChild(parent1, parent2)
              |> HierarchyGameObjectEngineService.addChild(parent2, gameObject);

            _triggerPicking();

            let editorState = StateEditorService.getState();
            let engineState = StateEngineService.unsafeGetState();
            let sceneGameObject =
              SceneEngineService.getSceneGameObject(engineState);
            (
              SceneTreeEditorService.getIsShowChildern(
                parent1,
                sceneGameObject,
                editorState,
              ),
              SceneTreeEditorService.getIsShowChildern(
                parent2,
                sceneGameObject,
                editorState,
              ),
            )
            |> expect == (true, true);
          });
        });
      });

      describe("if not find", () =>
        describe("trigger pick fail event", () => {
          let _prepare = () =>
            InitPickingJobTool.prepareOneGameObject(
              ~sandbox,
              ~viewWidth=500,
              ~viewHeight=200,
              ~offsetLeft=10,
              ~offsetTop=20,
              ~cameraPos=(0., 0., 20.),
              ~gameObjectPos=(0., 0., 0.),
              ~gameObjectEulerAngles=(0., 0., 0.),
              ~createGameObjectFunc=InitPickingJobTool.createCube,
              (),
            );

          let _triggerPicking = () =>
            InitPickingJobTool.triggerPickingAndRestore(
              ~sandbox,
              ~pageX=400 + 10,
              ~pageY=100 + 20,
              (),
            );

          test("clear curent scene tree node", () => {
            let _ = _prepare();
            let gameObject = 500;
            GameObjectTool.setCurrentSceneTreeNode(gameObject);

            _triggerPicking();

            InitPickingJobTool.notPick();
          });
          test("clear curent asset node id", () => {
            let _ = _prepare();
            let nodeId = 500;
            MainEditorAssetNodeTool.setCurrentNodeId(nodeId);

            _triggerPicking();

            MainEditorAssetNodeTool.getCurrentNodeId
            |> StateLogicService.getEditorState
            |> expect == None;
          });
          test("clear curent select source", () => {
            let _ = _prepare();
            CurrentSelectSourceEditorService.setCurrentSelectSource(
              WidgetType.Asset,
            )
            |> StateLogicService.getAndSetEditorState;

            _triggerPicking();

            CurrentSelectSourceEditorService.getCurrentSelectSource
            |> StateLogicService.getEditorState
            |> expect == None;
          });
        })
      );

      describe("isIntersectTriangle", () =>
        describe("test cull", () => {
          let _isIntersectTriangle =
              (
                ~sandbox,
                ~cullType,
                ~va,
                ~vb,
                ~vc,
                ~locationInView,
                ~viewWidth,
                ~viewHeight,
                ~cameraPos,
              ) => {
            InitPickingJobTool.prepareStateAndView(
              ~sandbox,
              ~viewWidth,
              ~viewHeight,
            );

            let editorState = StateEditorService.getState();
            let engineState = StateEngineService.unsafeGetState();

            let (editCamera, (editorState, engineState)) =
              InitPickingJobTool.prepareCamera(
                cameraPos,
                (viewWidth, viewHeight),
                (editorState, engineState),
              );

            let cameraGameObject =
              SceneViewEditorService.unsafeGetEditCamera(editorState);

            let ray =
              RayUtils.createPerspectiveCameraRay(
                InitPickingJobUtil._convertMouselocationInViewToNDC(
                  locationInView,
                  InitPickingJobUtil._getSceneViewSize(editorState),
                ),
                InitPickingJobUtil._getPerspectiveCameraData(
                  cameraGameObject,
                  (editorState, engineState),
                ),
              );

            RayUtils.checkIntersectTriangle(cullType, va, vb, vc, ray)
            |> Js.Option.isSome;
          };

          describe("test back cull", () => {
            test("test intersect front side", () =>
              _isIntersectTriangle(
                ~sandbox,
                ~cullType=InitPickingJobType.Back,
                ~viewWidth=500,
                ~viewHeight=200,
                ~va=(1., 0., 0.),
                ~vb=(0., 1., 0.),
                ~vc=((-1.), 0., 0.),
                ~locationInView=(250, 100),
                ~cameraPos=(0., 0., 2.),
              )
              |> expect == true
            );
            test("test not intersect back side", () =>
              _isIntersectTriangle(
                ~sandbox,
                ~cullType=InitPickingJobType.Back,
                ~viewWidth=500,
                ~viewHeight=200,
                ~va=((-1.), 0., 0.),
                ~vb=(0., 1., 0.),
                ~vc=(1., 0., 0.),
                ~locationInView=(250, 100),
                ~cameraPos=(0., 0., 2.),
              )
              |> expect == false
            );
          });

          describe("test front cull", () => {
            test("test intersect back side", () =>
              _isIntersectTriangle(
                ~sandbox,
                ~cullType=InitPickingJobType.Front,
                ~viewWidth=500,
                ~viewHeight=200,
                ~va=((-1.), 0., 0.),
                ~vb=(0., 1., 0.),
                ~vc=(1., 0., 0.),
                ~locationInView=(250, 100),
                ~cameraPos=(0., 0., 2.),
              )
              |> expect == true
            );
            test("test not intersect front side", () =>
              _isIntersectTriangle(
                ~sandbox,
                ~cullType=InitPickingJobType.Front,
                ~viewWidth=500,
                ~viewHeight=200,
                ~va=(1., 0., 0.),
                ~vb=(0., 1., 0.),
                ~vc=((-1.), 0., 0.),
                ~locationInView=(250, 100),
                ~cameraPos=(0., 0., 2.),
              )
              |> expect == false
            );
          });
          describe("test not cull", () => {
            test("test intersect back side", () =>
              _isIntersectTriangle(
                ~sandbox,
                ~cullType=InitPickingJobType.None,
                ~viewWidth=500,
                ~viewHeight=200,
                ~va=((-1.), 0., 0.),
                ~vb=(0., 1., 0.),
                ~vc=(1., 0., 0.),
                ~locationInView=(250, 100),
                ~cameraPos=(0., 0., 2.),
              )
              |> expect == true
            );
            test("test intersect front side", () =>
              _isIntersectTriangle(
                ~sandbox,
                ~cullType=InitPickingJobType.None,
                ~viewWidth=500,
                ~viewHeight=200,
                ~va=(1., 0., 0.),
                ~vb=(0., 1., 0.),
                ~vc=((-1.), 0., 0.),
                ~locationInView=(250, 100),
                ~cameraPos=(0., 0., 2.),
              )
              |> expect == true
            );
          });
          describe("test both cull", () => {
            test("test not intersect back side", () =>
              _isIntersectTriangle(
                ~sandbox,
                ~cullType=InitPickingJobType.Both,
                ~viewWidth=500,
                ~viewHeight=200,
                ~va=((-1.), 0., 0.),
                ~vb=(0., 1., 0.),
                ~vc=(1., 0., 0.),
                ~locationInView=(250, 100),
                ~cameraPos=(0., 0., 2.),
              )
              |> expect == false
            );
            test("test not intersect front side", () =>
              _isIntersectTriangle(
                ~sandbox,
                ~cullType=InitPickingJobType.Both,
                ~viewWidth=500,
                ~viewHeight=200,
                ~va=(1., 0., 0.),
                ~vb=(0., 1., 0.),
                ~vc=((-1.), 0., 0.),
                ~locationInView=(250, 100),
                ~cameraPos=(0., 0., 2.),
              )
              |> expect == false
            );
          });
        })
      );

      describe("fix bug", () =>
        describe("can pick the geometry which has indices32 data", () => {
          let _createIndices32Triangle = engineState => {
            open Js.Typed_array;

            let (engineState, geometry) =
              GeometryEngineService.create(engineState);

            let vertices1 =
              Float32Array.make([|1., 0., 0., 0., 1., 0., (-1.), 0., 0.|]);
            let indices1 = Uint32Array.make([|0, 1, 2|]);

            let engineState =
              engineState
              |> GeometryEngineService.setGeometryVertices(
                   geometry,
                   vertices1,
                 )
              |> GeometryEngineService.setGeometryIndices32(
                   geometry,
                   indices1,
                 );

            InitPickingJobTool.createGameObject(geometry, engineState);
          };
          let _prepare = () =>
            InitPickingJobTool.prepareOneGameObject(
              ~sandbox,
              ~viewWidth=500,
              ~viewHeight=200,
              ~offsetLeft=0,
              ~offsetTop=0,
              ~cameraPos=(0., 0., 3.),
              ~gameObjectPos=(0., 0., 0.),
              ~gameObjectEulerAngles=(0., 0., 0.),
              ~createGameObjectFunc=_createIndices32Triangle,
              (),
            );

          test("test pick", () => {
            let gameObject1 = _prepare();

            InitPickingJobTool.triggerPickingAndRestore(
              ~sandbox,
              ~pageX=250,
              ~pageY=100,
              (),
            );

            InitPickingJobTool.pickOne(gameObject1);
          });
        })
      );
    });
  });