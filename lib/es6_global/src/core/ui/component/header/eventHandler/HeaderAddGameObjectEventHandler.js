'use strict';

import * as Curry                                from "../../../../../../../../node_modules/bs-platform/lib/es6/curry.js";
import * as Log$WonderLog                        from "../../../../../../../../node_modules/wonder-log/lib/es6_global/src/Log.js";
import * as AppStore$WonderEditor                from "../../../store/AppStore.js";
import * as EventHandler$WonderEditor            from "../../../eventHandler/EventHandler.js";
import * as SceneService$WonderEditor            from "../../../../../service/primitive/SceneService.js";
import * as EmptyEventHandler$WonderEditor       from "../../../eventHandler/EmptyEventHandler.js";
import * as StateLogicService$WonderEditor       from "../../../../../service/stateTuple/StateLogicService.js";
import * as SceneEngineService$WonderEditor      from "../../../../../service/state/engine/SceneEngineService.js";
import * as StateEngineService$WonderEditor      from "../../../../../service/state/engine/StateEngineService.js";
import * as SceneGraphDataUtils$WonderEditor     from "../../../../utils/SceneGraphDataUtils.js";
import * as MainEditorSceneTreeView$WonderEditor from "../../../../component/mainEditor/component/sceneTree/logic/view/MainEditorSceneTreeView.js";

var onSelect = EmptyEventHandler$WonderEditor.EmptyEventHandler[0];

var onDrop = EmptyEventHandler$WonderEditor.EmptyEventHandler[2];

var onMarkRedoUndo = EmptyEventHandler$WonderEditor.EmptyEventHandler[3];

function onClick(param, type_, _) {
  var match;
  if (type_ === "box") {
    var partial_arg = StateLogicService$WonderEditor.getEditorState(SceneService$WonderEditor.unsafeGetScene);
    match = StateLogicService$WonderEditor.getEngineState((function (param) {
            return SceneEngineService$WonderEditor.addBox(partial_arg, param);
          }));
  } else {
    match = Log$WonderLog.fatal(Log$WonderLog.buildFatalMessage("addGameObject", "specific type:" + (String(type_) + " should exist"), "", "", "type:" + (String(type_) + "")));
  }
  var newGameObject = match[0];
  StateEngineService$WonderEditor.setState(match[1]);
  var partial_arg$1 = SceneGraphDataUtils$WonderEditor.unsafeGetSceneGraphDataFromStore(param[0]);
  Curry._1(param[1], [
        AppStore$WonderEditor.SceneTreeAction,
        /* SetSceneGraph */[/* Some */[StateLogicService$WonderEditor.getState((function (param) {
                    return MainEditorSceneTreeView$WonderEditor.buildSceneGraphDataWithNewGameObject(newGameObject, partial_arg$1, param);
                  }))]]
      ]);
  return /* () */0;
}

var AddGameObjectEventHandler = /* module */[
  /* onSelect */onSelect,
  /* onDrop */onDrop,
  /* onMarkRedoUndo */onMarkRedoUndo,
  /* onClick */onClick
];

var MakeEventHandler = EventHandler$WonderEditor.MakeEventHandler([
      onSelect,
      onDrop,
      onClick,
      onMarkRedoUndo
    ]);

export {
  AddGameObjectEventHandler ,
  MakeEventHandler          ,
  
}
/* MakeEventHandler Not a pure module */
