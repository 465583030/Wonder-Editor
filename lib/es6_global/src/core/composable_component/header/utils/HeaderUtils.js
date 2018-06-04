

import * as Js from "../../../../../../../node_modules/bs-platform/lib/es6/js.js";
import * as GameObjectUtils$WonderEditor from "../../../utils/GameObjectUtils.js";
import * as StateLogicService$WonderEditor from "../../../../service/stateTuple/logic/StateLogicService.js";
import * as SceneEditorService$WonderEditor from "../../../../service/state/editor/SceneEditorService.js";
import * as CameraEngineService$WonderEditor from "../../../../service/state/engine/CameraEngineService.js";

function doesSceneHasRemoveableCamera() {
  var match = StateLogicService$WonderEditor.getEngineStateToGetData((function (engineState) {
          return GameObjectUtils$WonderEditor.getChildren(StateLogicService$WonderEditor.getEditorState(SceneEditorService$WonderEditor.unsafeGetScene), engineState).filter((function (gameObject) {
                        return StateLogicService$WonderEditor.getEngineStateToGetData((function (param) {
                                      return CameraEngineService$WonderEditor.isCamera(gameObject, param);
                                    }));
                      })).length;
        }));
  return match !== 1;
}

function isGameObjectNotRemoveable(gameObject) {
  if (gameObject) {
    var gameObject$1 = gameObject[0];
    var match = StateLogicService$WonderEditor.getEngineStateToGetData((function (param) {
            return CameraEngineService$WonderEditor.isCamera(gameObject$1, param);
          }));
    if (match) {
      return !doesSceneHasRemoveableCamera(/* () */0);
    } else {
      return Js.false_;
    }
  } else {
    return Js.true_;
  }
}

export {
  doesSceneHasRemoveableCamera ,
  isGameObjectNotRemoveable ,
  
}
/* GameObjectUtils-WonderEditor Not a pure module */
