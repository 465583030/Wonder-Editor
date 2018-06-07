open SceneGraphType;

let getFlag = () => EditorType.SceneTree;

let handleFlag = startFlag =>
  switch (startFlag) {
  | None => false
  | Some(startFlag) => startFlag === getFlag()
  };

let _isDragedGameObjectBeTargetGameObjectParent =
    (targetGameObject, dragedGameObject, engineState) => {
  let rec _judgeAllParents = (targetTransform, dragedTransform, engineState) =>
    switch (
      TransformEngineService.getParent(targetTransform, engineState)
      |> Js.Undefined.to_opt
    ) {
    | None => false
    | Some(transformParent) =>
      transformParent === dragedTransform ?
        true : _judgeAllParents(transformParent, dragedTransform, engineState)
    };
  _judgeAllParents(
    GameObjectComponentEngineService.getTransformComponent(
      targetGameObject,
      engineState,
    ),
    GameObjectComponentEngineService.getTransformComponent(
      dragedGameObject,
      engineState,
    ),
    engineState,
  );
};

let _isTargetGameObjectBeRemovedGameObjectParent =
    (dragedGameObject, targetGameObject, engineState) =>
  switch (
    engineState
    |> TransformEngineService.getParent(
         engineState
         |> GameObjectComponentEngineService.getTransformComponent(
              dragedGameObject,
            ),
       )
    |> Js.Undefined.to_opt
  ) {
  | None => false
  | Some(transformParent) =>
    transformParent
    === GameObjectComponentEngineService.getTransformComponent(
          targetGameObject,
          engineState,
        ) ?
      true : false
  };

let isGameObjectRelationError =
    (targetGameObject, dragedGameObject, (editorState, engineState)) =>
  targetGameObject === dragedGameObject ?
    true :
    _isDragedGameObjectBeTargetGameObjectParent(
      targetGameObject,
      dragedGameObject,
      engineState,
    ) ?
      true :
      _isTargetGameObjectBeRemovedGameObjectParent(
        dragedGameObject,
        targetGameObject,
        engineState,
      );

let _getGameObjectName = (gameObject, engineState) =>
  CameraEngineService.isCamera(gameObject, engineState) ?
    "camera" : {j|gameObject$gameObject|j};

let _buildTreeNode = (gameObject, engineState) => {
  name: _getGameObjectName(gameObject, engineState),
  uid: gameObject,
  children: [||],
};

let _buildSceneGraphData = (gameObject, engineState) => {
  let rec _buildSceneGraphDataRec = (gameObject, treeNode, engineState) =>
    GameObjectUtils.hasChildren(gameObject, engineState) ?
      engineState
      |> GameObjectUtils.getChildren(gameObject)
      |> WonderCommonlib.ArrayService.reduceOneParam(
           (. {children} as treeNode, child) => {
             ...treeNode,
             children:
               children
               |> Js.Array.copy
               |> ArrayService.push(
                    _buildSceneGraphDataRec(
                      child,
                      _buildTreeNode(child, engineState),
                      engineState,
                    ),
                  ),
           },
           treeNode,
         ) :
      treeNode;
  _buildSceneGraphDataRec(
    gameObject,
    _buildTreeNode(gameObject, engineState),
    engineState,
  );
};

let getSceneGraphDataFromEngine = ((editorState, engineState)) => [|
  _buildSceneGraphData(
    editorState |> SceneEditorService.unsafeGetScene,
    engineState,
  ),
|];

let buildSceneGraphDataWithNewGameObject =
    (
      newGameObject,
      oldSceneGraphData: array(SceneGraphType.sceneTreeNodeType),
      engineState,
    ) => {
  let scene = oldSceneGraphData |> ArrayService.getFirst;
  [|
    {
      ...scene,
      children:
        scene.children
        |> Js.Array.copy
        |> ArrayService.push(engineState |> _buildTreeNode(newGameObject)),
    },
  |]
  |> WonderLog.Contract.ensureCheck(
       sceneGraphArray =>
         WonderLog.(
           Contract.(
             test(
               Log.buildAssertMessage(
                 ~expect=
                   {j|the draged scene graph data == scene data from engine|j},
                 ~actual={j|not|j},
               ),
               () =>
               getSceneGraphDataFromEngine
               |> StateLogicService.getStateToGetData == sceneGraphArray
               |> assertTrue
             )
           )
         ),
       StateEditorService.getStateIsDebug(),
     );
};

let _removeDragedTreeNodeFromSceneGrahph = (dragedUid, sceneGraphArrayData) => {
  let rec _iterateSceneGraph =
          (dragedUid, sceneGraphArray, newSceneGraphArray, dragedTreeNode) =>
    sceneGraphArray
    |> WonderCommonlib.ArrayService.reduceOneParam(
         (.
           (newSceneGraphArray, dragedTreeNode),
           {uid, children} as treeNode,
         ) =>
           uid === dragedUid ?
             (newSceneGraphArray, Some(treeNode)) :
             {
               let (newChildrenSceneGraphArray, dragedTreeNode) =
                 _iterateSceneGraph(
                   dragedUid,
                   children,
                   [||],
                   dragedTreeNode,
                 );
               (
                 newSceneGraphArray
                 |> ArrayService.push({
                      ...treeNode,
                      children: newChildrenSceneGraphArray,
                    }),
                 dragedTreeNode,
               );
             },
         (newSceneGraphArray, dragedTreeNode),
       );
  switch (_iterateSceneGraph(dragedUid, sceneGraphArrayData, [||], None)) {
  | (_, None) =>
    WonderLog.Log.fatal(
      WonderLog.Log.buildFatalMessage(
        ~title="_removeDragedTreeNodeFromSceneGrahph",
        ~description={j|the draged treeNode $dragedUid is not exist|j},
        ~reason="",
        ~solution={j||j},
        ~params={j|dragedUid:$dragedUid|j},
      ),
    )
  | (newSceneGraphArray, Some(dragedTreeNode)) => (
      newSceneGraphArray,
      dragedTreeNode,
    )
  };
};

let rec _insertRemovedTreeNodeToTargetTreeNode =
        (targetUid, (sceneGraphArrayData, dragedTreeNode)) =>
  sceneGraphArrayData
  |> Js.Array.map(({uid, children} as treeNode) =>
       uid === targetUid ?
         {
           ...treeNode,
           children:
             children |> Js.Array.copy |> ArrayService.push(dragedTreeNode),
         } :
         {
           ...treeNode,
           children:
             _insertRemovedTreeNodeToTargetTreeNode(
               targetUid,
               (children, dragedTreeNode),
             ),
         }
     );

let getDragedSceneGraphData =
    (
      targetUid: int,
      dragedUid: int,
      sceneGraphArrayData: array(sceneTreeNodeType),
    ) =>
  _removeDragedTreeNodeFromSceneGrahph(dragedUid, sceneGraphArrayData)
  |> _insertRemovedTreeNodeToTargetTreeNode(targetUid)
  |> WonderLog.Contract.ensureCheck(
       dragedSceneGraph =>
         WonderLog.(
           Contract.(
             test(
               Log.buildAssertMessage(
                 ~expect=
                   {j|the draged scene graph data == scene data from engine|j},
                 ~actual={j|not|j},
               ),
               () =>
               getSceneGraphDataFromEngine
               |> StateLogicService.getStateToGetData == dragedSceneGraph
               |> assertTrue
             )
           )
         ),
       StateEditorService.getStateIsDebug(),
     );