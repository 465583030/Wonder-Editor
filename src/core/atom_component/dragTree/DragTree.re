Css.importCss("./css/dragTree.css");

type state = {style: ReactDOMRe.Style.t};

type action =
  | Nothing
  | DragEnter
  | DragLeave
  | DragDrop(int, int);

module Method = {
  let handleDragEnter = (id, handleFlag, handleRelationError, _event) =>
    DragEventBaseUtils.isTriggerDragEnter(id, handleFlag, handleRelationError) ?
      DragEnter : Nothing;

  let handleDragLeave = (id, handleFlag, handleRelationError, event) => {
    let e = ReactEvent.convertReactMouseEventToJsEvent(event);
    DomHelper.stopPropagation(e);
    DragEventBaseUtils.isTriggerDragLeave(id, handleFlag, handleRelationError) ?
      DragLeave : Nothing;
  };

  let handleDrop = (uid, handleFlag, handleRelationError, event) => {
    let e = ReactEvent.convertReactMouseEventToJsEvent(event);
    let startId = DragUtils.getDragedUid(e);
    DragEventBaseUtils.isTriggerDragDrop(
      uid,
      startId,
      handleFlag,
      handleRelationError,
    ) ?
      DragDrop(uid, startId) : DragLeave;
  };
};

let component = ReasonReact.reducerComponent("DragTree");

let reducer = (onDrop, action, state) =>
  switch (action) {
  | DragEnter =>
    ReasonReact.Update({
      ...state,
      style:
        ReactUtils.addStyleProp(
          "backgroundColor",
          "rgba(0,0,1,1.0)",
          state.style,
        ),
    })

  | DragLeave =>
    ReasonReact.Update({
      ...state,
      style:
        ReactUtils.addStyleProp("backgroundColor", "#c0c0c0", state.style),
    })

  | DragDrop(targetId, removedId) =>
    let (flag, _) =
      StateEditorService.getState()
      |> CurrentDragSourceEditorService.getCurrentDragSource;

    ReasonReactUtils.sideEffects(() => onDrop((targetId, removedId, flag)));

  | Nothing => ReasonReact.NoUpdate
  };

let render =
    (
      treeArrayData,
      rootUid,
      (handleFlag, handleRelationError),
      {state, send}: ReasonReact.self('a, 'b, 'c),
    ) =>
  <article className="wonder-drag-tree">
    (ReasonReact.arrayToElement(treeArrayData))
    <div
      style=state.style
      className="wonder-disable-drag"
      onDragEnter=(
        _e =>
          send(
            Method.handleDragEnter(
              rootUid,
              handleFlag,
              handleRelationError,
              _e,
            ),
          )
      )
      onDragLeave=(
        _e =>
          send(
            Method.handleDragLeave(
              rootUid,
              handleFlag,
              handleRelationError,
              _e,
            ),
          )
      )
      onDragOver=DragEventUtils.handleDragOver
      onDrop=(
        _e =>
          send(
            Method.handleDrop(rootUid, handleFlag, handleRelationError, _e),
          )
      )
    />
  </article>;

let make =
    (
      ~treeArrayData,
      ~rootUid,
      ~onDrop,
      ~handleFlag,
      ~handleRelationError,
      _children,
    ) => {
  ...component,
  initialState: () => {
    style: ReactDOMRe.Style.make(~backgroundColor="#c0c0c0", ()),
  },
  reducer: reducer(onDrop),
  render: self =>
    render(treeArrayData, rootUid, (handleFlag, handleRelationError), self),
};