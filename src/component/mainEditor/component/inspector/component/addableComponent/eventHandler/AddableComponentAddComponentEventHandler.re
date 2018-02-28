module AddComponentEventHandler = {
  include EmptyEventHandler.EmptyEventHandler;
  type prepareTuple = string;
  type dataTuple = Wonderjs.GameObjectType.gameObject;
  let onClick = ((store, dispatch), type_, currentGameObject) => {
    MainEditorComponentView.addComponentByType(type_, currentGameObject)
    |> OperateStateUtils.getAndSetState;
    dispatch(AppStore.ReLoad) |> ignore
  };
};

module MakeEventHandler = EventHandler.MakeEventHandler(AddComponentEventHandler);