'use strict';

import * as Curry                            from "../../../../../../../../../../node_modules/bs-platform/lib/es6/curry.js";
import * as AppStore$WonderEditor            from "../../../../../../ui/store/AppStore.js";
import * as EventHandler$WonderEditor        from "../../../../../../ui/eventHandler/EventHandler.js";
import * as SceneTreeUtils$WonderEditor      from "../../utils/SceneTreeUtils.js";
import * as GameObjectUtils$WonderEditor     from "../../../../../../utils/GameObjectUtils.js";
import * as EmptyEventHandler$WonderEditor   from "../../../../../../ui/eventHandler/EmptyEventHandler.js";
import * as StateLogicService$WonderEditor   from "../../../../../../../service/stateTuple/logic/StateLogicService.js";
import * as SceneTreeStoreUtils$WonderEditor from "../../utils/SceneTreeStoreUtils.js";

var onSelect = EmptyEventHandler$WonderEditor.EmptyEventHandler[0];

var onClick = EmptyEventHandler$WonderEditor.EmptyEventHandler[1];

var onMarkRedoUndoByFirstStack = EmptyEventHandler$WonderEditor.EmptyEventHandler[3];

var onMarkRedoUndoByLastStack = EmptyEventHandler$WonderEditor.EmptyEventHandler[4];

function onDrop(param, _, param$1) {
  var dragedUid = param$1[1];
  var targetUid = param$1[0];
  var dispatch = param[1];
  var match = StateLogicService$WonderEditor.getEngineStateToGetData((function (param) {
          return SceneTreeUtils$WonderEditor.isGameObjectRelationError(targetUid, dragedUid, param);
        }));
  if (match !== 0) {
    Curry._1(dispatch, AppStore$WonderEditor.ReLoad);
    return /* () */0;
  } else {
    StateLogicService$WonderEditor.getAndRefreshEngineStateWithDiff(/* int array */[
          targetUid,
          dragedUid
        ], /* GameObject */0, GameObjectUtils$WonderEditor.setParentKeepOrder);
    Curry._1(dispatch, [
          AppStore$WonderEditor.SceneTreeAction,
          /* SetSceneGraph */[/* Some */[SceneTreeUtils$WonderEditor.getDragedSceneGraphData(targetUid, dragedUid, SceneTreeStoreUtils$WonderEditor.unsafeGetSceneGraphDataFromStore(param[0]))]]
        ]);
    return /* () */0;
  }
}

var DragEventHandler = /* module */[
  /* onSelect */onSelect,
  /* onClick */onClick,
  /* onMarkRedoUndoByFirstStack */onMarkRedoUndoByFirstStack,
  /* onMarkRedoUndoByLastStack */onMarkRedoUndoByLastStack,
  /* onDrop */onDrop
];

var MakeEventHandler = EventHandler$WonderEditor.MakeEventHandler([
      onSelect,
      onDrop,
      onClick,
      onMarkRedoUndoByFirstStack,
      onMarkRedoUndoByLastStack
    ]);

export {
  DragEventHandler ,
  MakeEventHandler ,
  
}
/* MakeEventHandler Not a pure module */
