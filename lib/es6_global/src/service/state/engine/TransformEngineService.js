'use strict';

import * as Transform$Wonderjs from "../../../../../../node_modules/wonder.js/lib/es6_global/src/ecs/component/api/transform/Transform.js";

var getParent = Transform$Wonderjs.getTransformParent;

var setParent = Transform$Wonderjs.setTransformParent;

var setParentKeepOrder = Transform$Wonderjs.setTransformParentKeepOrder;

var getChildren = Transform$Wonderjs.getTransformChildren;

var getLocalPosition = Transform$Wonderjs.getTransformLocalPosition;

var setLocalPosition = Transform$Wonderjs.setTransformLocalPosition;

var getGameObjectByTransform = Transform$Wonderjs.getTransformGameObject;

export {
  getLocalPosition         ,
  setLocalPosition         ,
  getParent                ,
  setParent                ,
  setParentKeepOrder       ,
  getChildren              ,
  getGameObjectByTransform ,
  
}
/* Transform-Wonderjs Not a pure module */
