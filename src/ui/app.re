let importCss = (css: string) => {};

importCss("./css/app.css");

let component = ReasonReact.statelessComponent("App");

let make = (~state: AppStore.appState, ~dispatch, _children) => {
  let _isDidMount = (state: AppStore.appState) => state.isDidMount;
  {
    ...component,
    didMount: (_self) => {
      let componentsMap = ComponentMapConfig.createComponentMap(dispatch);
      dispatch(AppStore.MapAction(StoreMap(Some(componentsMap))));
      dispatch(AppStore.DidMountAction);
      MainEditorView.start();
      ReasonReact.NoUpdate
    },
    render: (_self) =>
      if (_isDidMount(state)) {
        <div className="app-component">
          (
            ReasonReact.arrayToElement(
              ParseSystem.buildSpecificComponents(
                "app",
                state,
                BuildAppComponent.buildComponentByName
              )
            )
          )
          <canvas key="webGL" id="webgl" />
        </div>
      } else {
        <div> <canvas key="webGL" id="webgl" /> </div>
      }
  }
};