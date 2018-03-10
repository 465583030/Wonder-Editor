'use strict';

import * as Caml_obj                                      from "../../../../../../../../../../node_modules/bs-platform/lib/es6/caml_obj.js";
import * as Log$WonderLog                                 from "../../../../../../../../../../node_modules/wonder-log/lib/es6_global/src/Log.js";
import * as Contract$WonderLog                            from "../../../../../../../../../../node_modules/wonder-log/lib/es6_global/src/Contract.js";
import * as ArrayService$WonderEditor                     from "../../../../../../../service/atom/ArrayService.js";
import * as StateLogicService$WonderEditor                from "../../../../../../../service/stateTuple/StateLogicService.js";
import * as StateEditorService$WonderEditor               from "../../../../../../../service/state/editor/StateEditorService.js";
import * as MainEditorSceneEdit$WonderEditor              from "../../../../logic/edit/MainEditorSceneEdit.js";
import * as TransformEngineService$WonderEditor           from "../../../../../../../service/state/engine/TransformEngineService.js";
import * as GameObjectEngineService$WonderEditor          from "../../../../../../../service/state/engine/GameObjectEngineService.js";
import * as GameObjectComponentEngineService$WonderEditor from "../../../../../../../service/state/engine/GameObjectComponentEngineService.js";

function _isDragedGameObjectBeTargetGameObjectParent(targetGameObject, dragedGameObject, engineState) {
  var _targetTransform = GameObjectComponentEngineService$WonderEditor.getTransformComponent(targetGameObject, engineState);
  var dragedTransform = GameObjectComponentEngineService$WonderEditor.getTransformComponent(dragedGameObject, engineState);
  var engineState$1 = engineState;
  while(true) {
    var targetTransform = _targetTransform;
    var match = TransformEngineService$WonderEditor.getParent(targetTransform, engineState$1);
    if (match == null) {
      return /* false */0;
    } else {
      var match$1 = +(match === dragedTransform);
      if (match$1 !== 0) {
        return /* true */1;
      } else {
        _targetTransform = match;
        continue ;
        
      }
    }
  };
}

function isGameObjectRelationError(targetGameObject, dragedGameObject, param) {
  var match = +(targetGameObject === dragedGameObject);
  if (match !== 0) {
    return /* true */1;
  } else {
    return _isDragedGameObjectBeTargetGameObjectParent(targetGameObject, dragedGameObject, param[1]);
  }
}

function setParent(parentGameObject, childGameObject, param) {
  var engineState = param[1];
  return /* tuple */[
          param[0],
          TransformEngineService$WonderEditor.setParent(GameObjectComponentEngineService$WonderEditor.getTransformComponent(parentGameObject, engineState), GameObjectComponentEngineService$WonderEditor.getTransformComponent(childGameObject, engineState), engineState)
        ];
}

function setTransformParentKeepOrder(parentGameObject, childGameObject, param) {
  var engineState = param[1];
  return /* tuple */[
          param[0],
          TransformEngineService$WonderEditor.setParentKeepOrder(GameObjectComponentEngineService$WonderEditor.getTransformComponent(parentGameObject, engineState), GameObjectComponentEngineService$WonderEditor.getTransformComponent(childGameObject, engineState), engineState)
        ];
}

function _getGameObjectName(gameObject, engineState) {
  var match = GameObjectComponentEngineService$WonderEditor.hasCameraControllerComponent(gameObject, engineState);
  if (match !== 0) {
    return "camera";
  } else {
    return "gameObject" + (String(gameObject) + "");
  }
}

function _buildTreeNode(gameObject, engineState) {
  return /* record */[
          /* name */_getGameObjectName(gameObject, engineState),
          /* uid */gameObject,
          /* children : array */[]
        ];
}

function _buildSceneGraphData(gameObject, engineState) {
  var _buildSceneGraphDataRec = function (gameObject, treeNode, engineState) {
    var match = GameObjectEngineService$WonderEditor.hasChildren(gameObject, engineState);
    if (match !== 0) {
      return GameObjectEngineService$WonderEditor.getChildren(gameObject, engineState).reduce((function (treeNode, child) {
                    return /* record */[
                            /* name */treeNode[/* name */0],
                            /* uid */treeNode[/* uid */1],
                            /* children */ArrayService$WonderEditor.push(_buildSceneGraphDataRec(child, _buildTreeNode(child, engineState), engineState), treeNode[/* children */2].slice())
                          ];
                  }), treeNode);
    } else {
      return treeNode;
    }
  };
  return _buildSceneGraphDataRec(gameObject, _buildTreeNode(gameObject, engineState), engineState);
}

