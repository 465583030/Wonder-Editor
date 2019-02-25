

import * as Curry from "../../../../../../../../../../../../../../../node_modules/bs-platform/lib/es6/curry.js";
import * as React from "react";
import * as ReasonReact from "../../../../../../../../../../../../../../../node_modules/reason-react/lib/es6_global/src/ReasonReact.js";
import * as Color$WonderEditor from "../../../../../../../../../../../external/Color.js";
import * as ColorType$WonderEditor from "../../../../../../../../../../../external/type/ColorType.js";
import * as StateLogicService$WonderEditor from "../../../../../../../../../../../../service/stateTuple/logic/StateLogicService.js";
import * as PickColorComponent$WonderEditor from "../../../../../../../atom_component/PickColorComponent/ui/PickColorComponent.js";
import * as PointLightEngineService$WonderEditor from "../../../../../../../../../../../../service/state/engine/PointLightEngineService.js";
import * as MainEditorPointLightUtils$WonderEditor from "../utils/MainEditorPointLightUtils.js";
import * as MainEditorFloatInputBaseComponent$WonderEditor from "../../../../../atom_component/FloatInputBaseComponent/MainEditorFloatInputBaseComponent.js";
import * as PointLightCloseColorPickEventHandler$WonderEditor from "./eventHandler/PointLightCloseColorPickEventHandler.js";

var component = ReasonReact.statelessComponent("MainEditorPointLight");

function getColor(lightComponent, _) {
  return Color$WonderEditor.getHexString(StateLogicService$WonderEditor.getEngineStateToGetData((function (param) {
                    return PointLightEngineService$WonderEditor.getPointLightColor(lightComponent, param);
                  })));
}

function changeColor(lightComponent, value) {
  var __x = Color$WonderEditor.getEngineColorRgbArr(ColorType$WonderEditor.convertColorObjToColorPickType(value));
  return StateLogicService$WonderEditor.getAndRefreshEngineStateWithFunc((function (param) {
                return PointLightEngineService$WonderEditor.setPointLightColor(__x, lightComponent, param);
              }));
}

var closeColorPick = PointLightCloseColorPickEventHandler$WonderEditor.MakeEventHandler[/* pushUndoStackWithCopiedEngineState */1];

function buildColorPickComponent(param, lightComponent) {
  return ReasonReact.element(undefined, undefined, PickColorComponent$WonderEditor.make("Color", (function () {
                    return Color$WonderEditor.getHexString(StateLogicService$WonderEditor.getEngineStateToGetData((function (param) {
                                      return PointLightEngineService$WonderEditor.getPointLightColor(lightComponent, param);
                                    })));
                  }), (function (param) {
                    return changeColor(lightComponent, param);
                  }), Curry._2(closeColorPick, /* tuple */[
                      param[0],
                      param[1]
                    ], lightComponent), /* array */[]));
}

function buildIntensityComponent(param, lightComponent) {
  var dispatchFunc = param[1];
  var uiState = param[0];
  var partial_arg = /* tuple */[
    uiState,
    dispatchFunc
  ];
  var partial_arg$1 = /* tuple */[
    uiState,
    dispatchFunc
  ];
  return ReasonReact.element(undefined, undefined, MainEditorFloatInputBaseComponent$WonderEditor.make((function (param) {
                    return MainEditorPointLightUtils$WonderEditor.blurIntensityEvent(partial_arg, lightComponent, param);
                  }), "Intensity", (function (param) {
                    return PointLightEngineService$WonderEditor.getPointLightIntensity(lightComponent, param);
                  }), (function (param) {
                    return MainEditorPointLightUtils$WonderEditor.changeIntensity(lightComponent, param);
                  }), (function (param) {
                    return MainEditorPointLightUtils$WonderEditor.blurIntensityEvent(partial_arg$1, lightComponent, param);
                  }), /* array */[]));
}

function buildConstantComponent(param, lightComponent) {
  var dispatchFunc = param[1];
  var uiState = param[0];
  var partial_arg = /* tuple */[
    uiState,
    dispatchFunc
  ];
  var partial_arg$1 = /* tuple */[
    uiState,
    dispatchFunc
  ];
  return ReasonReact.element(undefined, undefined, MainEditorFloatInputBaseComponent$WonderEditor.make((function (param) {
                    return MainEditorPointLightUtils$WonderEditor.blurConstantEvent(partial_arg, lightComponent, param);
                  }), "Constant", (function (param) {
                    return PointLightEngineService$WonderEditor.getPointLightConstant(lightComponent, param);
                  }), (function (param) {
                    return MainEditorPointLightUtils$WonderEditor.changeConstant(lightComponent, param);
                  }), (function (param) {
                    return MainEditorPointLightUtils$WonderEditor.blurConstantEvent(partial_arg$1, lightComponent, param);
                  }), /* array */[]));
}

