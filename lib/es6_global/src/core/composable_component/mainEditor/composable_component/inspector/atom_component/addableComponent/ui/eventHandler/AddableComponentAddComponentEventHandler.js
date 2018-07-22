

import * as Curry from "../../../../../../../../../../../../node_modules/bs-platform/lib/es6/curry.js";
import * as AppStore$WonderEditor from "../../../../../../../../ui/store/AppStore.js";
import * as EventHandler$WonderEditor from "../../../../../../../../ui/eventHandler/EventHandler.js";
import * as EmptyEventHandler$WonderEditor from "../../../../../../../../ui/eventHandler/EmptyEventHandler.js";
import * as StateLogicService$WonderEditor from "../../../../../../../../../service/stateTuple/logic/StateLogicService.js";
import * as InspectorComponentUtils$WonderEditor from "../../../../utils/InspectorComponentUtils.js";
import * as GameObjectComponentEngineService$WonderEditor from "../../../../../../../../../service/state/engine/GameObjectComponentEngineService.js";

var setUndoValueToCopiedEngineState = EmptyEventHandler$WonderEditor.EmptyEventHandler[1];

function handleSelfLogic(param, type_, currentSceneTreeNode) {
  StateLogicService$WonderEditor.getAndRefreshEngineStateWithDiff(/* array */[/* record */[
          /* arguments : array */[currentSceneTreeNode],
          /* type_ : GameObject */0
        ]], (function (param, param$1) {
          return InspectorComponentUtils$WonderEditor.addComponentByType(type_, param, param$1);
        }));
  StateLogicService$WonderEditor.getEngineStateToGetData((function (param) {
          return GameObjectComponentEngineService$WonderEditor.hasSourceInstanceComponent(currentSceneTreeNode, param);
        }));
  Curry._1(param[1], [
        AppStore$WonderEditor.UpdateAction,
        /* Update */[/* array */[/* Inspector */1]]
      ]);
  return /* () */0;
}

var CustomEventHandler = /* module */[
  /* setUndoValueToCopiedEngineState */setUndoValueToCopiedEngineState,
  /* handleSelfLogic */handleSelfLogic
];

var MakeEventHandler = EventHandler$WonderEditor.MakeEventHandler([
      handleSelfLogic,
      setUndoValueToCopiedEngineState
    ]);

export {
  CustomEventHandler ,
  MakeEventHandler ,
  
}
/* MakeEventHandler Not a pure module */
