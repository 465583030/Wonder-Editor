open EditorType;

open AssetNodeType;

let getResult = (nodeId, editorState) =>
  editorState.assetRecord |> TextureNodeMapAssetService.getResult(nodeId);

let getTextureComponent = (nodeId, editorState) =>
  (getResult(nodeId, editorState) |> OptionService.unsafeGet).
    textureComponent;

let setTextureName = (nodeId, name, editorState) => {
  let textureComponent = getTextureComponent(nodeId, editorState);

  editorState
  |> ImageNodeMapAssetEditorService.setResult(
       textureComponent,
       {
         ...
           ImageNodeMapAssetEditorService.unsafeGetResult(
             textureComponent,
             editorState,
           ),
         name,
       },
     );
};

let hasTextureComponent = (material, editorState) =>
  TextureNodeMapAssetEditorService.getValidValues(editorState)
  |> Js.Array.find(({textureComponent}: AssetNodeType.textureResultType) =>
       JudgeTool.isEqual(textureComponent, material)
     )
  |> Js.Option.isSome;

let findTextureNodeIdByTextureComponent = (texture, editorState) =>
  switch (
    editorState
    |> TextureNodeMapAssetEditorService.getTextureNodeMap
    |> SparseMapService.getValidDataArr
    |> Js.Array.find(
         ((_, {textureComponent}: AssetNodeType.textureResultType)) =>
         textureComponent === texture
       )
  ) {
  | None => None
  | Some((textureNodeId, _)) => Some(textureNodeId)
  };

  let buildTextureAssetName= (imageName) => FileNameService.getBaseName(
                                            imageName,
                                          )