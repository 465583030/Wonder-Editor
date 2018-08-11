open AddGameObjectType;

module CustomEventHandler = {
  include EmptyEventHandler.EmptyEventHandler;
  type prepareTuple = addGameObjectType ;
  type dataTuple = unit;

  let handleSelfLogic = ((store, dispatchFunc), type_, ()) => {
    let newGameObject =
      switch (type_) {
      | Box => SceneUtils.addGameObject(PrimitiveEngineService.createBox)
      | EmptyGameObject =>
        SceneUtils.addGameObject(PrimitiveEngineService.createEmptyGameObject)
      };

    dispatchFunc(
      AppStore.SceneTreeAction(
        SetSceneGraph(
          Some(
            SceneTreeUtils.buildSceneGraphDataWithNewGameObject(
              newGameObject,
              store |> StoreUtils.unsafeGetSceneGraphDataFromStore,
            )
            |> StateLogicService.getEngineStateToGetData,
          ),
        ),
      ),
    )
    |> ignore;

    dispatchFunc(AppStore.UpdateAction(Update([|UpdateStore.SceneTree|])))
    |> ignore;
  };
};

module MakeEventHandler = EventHandler.MakeEventHandler(CustomEventHandler);