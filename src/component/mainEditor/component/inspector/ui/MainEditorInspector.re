module Method = {
  let _getCurrentGameObject = () =>
    MainEditorStateView.prepareState() |> MainEditorSceneView.getCurrentGameObject;
  let _isSpecificComponentExistShowInspector = (allShowComponentsConfig, name) =>
    allShowComponentsConfig
    |> Js.Array.filter(
         ({componentName}: GameObjectComponentParseType.gameObjectCompoent) =>
           componentName == name
       )
    |> OperateArrayUtils.hasItem;
  let _getAllShowComponentList = (allShowComponentsConfig, allComponentList) =>
    allComponentList
    |> Js.List.filter(
         [@bs]
         (((type_, _)) => _isSpecificComponentExistShowInspector(allShowComponentsConfig, type_))
       );
  let _buildComponentUIComponent = (type_, gameObjectComponent, store, dispatch, componentArray) =>
    switch type_ {
    | "transform" =>
      componentArray
      |> OperateArrayUtils.push(
           <MainEditorTransform key=(DomHelper.getRandomKey()) store dispatch />
         )
    | "material" => componentArray
    | "cameraController" => componentArray
    | _ => ExcepetionHandleSystem.throwMessage({j|"the component: $type_ not exist"|j})
    };
  let _buildGameObjectallShowComponentsConfig =
      (currentGameObject, store, dispatch, allShowComponentsConfig) =>
    MainEditorStateView.prepareState()
    |> MainEditorGameObjectView.getCurrentGameObjectAllComponentList(currentGameObject)
    |> _getAllShowComponentList(allShowComponentsConfig)
    |> Js.List.foldLeft(
         [@bs]
         (
           (componentArray, (type_, gameObjectComponent)) =>
             _buildComponentUIComponent(type_, gameObjectComponent, store, dispatch, componentArray)
         ),
         [||]
       );
  let buildCurrentGameObjectComponent = (store, dispatch, allShowComponentsConfig) =>
    switch (_getCurrentGameObject()) {
    | None =>
      Js.log("no current game object");
      [||]
    | Some(gameObject) =>
      _buildGameObjectallShowComponentsConfig(gameObject, store, dispatch, allShowComponentsConfig)
    };
};

let component = ReasonReact.statelessComponent("MainEditorInspector");

let render = (store, dispatch, allShowComponentsConfig, _self) =>
  <article key="inspector" className="inspector-component">
    (
      ReasonReact.arrayToElement(
        Method.buildCurrentGameObjectComponent(store, dispatch, allShowComponentsConfig)
      )
    )
  </article>;

let make = (~store: AppStore.appState, ~dispatch, ~allShowComponentsConfig, _children) => {
  ...component,
  render: (self) => render(store, dispatch, allShowComponentsConfig, self)
};