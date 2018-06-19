open AssetNodeType;

type state = {style: ReactDOMRe.Style.t};

type retainedProps = {
  color: string,
  map: option(int),
};

type action =
  | Nothing
  | DragEnter
  | DragLeave
  | DragEnd
  | DragDrop(int);

module Method = {
  let handleFlag = startFlag =>
    switch (startFlag) {
    | None => false
    | Some(flag) => flag == AssetTreeUtils.getFlag()
    };

  let _getNodeResultFromNodeMap = (id, editorState) =>
    editorState
    |> AssetNodeMapEditorService.unsafeGetNodeMap
    |> WonderCommonlib.SparseMapService.unsafeGet(id);

  let handleTypeValid = (startId, editorState) =>
    switch (startId) {
    | None => false
    | Some(id) =>
      editorState
      |> _getNodeResultFromNodeMap(id)
      |> (({type_}) => type_ == AssetNodeType.Texture)
    };

  let setMaterialColor = MainEditorMaterialMarkRedoUndoEventHandler.MakeEventHandler.onMarkRedoUndoByLastStack;

  let onDrop = (dispatchFunc, startId, materialComponent) => {
    StateEditorService.getState()
    |> _getNodeResultFromNodeMap(startId)
    |> (
      ({name, type_, result}) =>
        /* TODO use texture diff(now is 0) */
        /* WonderLog.Log.print("drop start") |> ignore; */
        BasicMaterialEngineService.setMap(
          result |> OptionService.unsafeGet |> int_of_string,
          materialComponent,
        )
        |> StateLogicService.getAndRefreshEditAndRunEngineState
        /* WonderLog.Log.print("drop end") |> ignore; */
    );
    dispatchFunc(AppStore.ReLoad);
  };

  let _isTriggerEvent = (handleFlagFunc, handleTypeValidFunc) => {
    let editorState = StateEditorService.getState();
    let (flag, startId) =
      editorState |> CurrentDragSourceEditorService.getCurrentDragSource;

    handleFlagFunc(flag) && handleTypeValidFunc(startId, editorState);
  };

  let handleDragEnter = (handleFlagFunc, handleTypeValidFunc, _event) =>
    _isTriggerEvent(handleFlagFunc, handleTypeValidFunc) ?
      DragEnter : Nothing;

  let handleDragLeave = (handleFlagFunc, handleTypeValidFunc, event) => {
    let e = ReactEvent.convertReactMouseEventToJsEvent(event);
    DomHelper.stopPropagation(e);
    _isTriggerEvent(handleFlagFunc, handleTypeValidFunc) ?
      DragLeave : Nothing;
  };

  let handleDragOver = event => {
    let e = ReactEvent.convertReactMouseEventToJsEvent(event);
    DomHelper.preventDefault(e);
  };

  let handleDrop = (handleFlagFunc, handleTypeValidFunc, event) => {
    let e = ReactEvent.convertReactMouseEventToJsEvent(event);
    let startId = DragUtils.getDragedUid(e);
    _isTriggerEvent(handleFlagFunc, handleTypeValidFunc) ?
      DragDrop(startId) : DragLeave;
  };

  let handleDrageEnd = _event => {
    CurrentDragSourceEditorService.clearCurrentDragSource
    |> StateLogicService.getAndSetEditorState;
    DragEnd;
  };
};

let component =
  ReasonReact.reducerComponentWithRetainedProps("MainEditorBasicMaterial");

let reducer = (dispatchFunc, materialComponent, action, state) =>
  switch (action) {
  | DragEnter =>
    ReasonReact.Update({
      ...state,
      style:
        ReactUtils.addStyleProp("border", "2px dashed blue", state.style),
    })

  | DragLeave =>
    ReasonReact.Update({
      ...state,
      style: ReactUtils.addStyleProp("border", "1px solid red", state.style),
    })

  | DragEnd =>
    ReasonReact.Update({
      ...state,
      style:
        ReactUtils.addStyleProp("opacity", "1", state.style)
        |> ReactUtils.addStyleProp("border", "1px solid red"),
    })

  | DragDrop(startId) =>
    ReasonReactUtils.sideEffects(() =>
      Method.onDrop(dispatchFunc, startId, materialComponent)
    )

  | Nothing => ReasonReact.NoUpdate
  };

let render =
    (
      (store, dispatchFunc),
      materialComponent,
      {state, retainedProps, send}: ReasonReact.self('a, 'b, 'c),
    ) =>
  <article className="wonder-inspector-material">
    <StringInput
      defaultValue=retainedProps.color
      label="color"
      onBlur=(
        Method.setMaterialColor((store, dispatchFunc), materialComponent)
      )
    />
    <div className="material-texture" style=state.style>
      <div
        className="texture_ground"
        onDragEnd=(_e => send(Method.handleDrageEnd(_e)))
        onDragEnter=(
          _e =>
            send(
              Method.handleDragEnter(
                Method.handleFlag,
                Method.handleTypeValid,
                _e,
              ),
            )
        )
        onDragLeave=(
          _e =>
            send(
              Method.handleDragLeave(
                Method.handleFlag,
                Method.handleTypeValid,
                _e,
              ),
            )
        )
        onDragOver=Method.handleDragOver
        onDrop=(
          _e =>
            send(
              Method.handleDrop(
                Method.handleFlag,
                Method.handleTypeValid,
                _e,
              ),
            )
        )
      />
      <span className=""> (DomHelper.textEl("texture:")) </span>
      (
        switch (retainedProps.map) {
        | None => <img src="./public/img/null.jpg" />
        | Some(map) =>
          WonderLog.Log.print(("map", map)) |> ignore;
          ReasonReact.nullElement;
        }
      )
    </div>
  </article>;

let shouldUpdate =
    ({oldSelf, newSelf}: ReasonReact.oldNewSelf('a, retainedProps, 'c)) =>
  oldSelf.retainedProps != newSelf.retainedProps
  || oldSelf.state != newSelf.state;

let make =
    (~store: AppStore.appState, ~dispatchFunc, ~materialComponent, _children) => {
  ...component,
  retainedProps: {
    let color =
      BasicMaterialEngineService.getColor(materialComponent)
      |> StateLogicService.getEngineStateToGetData;
    let map =
      BasicMaterialEngineService.getMap(materialComponent)
      |> StateLogicService.getEngineStateToGetData;
    WonderLog.Log.print(map) |> ignore;
    {color: "#ffffff", map};
  },
  initialState: () => {style: ReactDOMRe.Style.make(~opacity="1", ())},
  reducer: reducer(dispatchFunc, materialComponent),
  shouldUpdate,
  render: self => render((store, dispatchFunc), materialComponent, self),
};