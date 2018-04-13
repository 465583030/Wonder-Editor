'use strict';

import * as AllStateData$WonderEditor                 from "../../service/stateTuple/data/AllStateData.js";
import * as LoopEngineService$WonderEditor            from "../../service/state/engine/LoopEngineService.js";
import * as StateLogicService$WonderEditor            from "../../service/stateTuple/logic/StateLogicService.js";
import * as ControllerHistoryUtils$WonderEditor       from "./ControllerHistoryUtils.js";
import * as EngineStateDataEditorService$WonderEditor from "../../service/state/editor/EngineStateDataEditorService.js";

function run(store) {
  EngineStateDataEditorService$WonderEditor.setIsRun(/* true */1);
  ControllerHistoryUtils$WonderEditor.copyHistoryStack(store, StateLogicService$WonderEditor.getStateForHistory(/* () */0), AllStateData$WonderEditor.getHistoryState(/* () */0));
  LoopEngineService$WonderEditor.loop(/* () */0);
  return /* () */0;
}

function stop(dispatch) {
  EngineStateDataEditorService$WonderEditor.setIsRun(/* false */0);
  return ControllerHistoryUtils$WonderEditor.restoreHistoryStack(dispatch, StateLogicService$WonderEditor.getEditEngineState(/* () */0), StateLogicService$WonderEditor.getRunEngineState(/* () */0), AllStateData$WonderEditor.getHistoryState(/* () */0));
}

export {
  run  ,
  stop ,
  
}
/* AllStateData-WonderEditor Not a pure module */
