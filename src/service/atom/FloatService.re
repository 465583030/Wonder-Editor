let truncateFloatValue = (value: float, count: int) => {
  let res = DomHelper.toFixed(value, count);

  DomHelper.makeStringToFloat(res);
};