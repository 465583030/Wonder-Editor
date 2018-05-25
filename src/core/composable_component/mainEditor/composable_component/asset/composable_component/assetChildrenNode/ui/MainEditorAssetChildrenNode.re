open AssetNodeType;

open AssetTreeNodeType;

module Method = {
  let getSign = () => "assetChildrenNode";
  let isIdEqualCurrentAssetTreeNodeId = (currentAssetTreeNode, id) =>
    switch currentAssetTreeNode {
    | None => false
    | Some(nodeId) => AssetUtils.isIdEqual(id, nodeId)
    };
  let showSpecificTreeNodeChildren =
      (store, dispatch, nodeMap, currentAssetTreeNode, assetTreeNodeChildren) =>
    assetTreeNodeChildren
    |> Js.Array.map(
         ({id}: assetTreeNodeType) => {
           let {name, type_, result} = nodeMap |> WonderCommonlib.SparseMapService.unsafeGet(id);
           switch type_ {
           | Folder =>
             <FolderBox
               key=(DomHelper.getRandomKey())
               store
               dispatch
               imgSrc="./public/img/11.jpg"
               folderId=id
               name
               isSelected=(isIdEqualCurrentAssetTreeNodeId(currentAssetTreeNode, id))
               sign=(AssetTreeUtils.getSign())
             />
           | Image =>
             <FileBox
               key=(DomHelper.getRandomKey())
               store
               dispatch
               imgSrc=(result |> Js.Option.getExn)
               fileId=id
               fileName=name
               sign=(getSign())
               isSelected=(isIdEqualCurrentAssetTreeNodeId(currentAssetTreeNode, id))
             />
           | Json =>
             <FileBox
               key=(DomHelper.getRandomKey())
               store
               dispatch
               imgSrc="./public/img/12.jpg"
               fileId=id
               fileName=name
               sign=(getSign())
               isSelected=(isIdEqualCurrentAssetTreeNodeId(currentAssetTreeNode, id))
             />
           | _ =>
             WonderLog.Log.fatal(
               WonderLog.Log.buildFatalMessage(
                 ~title="showSpecificTreeNodeChildren",
                 ~description={j||j},
                 ~reason="",
                 ~solution={j||j},
                 ~params={j||j}
               )
             )
           }
         }
       );
  let buildContent = (store, dispatch) => {
    let editorState = StateEditorService.getState();
    WonderLog.Log.print(("id", editorState |> AssetUtils.getTargetTreeNodeId)) |> ignore;
    editorState
    |> AssetTreeRootEditorService.unsafeGetAssetTreeRoot
    |> WonderLog.Log.print
    |> AssetUtils.getSpecificTreeNodeById(editorState |> AssetUtils.getTargetTreeNodeId)
    |> OptionService.unsafeGet
    |> ((currentParentAssetTreeNode) => currentParentAssetTreeNode.children)
    |> showSpecificTreeNodeChildren(
         store,
         dispatch,
         editorState |> AssetNodeMapEditorService.unsafeGetNodeMap,
         editorState |> AssetCurrentAssetTreeNodeEditorService.getCurrentAssetTreeNode
       )
  };
};

let component = ReasonReact.statelessComponent("MainEditorAssetHeader");

let render = (store, dispatch, _self) =>
  <article key="assetChildrenNode" className="asset-content">
    (ReasonReact.arrayToElement(Method.buildContent(store, dispatch)))
  </article>;

let make = (~store: AppStore.appState, ~dispatch, _children) => {
  ...component,
  render: (self) => render(store, dispatch, self)
};