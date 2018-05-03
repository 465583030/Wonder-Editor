open EditorType;

open EditorStateDataType;

let _createState = () => {
  assetRecord: {
    assetTree: None,
    index: 0,
    currentTreeNode: None,
    fileMap: WonderCommonlib.SparseMapService.createEmpty()
  },
  sceneRecord: {root: None, diffMap: None, currentGameObject: None, isRun: false},
  currentSign: "",
  loopId: (-1)
};

let editorStateData = {
  state: _createState(),
  isDebug: true,
  engineStateDataForEdit: StateEngineService.createStateData(),
  engineStateDataForRun: StateEngineService.createStateData()
};