open Immutable;

open EditorStateDataTypeEdit;

let getState = (data) => data.state;

let setState = (data, state) => {
  data.state = state;
  state
};

/* TODO rename to redoStack, redo; undo... */

let past: ref(Stack.t(EditorStateDataTypeEdit.editorState)) = ref(Stack.empty());

let future: ref(Stack.t(EditorStateDataTypeEdit.editorState)) = ref(Stack.empty());

/* TODO refactor:duplication with UIStateHistory, EngineStateOper
move to src/utils/RedoUndoStructureUtils */
let goBack = (currentState) =>
  switch (Stack.first(past^)) {
  | Some(lastState) =>
    future := Stack.addFirst(currentState, future^);
    past := Stack.removeFirstOrRaise(past^);
    lastState
  | None => currentState
  };

let goForward = (currentState) =>
  switch (Stack.first(future^)) {
  | Some(nextState) =>
    past := Stack.addFirst(currentState, past^);
    future := Stack.removeFirstOrRaise(future^);
    nextState
  | None => currentState
  };

let storeEditorState = (currentState) => {
  past := Stack.addFirst(currentState, past^);
  future := Stack.empty()
};

let clearEditorState = () => {
  past := Stack.empty();
  future := Stack.empty()
};