open CurrentNodeDataType;

module CustomEventHandler = {
  include EmptyEventHandler.EmptyEventHandler;
  type prepareTuple = unit;
  type dataTuple = unit;

  let _isRemoveAssetTreeNode = (currentNodeId, currentNodeParentId) =>
    AssetTreeEditorService.isIdEqual(currentNodeParentId, currentNodeId);

  let handleSelfLogic = ((store, dispatchFunc), (), ()) => {
    let editorState = StateEditorService.getState();
    let engineState = StateEngineService.unsafeGetState();

    let {currentNodeId} =
      editorState |> AssetCurrentNodeDataEditorService.unsafeGetCurrentNodeData;
    let (newAssetTreeRoot, removedTreeNode) =
      editorState
      |> AssetTreeRootEditorService.unsafeGetAssetTreeRoot
      |> RemoveNodeAssetTreeAssetEditorService.removeSpecificTreeNode(
           currentNodeId,
         );

    let ((editorState, engineState), removedAssetIdArr) =
      (editorState, engineState)
      |> RemoveNodeAssetTreeAssetEditorService.deepRemoveTreeNode(
           removedTreeNode,
         );

    StateLogicService.refreshEngineState(engineState);

    let editorState =
      editorState
      |> AssetRemovedAssetIdArrayEditorService.getRemovedAssetIdArray
      |> Js.Array.concat(removedAssetIdArr)
      |. AssetRemovedAssetIdArrayEditorService.setRemovedAssetIdArray(
           editorState,
         );

    let editorState =
      _isRemoveAssetTreeNode(
        currentNodeId,
        AssetTreeUtils.getTargetTreeNodeId(editorState),
      ) ?
        editorState
        |> AssetCurrentNodeParentIdEditorService.clearCurrentNodeParentId
        |> AssetTreeRootEditorService.setAssetTreeRoot(newAssetTreeRoot)
        |> AssetCurrentNodeDataEditorService.clearCurrentNodeData :
        editorState
        |> AssetTreeRootEditorService.setAssetTreeRoot(newAssetTreeRoot)
        |> AssetCurrentNodeDataEditorService.clearCurrentNodeData;

    editorState |> StateEditorService.setState |> ignore;

    dispatchFunc(
      AppStore.SceneTreeAction(
        SetSceneGraph(
          Some(
            SceneTreeUtils.getSceneGraphDataFromEngine
            |> StateLogicService.getStateToGetData,
          ),
        ),
      ),
    )
    |> ignore;

    dispatchFunc(AppStore.UpdateAction(Update([|All|]))) |> ignore;
  };
};

module MakeEventHandler = EventHandler.MakeEventHandler(CustomEventHandler);