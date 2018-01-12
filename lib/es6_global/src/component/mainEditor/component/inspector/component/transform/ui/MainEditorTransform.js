'use strict';

import * as React                                from "react";
import * as ReasonReact                          from "../../../../../../../../../../node_modules/reason-react/lib/es6_global/src/reasonReact.js";
import * as DomHelper$WonderEditor               from "../../../../../../../external/DomHelper.js";
import * as FloatInput$WonderEditor              from "../../../../../../../ui/component/floatInput/FloatInput.js";
import * as OperateFloatUtils$WonderEditor       from "../utils/OperateFloatUtils.js";
import * as MainEditorStateView$WonderEditor     from "../../../../../logic/view/MainEditorStateView.js";
import * as MainEditorTransformView$WonderEditor from "../logic/view/MainEditorTransformView.js";

function truncateTransformValue(param) {
  return /* tuple */[
          OperateFloatUtils$WonderEditor.truncateFloatValue(param[0], 6),
          OperateFloatUtils$WonderEditor.truncateFloatValue(param[1], 6),
          OperateFloatUtils$WonderEditor.truncateFloatValue(param[2], 6)
        ];
}

function getCurrentGameObjectLocalPosition() {
  var state = MainEditorStateView$WonderEditor.prepareState(/* () */0);
  return MainEditorTransformView$WonderEditor.getCurrentGameObjectLocalPosition((console.log(state[0]), state));
}

function setCurrentGameObjectLocalPosition(x, y, z) {
  return MainEditorStateView$WonderEditor.finishState(MainEditorTransformView$WonderEditor.setCurrentGameObjectLocalPosition(/* tuple */[
                  x,
                  y,
                  z
                ], MainEditorStateView$WonderEditor.prepareState(/* () */0)));
}

function changeX(value) {
  var match = getCurrentGameObjectLocalPosition(/* () */0);
  console.log(match[0]);
  return setCurrentGameObjectLocalPosition(value, match[1], match[2]);
}

function changeY(value) {
  var match = getCurrentGameObjectLocalPosition(/* () */0);
  return setCurrentGameObjectLocalPosition(match[0], value, match[2]);
}

function changeZ(value) {
  var match = getCurrentGameObjectLocalPosition(/* () */0);
  return setCurrentGameObjectLocalPosition(match[0], match[1], value);
}

var Method = /* module */[
  /* truncateTransformValue */truncateTransformValue,
  /* getCurrentGameObjectLocalPosition */getCurrentGameObjectLocalPosition,
  /* setCurrentGameObjectLocalPosition */setCurrentGameObjectLocalPosition,
  /* changeX */changeX,
  /* changeY */changeY,
  /* changeZ */changeZ
];

var component = ReasonReact.statelessComponent("MainEditorTransform");

function render(_, _$1, _$2) {
  var match = truncateTransformValue(getCurrentGameObjectLocalPosition(/* () */0));
  return React.createElement("article", {
              key: DomHelper$WonderEditor.getRandomKey(/* () */0),
              className: "transform-component"
            }, ReasonReact.element(/* None */0, /* None */0, FloatInput$WonderEditor.make(/* Some */[match[0]], /* Some */["X"], /* Some */[changeX], /* array */[])), ReasonReact.element(/* None */0, /* None */0, FloatInput$WonderEditor.make(/* Some */[match[1]], /* Some */["Y"], /* Some */[changeY], /* array */[])), ReasonReact.element(/* None */0, /* None */0, FloatInput$WonderEditor.make(/* Some */[match[2]], /* Some */["Z"], /* Some */[changeZ], /* array */[])));
}

function make(store, dispatch, _) {
  var newrecord = component.slice();
  newrecord[/* render */9] = (function (param) {
      return render(store, dispatch, param);
    });
  return newrecord;
}

export {
  Method    ,
  component ,
  render    ,
  make      ,
  
}
/* component Not a pure module */
