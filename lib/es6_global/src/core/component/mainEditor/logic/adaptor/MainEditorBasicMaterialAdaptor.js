'use strict';

import * as Material$Wonderjs      from "../../../../../../../../node_modules/wonder.js/lib/es6_global/src/ecs/component/api/material/Material.js";
import * as BasicMaterial$Wonderjs from "../../../../../../../../node_modules/wonder.js/lib/es6_global/src/ecs/component/api/material/BasicMaterial.js";

var create = BasicMaterial$Wonderjs.createBasicMaterial;

var getBasicMaterialColor = Material$Wonderjs.getMaterialColor;

var setBasicMaterialColor = Material$Wonderjs.setMaterialColor;

export {
  create                ,
  getBasicMaterialColor ,
  setBasicMaterialColor ,
  
}
/* Material-Wonderjs Not a pure module */
