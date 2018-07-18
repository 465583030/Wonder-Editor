module CustomEventHandler = {
  include EmptyEventHandler.EmptyEventHandler;
  type prepareTuple = unit;
  type dataTuple = unit;

  let _checkSceneGraphDataAndDispatch = (dispatchFunc, newSceneGraphArr) => {
    WonderLog.Contract.requireCheck(
      () =>
        WonderLog.(
          Contract.(
            test(
              Log.buildAssertMessage(
                ~expect=
                  {j|the newSceneGraphArr should equal the sceneGraph from engine|j},
                ~actual={j|not|j},
              ),
              () =>
              SceneTreeUtils.getSceneGraphDataFromEngine
              |> StateLogicService.getStateToGetData == newSceneGraphArr
              |> assertTrue
            )
          )
        ),
      StateEditorService.getStateIsDebug(),
    );

    dispatchFunc(
      AppStore.SceneTreeAction(SetSceneGraph(Some(newSceneGraphArr))),
    )
    |> ignore;
  };

  let _getRemovedSceneGraphData = sceneGraphArr =>
    switch (
      SceneEditorService.getCurrentSceneTreeNode
      |> StateLogicService.getEditorState
    ) {
    | None =>
      WonderLog.Log.error(
        WonderLog.Log.buildErrorMessage(
          ~title="disposeCurrentSceneTreeNode",
          ~description=
            {j|current gameObject should exist, but actual is None|j},
          ~reason="",
          ~solution={j|set current gameObject|j},
          ~params={j||j},
        ),
      );
      (sceneGraphArr, None);
    | Some(gameObject) =>
      CameraEngineService.isCamera(gameObject)
      |> StateLogicService.getEngineStateToGetData ?
        HeaderUtils.doesSceneHasRemoveableCamera() ?
          {
            let (newSceneGraphArr, removedTreeNode) =
              sceneGraphArr |> SceneTreeUtils.removeDragedTreeNode(gameObject);
            (newSceneGraphArr, removedTreeNode |. Some);
          } :
          {
            WonderLog.Log.warn({j|can't remove last camera|j});
            (sceneGraphArr, None);
          } :
        {
          let (newSceneGraphArr, removedTreeNode) =
            sceneGraphArr |> SceneTreeUtils.removeDragedTreeNode(gameObject);
          (newSceneGraphArr, removedTreeNode |. Some);
        }
    };

  let handleSelfLogic = ((store, dispatchFunc), (), ()) => {
    let sceneGraphArr =
      store |> SceneTreeUtils.unsafeGetSceneGraphDataFromStore;

<<<<<<< HEAD
    let (newSceneGraphArr, removedTreeNode) =
      _getRemovedSceneGraphData(sceneGraphArr);
=======
    let _getRemovedSceneGraphData = () =>
      switch (
        SceneEditorService.getCurrentSceneTreeNode
        |> StateLogicService.getEditorState
      ) {
      | None =>
        WonderLog.Log.error(
          WonderLog.Log.buildErrorMessage(
            ~title="disposeCurrentSceneTreeNode",
            ~description=
              {j|current gameObject should exist, but actual is None|j},
            ~reason="",
            ~solution={j|set current gameObject|j},
            ~params={j||j},
          ),
        );
        (sceneGraphArr, None);
      | Some(gameObject) =>
        CameraEngineService.isCamera(gameObject)
        |> StateLogicService.getEngineStateToGetData ?
          HeaderUtils.doesSceneHasRemoveableCamera() ?
            {
              let (newSceneGraphArr, removedTreeNode) =
                sceneGraphArr
                |> SceneTreeUtils.removeDragedTreeNode(gameObject);
              (newSceneGraphArr, removedTreeNode |. Some);
            } :
            {
              WonderLog.Log.warn({j|can't remove last camera|j});
              (sceneGraphArr, None);
            } :
          {
            let (newSceneGraphArr, removedTreeNode) =
              sceneGraphArr |> SceneTreeUtils.removeDragedTreeNode(gameObject);
            (newSceneGraphArr, removedTreeNode |. Some);
          }
      };
>>>>>>> 8f76fb41c78bbf8347f3981e0bbf75a730cbc9cf

    let (newSceneGraphArr, removedTreeNode) = _getRemovedSceneGraphData();

    switch (removedTreeNode) {
    | None => ()
    | Some(removedTreeNode) =>
      removedTreeNode
      |> CurrentSceneTreeNodeLogicService.disposeCurrentSceneTreeNode
    };

    _checkSceneGraphDataAndDispatch(dispatchFunc, newSceneGraphArr);
  };
};

module MakeEventHandler = EventHandler.MakeEventHandler(CustomEventHandler);