function buildLinearComponent(param, lightComponent) {
  var dispatchFunc = param[1];
  var uiState = param[0];
  var partial_arg = /* tuple */[
    uiState,
    dispatchFunc
  ];
  var partial_arg$1 = /* tuple */[
    uiState,
    dispatchFunc
  ];
  return ReasonReact.element(undefined, undefined, MainEditorFloatInputBaseComponent$WonderEditor.make((function (param) {
                    return MainEditorPointLightUtils$WonderEditor.blurLinearEvent(partial_arg, lightComponent, param);
                  }), "Linear", (function (param) {
                    return PointLightEngineService$WonderEditor.getPointLightLinear(lightComponent, param);
                  }), (function (param) {
                    return MainEditorPointLightUtils$WonderEditor.changeLinear(lightComponent, param);
                  }), (function (param) {
                    return MainEditorPointLightUtils$WonderEditor.blurLinearEvent(partial_arg$1, lightComponent, param);
                  }), /* array */[]));
}

function buildQuadraticComponent(param, lightComponent) {
  var dispatchFunc = param[1];
  var uiState = param[0];
  var partial_arg = /* tuple */[
    uiState,
    dispatchFunc
  ];
  var partial_arg$1 = /* tuple */[
    uiState,
    dispatchFunc
  ];
  return ReasonReact.element(undefined, undefined, MainEditorFloatInputBaseComponent$WonderEditor.make((function (param) {
                    return MainEditorPointLightUtils$WonderEditor.blurQuadraticEvent(partial_arg, lightComponent, param);
                  }), "Quadratic", (function (param) {
                    return PointLightEngineService$WonderEditor.getPointLightQuadratic(lightComponent, param);
                  }), (function (param) {
                    return MainEditorPointLightUtils$WonderEditor.changeQuadratic(lightComponent, param);
                  }), (function (param) {
                    return MainEditorPointLightUtils$WonderEditor.blurQuadraticEvent(partial_arg$1, lightComponent, param);
                  }), /* array */[]));
}

function buildRangeComponent(param, lightComponent) {
  var dispatchFunc = param[1];
  var uiState = param[0];
  var partial_arg = /* tuple */[
    uiState,
    dispatchFunc
  ];
  var partial_arg$1 = /* tuple */[
    uiState,
    dispatchFunc
  ];
  return ReasonReact.element(undefined, undefined, MainEditorFloatInputBaseComponent$WonderEditor.make((function (param) {
                    return MainEditorPointLightUtils$WonderEditor.blurRangeEvent(partial_arg, lightComponent, param);
                  }), "Range", (function (param) {
                    return PointLightEngineService$WonderEditor.getPointLightRange(lightComponent, param);
                  }), (function (param) {
                    return MainEditorPointLightUtils$WonderEditor.changeRange(lightComponent, param);
                  }), (function (param) {
                    return MainEditorPointLightUtils$WonderEditor.blurRangeEvent(partial_arg$1, lightComponent, param);
                  }), /* array */[]));
}

var Method = /* module */[
  /* getColor */getColor,
  /* changeColor */changeColor,
  /* closeColorPick */closeColorPick,
  /* buildColorPickComponent */buildColorPickComponent,
  /* buildIntensityComponent */buildIntensityComponent,
  /* buildConstantComponent */buildConstantComponent,
  /* buildLinearComponent */buildLinearComponent,
  /* buildQuadraticComponent */buildQuadraticComponent,
  /* buildRangeComponent */buildRangeComponent
];

function render(param, lightComponent, _) {
  var dispatchFunc = param[1];
  var uiState = param[0];
  return React.createElement("article", {
              className: "wonder-point-light"
            }, buildColorPickComponent(/* tuple */[
                  uiState,
                  dispatchFunc
                ], lightComponent), buildIntensityComponent(/* tuple */[
                  uiState,
                  dispatchFunc
                ], lightComponent), buildConstantComponent(/* tuple */[
                  uiState,
                  dispatchFunc
                ], lightComponent), buildLinearComponent(/* tuple */[
                  uiState,
                  dispatchFunc
                ], lightComponent), buildQuadraticComponent(/* tuple */[
                  uiState,
                  dispatchFunc
                ], lightComponent), buildRangeComponent(/* tuple */[
                  uiState,
                  dispatchFunc
                ], lightComponent));
}

function make(uiState, dispatchFunc, lightComponent, _) {
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
                          uiState,
                          dispatchFunc
                        ], lightComponent, self);
            }),
          /* initialState */component[/* initialState */10],
          /* retainedProps */component[/* retainedProps */11],
          /* reducer */component[/* reducer */12],
          /* subscriptions */component[/* subscriptions */13],
          /* jsElementWrapped */component[/* jsElementWrapped */14]
        ];
}

export {
  component ,
  Method ,
  render ,
  make ,
  
}
/* component Not a pure module */
