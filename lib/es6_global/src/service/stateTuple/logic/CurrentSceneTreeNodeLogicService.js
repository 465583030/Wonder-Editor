

import * as StateLogicService$WonderEditor from "./StateLogicService.js";
import * as SceneEditorService$WonderEditor from "../../state/editor/SceneEditorService.js";
import * as GameObjectEngineService$WonderEditor from "../../state/engine/GameObjectEngineService.js";

function disposeCurrentSceneTreeNode(gameObject) {
  StateLogicService$WonderEditor.getAndRefreshEngineStateWithDiff(/* array */[/* record */[
          /* arguments : array */[gameObject],
          /* type_ : GameObject */0
        ]], GameObjectEngineService$WonderEditor.disposeGameObjectKeepOrder);
  return StateLogicService$WonderEditor.getAndSetEditorState(SceneEditorService$WonderEditor.clearCurrentSceneTreeNode);
}

export {
  disposeCurrentSceneTreeNode ,
  
}
/* StateLogicService-WonderEditor Not a pure module */
