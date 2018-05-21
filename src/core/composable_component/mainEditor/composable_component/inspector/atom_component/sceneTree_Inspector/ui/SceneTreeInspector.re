module Method = {
  let _buildComponentBox = ((type_, component), (store, dispatch), isClose, buildComponentFunc) =>
    <ComponentBox
      key=(DomHelper.getRandomKey())
      header=type_
      closable=isClose
      gameObjectComponent=(buildComponentFunc(store, dispatch, component))
    />;
  let _buildTransform = (store, dispatch, component) =>
    <MainEditorTransform
      key=(DomHelper.getRandomKey())
      store
      dispatch
      transformComponent=component
    />;
  let _buildBasicMaterial = (store, dispatch, component) =>
    <MainEditorBasicMaterial
      key=(DomHelper.getRandomKey())
      store
      dispatch
      materialComponent=component
    />;
  let _buildSouceInstance = (store, dispatch, component) =>
    <div key=(DomHelper.getRandomKey())> (DomHelper.textEl("simulate source instance")) </div>;
  let _buildBasicCameraView = (store, dispatch, component) =>
    <div key=(DomHelper.getRandomKey())> (DomHelper.textEl("simulate basic camera view")) </div>;
  let _buildPerspectiveCameraProjection = (store, dispatch, component) =>
    <div key=(DomHelper.getRandomKey())>
      (DomHelper.textEl("simulate perspective camera view"))
    </div>;
  let _buildComponentUIComponent = ((type_, component), (store, dispatch)) =>
    switch type_ {
    | "transform" =>
      _buildTransform |> _buildComponentBox((type_, component), (store, dispatch), false)
    | "basicMaterial" =>
      _buildBasicMaterial |> _buildComponentBox((type_, component), (store, dispatch), false)
    | "sourceInstance" =>
      _buildSouceInstance |> _buildComponentBox((type_, component), (store, dispatch), true)
    | "basicCameraView" =>
      _buildBasicCameraView |> _buildComponentBox((type_, component), (store, dispatch), true)
    | "perspectiveCameraProjection" =>
      _buildPerspectiveCameraProjection
      |> _buildComponentBox((type_, component), (store, dispatch), true)
    | _ =>
      WonderLog.Log.fatal(
        WonderLog.Log.buildFatalMessage(
          ~title="_buildComponentUIComponent",
          ~description={j|the component: $type_ not exist|j},
          ~reason="",
          ~solution={j||j},
          ~params={j|type:$type_, component:$component|j}
        )
      )
    };
  let _buildGameObjectAllShowComponent = (componentList, store, dispatch) =>
    componentList
    |> Js.List.foldLeft(
         [@bs]
         (
           (componentArray, (type_, component)) =>
             componentArray
             |> ArrayService.push(
                  _buildComponentUIComponent((type_, component), (store, dispatch))
                )
         ),
         [||]
       );
  let buildCurrentSceneTreeNodeComponent =
      (store, dispatch, allShowComponentConfig, currentSceneTreeNode) =>
    switch currentSceneTreeNode {
    | None => [||]
    | Some(gameObject) =>
      let (addedComponentList, addableComponentList) =
        InspectorGameObjectUtils.buildCurrentSceneTreeNodeShowComponentList(
          gameObject,
          allShowComponentConfig
        )
        |> StateLogicService.getEngineStateToGetData;
      _buildGameObjectAllShowComponent(addedComponentList, store, dispatch)
      |> ArrayService.push(
           <AddableComponent
             key=(DomHelper.getRandomKey())
             reduxTuple=(store, dispatch)
             currentSceneTreeNode=gameObject
             addableComponentList
           />
         )
    };
};

let component = ReasonReact.statelessComponent("SceneTreeInspector");

let render = (store, dispatch, allShowComponentConfig, currentSceneTreeNode, _self) =>
  <article key="SceneTreeInspector" className="inspector-component">
    (
      ReasonReact.arrayToElement(
        Method.buildCurrentSceneTreeNodeComponent(
          store,
          dispatch,
          allShowComponentConfig,
          currentSceneTreeNode
        )
      )
    )
  </article>;

let make =
    (~store: AppStore.appState, ~dispatch, ~allShowComponentConfig, ~currentSceneTreeNode, _children) => {
  ...component,
  render: (self) => render(store, dispatch, allShowComponentConfig, currentSceneTreeNode, self)
};