function getSceneGraphDataFromEngine(param) {
  return /* array */[_buildSceneGraphData(MainEditorSceneEdit$WonderEditor.unsafeGetScene(param[0]), param[1])];
}

function buildSceneGraphDataWithNewGameObject(newGameObject, oldSceneGraphData, param) {
  var scene = ArrayService$WonderEditor.getFirst(oldSceneGraphData);
  return /* array */[/* record */[
            /* name */scene[/* name */0],
            /* uid */scene[/* uid */1],
            /* children */ArrayService$WonderEditor.push(_buildTreeNode(newGameObject, param[1]), scene[/* children */2].slice())
          ]];
}

function _removeDragedTreeNodeFromSceneGrahph(dragedUid, sceneGraphArrayData) {
  var _iterateSceneGraph = function (dragedUid, sceneGraphArray, newSceneGraphArray, dragedTreeNode) {
    return sceneGraphArray.reduce((function (param, treeNode) {
                  var newSceneGraphArray = param[0];
                  var match = +(treeNode[/* uid */1] === dragedUid);
                  if (match !== 0) {
                    return /* tuple */[
                            newSceneGraphArray,
                            /* Some */[treeNode]
                          ];
                  } else {
                    var match$1 = _iterateSceneGraph(dragedUid, treeNode[/* children */2], /* array */[], param[1]);
                    return /* tuple */[
                            ArrayService$WonderEditor.push(/* record */[
                                  /* name */treeNode[/* name */0],
                                  /* uid */treeNode[/* uid */1],
                                  /* children */match$1[0]
                                ], newSceneGraphArray),
                            match$1[1]
                          ];
                  }
                }), /* tuple */[
                newSceneGraphArray,
                dragedTreeNode
              ]);
  };
  var match = _iterateSceneGraph(dragedUid, sceneGraphArrayData, /* array */[], /* None */0);
  var match$1 = match[1];
  if (match$1) {
    return /* tuple */[
            match[0],
            match$1[0]
          ];
  } else {
    return Log$WonderLog.fatal(Log$WonderLog.buildFatalMessage("_removeDragedTreeNodeFromSceneGrahph", "the draged treeNode " + (String(dragedUid) + " is not exist"), "", "", "dragedUid:" + (String(dragedUid) + "")));
  }
}

function _insertRemovedTreeNodeToTargetTreeNode(targetUid, param) {
  var dragedTreeNode = param[1];
  return param[0].map((function (treeNode) {
                var children = treeNode[/* children */2];
                var match = +(treeNode[/* uid */1] === targetUid);
                if (match !== 0) {
                  return /* record */[
                          /* name */treeNode[/* name */0],
                          /* uid */treeNode[/* uid */1],
                          /* children */ArrayService$WonderEditor.push(dragedTreeNode, children)
                        ];
                } else {
                  return /* record */[
                          /* name */treeNode[/* name */0],
                          /* uid */treeNode[/* uid */1],
                          /* children */_insertRemovedTreeNodeToTargetTreeNode(targetUid, /* tuple */[
                                children,
                                dragedTreeNode
                              ])
                        ];
                }
              }));
}

function getDragedSceneGraphData(targetUid, dragedUid, sceneGraphArrayData) {
  return Contract$WonderLog.ensureCheck((function (dragedSceneGraph) {
                return Contract$WonderLog.test(Log$WonderLog.buildAssertMessage("the draged scene graph data == scene data from engine", "not"), (function () {
                              return Contract$WonderLog.assertTrue(Caml_obj.caml_equal(StateLogicService$WonderEditor.getState(getSceneGraphDataFromEngine), dragedSceneGraph));
                            }));
              }), StateEditorService$WonderEditor.getStateIsDebug(/* () */0), _insertRemovedTreeNodeToTargetTreeNode(targetUid, _removeDragedTreeNodeFromSceneGrahph(dragedUid, sceneGraphArrayData)));
}

export {
  _isDragedGameObjectBeTargetGameObjectParent ,
  isGameObjectRelationError                   ,
  setParent                                   ,
  setTransformParentKeepOrder                 ,
  _getGameObjectName                          ,
  _buildTreeNode                              ,
  _buildSceneGraphData                        ,
  getSceneGraphDataFromEngine                 ,
  buildSceneGraphDataWithNewGameObject        ,
  _removeDragedTreeNodeFromSceneGrahph        ,
  _insertRemovedTreeNodeToTargetTreeNode      ,
  getDragedSceneGraphData                     ,
  
}
/* Log-WonderLog Not a pure module */
