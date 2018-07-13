let _prepareSpecificGameObjectsForEditEngineState = editEngineState => {
  let scene = MainEditorSceneTool.unsafeGetScene();
  let (engineState, camera) =
    CameraEngineService.createCamera(editEngineState);
  let (engineState, box) = PrimitiveEngineService.createBox(engineState);

  engineState
  |> GameObjectUtils.addChild(scene, camera)
  |> GameObjectUtils.addChild(scene, box);
};

let _buildThreeLayerSceneGraphToTargetEngine = engineState => {
  let scene = MainEditorSceneTool.unsafeGetScene();
  let (engineState, box1) = PrimitiveEngineService.createBox(engineState);
  let (engineState, box2) = PrimitiveEngineService.createBox(engineState);
  let (engineState, box3) = PrimitiveEngineService.createBox(engineState);
  let (engineState, box4) = PrimitiveEngineService.createBox(engineState);

  engineState
  |> GameObjectUtils.addChild(scene, box1)
  |> GameObjectUtils.addChild(box1, box4)
  |> GameObjectUtils.addChild(scene, box2)
  |> GameObjectUtils.addChild(scene, box3);
};

let buildThreeLayerSceneGraphToEngine = () => {
  let (editorState, editEngineState) =
    StateLogicService.getEditEngineState()
    |> _prepareSpecificGameObjectsForEditEngineState
    |> DefaultSceneUtils.computeDiffValue(StateEditorService.getState());

  editEngineState
  |> _buildThreeLayerSceneGraphToTargetEngine
  |> StateLogicService.setEditEngineState;

  editorState |> StateEditorService.setState |> ignore;

  StateLogicService.getRunEngineState()
  |> _buildThreeLayerSceneGraphToTargetEngine
  |> StateLogicService.setRunEngineState;
};

let _buildFourLayerSceneGraphToTargetEngine = engineState => {
  let scene = MainEditorSceneTool.unsafeGetScene();
  let (engineState, box1) = PrimitiveEngineService.createBox(engineState);
  let (engineState, box2) = PrimitiveEngineService.createBox(engineState);
  let (engineState, box3) = PrimitiveEngineService.createBox(engineState);
  let (engineState, box4) = PrimitiveEngineService.createBox(engineState);

  engineState
  |> GameObjectUtils.addChild(scene, box1)
  |> GameObjectUtils.addChild(box1, box3)
  |> GameObjectUtils.addChild(box3, box4)
  |> GameObjectUtils.addChild(scene, box2);
};

let buildFourLayerSceneGraphToEngine = () => {
  let (editorState, editEngineState) =
    StateLogicService.getEditEngineState()
    |> _prepareSpecificGameObjectsForEditEngineState
    |> DefaultSceneUtils.computeDiffValue(StateEditorService.getState());

  editEngineState
  |> _buildFourLayerSceneGraphToTargetEngine
  |> StateLogicService.setEditEngineState;
  editorState |> StateEditorService.setState |> ignore;

  StateLogicService.getRunEngineState()
  |> _buildFourLayerSceneGraphToTargetEngine
  |> StateLogicService.setRunEngineState;
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