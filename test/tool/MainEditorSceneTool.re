let unsafeGetScene = () => SceneEditorService.unsafeGetScene |> StateLogicService.getEditorState;

let unsafeGetCurrentGameObject = () =>
  SceneEditorService.unsafeGetCurrentGameObject |> StateLogicService.getEditorState;

let clearCurrentGameObject = () =>
  SceneEditorService.clearCurrentGameObject |> StateLogicService.getAndSetEditorState;

let addFakeVboBufferForGameObject = (gameObject) => {
  StateLogicService.getEngineStateForEdit()
  |> MainEditorVboBufferTool.passBufferShouldExistCheckWhenDisposeGeometry(
       GameObjectComponentEngineService.getBoxGeometryComponent(gameObject)
       |> StateLogicService.getEngineStateToGetData
     )
  |> StateLogicService.setEngineStateForEdit;
  StateLogicService.getEngineStateForRun()
  |> MainEditorVboBufferTool.passBufferShouldExistCheckWhenDisposeGeometry(
       GameObjectComponentEngineService.getBoxGeometryComponent(gameObject)
       |> StateLogicService.getEngineStateToGetData
     )
  |> StateLogicService.setEngineStateForRun
  |> ignore
};

let clearSceneChildren = () => {
  let scene = unsafeGetScene();
  let engineStateForEdit = StateLogicService.getEngineStateForEdit();
  let engineStateForEdit =
    engineStateForEdit
    |> GameObjectUtils.getChildren(scene)
    |> Js.Array.reduce(
         (engineState, child) =>
           GameObjectComponentEngineService.hasBoxGeometryComponent(child, engineState) ?
             engineState
             |> MainEditorVboBufferTool.passBufferShouldExistCheckWhenDisposeGeometry(
                  GameObjectComponentEngineService.getBoxGeometryComponent(child, engineState)
                ) :
             engineState,
         engineStateForEdit
       );
  engineStateForEdit
  |> GameObjectUtils.disposeGameObjectChildren(scene)
  |> StateLogicService.setEngineStateForEdit;
  let engineStateForRun = StateLogicService.getEngineStateForRun();
  let engineStateForRun =
    engineStateForRun
    |> GameObjectUtils.getChildren(scene)
    |> Js.Array.reduce(
         (engineState, child) =>
           GameObjectComponentEngineService.hasBoxGeometryComponent(child, engineState) ?
             engineState
             |> MainEditorVboBufferTool.passBufferShouldExistCheckWhenDisposeGeometry(
                  GameObjectComponentEngineService.getBoxGeometryComponent(child, engineState)
                ) :
             engineState,
         engineStateForRun
       );
  engineStateForRun
  |> GameObjectUtils.disposeGameObjectChildren(scene)
  |> StateLogicService.setEngineStateForRun
};

let getCurrentGameObjectTransform = () =>
  GameObjectComponentEngineService.getTransformComponent(unsafeGetCurrentGameObject())
  |> StateLogicService.getEngineStateToGetData;

let getCurrentGameObjectMaterial = () =>
  GameObjectComponentEngineService.getBasicMaterialComponent(unsafeGetCurrentGameObject())
  |> StateLogicService.getEngineStateToGetData;

let getCurrentGameObject = () =>
  SceneEditorService.getCurrentGameObject |> StateLogicService.getEditorState;

let setCurrentGameObject = (gameObject) =>
  SceneEditorService.setCurrentGameObject(gameObject) |> StateLogicService.getAndSetEditorState;

let hasCurrentGameObject = () =>
  SceneEditorService.hasCurrentGameObject |> StateLogicService.getEditorState;

let setCameraTobeCurrentGameObject = () =>
  unsafeGetScene()
  |> GameObjectTool.getChildren
  |> Js.Array.filter(
       (gameObject) =>
         CameraEngineService.isCamera(gameObject) |> StateLogicService.getEngineStateToGetData
     )
  |> ArrayService.getFirst
  |> setCurrentGameObject;

let setFirstBoxTobeCurrentGameObject = () =>
  unsafeGetScene()
  |> GameObjectTool.getChildren
  |> Js.Array.filter(
       (gameObject) =>
         ! (CameraEngineService.isCamera(gameObject) |> StateLogicService.getEngineStateToGetData)
     )
  |> ArrayService.getFirst
  |> setCurrentGameObject;

let _createDefaultSceneGameObjects = (engineState) => {
  let (engineState, camera) = CameraEngineService.createCamera(engineState);
  let (engineState, box1) = PrimitiveEngineService.createBox(engineState);
  let (engineState, box2) = PrimitiveEngineService.createBox(engineState);
  let (engineState, box3) = PrimitiveEngineService.createBox(engineState);
  let engineState =
    engineState
    |> GameObjectEngineService.initGameObject(camera)
    |> GameObjectEngineService.initGameObject(box1)
    |> GameObjectEngineService.initGameObject(box2)
    |> GameObjectEngineService.initGameObject(box3);
  (camera, box1, box2, box3, engineState)
};

let prepareDefaultScene = (setCurrentGameObjectFunc) => {
  clearSceneChildren();
  let scene = unsafeGetScene();
  let (camera, box1, box2, box3, engineStateForEdit) =
    _createDefaultSceneGameObjects(StateLogicService.getEngineStateForEdit());
  engineStateForEdit
  |> GameObjectUtils.addChild(scene, camera)
  |> GameObjectUtils.addChild(scene, box1)
  |> GameObjectUtils.addChild(scene, box2)
  |> GameObjectUtils.addChild(scene, box3)
  |> StateLogicService.setEngineStateForEdit;
  let (camera, box1, box2, box3, engineStateForRun) =
    _createDefaultSceneGameObjects(StateLogicService.getEngineStateForRun());
  engineStateForRun
  |> GameObjectUtils.addChild(scene, camera)
  |> GameObjectUtils.addChild(scene, box1)
  |> GameObjectUtils.addChild(scene, box2)
  |> GameObjectUtils.addChild(scene, box3)
  |> StateLogicService.setEngineStateForRun;
  setCurrentGameObjectFunc()
};

let _isBox = (gameObject, engineState) =>
  GameObjectComponentEngineService.hasBoxGeometryComponent(gameObject, engineState);

let getBoxInDefaultScene = (engineState) =>
  GameObjectUtils.getChildren(unsafeGetScene(), engineState)
  |> Js.Array.filter((gameObject) => _isBox(gameObject, engineState))
  |> WonderCommonlib.ArrayService.unsafePop;