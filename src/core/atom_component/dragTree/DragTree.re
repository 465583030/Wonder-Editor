Css.importCss("./css/dragTree.css");

type state = {style: ReactDOMRe.Style.t};

type action =
  | Nothing
  | DragEnter
  | DragLeave
  | DragDrop(int, int);

module Method = {
  let _isIdNotEqual = (startId, targetId) =>
    switch (startId) {
    | None => false
    | Some(startId) => startId !== targetId
    };
  let handleDragEnter = (id, handleSign, handleRelationError, _event) =>
    DragEventBaseUtils.isTriggerDragEnter(id, handleSign, handleRelationError) ?
      DragEnter : Nothing;
  let handleDragLeave = (id, handleSign, handleRelationError, event) => {
    let e = ReactEvent.convertReactMouseEventToJsEvent(event);
    DomHelper.stopPropagation(e);
    DragEventBaseUtils.isTriggerDragLeave(
      id,
      handleSign,
      handleRelationError,
      event,
    ) ?
      DragLeave : Nothing;
  };
  let handleDrop = (uid, handleRelationError, event) => {
    let e = ReactEvent.convertReactMouseEventToJsEvent(event);
    let startId = DragUtils.getDragedUid(e);
    DragEventBaseUtils.isTriggerDragDrop(uid, startId, handleRelationError) ?
      DragLeave : DragDrop(uid, startId);
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
    let (sign, _) =
      StateEditorService.getState()
      |> CurrentDragSourceEditorService.getCurrentDragSource;
    ReasonReact.SideEffects((_self => onDrop((targetId, removedId, sign))));
  | Nothing => ReasonReact.NoUpdate
  };

let render =
    (
      treeArrayData,
      rootUid,
      handleSign,
      handleRelationError,
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
              handleSign,
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
              handleSign,
              handleRelationError,
              _e,
            ),
          )
      )
      onDragOver=DragEventUtils.handleDragOver
      onDrop=(
        _e => send(Method.handleDrop(rootUid, handleRelationError, _e))
      )
    />
  </article>;

let make =
    (
      ~treeArrayData,
      ~rootUid,
      ~onDrop,
      ~handleSign,
      ~handleRelationError,
      _children,
    ) => {
  ...component,
  initialState: () => {
    style: ReactDOMRe.Style.make(~backgroundColor="#c0c0c0", ()),
  },
  reducer: reducer(onDrop),
  render: self =>
    render(treeArrayData, rootUid, handleSign, handleRelationError, self),
};