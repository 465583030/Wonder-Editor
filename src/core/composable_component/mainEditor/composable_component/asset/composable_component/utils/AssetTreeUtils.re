let getFlag = () => EditorType.AssetTree;

let handleFlag = startFlag => {
  WonderLog.Log.print(startFlag) |> ignore;
  switch (startFlag) {
  | None => false
  | Some(startFlag) => startFlag === getFlag()
  };
};

let onSelect = (dispatchFunc, nodeId) => {
  (
    editorState =>
      editorState
      |> CurrentNodeEditorService.clearCurrentNode
      |> AssetCurrentNodeIdEditorService.setCurrentNodeId(nodeId)
      |> AssetCurrentNodeParentIdEditorService.setCurrentNodeParentId(nodeId)
      |> CurrentSelectSourceEditorService.setCurrentSelectSource(
           EditorType.AssetTree,
         )
  )
  |> StateLogicService.getAndSetEditorState;

  dispatchFunc(AppStore.ReLoad);
};

let onDrop = (dispatchFunc, (targetId, removedId, currentDragSource)) =>
  switch (currentDragSource) {
  | None => WonderLog.Log.warn({j|can't drop to assetTree|j})
  | Some(flag) =>
    flag === getFlag() ?
      {
        let editorState = StateEditorService.getState();
        AssetUtils.isIdEqual(targetId, removedId) ?
          dispatchFunc(AppStore.ReLoad) :
          {
            let (newAssetTreeRoot, removedTreeNode) =
              editorState
              |> AssetTreeRootEditorService.unsafeGetAssetTreeRoot
              |> AssetUtils.removeSpecificTreeNode(removedId);
            newAssetTreeRoot
            |> AssetUtils.insertSourceTreeNodeToTargetTreeNodeChildren(
                 targetId,
                 removedTreeNode,
               )
            |. AssetTreeRootEditorService.setAssetTreeRoot(editorState)
            |> StateEditorService.setState
            |> ignore;
            dispatchFunc(AppStore.ReLoad);
          };
      } :
      WonderLog.Log.warn({j|can't drop to assetTree|j})
  };