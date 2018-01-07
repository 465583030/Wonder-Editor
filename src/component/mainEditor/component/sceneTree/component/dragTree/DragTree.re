open MainEditorSceneTreeType;

Css.importCss("./css/dragTree.css");

external toDomObj : ReactEventRe.Mouse.t => Js.t({..}) = "%identity";

type state = {currentStyle: ReactDOMRe.Style.t};

type action =
  | DragEnter
  | DragLeave;

module Method = {
  let getScene = () => MainEditorStateView.prepareState() |> MainEditorSceneView.getScene;
  let handleDragEnter = (_event) => DragEnter;
  let handleDragLeave = (event) => {
    let e = toDomObj(event);
    e##stopPropagation() |> ignore;
    DragLeave
  };
  let handleDragOver = (event) => {
    let e = toDomObj(event);
    e##preventDefault()
  };
  let handleDrop = (uid, onDropFinish, event) => {
    let e = toDomObj(event);
    onDropFinish(uid, DragUtils.getDragedId(e))
  };
  let _hasSceneGraphChildren = (children) => children |> Js.Array.length > 0;
  let rec renderSceneGraph = (onSelect, onDropFinish, sceneGraphData) =>
    sceneGraphData
    |> Array.map(
         ({uid, name, children}) =>
           _hasSceneGraphChildren(children) ?
             <TreeNode
               key=(DomHelper.getRandomKey())
               uid
               name
               onDropFinish
               onSelect
               treeChildren=(renderSceneGraph(onSelect, onDropFinish, children))
             /> :
             <TreeNode key=(DomHelper.getRandomKey()) uid name onDropFinish onSelect />
       );
};

let component = ReasonReact.reducerComponent("DragTree");

let reducer = (action, state) =>
  switch action {
  | DragEnter =>
    ReasonReact.Update({
      ...state,
      currentStyle:
        ReactUtils.addStyleProp("backgroundColor", "rgba(1,1,1,0.7)", state.currentStyle)
    })
  | DragLeave =>
    ReasonReact.Update({
      ...state,
      currentStyle: ReactUtils.addStyleProp("backgroundColor", "#c0c0c0", state.currentStyle)
    })
  };

let render = (eventHandleTuple, sceneGraphData, {state, reduce}: ReasonReact.self('a, 'b, 'c)) => {
  let (onSelect, onDropFinish) = eventHandleTuple;
  <article className="wonder-drag-tree">
    (ReasonReact.arrayToElement(Method.renderSceneGraph(onSelect, onDropFinish, sceneGraphData)))
    <div
      style=state.currentStyle
      className="wonder-disable-drag"
      onDragEnter=(reduce(Method.handleDragEnter))
      onDragLeave=(reduce(Method.handleDragLeave))
      onDragOver=Method.handleDragOver
      onDrop=(Method.handleDrop(Method.getScene(), onDropFinish))
    />
  </article>
};

let make = (~eventHandleTuple, ~sceneGraphData: array(MainEditorSceneTreeType.treeNode), _children) => {
  ...component,
  initialState: () => {currentStyle: ReactDOMRe.Style.make(~backgroundColor="#c0c0c0", ())},
  reducer,
  render: render(eventHandleTuple, sceneGraphData)
};