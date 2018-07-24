

import * as GeometryEngineService$WonderEditor from "./GeometryEngineService.js";
import * as GameObjectEngineService$WonderEditor from "./GameObjectEngineService.js";
import * as MeshRendererEngineService$WonderEditor from "./MeshRendererEngineService.js";
import * as LightMaterialEngineService$WonderEditor from "./LightMaterialEngineService.js";
import * as DirectionLightEngineService$WonderEditor from "./DirectionLightEngineService.js";
import * as GameObjectComponentEngineService$WonderEditor from "./GameObjectComponentEngineService.js";

function createBox(state) {
  var match = LightMaterialEngineService$WonderEditor.create(state);
  var match$1 = MeshRendererEngineService$WonderEditor.create(match[0]);
  var match$2 = GameObjectEngineService$WonderEditor.create(match$1[0]);
  var obj = match$2[1];
  var match$3 = GeometryEngineService$WonderEditor.createBoxGeometry(match$2[0]);
  var state$1 = GameObjectComponentEngineService$WonderEditor.addBoxGeometryComponent(obj, match$3[1], GameObjectComponentEngineService$WonderEditor.addMeshRendererComponent(obj, match$1[1], GameObjectComponentEngineService$WonderEditor.addLightMaterialComponent(obj, match[1], GameObjectEngineService$WonderEditor.setGameObjectName("cube", obj, match$3[0]))));
  return /* tuple */[
          state$1,
          obj
        ];
}

function createDirectionLight(state) {
  var match = GameObjectEngineService$WonderEditor.create(state);
  var obj = match[1];
  var match$1 = DirectionLightEngineService$WonderEditor.create(match[0]);
  var state$1 = GameObjectComponentEngineService$WonderEditor.addDirectionLightComponent(obj, match$1[1], GameObjectEngineService$WonderEditor.setGameObjectName("Direction Light", obj, match$1[0]));
  return /* tuple */[
          state$1,
          obj
        ];
}

export {
  createBox ,
  createDirectionLight ,
  
}
/* GeometryEngineService-WonderEditor Not a pure module */
