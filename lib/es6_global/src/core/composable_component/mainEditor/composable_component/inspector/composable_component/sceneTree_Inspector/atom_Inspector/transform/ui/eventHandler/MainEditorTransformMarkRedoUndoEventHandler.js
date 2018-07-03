

import * as Curry from "../../../../../../../../../../../../../../node_modules/bs-platform/lib/es6/curry.js";
import * as AppStore$WonderEditor from "../../../../../../../../../../ui/store/AppStore.js";
import * as EventHandler$WonderEditor from "../../../../../../../../../../ui/eventHandler/EventHandler.js";
import * as EmptyEventHandler$WonderEditor from "../../../../../../../../../../ui/eventHandler/EmptyEventHandler.js";

var onSelect = EmptyEventHandler$WonderEditor.EmptyEventHandler[0];

var onClick = EmptyEventHandler$WonderEditor.EmptyEventHandler[1];

var onDrop = EmptyEventHandler$WonderEditor.EmptyEventHandler[2];

var onMarkRedoUndoByStackLast = EmptyEventHandler$WonderEditor.EmptyEventHandler[4];

function onMarkRedoUndoByStackFirst(param, _, _$1) {
  Curry._1(param[1], AppStore$WonderEditor.ReLoad);
  return /* () */0;
}

var MarkRedoUndoEventHandler = /* module */[
  /* onSelect */onSelect,
  /* onClick */onClick,
  /* onDrop */onDrop,
  /* onMarkRedoUndoByStackLast */onMarkRedoUndoByStackLast,
  /* onMarkRedoUndoByStackFirst */onMarkRedoUndoByStackFirst
];

var MakeEventHandler = EventHandler$WonderEditor.MakeEventHandler([
      onSelect,
      onDrop,
      onClick,
      onMarkRedoUndoByStackFirst,
      onMarkRedoUndoByStackLast
    ]);

export {
  MarkRedoUndoEventHandler ,
  MakeEventHandler ,
  
}
/* MakeEventHandler Not a pure module */
