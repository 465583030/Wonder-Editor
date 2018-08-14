

import * as EventHandler$WonderEditor from "../../../../../../../../../../../ui/eventHandler/EventHandler.js";
import * as EmptyEventHandler$WonderEditor from "../../../../../../../../../../../ui/eventHandler/EmptyEventHandler.js";
import * as StateLogicService$WonderEditor from "../../../../../../../../../../../../service/stateTuple/logic/StateLogicService.js";
import * as StateEngineService$WonderEditor from "../../../../../../../../../../../../service/state/engine/StateEngineService.js";
import * as PerspectiveCameraProjectionEngineService$WonderEditor from "../../../../../../../../../../../../service/state/engine/PerspectiveCameraProjectionEngineService.js";

function setUndoValueToCopiedEngineState(_, perspectiveComponent, value) {
  return StateLogicService$WonderEditor.handleFuncWithDiff(/* array */[/* record */[
                /* arguments : array */[perspectiveComponent],
                /* type_ : PerspectiveCamera */8
              ]], (function (param, param$1) {
                return PerspectiveCameraProjectionEngineService$WonderEditor.setPerspectiveCameraAspect(value, param, param$1);
              }), /* tuple */[
              StateEngineService$WonderEditor.deepCopyForRestore(StateLogicService$WonderEditor.getEditEngineState(/* () */0)),
              StateEngineService$WonderEditor.deepCopyForRestore(StateLogicService$WonderEditor.getRunEngineState(/* () */0))
            ]);
}

var CustomEventHandler_000 = /* handleSelfLogic */EmptyEventHandler$WonderEditor.EmptyEventHandler[0];

var CustomEventHandler = /* module */[
  CustomEventHandler_000,
  /* setUndoValueToCopiedEngineState */setUndoValueToCopiedEngineState
];

var MakeEventHandler = EventHandler$WonderEditor.MakeEventHandler(CustomEventHandler);

export {
  CustomEventHandler ,
  MakeEventHandler ,
  
}
/* MakeEventHandler Not a pure module */