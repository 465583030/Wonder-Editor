open EditorType;
open AssetNodeType;

let getWDBNodeMap = editorState =>
  editorState.assetRecord |> WDBNodeMapAssetService.getWDBNodeMap;

let setWDBNodeMap = (wdbNodeMap, editorState) => {
  ...editorState,
  assetRecord:
    editorState.assetRecord
    |> WDBNodeMapAssetService.setWDBNodeMap(wdbNodeMap),
};

let setResult = (index, result, editorState) => {
  ...editorState,
  assetRecord:
    editorState.assetRecord |> WDBNodeMapAssetService.setResult(index, result),
};

let getWDBBaseName = (currentNodeId, wdbNodeMap) =>
  wdbNodeMap
  |> WonderCommonlib.SparseMapService.unsafeGet(currentNodeId)
  |> (({name}: wdbResultType) => name);

let getWDBTotalName = (currentNodeId, wdbNodeMap) =>
  wdbNodeMap
  |> WonderCommonlib.SparseMapService.unsafeGet(currentNodeId)
  |> (({name, extName}: wdbResultType) => name ++ extName);

let getWDBParentId = (currentNodeId, wdbNodeMap) =>
  wdbNodeMap
  |> WonderCommonlib.SparseMapService.unsafeGet(currentNodeId)
  |> (({parentFolderNodeId}: wdbResultType) => parentFolderNodeId);

let buildWDBNodeResult =
    (name, extName, parentFolderNodeId, wdbGameObject, wdbArrayBuffer) => {
  name,
  extName,
  parentFolderNodeId,
  wdbGameObject,
  wdbArrayBuffer,
};

let renameWDBNodeResult = (name, wdbNodeResult) : wdbResultType => {
  ...wdbNodeResult,
  name,
};

let setWDBNodeResultParent =
    (parentFolderNodeId, wdbNodeResult)
    : wdbResultType => {
  ...wdbNodeResult,
  parentFolderNodeId,
};