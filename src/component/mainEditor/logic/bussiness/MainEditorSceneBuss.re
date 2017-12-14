let getCurrentGameObject = (stateTuple) => {
  let (editorState, engineState) = stateTuple;
  let scene = editorState |> MainEditorSceneEdit.getScene;
  let currentGameObject =
    engineState
    |> MainEditorGameObjectOper.getChildren(scene)
    |> Js.Array.filter((gameObject) => ! MainEditorCameraOper.isCamera(gameObject, engineState))
    |> ArrayOperUtil.getFirst;
  (editorState, engineState, currentGameObject)
};