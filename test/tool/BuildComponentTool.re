let buildHeader = store =>
  ReactTestRenderer.create(
    <Header store dispatchFunc=(TestTool.getDispatch()) />,
  );

let buildSceneTree = store =>
  ReactTestRenderer.create(
    <MainEditorSceneTree store dispatchFunc=(TestTool.getDispatch()) />,
  );

let buildInspectorComponent = (store, addableComponentConfig) =>
  ReactTestRenderer.create(
    <MainEditorInspector
      store
      dispatchFunc=(TestTool.getDispatch())
      addableComponentConfig
    />,
  );

let buildMainEditorTransformComponent = (store, transformComponent) =>
  ReactTestRenderer.create(
    <MainEditorTransform
      store
      dispatchFunc=(TestTool.getDispatch())
      transformComponent
    />,
  );

let buildMaterial = () =>
  ReactTestRenderer.create(
    <MainEditorMaterial
      store=(TestTool.buildEmptyAppState())
      dispatchFunc=(TestTool.getDispatch())
    />,
  );

let buildBasicMaterial = materialComponent =>
  ReactTestRenderer.create(
    <MainEditorBasicMaterial
      store=(TestTool.buildEmptyAppState())
      dispatchFunc=(TestTool.getDispatch())
      materialComponent
    />,
  );

let buildLightMaterial = materialComponent =>
  ReactTestRenderer.create(
    <MainEditorLightMaterial
      store=(TestTool.buildEmptyAppState())
      dispatchFunc=(TestTool.getDispatch())
      materialComponent
    />,
  );

let buildDirectionLight = lightComponent =>
  ReactTestRenderer.create(
    <MainEditorDirectionLight
      store=(TestTool.buildEmptyAppState())
      dispatchFunc=(TestTool.getDispatch())
      lightComponent
    />,
  );


let buildAssetComponent = () =>
  ReactTestRenderer.create(
    <MainEditorAsset
      store=(TestTool.buildEmptyAppState())
      dispatchFunc=(TestTool.getDispatch())
    />,
  );
let buildAssetChildrenNode = debounceTime =>
  ReactTestRenderer.create(
    <MainEditorAssetChildrenNode
      store=(TestTool.buildEmptyAppState())
      dispatchFunc=(TestTool.getDispatch())
      dragImg=(DomHelper.createElement("img"))
      debounceTime
    />,
  );