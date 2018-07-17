

import * as Curry from "../../../../../../node_modules/bs-platform/lib/es6/curry.js";
import * as StateHistoryService$WonderEditor from "../../../service/stateTuple/history/StateHistoryService.js";
import * as MarkRedoUndoEventHandlerUtils$WonderEditor from "./utils/MarkRedoUndoEventHandlerUtils.js";

function MakeEventHandler(EventItem) {
  var onSelect = function (reduxTuple, prepareTuple, dataTuple) {
    MarkRedoUndoEventHandlerUtils$WonderEditor.markRedoUndoChangeUI(reduxTuple[0], StateHistoryService$WonderEditor.getStateForHistory(/* () */0));
    return Curry._3(EventItem[/* onSelect */0], reduxTuple, prepareTuple, dataTuple);
  };
  var onDrop = function (reduxTuple, prepareTuple, dataTuple) {
    MarkRedoUndoEventHandlerUtils$WonderEditor.markRedoUndoChangeUI(reduxTuple[0], StateHistoryService$WonderEditor.getStateForHistory(/* () */0));
    return Curry._3(EventItem[/* onDrop */1], reduxTuple, prepareTuple, dataTuple);
  };
  var onClick = function (reduxTuple, prepareTuple, dataTuple) {
    MarkRedoUndoEventHandlerUtils$WonderEditor.markRedoUndoChangeUI(reduxTuple[0], StateHistoryService$WonderEditor.getStateForHistory(/* () */0));
    return Curry._3(EventItem[/* onClick */2], reduxTuple, prepareTuple, dataTuple);
  };
  var onMarkRedoUndoByStackFirst = function (reduxTuple, prepareTuple, dataTuple) {
    return Curry._3(EventItem[/* onMarkRedoUndoByStackFirst */3], reduxTuple, prepareTuple, dataTuple);
  };
  var onMarkRedoUndoByStackLastReturnStore = function (reduxTuple, prepareTuple, dataTuple) {
    MarkRedoUndoEventHandlerUtils$WonderEditor.markRedoUndoChangeUI(reduxTuple[0], StateHistoryService$WonderEditor.getStateForHistory(/* () */0));
    Curry._3(EventItem[/* onMarkRedoUndoByStackLastReturnStore */4], reduxTuple, prepareTuple, dataTuple);
    return /* () */0;
  };
  return /* module */[
          /* onSelect */onSelect,
          /* onDrop */onDrop,
          /* onClick */onClick,
          /* onMarkRedoUndoByStackFirst */onMarkRedoUndoByStackFirst,
          /* onMarkRedoUndoByStackLastReturnStore */onMarkRedoUndoByStackLastReturnStore
        ];
}

export {
  MakeEventHandler ,
  
}
/* StateHistoryService-WonderEditor Not a pure module */
