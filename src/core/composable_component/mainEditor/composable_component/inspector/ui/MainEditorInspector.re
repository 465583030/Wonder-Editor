open EditorType;

type retainedProps = {
  currentSelectSource: option(sourceType),
  currentSceneTreeNode: option(int),
  currentNodeId: option(int)
};

module Method = {
  let showInspectorBySourceType =
      (
        store,
        dispatch,
        allShowComponentConfig,
        (currentSelectSource, currentSceneTreeNode, currentNodeId)
      ) => {
    let editorState = StateEditorService.getState();
    switch currentSelectSource {
    | None => ReasonReact.nullElement
    | Some(SceneTree) =>
      <SceneTreeInspector store dispatch allShowComponentConfig currentSceneTreeNode />
    | Some(AssetTree) =>
      switch currentNodeId {
      | None => ReasonReact.nullElement
      | Some(nodeId) =>
        <AssetTreeInspector
          key=(DomHelper.getRandomKey())
          store
          dispatch
          nodeId
          nodeResult=(
            editorState
            |> AssetNodeMapEditorService.unsafeGetNodeMap
            |> WonderCommonlib.SparseMapService.unsafeGet(nodeId)
          )
        />
      }
    }
  };
};

let component = ReasonReact.statelessComponentWithRetainedProps("MainEditorInspector");

let render = (store, dispatch, allShowComponentConfig, self: ReasonReact.self('a, 'b, 'c)) =>
  <article key="inspector" className="inspector-component">
    (
      Method.showInspectorBySourceType(
        store,
        dispatch,
        allShowComponentConfig,
        (
          self.retainedProps.currentSelectSource,
          self.retainedProps.currentSceneTreeNode,
          self.retainedProps.currentNodeId
        )
      )
    )
  </article>;

let shouldUpdate = ({oldSelf, newSelf}: ReasonReact.oldNewSelf('a, retainedProps, 'c)) =>
  oldSelf.retainedProps != newSelf.retainedProps;

let make = (~store: AppStore.appState, ~dispatch, ~allShowComponentConfig, _children) => {
  ...component,
  retainedProps: {
    currentSelectSource: CurrentSelectSourceEditorService.getCurrentSelectSource |> StateLogicService.getEditorState,
    currentSceneTreeNode:
      SceneEditorService.getCurrentSceneTreeNode |> StateLogicService.getEditorState,
    currentNodeId:
      AssetCurrentNodeIdEditorService.getCurrentNodeId |> StateLogicService.getEditorState
  },
  shouldUpdate,
  render: (self) => render(store, dispatch, allShowComponentConfig, self)
};