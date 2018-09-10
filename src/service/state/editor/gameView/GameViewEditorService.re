open EditorType;

let getViewRect = editorState => editorState.gameViewRecord.viewRect;

let unsafeGetViewRect = editorState =>
  getViewRect(editorState) |> OptionService.unsafeGet;

let updateViewRect = (x, y, width, height, editorState) => {
  ...editorState,
  gameViewRecord: {
    ...editorState.gameViewRecord,
    viewRect: Some((x, y, width, height)),
  },
};

let getActivedBasicCameraView = editorState =>
  editorState.gameViewRecord.activedBasicCameraView;

let setActivedBasicCameraView = (basicCameraView, editorState) => {
  ...editorState,
  gameViewRecord: {
    ...editorState.gameViewRecord,
    activedBasicCameraView: Some(basicCameraView),
  },
};