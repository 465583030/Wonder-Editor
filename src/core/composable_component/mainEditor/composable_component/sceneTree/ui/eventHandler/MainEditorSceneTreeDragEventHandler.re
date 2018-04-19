module DragEventHandler = {
  include EmptyEventHandler.EmptyEventHandler;
  type prepareTuple = unit;
  type dataTuple = (Wonderjs.GameObjectType.gameObject, Wonderjs.GameObjectType.gameObject);
  let onDrop = ((store, dispatch), (), (targetUid, dragedUid)) =>
    SceneTreeUtils.isGameObjectRelationError(targetUid, dragedUid)
    |> StateLogicService.getEngineStateToGetData ?
      dispatch(AppStore.ReLoad) |> ignore :
      {
        GameObjectUtils.setParentKeepOrder
        |> StateLogicService.getAndRefreshEngineStateWithDiff(
          [|
             targetUid,
             dragedUid
          |],
             DiffType.GameObject
           );
        dispatch(
          AppStore.SceneTreeAction(
            SetSceneGraph(
              Some(
                SceneTreeUtils.getDragedSceneGraphData(
                  targetUid,
                  dragedUid,
                  store |> SceneTreeStoreUtils.unsafeGetSceneGraphDataFromStore
                )
              )
            )
          )
        )
      }
      |> ignore;
};

module MakeEventHandler = EventHandler.MakeEventHandler(DragEventHandler);