let _getFromArray = (array, index) => ArrayService.getNth(index, array);

let triggerClickCameraAddComponentEvent = domChildren => {
  let articleParent = WonderCommonlib.ArrayService.unsafeGet(domChildren, 0);

  let article =
    WonderCommonlib.ArrayService.unsafeGet(articleParent##children, 4);
  let button = WonderCommonlib.ArrayService.unsafeGet(article##children, 0);
  BaseEventTool.triggerClickEvent(button);
};
let triggerClickAddComponentEvent = domChildren => {
  let articleParent = WonderCommonlib.ArrayService.unsafeGet(domChildren, 0);

  let article =
    WonderCommonlib.ArrayService.unsafeGet(articleParent##children, 3);
  let button = WonderCommonlib.ArrayService.unsafeGet(article##children, 0);
  BaseEventTool.triggerClickEvent(button);
};

let triggerClickAddArcballCamera = domChildren => {
  let articleParent = WonderCommonlib.ArrayService.unsafeGet(domChildren, 0);
  let article =
    WonderCommonlib.ArrayService.unsafeGet(articleParent##children, 4);

  let arcballDiv =
    WonderCommonlib.ArrayService.unsafeGet(article##children, 1);

  BaseEventTool.triggerClickEvent(arcballDiv);
};

let triggerClickAddLightEvent = domChildren => {
  let articleParent = WonderCommonlib.ArrayService.unsafeGet(domChildren, 0);
  let article =
    WonderCommonlib.ArrayService.unsafeGet(articleParent##children, 3);
  let lightDiv = WonderCommonlib.ArrayService.unsafeGet(article##children, 1);
  BaseEventTool.triggerClickEvent(lightDiv);
};

let triggerClickAddSourceInstanceEvent = domChildren => {
  let articleParent = WonderCommonlib.ArrayService.unsafeGet(domChildren, 0);
  let article =
    WonderCommonlib.ArrayService.unsafeGet(articleParent##children, 3);
  let sourceInstanceDiv =
    WonderCommonlib.ArrayService.unsafeGet(article##children, 2);
  BaseEventTool.triggerClickEvent(sourceInstanceDiv);
};

let triggerShowColorPickEvent = domChildren => {
  let articleParent = WonderCommonlib.ArrayService.unsafeGet(domChildren, 4);
  let div =
    WonderCommonlib.ArrayService.unsafeGet(articleParent##children, 0);
  let colorPickArticle =
    WonderCommonlib.ArrayService.unsafeGet(div##children, 0);
  let colorPickDiv =
    WonderCommonlib.ArrayService.unsafeGet(colorPickArticle##children, 0);

  let button =
    WonderCommonlib.ArrayService.unsafeGet(colorPickDiv##children, 2);
  BaseEventTool.triggerClickEvent(button);
};

let triggerCloseColorPickEvent = domChildren => {
  let articleParent = WonderCommonlib.ArrayService.unsafeGet(domChildren, 4);
  let div =
    WonderCommonlib.ArrayService.unsafeGet(articleParent##children, 0);
  let colorPickArticle =
    WonderCommonlib.ArrayService.unsafeGet(div##children, 0);
  let colorPickDiv =
    WonderCommonlib.ArrayService.unsafeGet(colorPickArticle##children, 0);

  let div = WonderCommonlib.ArrayService.unsafeGet(colorPickDiv##children, 3);
  let closeDiv = WonderCommonlib.ArrayService.unsafeGet(div##children, 1);

  BaseEventTool.triggerClickEvent(closeDiv);
};