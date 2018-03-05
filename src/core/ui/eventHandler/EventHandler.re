module type EventHandler = {
  type prepareTuple;
  type dataTuple;
  let onSelect:
    ((AppStore.appState, WonderEditor.ReduxThunk.thunk('b) => 'c), prepareTuple, dataTuple) => unit;
  let onDrop:
    ((AppStore.appState, WonderEditor.ReduxThunk.thunk('b) => 'c), prepareTuple, dataTuple) => unit;
  let onClick:
    ((AppStore.appState, WonderEditor.ReduxThunk.thunk('b) => 'c), prepareTuple, dataTuple) => unit;
  let onMarkRedoUndo:
    ((AppStore.appState, WonderEditor.ReduxThunk.thunk('b) => 'c), prepareTuple, dataTuple) => unit;
};

module MakeEventHandler = (EventItem: EventHandler) => {
  let onSelect = ((store, _) as reduxTuple, prepareTuple, dataTuple) => {
    MarkRedoUndoEventHandlerUtils.markRedoUndoChangeUI(store) |> StateFacade.getState;
    EventItem.onSelect(reduxTuple, prepareTuple, dataTuple)
  };
  let onDrop = ((store, _) as reduxTuple, prepareTuple, dataTuple) => {
    MarkRedoUndoEventHandlerUtils.markRedoUndoChangeUI(store) |> StateFacade.getState;
    EventItem.onDrop(reduxTuple, prepareTuple, dataTuple)
  };
  let onClick = ((store, _) as reduxTuple, prepareTuple, dataTuple) => {
    MarkRedoUndoEventHandlerUtils.markRedoUndoChangeUI(store) |> StateFacade.getState;
    EventItem.onClick(reduxTuple, prepareTuple, dataTuple)
  };
  let onMarkRedoUndo = ((store, _) as reduxTuple, prepareTuple, dataTuple) => {
    MarkRedoUndoEventHandlerUtils.markRedoUndoChangeNothing(AllStateData.getHistoryState(), store)
    |> StateFacade.getState;
    EventItem.onMarkRedoUndo(reduxTuple, prepareTuple, dataTuple)
  };
};