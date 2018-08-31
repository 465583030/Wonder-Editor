open Wonderjs;

let create = GameObjectAPI.createGameObject;

let initGameObject = GameObjectAPI.initGameObject;

let disposeGameObject = GameObjectAPI.disposeGameObject;

let cloneGameObject = GameObjectAPI.cloneGameObject;

let disposeGameObjectKeepOrder = GameObjectAPI.disposeGameObjectKeepOrder;

let disposeGameObjectKeepOrderRemoveGeometry = GameObjectAPI.disposeGameObjectKeepOrderRemoveGeometry;

/* let hasGameObjectBoxGeometryComponent = GameObjectAPI.hasGameObjectBoxGeometryComponent; */
/*
 let hasGameObjectLightMaterialComponent = GameObjectAPI.hasGameObjectLightMaterialComponent; */

/* let hasGameObjectDirectionLightComponent = GameObjectAPI.hasGameObjectDirectionLightComponent;

   let hasGameObjectPointLightComponent = GameObjectAPI.hasGameObjectPointLightComponent; */

let getGameObjectName = GameObjectAPI.getGameObjectName;

let unsafeGetGameObjectName = GameObjectAPI.unsafeGetGameObjectName;

let setGameObjectName = (name, gameObject, engineState) =>
  GameObjectAPI.setGameObjectName(gameObject, name, engineState);

let getAllChildrenTransform = (rootGameObject, state) =>
  GameObjectAPI.getAllChildrenTransform(rootGameObject, state);

let getAllGameObjects = (rootGameObject, state) =>
  GameObjectAPI.getAllGameObjects(rootGameObject, state);

let disposeGameObjectArr = (gameObjectArr, engineState) =>
  gameObjectArr
  |> WonderCommonlib.ArrayService.reduceOneParam(
       (. state, gameObject) =>
         disposeGameObjectKeepOrder(gameObject, state),
       engineState,
     );