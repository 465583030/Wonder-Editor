'use strict';

import * as Curry                                         from "../../../../../../../node_modules/bs-platform/lib/es6/curry.js";
import * as React                                         from "react";
import * as ReasonReact                                   from "../../../../../../../node_modules/reason-react/lib/es6_global/src/reasonReact.js";
import * as Css$WonderEditor                              from "../../../external/Css.js";
import * as AppStore$WonderEditor                         from "../../../ui/store/AppStore.js";
import * as MainUtils$WonderEditor                        from "../../../utils/MainUtils.js";
import * as SceneTreeUtils$WonderEditor                   from "../composable_component/sceneTree/utils/SceneTreeUtils.js";
import * as StateLogicService$WonderEditor                from "../../../../service/stateTuple/logic/StateLogicService.js";
import * as MainEditorInspector$WonderEditor              from "../composable_component/inspector/ui/MainEditorInspector.js";
import * as MainEditorSceneTree$WonderEditor              from "../composable_component/sceneTree/ui/MainEditorSceneTree.js";
import * as GameObjectAllComponentParseUtils$WonderEditor from "../../../config/utils/GameObjectAllComponentParseUtils.js";

Css$WonderEditor.importCss("./css/mainEditor.css");

var component = ReasonReact.statelessComponent("MainEditor");

function _buildNotStartElement() {
  return React.createElement("article", {
              key: "mainEditor",
              className: "wonder-mainEditor-component"
            }, React.createElement("div", {
                  key: "verticalComponent",
                  className: "vertical-component"
                }, React.createElement("div", {
                      key: "webglParent",
                      className: "webgl-parent"
                    }, React.createElement("canvas", {
                          key: "editWebgl",
                          id: "editCanvas"
                        })), React.createElement("div", {
                      key: "webglRun",
                      className: "webgl-parent"
                    }, React.createElement("canvas", {
                          key: "runWebgl",
                          id: "runCanvas"
                        }))));
}

function _buildStartedElement(store, dispatch) {
  return React.createElement("article", {
              key: "mainEditor",
              className: "wonder-mainEditor-component"
            }, React.createElement("div", {
                  key: "verticalComponent",
                  className: "vertical-component"
                }, React.createElement("div", {
                      className: "inline-component inspector-parent"
                    }, ReasonReact.element(/* None */0, /* None */0, MainEditorInspector$WonderEditor.make(store, dispatch, GameObjectAllComponentParseUtils$WonderEditor.getGameObjectAllComponentConfig(/* () */0), /* array */[]))), React.createElement("div", {
                      className: "inline-component sceneTree-parent"
                    }, ReasonReact.element(/* None */0, /* None */0, MainEditorSceneTree$WonderEditor.make(store, dispatch, /* array */[]))), React.createElement("div", {
                      key: "webglParent",
                      className: "webgl-parent"
                    }, React.createElement("canvas", {
                          key: "editWebgl",
                          id: "editCanvas"
                        })), React.createElement("div", {
                      key: "webglRun",
                      className: "webgl-parent"
                    }, React.createElement("canvas", {
                          key: "runWebgl",
                          id: "runCanvas"
                        }))));
}

function render(store, dispatch, _) {
  var match = store[/* isEditorAndEngineStart */0];
  if (match !== 0) {
    return _buildStartedElement(store, dispatch);
  } else {
    return _buildNotStartElement(/* () */0);
  }
}

function make(store, dispatch, _) {
  var newrecord = component.slice();
  newrecord[/* didMount */4] = (function () {
      MainUtils$WonderEditor.start(/* () */0).then((function () {
              Curry._1(dispatch, [
                    AppStore$WonderEditor.SceneTreeAction,
                    /* SetSceneGraph */[/* Some */[StateLogicService$WonderEditor.getStateToGetData(SceneTreeUtils$WonderEditor.getSceneGraphDataFromEngine)]]
                  ]);
              return Promise.resolve(Curry._1(dispatch, AppStore$WonderEditor.StartEngineAction));
            }));
      return /* NoUpdate */0;
    });
  newrecord[/* render */9] = (function (self) {
      return render(store, dispatch, self);
    });
  return newrecord;
}

export {
  component             ,
  _buildNotStartElement ,
  _buildStartedElement  ,
  render                ,
  make                  ,
  
}
/*  Not a pure module */
