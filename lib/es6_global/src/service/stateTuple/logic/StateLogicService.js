

import * as Curry from "../../../../../../node_modules/bs-platform/lib/es6/curry.js";
import * as StateEditorService$WonderEditor from "../../state/editor/StateEditorService.js";
import * as StateEngineService$WonderEditor from "../../state/engine/StateEngineService.js";
import * as DirectorEngineService$WonderEditor from "../../state/engine/DirectorEngineService.js";

function getEngineStateToGetData(handleFunc) {
  return Curry._1(handleFunc, StateEngineService$WonderEditor.unsafeGetState(/* () */0));
}

function getAndSetEngineState(handleFunc) {
  StateEngineService$WonderEditor.setState(Curry._1(handleFunc, StateEngineService$WonderEditor.unsafeGetState(/* () */0)));
  return /* () */0;
}

function refreshEngineState(engineState) {
  StateEngineService$WonderEditor.setState(DirectorEngineService$WonderEditor.loopBody(0, engineState));
  return /* () */0;
}

function refreshEngineStateAndReturnEngineState(engineState) {
  return DirectorEngineService$WonderEditor.loopBody(0, engineState);
}

function getAndRefreshEngineState() {
  StateEngineService$WonderEditor.setState(DirectorEngineService$WonderEditor.loopBody(0, StateEngineService$WonderEditor.unsafeGetState(/* () */0)));
  return /* () */0;
}

function getAndRefreshEngineStateWithFunc(handleFunc) {
  StateEngineService$WonderEditor.setState(DirectorEngineService$WonderEditor.loopBody(0, Curry._1(handleFunc, StateEngineService$WonderEditor.unsafeGetState(/* () */0))));
  return /* () */0;
}

function getEditorState(handleFunc) {
  return Curry._1(handleFunc, StateEditorService$WonderEditor.getState(/* () */0));
}

function getAndSetEditorState(handleFunc) {
  StateEditorService$WonderEditor.setState(Curry._1(handleFunc, StateEditorService$WonderEditor.getState(/* () */0)));
  return /* () */0;
}

function getStateToGetData(handleFunc) {
  return Curry._1(handleFunc, /* tuple */[
              StateEditorService$WonderEditor.getState(/* () */0),
              StateEngineService$WonderEditor.unsafeGetState(/* () */0)
            ]);
}

export {
  getEngineStateToGetData ,
  getAndSetEngineState ,
  refreshEngineState ,
  refreshEngineStateAndReturnEngineState ,
  getAndRefreshEngineState ,
  getAndRefreshEngineStateWithFunc ,
  getEditorState ,
  getAndSetEditorState ,
  getStateToGetData ,
  
}
/* StateEditorService-WonderEditor Not a pure module */
