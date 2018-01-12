module Method: {
  let setCurrentGameObject: Wonderjs.GameObjectType.gameObject => unit;
  let onDropFinish:
    (
      AppStore.appState,
      WonderEditor.ReduxThunk.thunk('a) => 'b,
      Wonderjs.GameObjectType.gameObject,
      Wonderjs.GameObjectType.gameObject
    ) =>
    'b;
  let buildTreeArrayData:
    (int => unit, (int, int) => unit, array(MainEditorSceneTreeType.treeNode)) =>
    array(ReasonReact.reactElement);
};

let render:
  (AppStore.appState, WonderEditor.ReduxThunk.thunk('a) => unit, 'b) => ReasonReact.reactElement;

let make:
  (~store: AppStore.appState, ~dispatch: WonderEditor.ReduxThunk.thunk('a) => unit, 'children) =>
  ReasonReact.component(ReasonReact.stateless, ReasonReact.noRetainedProps, ReasonReact.actionless);