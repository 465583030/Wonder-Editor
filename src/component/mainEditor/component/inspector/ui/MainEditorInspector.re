module Method = {
  let _getCurrentGameObject = () =>
    MainEditorStateView.prepareState() |> MainEditorSceneView.getCurrentGameObject;
  let _hasCurrentGameObject = () =>
    MainEditorStateView.prepareState() |> MainEditorSceneView.hasCurrentGameObject;
  let _hasMaterialComponent = (gameObject) =>
    MainEditorStateView.prepareState() |> MainEditorGameObjectView.hasMaterialComponent(gameObject);
  /* todo add component by gameObject type */
  let _buildComponentByType = () => {
    let currentGameObject = _getCurrentGameObject();
    Js.log(_hasMaterialComponent(currentGameObject))
  };
  let buildCurrentGameObjectComponent = (store, dispatch) =>
    switch (_hasCurrentGameObject()) {
    | false =>
      Js.log("no current game object");
      ReasonReact.nullElement
    | true =>
      _buildComponentByType();
      Js.log(_getCurrentGameObject());
      <MainEditorTransform store dispatch />
    };
};

let component = ReasonReact.statelessComponent("MainEditorInspector");

let make = (~store: AppStore.appState, ~dispatch, _children) => {
  ...component,
  render: (_self) =>
    <article key="inspector" className="inspector-component">
      (Method.buildCurrentGameObjectComponent(store, dispatch))
    </article>
};