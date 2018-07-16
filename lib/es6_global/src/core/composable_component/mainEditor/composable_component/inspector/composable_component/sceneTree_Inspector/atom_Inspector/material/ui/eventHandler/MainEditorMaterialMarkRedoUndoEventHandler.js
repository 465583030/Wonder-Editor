

import * as Curry from "../../../../../../../../../../../../../../node_modules/bs-platform/lib/es6/curry.js";
import * as AppStore$WonderEditor from "../../../../../../../../../../ui/store/AppStore.js";
import * as EventHandler$WonderEditor from "../../../../../../../../../../ui/eventHandler/EventHandler.js";
import * as EmptyEventHandler$WonderEditor from "../../../../../../../../../../ui/eventHandler/EmptyEventHandler.js";
import * as StateLogicService$WonderEditor from "../../../../../../../../../../../service/stateTuple/logic/StateLogicService.js";
import * as BasicMaterialEngineService$WonderEditor from "../../../../../../../../../../../service/state/engine/BasicMaterialEngineService.js";

var onSelect = EmptyEventHandler$WonderEditor.EmptyEventHandler[0];

var onClick = EmptyEventHandler$WonderEditor.EmptyEventHandler[1];

var onDrop = EmptyEventHandler$WonderEditor.EmptyEventHandler[2];

var onMarkRedoUndoByStackFirst = EmptyEventHandler$WonderEditor.EmptyEventHandler[3];

function onMarkRedoUndoByStackLastReturnStore(param, materialComponent, value) {
  StateLogicService$WonderEditor.getAndRefreshEngineStateWithDiff(/* array */[/* record */[
          /* arguments : array */[materialComponent],
          /* type_ : Material */2
        ]], (function (param, param$1) {
          return BasicMaterialEngineService$WonderEditor.setColor(value, param, param$1);
        }));
  Curry._1(param[1], AppStore$WonderEditor.ReLoad);
  return param[0];
}

var MarkRedoUndoEventHandler = /* module */[
  /* onSelect */onSelect,
  /* onClick */onClick,
  /* onDrop */onDrop,
  /* onMarkRedoUndoByStackFirst */onMarkRedoUndoByStackFirst,
  /* onMarkRedoUndoByStackLastReturnStore */onMarkRedoUndoByStackLastReturnStore
];

var MakeEventHandler = EventHandler$WonderEditor.MakeEventHandler([
      onSelect,
      onDrop,
      onClick,
      onMarkRedoUndoByStackFirst,
      onMarkRedoUndoByStackLastReturnStore
    ]);

export {
  MarkRedoUndoEventHandler ,
  MakeEventHandler ,
  
}
/* MakeEventHandler Not a pure module */
