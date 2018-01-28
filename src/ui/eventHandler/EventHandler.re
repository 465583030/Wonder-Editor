module type EventHandler = {
  type prepareTuple;
  type dataTuple;
  let onSelect:
    ((AppStore.appState, WonderEditor.ReduxThunk.thunk('b) => 'c), prepareTuple, dataTuple) => unit;
  let onDrop:
    ((AppStore.appState, WonderEditor.ReduxThunk.thunk('b) => 'c), prepareTuple, dataTuple) => unit;
  let onMarkRedoUndo:
    ((AppStore.appState, WonderEditor.ReduxThunk.thunk('b) => 'c), prepareTuple, dataTuple) => unit;
};

module MakeEventHandler = (EventItem: EventHandler) => {
  let onSelect = ((store, _) as reduxTuple, prepareTuple, dataTuple) => {
    MarkRedoUndoEventHandlerUtils.markRedoUndoChangeUI(store);
    EventItem.onSelect(reduxTuple, prepareTuple, dataTuple);
    MarkRedoUndoEventHandlerUtils.markRedoUndoChangeNothing(AllStateData.getAllState(), store)
  };
  let onDrop = ((store, _) as reduxTuple, prepareTuple, dataTuple) => {
    MarkRedoUndoEventHandlerUtils.markRedoUndoChangeUI(store);
    EventItem.onDrop(reduxTuple, prepareTuple, dataTuple)
  };
  let onMarkRedoUndo = ((store, _) as reduxTuple, prepareTuple, dataTuple) => {
    MarkRedoUndoEventHandlerUtils.markRedoUndoChangeNothing(AllStateData.getAllState(), store);
    EventItem.onMarkRedoUndo(reduxTuple, prepareTuple, dataTuple)
  };
};