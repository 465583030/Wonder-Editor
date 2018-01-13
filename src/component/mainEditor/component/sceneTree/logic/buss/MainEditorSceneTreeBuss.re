open Contract;

open MainEditorSceneTreeType;

let _isDragedGameObjectEqualTargetGameObject = (targetGameObject, dragedGameObject) =>
  targetGameObject === dragedGameObject;

let _isDragedGameObjectBeTargetGameObjectParent =
        (targetGameObject, dragedGameObject, engineState) => {
  let rec _judgeAllParents = (targetTransform, dragedTransform, engineState) =>
    switch (MainEditorTransformOper.getParent(targetTransform, engineState) |> Js.Nullable.to_opt) {
    | None => false
    | Some(transformParent) =>
      transformParent === dragedTransform ?
        true : _judgeAllParents(transformParent, dragedTransform, engineState)
    };
  _judgeAllParents(
    MainEditorGameObjectOper.getTransformComponent(targetGameObject, engineState),
    MainEditorGameObjectOper.getTransformComponent(dragedGameObject, engineState),
    engineState
  )
};

let isGameObjectRelationError = (targetGameObject, dragedGameObject, (_, engineState)) =>
  _isDragedGameObjectEqualTargetGameObject(targetGameObject, dragedGameObject) ?
    true :
    _isDragedGameObjectBeTargetGameObjectParent(targetGameObject, dragedGameObject, engineState);

let setParent = (parentGameObject, childGameObject, (editorState, engineState)) => (
  editorState,
  MainEditorTransformOper.setParent(
    MainEditorGameObjectOper.getTransformComponent(parentGameObject, engineState),
    MainEditorGameObjectOper.getTransformComponent(childGameObject, engineState),
    engineState
  )
);

let _getGameObjectName = (gameObject, engineState) =>
  MainEditorCameraOper.isCamera(gameObject, engineState) ? "camera" : {j|gameObject$gameObject|j};

let _buildTreeNode = (gameObject, engineState) => {
  name: _getGameObjectName(gameObject, engineState),
  uid: gameObject,
  children: [||]
};

let _buildSceneGraphData = (gameObject, engineState) => {
  let rec _buildSceneGraphDataRec = (gameObject, treeNode, engineState) =>
    MainEditorGameObjectOper.hasChildren(gameObject, engineState) ?
      engineState
      |> MainEditorGameObjectOper.getChildren(gameObject)
      |> Js.Array.reduce(
           ({children} as treeNode, child) => {
             ...treeNode,
             children:
               children
               |> Js.Array.copy
               |> OperateArrayUtils.push(
                    _buildSceneGraphDataRec(child, _buildTreeNode(child, engineState), engineState)
                  )
           },
           treeNode
         ) :
      treeNode;
  _buildSceneGraphDataRec(gameObject, _buildTreeNode(gameObject, engineState), engineState)
};

let getSceneGraphDataFromEngine = ((editorState, engineState)) => [|
  _buildSceneGraphData(editorState |> MainEditorSceneEdit.unsafeGetScene, engineState)
|];

let _removeDragedTreeNodeFromSceneGrahph = (dragedUid, sceneGraphArrayData) => {
  let rec _iterateSceneGraph = (dragedUid, sceneGraphArray, newSceneGraphArray, dragedTreeNode) =>
    sceneGraphArray
    |> Js.Array.reduce(
         ((newSceneGraphArray, dragedTreeNode), {uid, children} as treeNode) =>
           uid === dragedUid ?
             (newSceneGraphArray, Some(treeNode)) :
             {
               let (newChildrenSceneGraphArray, dragedTreeNode) =
                 _iterateSceneGraph(dragedUid, children, [||], dragedTreeNode);
               (
                 newSceneGraphArray
                 |> OperateArrayUtils.push({...treeNode, children: newChildrenSceneGraphArray}),
                 dragedTreeNode
               )
             },
         (newSceneGraphArray, dragedTreeNode)
       );
  switch (_iterateSceneGraph(dragedUid, sceneGraphArrayData, [||], None)) {
  | (_, None) => ExcepetionHandleSystem.throwMessage("the draged treeNode should exist")
  | (newSceneGraphArray, Some(dragedTreeNode)) => (newSceneGraphArray, dragedTreeNode)
  }
};

let rec _insertRemovedTreeNodeToTargetTreeNode = (targetUid, (sceneGraphArrayData, dragedTreeNode)) =>
  sceneGraphArrayData
  |> Js.Array.map(
       ({uid, children} as treeNode) =>
         uid === targetUid ?
           {...treeNode, children: children |> OperateArrayUtils.push(dragedTreeNode)} :
           {
             ...treeNode,
             children: _insertRemovedTreeNodeToTargetTreeNode(targetUid, (children, dragedTreeNode))
           }
     );

let getDragedSceneGraphData = (targetUid: int, dragedUid: int, sceneGraphArrayData: array(treeNode)) =>
  _removeDragedTreeNodeFromSceneGrahph(dragedUid, sceneGraphArrayData)
  |> _insertRemovedTreeNodeToTargetTreeNode(targetUid)
  |> ensureCheck(
       (result) =>
         test(
           "the draged scene graph data should == scene graph data from engine",
           () => {
             let sceneGraphFromEngine =
               MainEditorStateView.prepareState() |> getSceneGraphDataFromEngine;
             sceneGraphFromEngine == result |> assertTrue
           }
         )
     );