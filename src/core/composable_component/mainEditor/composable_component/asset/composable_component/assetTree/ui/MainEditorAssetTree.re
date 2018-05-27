open AssetNodeType;

open AssetTreeNodeType;

module Method = {
  let handleSign = (startSign) =>
    startSign === AssetTreeUtils.getSign()
    || startSign === MainEditorAssetChildrenNode.Method.getSign();
  let onDrop = (dispatch, (targetId, removedId, currentDragSource)) => {
    WonderLog.Log.print(currentDragSource) |> ignore;
    switch currentDragSource {
    | sign
        when
          sign === MainEditorAssetChildrenNode.Method.getSign()
          || sign === AssetTreeUtils.getSign() =>
      let editorState = StateEditorService.getState();
      AssetUtils.isIdEqual(targetId, removedId) ?
        dispatch(AppStore.ReLoad) :
        {
          let (newAssetTree, removedTreeNode) =
            editorState
            |> AssetTreeRootEditorService.unsafeGetAssetTreeRoot
            |> AssetUtils.removeSpecificTreeNodeFromAssetTree(removedId);
          editorState
          |> AssetTreeRootEditorService.setAssetTreeRoot(
               AssetUtils.insertNewTreeNodeToTargetTreeNode(
                 targetId,
                 removedTreeNode,
                 newAssetTree
               )
             )
          |> StateEditorService.setState;
          dispatch(AppStore.ReLoad)
        }
    | _ => WonderLog.Log.log({j|can't drop to assetTree|j})
    }
  };
  let _isSelected = (currentNodeParentId, id) =>
    AssetUtils.getTargetTreeNodeId(currentNodeParentId) |> StateLogicService.getEditorState === id ?
      true : false;
  let _isActive = (currentNodeParentId) =>
    switch (AssetCurrentNodeIdEditorService.getCurrentNodeId |> StateLogicService.getEditorState) {
    | None => false
    | Some(currentNodeId) =>
      AssetUtils.isIdEqual(
        AssetUtils.getTargetTreeNodeId(currentNodeParentId) |> StateLogicService.getEditorState,
        currentNodeId
      ) ?
        true : false
    };
  let _isNotRoot = (uid) =>
    ((editorState) => editorState |> AssetTreeRootEditorService.getRootTreeNodeId != uid)
    |> StateLogicService.getEditorState;
  let buildAssetTreeNodeArray = (currentNodeParentId, onSelect, onDrop, assetTreeRoot) => {
    let rec _iterateAssetTreeArray = (onSelect, onDrop, assetTreeArray) =>
      assetTreeArray
      |> Array.map(
           ({id, children}: assetTreeNodeType) => {
             let nodeResult =
               StateEditorService.getState()
               |> AssetNodeMapEditorService.unsafeGetNodeMap
               |> WonderCommonlib.SparseMapService.unsafeGet(id);
             switch nodeResult.type_ {
             | Folder =>
               ArrayService.hasItem(children) ?
                 <TreeNode
                   key=(DomHelper.getRandomKey())
                   attributeTuple=(
                     id,
                     nodeResult.name,
                     _isSelected(currentNodeParentId, id),
                     _isActive(currentNodeParentId)
                   )
                   eventHandleTuple=(
                     onSelect,
                     onDrop,
                     handleSign,
                     AssetUtils.isTreeNodeRelationError
                   )
                   sign=(AssetTreeUtils.getSign())
                   icon="./public/img/12.jpg"
                   dragable=(_isNotRoot(id))
                   treeChildren=(_iterateAssetTreeArray(onSelect, onDrop, children))
                 /> :
                 <TreeNode
                   key=(DomHelper.getRandomKey())
                   attributeTuple=(
                     id,
                     nodeResult.name,
                     _isSelected(currentNodeParentId, id),
                     _isActive(currentNodeParentId)
                   )
                   eventHandleTuple=(
                     onSelect,
                     onDrop,
                     handleSign,
                     AssetUtils.isTreeNodeRelationError
                   )
                   sign=(AssetTreeUtils.getSign())
                   icon="./public/img/12.jpg"
                   dragable=(_isNotRoot(id))
                 />
             | _ => ReasonReact.nullElement
             }
           }
         );
    _iterateAssetTreeArray(onSelect, onDrop, [|assetTreeRoot|])
  };
};

let component = ReasonReact.statelessComponent("AssetTree");

let render = (store, dispatch, currentNodeParentId, setNodeParentId, _self) =>
  <article key="assetTreeRoot" className="tree-content">
    (
      ReasonReact.arrayToElement(
        (
          (editorState) =>
            editorState
            |> AssetTreeRootEditorService.unsafeGetAssetTreeRoot
            |> Method.buildAssetTreeNodeArray(
                 currentNodeParentId,
                 AssetTreeUtils.onSelect(dispatch, setNodeParentId),
                 Method.onDrop(dispatch)
               )
        )
        |> StateLogicService.getEditorState
      )
    )
  </article>;

let make =
    (~store: AppStore.appState, ~dispatch, ~currentNodeParentId, ~setNodeParentId, _children) => {
  ...component,
  render: (self) => render(store, dispatch, currentNodeParentId, setNodeParentId, self)
};