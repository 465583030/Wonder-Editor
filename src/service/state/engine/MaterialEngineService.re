let hasMaterialComponent = (gameObject, engineState) =>
  engineState
  |> GameObjectComponentEngineService.hasBasicMaterialComponent(gameObject)
  || engineState
  |> GameObjectComponentEngineService.hasLightMaterialComponent(gameObject);

let getMaterialComponent = GameObjectComponentEngineService.getLightMaterialComponent;