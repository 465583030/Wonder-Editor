'use strict';

import * as Curry                                          from "../../../../../../node_modules/bs-platform/lib/es6/curry.js";
import * as React                                          from "react";
import * as ReasonReact                                    from "../../../../../../node_modules/reason-react/lib/es6_global/src/reasonReact.js";
import * as Css$WonderEditor                               from "../../../external/Css.js";
import * as AppStore$WonderEditor                          from "../../../ui/store/AppStore.js";
import * as OperateStateUtils$WonderEditor                 from "../../../utils/OperateStateUtils.js";
import * as MainEditorMainView$WonderEditor                from "../logic/view/MainEditorMainView.js";
import * as MainEditorInspector$WonderEditor               from "../component/inspector/ui/MainEditorInspector.js";
import * as MainEditorSceneTree$WonderEditor               from "../component/sceneTree/ui/MainEditorSceneTree.js";
import * as MainEditorSceneTreeView$WonderEditor           from "../component/sceneTree/logic/view/MainEditorSceneTreeView.js";
import * as GameObjectAllComponentParseSystem$WonderEditor from "../component/inspector/logic/config/system/GameObjectAllComponentParseSystem.js";

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
                          key: "webGL",
                          id: "webgl"
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
                    }, ReasonReact.element(/* None */0, /* None */0, MainEditorInspector$WonderEditor.make(store, dispatch, GameObjectAllComponentParseSystem$WonderEditor.getGameObjectAllComponentConfig(/* () */0), /* array */[]))), React.createElement("div", {
                      className: "inline-component sceneTree-parent"
                    }, ReasonReact.element(/* None */0, /* None */0, MainEditorSceneTree$WonderEditor.make(store, dispatch, /* array */[]))), React.createElement("div", {
                      key: "webglParent",
                      className: "webgl-parent"
                    }, React.createElement("canvas", {
                          key: "webGL",
                          id: "webgl"
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
      MainEditorMainView$WonderEditor.start(/* () */0);
      Curry._1(dispatch, AppStore$WonderEditor.StartEngineAction);
      Curry._1(dispatch, [
            AppStore$WonderEditor.SceneTreeAction,
            /* SetSceneGraph */[/* Some */[OperateStateUtils$WonderEditor.getState(MainEditorSceneTreeView$WonderEditor.getSceneGraphDataFromEngine)]]
          ]);
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
