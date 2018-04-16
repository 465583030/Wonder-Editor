'use strict';

import * as Curry                           from "../../../../../node_modules/bs-platform/lib/es6/curry.js";
import * as Immutable                       from "../../../../../node_modules/immutable-re/lib/es6_global/src/Immutable.js";
import * as Log$WonderLog                   from "../../../../../node_modules/wonder-log/lib/es6_global/src/Log.js";
import * as AppStore$WonderEditor           from "../ui/store/AppStore.js";
import * as AllStateData$WonderEditor       from "../../service/stateTuple/data/AllStateData.js";
import * as StateLogicService$WonderEditor  from "../../service/stateTuple/logic/StateLogicService.js";
import * as StateEngineService$WonderEditor from "../../service/state/engine/StateEngineService.js";

function copyHistoryStack(store, param, historyState) {
  var engineStateForEdit = StateEngineService$WonderEditor.deepCopyForRestore(param[1]);
  var engineStateForRun = StateEngineService$WonderEditor.deepCopyForRestore(param[2]);
  var newrecord = historyState.slice();
  return AllStateData$WonderEditor.setHistoryState((newrecord[/* copiedRedoUndoStackRecord */1] = /* record */[
                /* uiRedoStack */historyState[/* uiRedoStack */2],
                /* uiUndoStack */Immutable.Stack[/* addFirst */17](store, historyState[/* uiUndoStack */3]),
                /* editorRedoStack */historyState[/* editorRedoStack */4],
                /* editorUndoStack */Immutable.Stack[/* addFirst */17](param[0], historyState[/* editorUndoStack */5]),
                /* engineForEditRedoStack */historyState[/* engineForEditRedoStack */6],
                /* engineForEditUndoStack */Immutable.Stack[/* addFirst */17](engineStateForEdit, historyState[/* engineForEditUndoStack */7]),
                /* engineForRunRedoStack */historyState[/* engineForRunRedoStack */8],
                /* engineForRunUndoStack */Immutable.Stack[/* addFirst */17](engineStateForRun, historyState[/* engineForRunUndoStack */9])
              ], newrecord));
}

function restoreHistoryStack(dispatch, engineStateForEdit, engineStateForRun, historyState) {
  var match = Curry._1(Immutable.Stack[/* first */14], historyState[/* copiedRedoUndoStackRecord */1][/* uiUndoStack */1]);
  var match$1 = Curry._1(Immutable.Stack[/* first */14], historyState[/* copiedRedoUndoStackRecord */1][/* editorUndoStack */3]);
  var match$2 = Curry._1(Immutable.Stack[/* first */14], historyState[/* copiedRedoUndoStackRecord */1][/* engineForEditUndoStack */5]);
  var match$3 = Curry._1(Immutable.Stack[/* first */14], historyState[/* copiedRedoUndoStackRecord */1][/* engineForRunUndoStack */7]);
  var exit = 0;
  if (match) {
    if (match$1) {
      if (match$2) {
        if (match$3) {
          Curry._1(dispatch, [
                AppStore$WonderEditor.ReplaceState,
                match[0]
              ]);
          StateLogicService$WonderEditor.refreshStateForHistory(/* tuple */[
                match$1[0],
                StateEngineService$WonderEditor.restoreState(engineStateForEdit, match$2[0]),
                StateEngineService$WonderEditor.restoreState(engineStateForRun, match$3[0])
              ]);
          return AllStateData$WonderEditor.setHistoryState(/* record */[
                      /* markRedoUndoStack */historyState[/* markRedoUndoStack */0],
                      /* copiedRedoUndoStackRecord */historyState[/* copiedRedoUndoStackRecord */1],
                      /* uiRedoStack */historyState[/* copiedRedoUndoStackRecord */1][/* uiRedoStack */0],
                      /* uiUndoStack */Immutable.Stack[/* removeFirstOrRaise */19](historyState[/* copiedRedoUndoStackRecord */1][/* uiUndoStack */1]),
                      /* editorRedoStack */historyState[/* copiedRedoUndoStackRecord */1][/* editorRedoStack */2],
                      /* editorUndoStack */Immutable.Stack[/* removeFirstOrRaise */19](historyState[/* copiedRedoUndoStackRecord */1][/* editorUndoStack */3]),
                      /* engineForEditRedoStack */historyState[/* copiedRedoUndoStackRecord */1][/* engineForEditRedoStack */4],
                      /* engineForEditUndoStack */Immutable.Stack[/* removeFirstOrRaise */19](historyState[/* copiedRedoUndoStackRecord */1][/* engineForEditUndoStack */5]),
                      /* engineForRunRedoStack */historyState[/* copiedRedoUndoStackRecord */1][/* engineForRunRedoStack */6],
                      /* engineForRunUndoStack */Immutable.Stack[/* removeFirstOrRaise */19](historyState[/* copiedRedoUndoStackRecord */1][/* engineForRunUndoStack */7])
                    ]);
        } else {
          exit = 1;
        }
      } else {
        exit = 1;
      }
    } else {
      exit = 1;
    }
  } else {
    exit = 1;
  }
  if (exit === 1) {
    return Log$WonderLog.fatal(Log$WonderLog.buildFatalMessage("restoreHistoryStack", "expect history copiedRedoUndoStackRecord undo stack have value, but not", "", "check history copiedRedoUndoStackRecord undo stack", "historyState:" + (String(historyState) + "")));
  }
  
}

export {
  copyHistoryStack    ,
  restoreHistoryStack ,
  
}
/* Immutable Not a pure module */
