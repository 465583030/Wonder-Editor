let truncateTransformValue = ((x, y, z)) => {
  let truncateLen = 6;
  (
    FloatService.truncateFloatValue(x, truncateLen),
    FloatService.truncateFloatValue(y, truncateLen),
    FloatService.truncateFloatValue(z, truncateLen),
  );
};

let getSceneTreeNodeLocalPosition = transformComponent =>
  TransformEngineService.getLocalPosition(transformComponent)
  |> StateLogicService.getEngineStateToGetData;

let getTransformPositionData = transformComponent =>
  getSceneTreeNodeLocalPosition(transformComponent) |> truncateTransformValue;

let getTransformScaleData = transformComponent =>
  TransformEngineService.getLocalScale(transformComponent)
  |> StateLogicService.getEngineStateToGetData
  |> truncateTransformValue;