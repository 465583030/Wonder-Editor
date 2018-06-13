module MarkRedoUndoEventHandler = {
  include EmptyEventHandler.EmptyEventHandler;
  type prepareTuple = Wonderjs.MaterialType.material;
  type dataTuple = string;
  let onMarkRedoUndoByLastStack =
      ((store, dispatchFunc), materialComponent, value) => {
    BasicMaterialEngineService.setColor([|0.4, 0.6, 0.7|])
    |> StateLogicService.getAndRefreshEngineStateWithDiff(
         [|materialComponent|],
         DiffType.Material,
       );
    dispatchFunc(AppStore.ReLoad);
    ();
  };
};

module MakeEventHandler =
  EventHandler.MakeEventHandler(MarkRedoUndoEventHandler);