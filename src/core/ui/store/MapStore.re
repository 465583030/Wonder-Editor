/* TODO all: all store related logic should move to service/state/ui/ */
type mapAction('a) =
  | StoreMap('a);

type mapValue;

type componentMapType = Js.Dict.t(mapValue);

type componentsMapType = Js.Dict.t(componentMapType);

type componentsMap = option(componentsMapType);

type mapState = {mutable componentsMap};

let mapReducer = (state: mapState, action: mapAction('a)) : mapState =>
  switch action {
  | StoreMap(map) => {...state, componentsMap: map}
  };