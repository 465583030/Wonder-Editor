let unsafeGetScene = () => SceneEditorService.unsafeGetScene |> StateLogicService.getEditorState;

let setCameraTobeCurrentGameObject = () =>
  unsafeGetScene()
  |> GameObjectTool.getChildren
  |> Js.Array.filter(
       (gameObject) =>
         CameraEngineService.isCamera(gameObject) |> StateLogicService.getEngineStateToGetData
     )
  |> ArrayService.getFirst
  |> GameObjectTool.setCurrentGameObject;

let getBoxByIndex = (index, engineState) =>
  engineState
  |> GameObjectUtils.getChildren(unsafeGetScene())
  |> Js.Array.filter((gameObject) => ! CameraEngineService.isCamera(gameObject, engineState))
  |> ArrayService.getNth(index);

let setFirstBoxTobeCurrentGameObject = () =>
  getBoxByIndex(0, StateLogicService.getRunEngineState()) |> GameObjectTool.setCurrentGameObject;

let initStateAndGl = (sandbox) => {
  TestTool.initEditorAndEngineStateAndInitScene(sandbox);
  TestToolEngine.setFakeGl(sandbox);
  AllMaterialToolEngine.prepareForInit()
};

let createDefaultScene = (sandbox, setCurrentGameObjectFunc) => {
  let scene = unsafeGetScene();
  let editorState = StateEditorService.getState();
  let editEngineState = StateLogicService.getEditEngineState();
  let (editEngineState, box) =
    editEngineState |> DefaultSceneUtils.prepareSpecificGameObjectsForEditEngineState(scene);
  let (editorState, editEngineState) =
    editEngineState |> DefaultSceneUtils.computeDiffValue(editorState);
  let (editEngineState, camera) = editEngineState |> DefaultSceneUtils.createDefaultScene(scene);
  editorState |> StateEditorService.setState |> ignore;
  editEngineState
  |> GameObjectUtils.setParentKeepOrder(camera, box)
  |> FakeGlToolEngine.setFakeGl(FakeGlToolEngine.buildFakeGl(~sandbox, ()))
  |> StateLogicService.setEditEngineState;
  let (engineState, _) =
    StateLogicService.getRunEngineState() |> DefaultSceneUtils.createDefaultScene(scene);
  engineState
  |> FakeGlToolEngine.setFakeGl(FakeGlToolEngine.buildFakeGl(~sandbox, ()))
  |> StateLogicService.setRunEngineState;
  setCurrentGameObjectFunc()
};

let _isBox = (gameObject, engineState) =>
  GameObjectComponentEngineService.hasBoxGeometryComponent(gameObject, engineState);

let getBoxInDefaultScene = (engineState) =>
  GameObjectUtils.getChildren(unsafeGetScene(), engineState)
  |> Js.Array.filter((gameObject) => _isBox(gameObject, engineState))
  |> WonderCommonlib.ArrayService.unsafePop;