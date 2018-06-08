module Method = {
  let _buildComponentBox = ((type_, component), (store, dispatchFunc), isClosable, buildComponentFunc) =>
    <ComponentBox
      key=(DomHelper.getRandomKey())
      header=type_
      isClosable
      gameObjectComponent=(buildComponentFunc(store, dispatchFunc, component))
    />;
  let _buildTransform = (store, dispatchFunc, component) =>
    <MainEditorTransform
      key=(DomHelper.getRandomKey())
      store
      dispatchFunc
      transformComponent=component
    />;
  let _buildBasicMaterial = (store, dispatchFunc, component) =>
    <MainEditorBasicMaterial
      key=(DomHelper.getRandomKey())
      store
      dispatchFunc
      materialComponent=component
    />;
  let _buildSouceInstance = (store, dispatchFunc, component) =>
    <div key=(DomHelper.getRandomKey())> (DomHelper.textEl("simulate source instance")) </div>;
  let _buildBasicCameraView = (store, dispatchFunc, component) =>
    <div key=(DomHelper.getRandomKey())> (DomHelper.textEl("simulate basic camera view")) </div>;
  let _buildPerspectiveCameraProjection = (store, dispatchFunc, component) =>
    <div key=(DomHelper.getRandomKey())>
      (DomHelper.textEl("simulate perspective camera view"))
    </div>;
  let _buildComponentUIComponent = ((type_, component), (store, dispatchFunc)) =>
    switch type_ {
    | "transform" =>
      _buildTransform |> _buildComponentBox((type_, component), (store, dispatchFunc), false)
    | "basicMaterial" =>
      _buildBasicMaterial |> _buildComponentBox((type_, component), (store, dispatchFunc), false)
    | "sourceInstance" =>
      _buildSouceInstance |> _buildComponentBox((type_, component), (store, dispatchFunc), true)
    | "basicCameraView" =>
      _buildBasicCameraView |> _buildComponentBox((type_, component), (store, dispatchFunc), true)
    | "perspectiveCameraProjection" =>
      _buildPerspectiveCameraProjection
      |> _buildComponentBox((type_, component), (store, dispatchFunc), true)
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
  let _buildGameObjectAllShowComponent = (componentList, store, dispatchFunc) =>
    componentList
    |> Js.List.foldLeft(
         [@bs]
         (
           (componentArray, (type_, component)) =>
             componentArray
             |> ArrayService.push(
                  _buildComponentUIComponent((type_, component), (store, dispatchFunc))
                )
         ),
         [||]
       );
  let buildCurrentSceneTreeNodeComponent =
      (store, dispatchFunc, allShowComponentConfig, currentSceneTreeNode) =>
    switch currentSceneTreeNode {
    | None => [||]
    | Some(gameObject) =>
      let (addedComponentList, addableComponentList) =
        InspectorGameObjectUtils.buildCurrentSceneTreeNodeShowComponentList(
          gameObject,
          allShowComponentConfig
        )
        |> StateLogicService.getEngineStateToGetData;
      _buildGameObjectAllShowComponent(addedComponentList, store, dispatchFunc)
      |> ArrayService.push(
           <AddableComponent
             key=(DomHelper.getRandomKey())
             reduxTuple=(store, dispatchFunc)
             currentSceneTreeNode=gameObject
             addableComponentList
           />
         )
    };
};

let component = ReasonReact.statelessComponent("SceneTreeInspector");

let render = (store, dispatchFunc, allShowComponentConfig, currentSceneTreeNode, _self) =>
  <article key="SceneTreeInspector" className="inspector-component">
    (
      ReasonReact.arrayToElement(
        Method.buildCurrentSceneTreeNodeComponent(
          store,
          dispatchFunc,
          allShowComponentConfig,
          currentSceneTreeNode
        )
      )
    )
  </article>;

let make =
    (~store: AppStore.appState, ~dispatchFunc, ~allShowComponentConfig, ~currentSceneTreeNode, _children) => {
  ...component,
  render: (self) => render(store, dispatchFunc, allShowComponentConfig, currentSceneTreeNode, self)
};