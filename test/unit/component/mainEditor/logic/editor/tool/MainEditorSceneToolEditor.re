let unsafeGetCurrentGameObject = () =>
  MainEditorStateView.prepareState() |> MainEditorSceneView.unsafeGetCurrentGameObject;

let clearCurrentGameObject = () =>
  MainEditorStateView.prepareState()
  |> MainEditorSceneView.clearCurrentGameObject
  |> MainEditorStateView.finishState;

let addFakeVboBufferForGameObject = (gameObject) => {
  let engineState = EngineStateView.getEngineState();
  engineState
  |> MainEditorVboBufferToolEngine.passBufferShouldExistCheckWhenDisposeGeometry(
       MainEditorGameObjectAdaptor.getGeometryComponent(gameObject, engineState)
     )
  |> EngineStateView.setEngineState
  |> ignore
};

let getCurrentGameObjectTransform = () => {
  let (_, engineState) = MainEditorStateView.prepareState();
  engineState |> MainEditorGameObjectOper.getTransformComponent(unsafeGetCurrentGameObject())
};

let getCurrentGameObject = () =>
  MainEditorStateView.prepareState() |> MainEditorSceneView.getCurrentGameObject;

let setCurrentGameObject = (gameObject) =>
  MainEditorStateView.prepareState()
  |> MainEditorSceneView.setCurrentGameObject(gameObject)
  |> MainEditorStateView.finishState;

let hasCurrentGameObject = () =>
  MainEditorStateView.prepareState() |> MainEditorSceneView.hasCurrentGameObject;

let setCameraTobeCurrentGameObject = () => {
  let (_, engineState) = MainEditorStateView.prepareState();
  MainEditorSceneToolEngine.unsafeGetScene()
  |> MainEditorSceneToolEngine.getChildren
  |> Js.Array.filter((gameObject) => engineState |> MainEditorCameraOper.isCamera(gameObject))
  |> OperateArrayUtils.getFirst
  |> setCurrentGameObject
};

let setFirstBoxTobeCurrentGameObject = () => {
  let (_, engineState) = MainEditorStateView.prepareState();
  MainEditorSceneToolEngine.unsafeGetScene()
  |> MainEditorSceneToolEngine.getChildren
  |> Js.Array.filter((gameObject) => ! (engineState |> MainEditorCameraOper.isCamera(gameObject)))
  |> OperateArrayUtils.getFirst
  |> setCurrentGameObject
};

let prepareDefaultScene = (setCurrentGameObjectFunc) => {
  MainEditorSceneToolEngine.clearSceneChildren();
  let (editorState, engineState) = MainEditorStateView.prepareState();
  let scene = MainEditorSceneToolEngine.unsafeGetScene();
  let (engineState, camera) = MainEditorCameraOper.createCamera(engineState);
  let (engineState, box1) = MainEditorPrimitiveOper.createBox(engineState);
  let (engineState, box2) = MainEditorPrimitiveOper.createBox(engineState);
  let (engineState, box3) = MainEditorPrimitiveOper.createBox(engineState);
  let engineState =
    engineState
    |> MainEditorGameObjectOper.addChild(scene, camera)
    |> MainEditorGameObjectOper.addChild(scene, box1)
    |> MainEditorGameObjectOper.addChild(scene, box2)
    |> MainEditorGameObjectOper.addChild(scene, box3);
  let engineState =
    engineState
    |> MainEditorGameObjectAdaptor.initGameObject(camera)
    |> MainEditorGameObjectAdaptor.initGameObject(box1)
    |> MainEditorGameObjectAdaptor.initGameObject(box2)
    |> MainEditorGameObjectAdaptor.initGameObject(box3);
  (editorState, engineState) |> MainEditorStateView.finishState;
  setCurrentGameObjectFunc()
};