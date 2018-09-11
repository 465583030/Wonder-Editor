type retainedProps = {isEngineStart: bool};

module Method = {
  let _getCanvasParentSize = parent => (
    parent##offsetWidth,
    parent##offsetHeight,
  );

  let _setAllAspectsWhoseAspectBasedOnCanvasSize = engineState =>
    GameObjectComponentEngineService.getAllPerspectiveCameraProjectionComponents(
      engineState,
    );

  let _updateViewRect = (canvasWidth, canvasHeight) =>
    StateEditorService.setState(
      StateEditorService.getState()
      |> SceneViewEditorService.updateViewRect(
           0,
           0,
           canvasWidth / 2,
           canvasHeight,
         )
      |> GameViewEditorService.updateViewRect(
           canvasWidth / 2,
           canvasHeight,
           canvasWidth / 2,
           canvasHeight,
         ),
    );

  let resizeCanvasAndViewPort = () => {
    let (width, height) =
      DomHelper.getElementById("canvasParent")
      |> DomHelperType.convertDomElementToJsObj
      |> _getCanvasParentSize;

    WonderLog.Log.print(("resize. width,height: ", width, height)) |> ignore;

    DomHelper.getElementById("canvas")
    |> DomHelperType.convertDomElementToJsObj
    |> ScreenEngineService.setScreenSize((width, height, width, height))
    |> ignore;

    _updateViewRect(width, height) |> ignore;

    StateEngineService.unsafeGetState()
    |> PerspectiveCameraProjectionEngineService.markAllPerspectiveCameraProjectionsDirty
    |> DeviceManagerEngineService.setViewport((
         0,
         0,
         width |> NumberType.convertFloatToInt,
         height |> NumberType.convertFloatToInt,
       ))
    |> DirectorEngineService.loopBody(0.)
    |> StateEngineService.setState
    |> ignore;
  };
  /* let buildStartedRunWebglComponent = () =>
     SceneUtils.isSceneHaveNoCamera() ?
       <div className="runNoCamera">
         <span className="runNoCamera-text">
           (DomHelper.textEl("No Camera !"))
         </span>
       </div> :
       ReasonReact.null;*/
};

let component = ReasonReact.statelessComponentWithRetainedProps("MainEditor");

let _buildNotStartElement = () =>
  <article key="mainEditor" className="wonder-mainEditor-component">
    <div key="leftComponent" className="left-component">
      <div className="top-widget">
        <div id="canvasParent" key="webglParent" className="webgl-parent">
          <canvas key="webgl" id="canvas" />
        </div>
      </div>
      /* <div key="webglRun" className="webgl-parent">
           <canvas key="runWebgl" id="runCanvas" />
         </div> */
      <div className="bottom-widget" />
    </div>
    <div key="rightComponent" className="right-component" />
  </article>;

/* TODO handle no camera */
let _buildStartedElement = (store, dispatchFunc) =>
  <article key="mainEditor" className="wonder-mainEditor-component">
    <div key="leftComponent" className="left-component">
      <div className="top-widget">
        <div className="inline-component sceneTree-parent">
          <MainEditorSceneTree store dispatchFunc />
        </div>
        <div id="canvasParent" key="webglParent" className="webgl-parent">
          <canvas key="webgl" id="canvas" />
        </div>
      </div>
      /* <div key="webglRun" className="webgl-parent">
           (Method.buildStartedRunWebglComponent())
           <canvas key="runWebgl" id="runCanvas" />
         </div> */
      <div className="bottom-widget">
        <MainEditorBottomComponents store dispatchFunc />
      </div>
    </div>
    <div key="rightComponent" className="right-component">
      <div className="inline-component inspector-parent">
        <MainEditorInspector
          store
          dispatchFunc
          addableComponentConfig=(
            GameObjectAllComponentParseUtils.getGameObjectAllComponentConfig()
          )
        />
      </div>
    </div>
  </article>;

let render = (store: AppStore.appState, dispatchFunc, _self) =>
  store.isEditorAndEngineStart ?
    _buildStartedElement(store, dispatchFunc) : _buildNotStartElement();

let make = (~store: AppStore.appState, ~dispatchFunc, _children) => {
  ...component,
  retainedProps: {
    isEngineStart: store.isEditorAndEngineStart,
  },
  didUpdate:
    ({oldSelf, newSelf}: ReasonReact.oldNewSelf('a, retainedProps, 'c)) =>
    store.isEditorAndEngineStart
    && oldSelf.retainedProps != newSelf.retainedProps ?
      Method.resizeCanvasAndViewPort() : (),
  didMount: _self => {
    Js.Promise.(
      MainUtils.start()
      |> then_(_ => {
           (
             editorState => {
               let (assetTree, editorState) =
                 editorState |> AssetTreeNodeUtils.initRootAssetTree;
               editorState
               |> AssetTreeRootEditorService.setAssetTreeRoot(assetTree);
             }
           )
           |> StateLogicService.getAndSetEditorState;
           dispatchFunc(
             AppStore.SceneTreeAction(
               SetSceneGraph(
                 Some(
                   SceneTreeUtils.getSceneGraphDataFromEngine
                   |> StateLogicService.getStateToGetData,
                 ),
               ),
             ),
           );
           dispatchFunc(AppStore.StartEngineAction) |> resolve;
         })
      |> ignore
    );

    DomHelper.onresize(Method.resizeCanvasAndViewPort);
  },
  render: self => render(store, dispatchFunc, self),
};