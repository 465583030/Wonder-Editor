

import * as Curry from "../../../../../../../../../../../node_modules/bs-platform/lib/es6/curry.js";
import * as React from "react";
import * as Js_list from "../../../../../../../../../../../node_modules/bs-platform/lib/es6/js_list.js";
import * as ReasonReact from "../../../../../../../../../../../node_modules/reason-react/lib/es6_global/src/ReasonReact.js";
import * as Log$WonderLog from "../../../../../../../../../../../node_modules/wonder-log/lib/es6_global/src/Log.js";
import * as DomHelper$WonderEditor from "../../../../../../../external/DomHelper.js";
import * as ArrayService$WonderEditor from "../../../../../../../../service/atom/ArrayService.js";
import * as ComponentBox$WonderEditor from "../../../../../atom_component/componentBox/ui/ComponentBox.js";
import * as AddableComponent$WonderEditor from "../../addableComponent/ui/AddableComponent.js";
import * as StateLogicService$WonderEditor from "../../../../../../../../service/stateTuple/logic/StateLogicService.js";
import * as MainEditorTransform$WonderEditor from "../../../composable_component/transform/ui/MainEditorTransform.js";
import * as MainEditorBasicMaterial$WonderEditor from "../../../composable_component/material/ui/MainEditorBasicMaterial.js";
import * as InspectorGameObjectUtils$WonderEditor from "../../../utils/InspectorGameObjectUtils.js";

function _buildComponentBox(param, param$1, isClosable, buildComponentFunc) {
  return ReasonReact.element(/* Some */[DomHelper$WonderEditor.getRandomKey(/* () */0)], /* None */0, ComponentBox$WonderEditor.make(param[0], isClosable, Curry._2(buildComponentFunc, /* tuple */[
                      param$1[0],
                      param$1[1]
                    ], param[1]), /* array */[]));
}

function _buildTransform(param, component) {
  return ReasonReact.element(/* Some */[DomHelper$WonderEditor.getRandomKey(/* () */0)], /* None */0, MainEditorTransform$WonderEditor.make(param[0], param[1], component, /* array */[]));
}

function _buildBasicMaterial(param, component) {
  return ReasonReact.element(/* Some */[DomHelper$WonderEditor.getRandomKey(/* () */0)], /* None */0, MainEditorBasicMaterial$WonderEditor.make(param[0], param[1], component, /* array */[]));
}

function _buildSouceInstance(_, _$1) {
  return React.createElement("div", {
              key: DomHelper$WonderEditor.getRandomKey(/* () */0)
            }, DomHelper$WonderEditor.textEl("simulate source instance"));
}

function _buildBasicCameraView(_, _$1) {
  return React.createElement("div", {
              key: DomHelper$WonderEditor.getRandomKey(/* () */0)
            }, DomHelper$WonderEditor.textEl("simulate basic camera view"));
}

function _buildPerspectiveCameraProjection(_, _$1) {
  return React.createElement("div", {
              key: DomHelper$WonderEditor.getRandomKey(/* () */0)
            }, DomHelper$WonderEditor.textEl("simulate perspective camera view"));
}

function _buildComponentUIComponent(param, param$1) {
  var dispatchFunc = param$1[1];
  var store = param$1[0];
  var component = param[1];
  var type_ = param[0];
  switch (type_) {
    case "basicCameraView" : 
        return _buildComponentBox(/* tuple */[
                    type_,
                    component
                  ], /* tuple */[
                    store,
                    dispatchFunc
                  ], true, _buildBasicCameraView);
    case "basicMaterial" : 
        return _buildComponentBox(/* tuple */[
                    type_,
                    component
                  ], /* tuple */[
                    store,
                    dispatchFunc
                  ], false, _buildBasicMaterial);
    case "perspectiveCameraProjection" : 
        return _buildComponentBox(/* tuple */[
                    type_,
                    component
                  ], /* tuple */[
                    store,
                    dispatchFunc
                  ], true, _buildPerspectiveCameraProjection);
    case "sourceInstance" : 
        return _buildComponentBox(/* tuple */[
                    type_,
                    component
                  ], /* tuple */[
                    store,
                    dispatchFunc
                  ], true, _buildSouceInstance);
    case "transform" : 
        return _buildComponentBox(/* tuple */[
                    type_,
                    component
                  ], /* tuple */[
                    store,
                    dispatchFunc
                  ], false, _buildTransform);
    default:
      return Log$WonderLog.fatal(Log$WonderLog.buildFatalMessage("_buildComponentUIComponent", "the component: " + (String(type_) + " not exist"), "", "", "type:" + (String(type_) + (", component:" + (String(component) + "")))));
  }
}

