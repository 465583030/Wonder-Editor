

import * as Curry from "../../../../../../../../node_modules/bs-platform/lib/es6/curry.js";
import * as Caml_obj from "../../../../../../../../node_modules/bs-platform/lib/es6/caml_obj.js";
import * as Log$WonderLog from "../../../../../../../../node_modules/wonder-log/lib/es6_global/src/Log.js";
import * as Contract$WonderLog from "../../../../../../../../node_modules/wonder-log/lib/es6_global/src/Contract.js";
import * as AppStore$WonderEditor from "../../../../ui/store/AppStore.js";
import * as StoreUtils$WonderEditor from "../../../../utils/ui/StoreUtils.js";
import * as HeaderUtils$WonderEditor from "../../utils/HeaderUtils.js";
import * as EventHandler$WonderEditor from "../../../../ui/eventHandler/EventHandler.js";
import * as SceneTreeUtils$WonderEditor from "../../../mainEditor/composable_component/sceneTree/utils/SceneTreeUtils.js";
import * as EmptyEventHandler$WonderEditor from "../../../../ui/eventHandler/EmptyEventHandler.js";
import * as StateLogicService$WonderEditor from "../../../../../service/stateTuple/logic/StateLogicService.js";
import * as SceneEditorService$WonderEditor from "../../../../../service/state/editor/SceneEditorService.js";
import * as StateEditorService$WonderEditor from "../../../../../service/state/editor/StateEditorService.js";
import * as CameraEngineService$WonderEditor from "../../../../../service/state/engine/CameraEngineService.js";
import * as CurrentSceneTreeNodeLogicService$WonderEditor from "../../../../../service/stateTuple/logic/CurrentSceneTreeNodeLogicService.js";

var setUndoValueToCopiedEngineState = EmptyEventHandler$WonderEditor.EmptyEventHandler[1];

function _checkSceneGraphDataAndDispatch(dispatchFunc, newSceneGraphArr) {
  Contract$WonderLog.requireCheck((function () {
          return Contract$WonderLog.test(Log$WonderLog.buildAssertMessage("the newSceneGraphArr should equal the sceneGraph from engine", "not"), (function () {
                        return Contract$WonderLog.assertTrue(Caml_obj.caml_equal(StateLogicService$WonderEditor.getStateToGetData(SceneTreeUtils$WonderEditor.getSceneGraphDataFromEngine), newSceneGraphArr));
                      }));
        }), StateEditorService$WonderEditor.getStateIsDebug(/* () */0));
  Curry._1(dispatchFunc, [
        AppStore$WonderEditor.SceneTreeAction,
        /* SetSceneGraph */[newSceneGraphArr]
      ]);
  Curry._1(dispatchFunc, [
        AppStore$WonderEditor.UpdateAction,
        /* Update */[/* array */[
            /* Header */1,
            /* Inspector */2,
            /* SceneTree */4
          ]]
      ]);
  return /* () */0;
}

function _getRemovedSceneGraphData(sceneGraphArr) {
  var match = StateLogicService$WonderEditor.getEditorState(SceneEditorService$WonderEditor.getCurrentSceneTreeNode);
  if (match !== undefined) {
    var gameObject = match;
    var match$1 = StateLogicService$WonderEditor.getEngineStateToGetData((function (param) {
            return CameraEngineService$WonderEditor.isCamera(gameObject, param);
          }));
    if (match$1) {
      var match$2 = HeaderUtils$WonderEditor.doesSceneHasRemoveableCamera(/* () */0);
      if (match$2) {
        var match$3 = SceneTreeUtils$WonderEditor.removeDragedTreeNode(gameObject, sceneGraphArr);
        return /* tuple */[
                match$3[0],
                match$3[1]
              ];
      } else {
        Log$WonderLog.warn("can\'t remove last camera");
        return /* tuple */[
                sceneGraphArr,
                undefined
              ];
      }
    } else {
      var match$4 = SceneTreeUtils$WonderEditor.removeDragedTreeNode(gameObject, sceneGraphArr);
      return /* tuple */[
              match$4[0],
              match$4[1]
            ];
    }
  } else {
    Log$WonderLog.error(Log$WonderLog.buildErrorMessage("disposeCurrentSceneTreeNode", "current gameObject should exist, but actual is None", "", "set current gameObject", ""));
    return /* tuple */[
            sceneGraphArr,
            undefined
          ];
  }
}

function handleSelfLogic(param, _, _$1) {
  var sceneGraphArr = StoreUtils$WonderEditor.unsafeGetSceneGraphDataFromStore(param[0]);
  var match = _getRemovedSceneGraphData(sceneGraphArr);
  var removedTreeNode = match[1];
  if (removedTreeNode !== undefined) {
    CurrentSceneTreeNodeLogicService$WonderEditor.disposeCurrentSceneTreeNode(removedTreeNode);
  }
  return _checkSceneGraphDataAndDispatch(param[1], match[0]);
}

var CustomEventHandler = /* module */[
  /* setUndoValueToCopiedEngineState */setUndoValueToCopiedEngineState,
  /* _checkSceneGraphDataAndDispatch */_checkSceneGraphDataAndDispatch,
  /* _getRemovedSceneGraphData */_getRemovedSceneGraphData,
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
