Css.importCss("./css/mainEditor.css");

let component = ReasonReact.statelessComponent("MainEditor");

module Method = {
  let getSceneGraphFromEngine = () =>
    MainEditorStateView.prepareState() |> MainEditorSceneTreeView.getSceneGraphData;
};

let make = (~store: AppStore.appState, ~dispatch, _children) => {
  ...component,
  didMount: (_self) => {
    MainEditorMainView.start();
    dispatch(AppStore.StartEngineAction);
    dispatch(AppStore.SceneTreeAction(SetSceneGraph(Some(Method.getSceneGraphFromEngine()))));
    ReasonReact.NoUpdate
  },
  render: (_self) =>
    if (store.isEditorAndEngineStart) {
      <article key="mainEditor" className="wonder-mainEditor-component">
        <div key="verticalComponent" className="vertical-component">
          <div className="inline-component inspector-parent">
            <MainEditorInspector store dispatch />
          </div>
          <div className="inline-component sceneTree-parent">
            <MainEditorSceneTree store dispatch />
          </div>
          <canvas key="webGL" id="webgl" />
        </div>
      </article>
    } else {
      <article key="mainEditor" className="wonder-mainEditor-component">
        <div key="verticalComponent" className="vertical-component">
          <canvas key="webGL" id="webgl" />
        </div>
      </article>
    }
};