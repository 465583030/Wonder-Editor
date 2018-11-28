

import * as ArrayService$WonderCommonlib from "../../../../../../node_modules/wonder-commonlib/lib/es6_global/src/ArrayService.js";
import * as TransformEngineService$WonderEditor from "../../../service/state/engine/TransformEngineService.js";
import * as PointLightEngineService$WonderEditor from "../../../service/state/engine/PointLightEngineService.js";
import * as MeshRendererEngineService$WonderEditor from "../../../service/state/engine/MeshRendererEngineService.js";
import * as DirectionLightEngineService$WonderEditor from "../../../service/state/engine/DirectionLightEngineService.js";
import * as GameObjectComponentEngineService$WonderEditor from "../../../service/state/engine/GameObjectComponentEngineService.js";

function setParentKeepOrder(parent, child, engineState) {
  return TransformEngineService$WonderEditor.setParentKeepOrder(GameObjectComponentEngineService$WonderEditor.unsafeGetTransformComponent(parent, engineState), GameObjectComponentEngineService$WonderEditor.unsafeGetTransformComponent(child, engineState), engineState);
}

function getParent(child, engineState) {
  return TransformEngineService$WonderEditor.getParent(GameObjectComponentEngineService$WonderEditor.unsafeGetTransformComponent(child, engineState), engineState);
}

function addChild(parent, child, engineState) {
  return TransformEngineService$WonderEditor.setParent(GameObjectComponentEngineService$WonderEditor.unsafeGetTransformComponent(parent, engineState), GameObjectComponentEngineService$WonderEditor.unsafeGetTransformComponent(child, engineState), engineState);
}

function getChildren(gameObject, engineState) {
  return TransformEngineService$WonderEditor.getChildren(GameObjectComponentEngineService$WonderEditor.unsafeGetTransformComponent(gameObject, engineState), engineState).map((function (transform) {
                return TransformEngineService$WonderEditor.getGameObjectByTransform(transform, engineState);
              }));
}

function hasChildren(gameObject, engineState) {
  return getChildren(gameObject, engineState).length > 0;
}

function setGameObjectIsRenderIfHasMeshRenderer(isRender, gameObject, engineState) {
  var _iterateGameObjectArr = function (gameObjectArr, engineState) {
    return ArrayService$WonderCommonlib.reduceOneParam((function (engineState, gameObject) {
                  var match = GameObjectComponentEngineService$WonderEditor.hasMeshRendererComponent(gameObject, engineState);
                  var engineState$1 = match ? MeshRendererEngineService$WonderEditor.setMeshRendererIsRender(GameObjectComponentEngineService$WonderEditor.unsafeGetMeshRendererComponent(gameObject, engineState), isRender, engineState) : engineState;
                  return _iterateGameObjectArr(getChildren(gameObject, engineState$1), engineState$1);
                }), engineState, gameObjectArr);
  };
  return _iterateGameObjectArr(/* array */[gameObject], engineState);
}

function setGameObjectIsRenderIfHasDirectionLight(isRender, gameObject, engineState) {
  var _iterateGameObjectArr = function (gameObjectArr, engineState) {
    return ArrayService$WonderCommonlib.reduceOneParam((function (engineState, gameObject) {
                  var match = GameObjectComponentEngineService$WonderEditor.hasDirectionLightComponent(gameObject, engineState);
                  var engineState$1 = match ? DirectionLightEngineService$WonderEditor.setDirectionLightIsRender(GameObjectComponentEngineService$WonderEditor.unsafeGetDirectionLightComponent(gameObject, engineState), isRender, engineState) : engineState;
                  return _iterateGameObjectArr(getChildren(gameObject, engineState$1), engineState$1);
                }), engineState, gameObjectArr);
  };
  return _iterateGameObjectArr(/* array */[gameObject], engineState);
}

function setGameObjectIsRenderIfHasPointLight(isRender, gameObject, engineState) {
  var _iterateGameObjectArr = function (gameObjectArr, engineState) {
    return ArrayService$WonderCommonlib.reduceOneParam((function (engineState, gameObject) {
                  var match = GameObjectComponentEngineService$WonderEditor.hasPointLightComponent(gameObject, engineState);
                  var engineState$1 = match ? PointLightEngineService$WonderEditor.setPointLightIsRender(GameObjectComponentEngineService$WonderEditor.unsafeGetPointLightComponent(gameObject, engineState), isRender, engineState) : engineState;
                  return _iterateGameObjectArr(getChildren(gameObject, engineState$1), engineState$1);
                }), engineState, gameObjectArr);
  };
  return _iterateGameObjectArr(/* array */[gameObject], engineState);
}

export {
  setParentKeepOrder ,
  getParent ,
  addChild ,
  getChildren ,
  hasChildren ,
  setGameObjectIsRenderIfHasMeshRenderer ,
  setGameObjectIsRenderIfHasDirectionLight ,
  setGameObjectIsRenderIfHasPointLight ,
  
}
/* ArrayService-WonderCommonlib Not a pure module */
