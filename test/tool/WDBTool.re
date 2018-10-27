let buildGLBPath = glbName =>
  Node.Path.join([|
    Node.Process.cwd(),
    "./test/res/glb/",
    {j|$glbName.glb|j},
  |]);

let convertGLBToWDB = glbName => {
  /*! fix fs.readFileSync returns corrupt ArrayBuffer (fs.readFile works as expected):
    https://github.com/nodejs/node/issues/11132 */
  let buffer = NodeExtendTool.readFileBufferSync(buildGLBPath(glbName));

  LoadTool.buildFakeTextDecoder(LoadTool.convertUint8ArrayToBuffer);
  LoadTool.buildFakeTextEncoder(.);

  buffer##buffer |> Wonderjs.ConverterAPI.convertGLBToWDB;
};

let _createPointLight = (editorState, engineState) => {
  let (editorState, (engineState, obj)) =
    GameObjectLogicService.createGameObject((editorState, engineState));
  let (engineState, pointLight) =
    PointLightEngineService.create(engineState);

  let engineState =
    engineState
    |> GameObjectEngineService.setGameObjectName("Point Light", obj);

  let (editorState, engineState) =
    (editorState, engineState)
    |> GameObjectLogicService.addPointLight(obj, pointLight);

  (editorState, engineState, obj);
};

let _createStateTuple = () => {
  let sandbox = Sinon.createSandbox();

  MainEditorSceneTool.initStateWithJob(
    ~sandbox=ref(sandbox),
    ~isBuildFakeDom=false,
    ~noWorkerJobRecord=
      NoWorkerJobConfigToolEngine.buildNoWorkerEmptyJobConfig(),
    (),
  );

  let editorState = StateEditorService.getState();
  let engineState = StateEngineService.unsafeGetState();

  let engineState =
    engineState
    |> FakeGlToolEngine.setFakeGl(
         FakeGlToolEngine.buildFakeGl(~sandbox=ref(sandbox), ()),
       );

  (editorState, engineState);
};

let generateDirectionPointLightsAndBoxWDBWithNewState = () => {
  let (editorState, engineState) = _createStateTuple();

  let (engineState, geometry) =
    GeometryEngineService.createCubeGeometry(engineState);
  let (engineState, lightMaterial) =
    LightMaterialEngineService.create(engineState);

  let (editorState, engineState, box1) =
    PrimitiveEngineService.createBox(
      (geometry, lightMaterial),
      editorState,
      engineState,
    );

  let (editorState, engineState, directionLight) =
    PrimitiveEngineService.createDirectionLight(editorState, engineState);

  let (editorState, engineState, pointLight) =
    _createPointLight(editorState, engineState);

  let (engineState, rootGameObject) =
    GameObjectEngineService.create(engineState);

  let engineState =
    engineState
    |> GameObjectUtils.addChild(rootGameObject, box1)
    |> GameObjectUtils.addChild(rootGameObject, directionLight)
    |> GameObjectUtils.addChild(rootGameObject, pointLight);

  LoadTool.buildFakeTextEncoder(.);

  let (engineState, wdbArrayBuffer) =
    HeaderExportPackageUtils._generateWDB(rootGameObject, engineState);

  wdbArrayBuffer;
};

let _generateSceneWDB = (editorState, engineState) => {
  let engineState =
    ManageIMGUIEngineService.setIMGUIFunc(
      Obj.magic(Js.Nullable.null),
      Obj.magic((. _, apiJsObj, engineState) => {
        let label = apiJsObj##label;
        let engineState =
          label(. (100., 30., 300., 200.), "imgui", 0, engineState);

        engineState;
      }),
      engineState,
    );

  let (engineState, geometry) =
    GeometryEngineService.createCubeGeometry(engineState);
  let (engineState, lightMaterial) =
    LightMaterialEngineService.create(engineState);

  let (editorState, engineState, box1) =
    PrimitiveEngineService.createBox(
      (geometry, lightMaterial),
      editorState,
      engineState,
    );

  let (editorState, engineState, camera) =
    CameraEngineService.createCamera(editorState, engineState);
  let (engineState, arcballCameraController) =
    ArcballCameraEngineService.create(engineState);

  let basicCameraViewComponent =
    GameObjectComponentEngineService.unsafeGetBasicCameraViewComponent(
      camera,
      engineState,
    );

  let engineState =
    engineState
    /* |> TransformEngineService.setLocalPosition(
         (20., 0., 100.),
         GameObjectComponentEngineService.unsafeGetTransformComponent(
           camera,
           engineState,
         ),
       ) */
    /* |> ArcballCameraEngineService.setArcballCameraControllerDistance(
            200.,
            arcballCameraController,
          )
       |> ArcballCameraEngineService.setArcballCameraControllerWheelSpeed(
            arcballCameraController,
            8.,
          )
       |> ArcballCameraEngineService.setArcballCameraControllerTheta(
            arcballCameraController,
            Js.Math._PI /. 5.,
          ) */
    |> ArcballCameraControllerLogicService.bindArcballCameraControllerEventForSceneView(
         arcballCameraController,
       )
    |> BasicCameraViewEngineService.activeBasicCameraView(
         basicCameraViewComponent,
       );

  let (editorState, engineState) =
    (editorState, engineState)
    |> GameObjectLogicService.addArcballCameraController(
         camera,
         arcballCameraController,
       );

  let (editorState, engineState, directionLight) =
    PrimitiveEngineService.createDirectionLight(editorState, engineState);

  /* let (editorState, engineState, pointLight) =
     _createPointLight(editorState, engineState); */

  let (engineState, rootGameObject) =
    GameObjectEngineService.create(engineState);

  let engineState =
    engineState
    |> GameObjectUtils.addChild(rootGameObject, box1)
    |> GameObjectUtils.addChild(rootGameObject, camera)
    |> GameObjectUtils.addChild(rootGameObject, directionLight);
  /* |> GameObjectUtils.addChild(rootGameObject, pointLight); */

  LoadTool.buildFakeTextEncoder(.);

  let (engineState, wdbArrayBuffer) =
    HeaderExportPackageUtils._generateWDB(rootGameObject, engineState);

  wdbArrayBuffer;
};

let generateSceneWDBWithNewState = () => {
  let (editorState, engineState) = _createStateTuple();

  _generateSceneWDB(editorState, engineState);
};