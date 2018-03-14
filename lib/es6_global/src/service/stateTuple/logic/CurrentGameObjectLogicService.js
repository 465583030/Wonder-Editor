'use strict';

import * as StateLogicService$WonderEditor       from "./StateLogicService.js";
import * as SceneEditorService$WonderEditor      from "../../state/editor/SceneEditorService.js";
import * as GameObjectEngineService$WonderEditor from "../../state/engine/GameObjectEngineService.js";

function disposeCurrentGameObject(gameObject) {
  StateLogicService$WonderEditor.getAndSetEngineState((function (param) {
          return GameObjectEngineService$WonderEditor.disposeGameObject(gameObject, param);
        }));
  return StateLogicService$WonderEditor.getAndSetEditorState(SceneEditorService$WonderEditor.clearCurrentGameObject);
}

export {
  disposeCurrentGameObject ,
  
}
/* StateLogicService-WonderEditor Not a pure module */