function _buildGameObjectAllShowComponent(param, componentList) {
  var dispatchFunc = param[1];
  var store = param[0];
  return Js_list.foldLeft((function (componentArray, param) {
                return ArrayService$WonderEditor.push(_buildComponentUIComponent(/* tuple */[
                                param[0],
                                param[1]
                              ], /* tuple */[
                                store,
                                dispatchFunc
                              ]), componentArray);
              }), /* array */[], componentList);
}

function buildCurrentSceneTreeNodeComponent(param, allShowComponentConfig, currentSceneTreeNode) {
  if (currentSceneTreeNode) {
    var gameObject = currentSceneTreeNode[0];
    var dispatchFunc = param[1];
    var store = param[0];
    var match = StateLogicService$WonderEditor.getEngineStateToGetData((function (param) {
            return InspectorGameObjectUtils$WonderEditor.buildCurrentSceneTreeNodeShowComponentList(gameObject, allShowComponentConfig, param);
          }));
    return ArrayService$WonderEditor.push(ReasonReact.element(/* Some */[DomHelper$WonderEditor.getRandomKey(/* () */0)], /* None */0, AddableComponent$WonderEditor.make(/* tuple */[
                        store,
                        dispatchFunc
                      ], gameObject, match[1], /* array */[])), _buildGameObjectAllShowComponent(/* tuple */[
                    store,
                    dispatchFunc
                  ], match[0]));
  } else {
    return /* array */[];
  }
}

var Method = /* module */[
  /* _buildComponentBox */_buildComponentBox,
  /* _buildTransform */_buildTransform,
  /* _buildBasicMaterial */_buildBasicMaterial,
  /* _buildSouceInstance */_buildSouceInstance,
  /* _buildBasicCameraView */_buildBasicCameraView,
  /* _buildPerspectiveCameraProjection */_buildPerspectiveCameraProjection,
  /* _buildComponentUIComponent */_buildComponentUIComponent,
  /* _buildGameObjectAllShowComponent */_buildGameObjectAllShowComponent,
  /* buildCurrentSceneTreeNodeComponent */buildCurrentSceneTreeNodeComponent
];

var component = ReasonReact.statelessComponent("SceneTreeInspector");

function render(param, allShowComponentConfig, currentSceneTreeNode, _) {
  return React.createElement("article", {
              key: "SceneTreeInspector",
              className: "inspector-component"
            }, buildCurrentSceneTreeNodeComponent(/* tuple */[
                  param[0],
                  param[1]
                ], allShowComponentConfig, currentSceneTreeNode));
}

function make(store, dispatchFunc, allShowComponentConfig, currentSceneTreeNode, _) {
  return /* record */[
          /* debugName */component[/* debugName */0],
          /* reactClassInternal */component[/* reactClassInternal */1],
          /* handedOffState */component[/* handedOffState */2],
          /* willReceiveProps */component[/* willReceiveProps */3],
          /* didMount */component[/* didMount */4],
          /* didUpdate */component[/* didUpdate */5],
          /* willUnmount */component[/* willUnmount */6],
          /* willUpdate */component[/* willUpdate */7],
          /* shouldUpdate */component[/* shouldUpdate */8],
          /* render */(function (self) {
              return render(/* tuple */[
                          store,
                          dispatchFunc
                        ], allShowComponentConfig, currentSceneTreeNode, self);
            }),
          /* initialState */component[/* initialState */10],
          /* retainedProps */component[/* retainedProps */11],
          /* reducer */component[/* reducer */12],
          /* subscriptions */component[/* subscriptions */13],
          /* jsElementWrapped */component[/* jsElementWrapped */14]
        ];
}

export {
  Method ,
  component ,
  render ,
  make ,
  
}
/* component Not a pure module */
