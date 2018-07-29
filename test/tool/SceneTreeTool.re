let _prepareSpecificGameObjectsForEditEngineState = editEngineState => {
  let editorState = None;
  let scene = MainEditorSceneTool.unsafeGetScene();
  let (editorState, engineState, camera) =
    CameraEngineService.createCamera(editorState, editEngineState);
  let (editorState, engineState, box) =
    PrimitiveEngineService.createBox(editorState, engineState);

  engineState
  |> GameObjectUtils.addChild(scene, camera)
  |> GameObjectUtils.addChild(scene, box);
};

let _buildTwoCameraSceneGraphToTargetEngine = (editorState, engineState) => {
  let scene = MainEditorSceneTool.unsafeGetScene();
  let (editorState, engineState, camera1) =
    CameraEngineService.createCamera(editorState, engineState);
  let (editorState, engineState, camera2) =
    CameraEngineService.createCamera(editorState, engineState);
  let (editorState, engineState, box1) =
    PrimitiveEngineService.createBox(editorState, engineState);

  (
    camera1,
    camera2,
    box1,
    editorState,
    engineState
    |> GameObjectUtils.addChild(scene, camera1)
    |> GameObjectUtils.addChild(scene, camera2)
    |> GameObjectUtils.addChild(scene, box1),
  );
};

let buildTwoCameraSceneGraphToEngine = () => {
  let (editorState, editEngineState) =
    StateLogicService.getEditEngineState()
    |> _prepareSpecificGameObjectsForEditEngineState
    |> DefaultSceneUtils.computeDiffValue(StateEditorService.getState());

  let (camera1, camera2, box1, _editorStateForDefaultScene, editEngineState) =
    editEngineState |> _buildTwoCameraSceneGraphToTargetEngine(None);

  editEngineState |> StateLogicService.setEditEngineState;

  let (camera1, camera2, box1, editorStateForDefaultScene, runEngineState) =
    StateLogicService.getRunEngineState()
    |> _buildTwoCameraSceneGraphToTargetEngine(editorState |. Some);

  runEngineState |> StateLogicService.setRunEngineState;

  editorStateForDefaultScene
  |> OptionService.unsafeGet
  |> StateEditorService.setState
  |> ignore;

  (camera1, camera2, box1);
};

let _buildThreeLayerSceneGraphToTargetEngine = (editorState, engineState) => {
  let scene = MainEditorSceneTool.unsafeGetScene();
  let (editorState, engineState, box1) =
    PrimitiveEngineService.createBox(editorState, engineState);
  let (editorState, engineState, box2) =
    PrimitiveEngineService.createBox(editorState, engineState);
  let (editorState, engineState, box3) =
    PrimitiveEngineService.createBox(editorState, engineState);
  let (editorState, engineState, box4) =
    PrimitiveEngineService.createBox(editorState, engineState);

  (
    editorState,
    engineState
    |> GameObjectUtils.addChild(scene, box1)
    |> GameObjectUtils.addChild(box1, box4)
    |> GameObjectUtils.addChild(scene, box2)
    |> GameObjectUtils.addChild(scene, box3),
  );
};

let buildThreeLayerSceneGraphToEngine = () => {
  let (editorState, editEngineState) =
    StateLogicService.getEditEngineState()
    |> _prepareSpecificGameObjectsForEditEngineState
    |> DefaultSceneUtils.computeDiffValue(StateEditorService.getState());

  let (_editorStateForDefaultScene, editEngineState) =
    editEngineState |> _buildThreeLayerSceneGraphToTargetEngine(None);

  editEngineState |> StateLogicService.setEditEngineState;

  let (editorStateForDefaultScene, runEngineState) =
    StateLogicService.getRunEngineState()
    |> _buildThreeLayerSceneGraphToTargetEngine(editorState |. Some);

  runEngineState |> StateLogicService.setRunEngineState;

  editorStateForDefaultScene
  |> OptionService.unsafeGet
  |> StateEditorService.setState
  |> ignore;
};

let _buildFourLayerSceneGraphToTargetEngine = (editorState, engineState) => {
  let scene = MainEditorSceneTool.unsafeGetScene();
  let (editorState, engineState, box1) =
    PrimitiveEngineService.createBox(editorState, engineState);
  let (editorState, engineState, box2) =
    PrimitiveEngineService.createBox(editorState, engineState);
  let (editorState, engineState, box3) =
    PrimitiveEngineService.createBox(editorState, engineState);
  let (editorState, engineState, box4) =
    PrimitiveEngineService.createBox(editorState, engineState);
  (
    box1,
    box2,
    box3,
    box4,
    editorState,
    engineState
    |> GameObjectUtils.addChild(scene, box1)
    |> GameObjectUtils.addChild(box1, box3)
    |> GameObjectUtils.addChild(box3, box4)
    |> GameObjectUtils.addChild(scene, box2),
  );
};

let buildFourLayerSceneGraphToEngine = () => {
  let (editorState, editEngineState) =
    StateLogicService.getEditEngineState()
    |> _prepareSpecificGameObjectsForEditEngineState
    |> DefaultSceneUtils.computeDiffValue(StateEditorService.getState());

  let (box1, box2, box3, box4, _editorStateForDefaultScene, editEngineState) =
    editEngineState |> _buildFourLayerSceneGraphToTargetEngine(None);

  editEngineState |> StateLogicService.setEditEngineState;

  let (box1, box2, box3, box4, editorStateForDefaultScene, runEngineState) =
    StateLogicService.getRunEngineState()
    |> _buildFourLayerSceneGraphToTargetEngine(editorState |. Some);

  runEngineState |> StateLogicService.setRunEngineState;

  editorStateForDefaultScene
  |> OptionService.unsafeGet
  |> StateEditorService.setState
  |> ignore;

  (box1, box2, box3, box4);
};

let clearCurrentGameObjectAndSetTreeSpecificGameObject = clickTreeNodeIndex => {
  SceneEditorService.clearCurrentSceneTreeNode
  |> StateLogicService.getAndSetEditorState;

  let component =
    BuildComponentTool.buildSceneTree(
      TestTool.buildAppStateSceneGraphFromEngine(),
    );

  BaseEventTool.triggerComponentEvent(
    component,
    SceneTreeEventTool.triggerClickEvent(clickTreeNodeIndex),
  );
};

let buildFourLayerSceneAndGetBox = () => {
  let (box1, box2, box3, box4) = buildFourLayerSceneGraphToEngine();

  let firstLayerFirstCubeDomIndex =
    SceneTreeNodeDomTool.OperateFourLayer.getFirstLayerFirstCubeDomIndex();

  clearCurrentGameObjectAndSetTreeSpecificGameObject(
    firstLayerFirstCubeDomIndex,
  );

  (box1, box2, box3, box4);
};