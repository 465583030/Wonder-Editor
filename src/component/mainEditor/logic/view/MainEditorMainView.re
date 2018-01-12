open EditorStateDataTypeEdit;

let _initEditor = MainEditorMainBuss.initEditor;

let _init = (editorState: editorState) => {
  let engineState = MainEditorMainBuss.initEngineMain();
  let (editorState, engineState) = _initEditor((editorState, engineState));
  let engineState = MainEditorMainBuss.initEngineDirector(engineState);
  (editorState, engineState)
};

let _loop = (stateTuple) => {
  /* todo save loop id */
  let rec _loopRequest = (time: float, stateTuple) =>
    DomHelper.requestAnimationFrame(
      (time: float) => {
        let (editorState, engineState) = stateTuple |> MainEditorMainBuss.loopBody(time);
        let editorState = MainEditorMainBuss.setEditorState(editorState);
        _loopRequest(time, (editorState, engineState)) |> ignore
      }
    );
  stateTuple |> _loopRequest(0.) |> ignore
};

let start = () => {
  let (editorState, engineState) = MainEditorMainBuss.getEditorState() |> _init;
  (editorState, engineState) |> _loop;
  (
    editorState |> MainEditorMainBuss.setEditorState,
    engineState |> MainEditorMainBuss.setEngineState
  )
};