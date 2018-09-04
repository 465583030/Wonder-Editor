open AssetNodeType;
let handleSpeficFuncByAssetNodeType =
    (
      type_,
      (
        handleFodlerFunc,
        handleJsonFunc,
        handleTextureFunc,
        handleMaterialFunc,
        handleWDBFunc,
      ),
    ) =>
  switch (type_) {
  | Folder =>
    StateEditorService.getState()
    |> AssetFolderNodeMapEditorService.getFolderNodeMap
    |> handleFodlerFunc
  | Texture =>
    StateEditorService.getState()
    |> AssetTextureNodeMapEditorService.getTextureNodeMap
    |> handleTextureFunc
  | Json =>
    StateEditorService.getState()
    |> AssetJsonNodeMapEditorService.getJsonNodeMap
    |> handleJsonFunc
  | Material =>
    StateEditorService.getState()
    |> AssetMaterialNodeMapEditorService.getMaterialNodeMap
    |> handleMaterialFunc
  | WDB =>
    StateEditorService.getState()
    |> AssetWDBNodeMapEditorService.getWDBNodeMap
    |> handleWDBFunc
  };