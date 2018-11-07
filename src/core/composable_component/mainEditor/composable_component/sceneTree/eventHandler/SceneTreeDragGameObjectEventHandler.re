module CustomEventHandler = {
  include EmptyEventHandler.EmptyEventHandler;

  type prepareTuple = unit;
  type dataTuple = (
    Wonderjs.GameObjectType.gameObject,
    Wonderjs.GameObjectType.gameObject,
  );

  let handleSelfLogic = ((store, dispatchFunc), (), (targetUid, dragedUid)) => {
    let isShowChildrenMap =
      (
        switch (store |> StoreUtils.getSceneGraphDataFromStore) {
        | None => [||]
        | Some(sceneGraphArray) => sceneGraphArray
        }
      )
      |> SceneTreeUtils.buildIsShowChildrenMap
      |> WonderCommonlib.SparseMapService.set(targetUid, true);

    GameObjectUtils.setParentKeepOrder(targetUid, dragedUid)
    |> StateLogicService.getAndRefreshEngineStateWithFunc;

    let editorState = StateEditorService.getState();
    let engineState = StateEngineService.unsafeGetState();

    dispatchFunc(
      AppStore.SceneTreeAction(
        SetSceneGraph(
          Some(
            SceneTreeUtils.getSceneGraphDataFromEngine((
              editorState,
              engineState,
            ))
            |> SceneTreeUtils.setIsShowChildrenByMap(isShowChildrenMap),
          ),
        ),
      ),
    )
    |> ignore;

    editorState |> StateEditorService.setState |> ignore;
    engineState |> StateEngineService.setState |> ignore;

    dispatchFunc(AppStore.UpdateAction(Update([|UpdateStore.SceneTree|])))
    |> ignore;
  };
};

module MakeEventHandler = EventHandler.MakeEventHandler(CustomEventHandler);