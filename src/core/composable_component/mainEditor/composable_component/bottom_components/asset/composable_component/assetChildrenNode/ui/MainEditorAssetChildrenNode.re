open AssetNodeType;

open AssetTreeNodeType;

open CurrentNodeDataType;

module Method = {
  let _isSelected = (currentNodeData, nodeId) =>
    switch (currentNodeData) {
    | None => false
    | Some({currentNodeId}) => AssetUtils.isIdEqual(nodeId, currentNodeId)
    };

  let showSpecificTreeNodeChildren =
      (
        (store, dispatchFunc),
        (dragImg, debounceTime, currentNodeData),
        (editorState, engineState),
        assetTreeNodeChildrenArr,
      ) =>
    assetTreeNodeChildrenArr
    |> Js.Array.map(({id as nodeId, type_}) =>
         switch (type_) {
         | Folder =>
           let {name}: folderResultType =
             editorState
             |> AssetFolderNodeMapEditorService.getFolderNodeMap
             |> WonderCommonlib.SparseMapService.unsafeGet(nodeId);

           <FolderBox
             key=(DomHelper.getRandomKey())
             store
             dispatchFunc
             dragImg
             imgSrc="./public/img/11.jpg"
             folderId=nodeId
             fileType=type_
             name
             isSelected=(_isSelected(currentNodeData, nodeId))
             widget=(AssetUtils.getWidget())
             debounceTime
             onDrop=(
               AssetTreeUtils.dragNodeToFolderFunc((store, dispatchFunc), ())
             )
             isWidget=AssetUtils.isWidget
             handleRelationError=AssetUtils.isTreeNodeRelationError
           />;
         | Texture =>
           let {textureIndex, imageId} =
             editorState
             |> AssetTextureNodeMapEditorService.getTextureNodeMap
             |> WonderCommonlib.SparseMapService.unsafeGet(nodeId);

           <FileBox
             key=(DomHelper.getRandomKey())
             store
             dispatchFunc
             dragImg
             imgSrc=(
               editorState
               |> AssetImageBase64MapEditorService.getImageBase64Map
               |> WonderCommonlib.SparseMapService.unsafeGet(imageId)
               |> (({base64}) => base64)
             )
             fileId=nodeId
             fileType=type_
             fileName=(
               BasicSourceTextureEngineService.unsafeGetBasicSourceTextureName(
                 textureIndex,
               )
               |> StateLogicService.getEngineStateToGetData
             )
             widget=(AssetUtils.getWidget())
             isSelected=(_isSelected(currentNodeData, nodeId))
           />;
         | Json =>
           let {name}: jsonResultType =
             editorState
             |> AssetJsonNodeMapEditorService.getJsonNodeMap
             |> WonderCommonlib.SparseMapService.unsafeGet(nodeId);

           <FileBox
             key=(DomHelper.getRandomKey())
             store
             dispatchFunc
             dragImg
             imgSrc="./public/img/12.jpg"
             fileId=nodeId
             fileType=type_
             fileName=name
             widget=(AssetUtils.getWidget())
             isSelected=(_isSelected(currentNodeData, nodeId))
           />;
         | Material =>
           let baseName =
             AssetMaterialNodeMapLogicService.getMaterialBaseName(
               nodeId,
               engineState,
               editorState
               |> AssetMaterialNodeMapEditorService.getMaterialNodeMap,
             );

           <FileBox
             key=(DomHelper.getRandomKey())
             store
             dispatchFunc
             dragImg
             imgSrc="./public/img/12.jpg"
             fileId=nodeId
             fileType=type_
             fileName=baseName
             widget=(AssetUtils.getWidget())
             isSelected=(_isSelected(currentNodeData, nodeId))
           />;
         | WDB =>
           let {name}: wdbResultType =
             editorState
             |> AssetWDBNodeMapEditorService.getWDBNodeMap
             |> WonderCommonlib.SparseMapService.unsafeGet(nodeId);

           <FileBox
             key=(DomHelper.getRandomKey())
             store
             dispatchFunc
             dragImg
             imgSrc="./public/img/12.jpg"
             fileId=nodeId
             fileType=type_
             fileName=name
             widget=(AssetUtils.getWidget())
             isSelected=(_isSelected(currentNodeData, nodeId))
           />;
         }
       );

  let buildCurrentTreeNodeChildrenComponent =
      ((store, dispatchFunc), dragImg, debounceTime) => {
    let editorState = StateEditorService.getState();
    let engineState = StateEngineService.unsafeGetState();

    editorState
    |> AssetTreeRootEditorService.unsafeGetAssetTreeRoot
    |> AssetUtils.getSpecificTreeNodeById(
         editorState |> AssetUtils.getTargetTreeNodeId,
       )
    |> OptionService.unsafeGet
    |> (currentParentNode => currentParentNode.children)
    |> showSpecificTreeNodeChildren(
         (store, dispatchFunc),
         (
           dragImg,
           debounceTime,
           editorState |> AssetCurrentNodeDataEditorService.getCurrentNodeData,
         ),
         (editorState, engineState),
       );
  };
};

let component = ReasonReact.statelessComponent("MainEditorAssetHeader");

let render = ((store, dispatchFunc), dragImg, debounceTime, _self) =>
  <article key="assetChildrenNode" className="wonder-asset-assetChildren">
    (
      ReasonReact.array(
        Method.buildCurrentTreeNodeChildrenComponent(
          (store, dispatchFunc),
          dragImg,
          debounceTime,
        ),
      )
    )
  </article>;

let make = (~store, ~dispatchFunc, ~dragImg, ~debounceTime, _children) => {
  ...component,
  render: self => render((store, dispatchFunc), dragImg, debounceTime, self),
};