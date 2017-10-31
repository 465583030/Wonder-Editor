open StringStore;

type ReduxThunk.thunk(_) +=
  | StringAction (stringAction);

type ReduxThunk.thunk('a) +=
  | ReplaceState ('a);

type appState = {
  notACounter:string
};

let appReducter = (state:appState, action) =>
  switch action {
  | StringAction(action) => {...state, notACounter: stringReduce(state.notACounter, action)}
  | ReplaceState(replacedState) => replacedState
  | _ => state
  };

type ReduxThunk.thunk(_) +=
  | TravelBackward
  | TravelForward;

let past = ref(Immutable.Stack.empty());

let future = ref(Immutable.Stack.empty());

let goBack = (currentState) =>
  switch (Immutable.Stack.first(past^)) {
  | Some(lastState) =>
    future := Immutable.Stack.addFirst(currentState, future^);
    past := Immutable.Stack.removeFirstOrRaise(past^);
    lastState
  | None => currentState
  };

let goForward = (currentState) =>
  switch (Immutable.Stack.first(future^)) {
  | Some(nextState) =>
    past := Immutable.Stack.addFirst(currentState, past^);
    future := Immutable.Stack.removeFirstOrRaise(future^);
    nextState
  | None => currentState
  };

/* 执行其他操作时，保存当前的state */
let recordHistory = (currentState) => {
  past := Immutable.Stack.addFirst(currentState, past^);
  future := Immutable.Stack.empty()
};

let timeTravel = (store, next, action) => {
  let currentState = Reductive.Store.getState(store);
  switch action {
  | TravelBackward => next(ReplaceState(goBack(currentState)))
  | TravelForward => next(ReplaceState(goForward(currentState)))
  | _ =>
    next(action);
    let newState = Reductive.Store.getState(store);
    if (currentState !== newState) {
      recordHistory(currentState)
    }
  }
};

let thunkedLoggedTimeTravelLogger = (store, next) =>
  next |> timeTravel(store) |> Middleware.logger(store) |> Middleware.thunk(store);

let store =
  Reductive.Store.create(
    ~reducer=appReducter,
    ~preloadedState={notACounter: ""},
    ~enhancer=thunkedLoggedTimeTravelLogger,
    ()
  );
