

import * as Curry from "../../../../../../../../../../../../../node_modules/bs-platform/lib/es6/curry.js";
import * as React from "react";
import * as ReasonReact from "../../../../../../../../../../../../../node_modules/reason-react/lib/es6_global/src/ReasonReact.js";
import * as DomHelper$WonderEditor from "../../../../../../../../../external/DomHelper.js";
import * as TransformUtils$WonderEditor from "../utils/TransformUtils.js";
import * as StateLogicService$WonderEditor from "../../../../../../../../../../service/stateTuple/logic/StateLogicService.js";
import * as TransformTemplate$WonderEditor from "../atom_component/transform_template/TransformTemplate.js";
import * as StateEngineService$WonderEditor from "../../../../../../../../../../service/state/engine/StateEngineService.js";
import * as ScaleBlurEventHandler$WonderEditor from "../eventHandler/ScaleBlurEventHandler.js";
import * as TransformEditorService$WonderEditor from "../../../../../../../../../../service/state/editor/transform/TransformEditorService.js";
import * as TransformEngineService$WonderEditor from "../../../../../../../../../../service/state/engine/TransformEngineService.js";
import * as PositionBlurEventHandler$WonderEditor from "../eventHandler/PositionBlurEventHandler.js";
import * as RotationBlurEventHandler$WonderEditor from "../eventHandler/RotationBlurEventHandler.js";
import * as GameObjectComponentEngineService$WonderEditor from "../../../../../../../../../../service/state/engine/GameObjectComponentEngineService.js";

function blurPositionEvent(param, transformComponent, param$1) {
  var z = param$1[2];
  var y = param$1[1];
  var x = param$1[0];
  var match = TransformUtils$WonderEditor.getTransformPositionData(transformComponent);
  var match$1 = TransformUtils$WonderEditor.isTransformVec3Equal(/* tuple */[
        x,
        y,
        z
      ], /* tuple */[
        match[0],
        match[1],
        match[2]
      ]);
  if (match$1) {
    return /* () */0;
  } else {
    return Curry._3(PositionBlurEventHandler$WonderEditor.MakeEventHandler[/* pushUndoStackWithCopiedEngineState */1], /* tuple */[
                param[0],
                param[1]
              ], transformComponent, /* tuple */[
                x,
                y,
                z
              ]);
  }
}

function blurRotationEvent(param, transformComponent, param$1) {
  var z = param$1[2];
  var y = param$1[1];
  var x = param$1[0];
  var match = TransformUtils$WonderEditor.getTransformRotationData(transformComponent);
  var match$1 = TransformUtils$WonderEditor.isTransformVec3Equal(/* tuple */[
        x,
        y,
        z
      ], /* tuple */[
        match[0],
        match[1],
        match[2]
      ]);
  if (match$1) {
    return /* () */0;
  } else {
    return Curry._3(RotationBlurEventHandler$WonderEditor.MakeEventHandler[/* pushUndoStackWithCopiedEngineState */1], /* tuple */[
                param[0],
                param[1]
              ], transformComponent, /* tuple */[
                x,
                y,
                z
              ]);
  }
}

function blurScaleEvent(param, transformComponent, param$1) {
  var z = param$1[2];
  var y = param$1[1];
  var x = param$1[0];
  var match = TransformUtils$WonderEditor.getTransformScaleData(transformComponent);
  var match$1 = TransformUtils$WonderEditor.isTransformVec3Equal(/* tuple */[
        x,
        y,
        z
      ], /* tuple */[
        match[0],
        match[1],
        match[2]
      ]);
  if (match$1) {
    return /* () */0;
  } else {
    return Curry._3(ScaleBlurEventHandler$WonderEditor.MakeEventHandler[/* pushUndoStackWithCopiedEngineState */1], /* tuple */[
                param[0],
                param[1]
              ], transformComponent, /* tuple */[
                x,
                y,
                z
              ]);
  }
}

function _setCurrentSceneTreeNodeLocalPosition(transformComponent, param) {
  var partial_arg_000 = param[0];
  var partial_arg_001 = param[1];
  var partial_arg_002 = param[2];
  var partial_arg = /* tuple */[
    partial_arg_000,
    partial_arg_001,
    partial_arg_002
  ];
  return StateLogicService$WonderEditor.getAndRefreshEngineStateWithFunc((function (param) {
                return TransformEngineService$WonderEditor.setLocalPosition(partial_arg, transformComponent, param);
              }));
}

function changePositionX(transformComponent, value) {
  var match = TransformUtils$WonderEditor.getSceneTreeNodeLocalPosition(transformComponent);
  return _setCurrentSceneTreeNodeLocalPosition(transformComponent, /* tuple */[
              value,
              match[1],
              match[2]
            ]);
}

function changePositionY(transformComponent, value) {
  var match = TransformUtils$WonderEditor.getSceneTreeNodeLocalPosition(transformComponent);
  return _setCurrentSceneTreeNodeLocalPosition(transformComponent, /* tuple */[
              match[0],
              value,
              match[2]
            ]);
}

function changePositionZ(transformComponent, value) {
  var match = TransformUtils$WonderEditor.getSceneTreeNodeLocalPosition(transformComponent);
  return _setCurrentSceneTreeNodeLocalPosition(transformComponent, /* tuple */[
              match[0],
              match[1],
              value
            ]);
}

function _setCurrentSceneTreeNodeLocalScale(transformComponent, param) {
  var partial_arg_000 = param[0];
  var partial_arg_001 = param[1];
  var partial_arg_002 = param[2];
  var partial_arg = /* tuple */[
    partial_arg_000,
    partial_arg_001,
    partial_arg_002
  ];
  return StateLogicService$WonderEditor.getAndRefreshEngineStateWithFunc((function (param) {
                return TransformEngineService$WonderEditor.setLocalScale(partial_arg, transformComponent, param);
              }));
}

function changeScaleX(transformComponent, value) {
  var match = StateLogicService$WonderEditor.getEngineStateToGetData((function (param) {
          return TransformEngineService$WonderEditor.getLocalScale(transformComponent, param);
        }));
  return _setCurrentSceneTreeNodeLocalScale(transformComponent, /* tuple */[
              value,
              match[1],
              match[2]
            ]);
}

function changeScaleY(transformComponent, value) {
  var match = StateLogicService$WonderEditor.getEngineStateToGetData((function (param) {
          return TransformEngineService$WonderEditor.getLocalScale(transformComponent, param);
        }));
  return _setCurrentSceneTreeNodeLocalScale(transformComponent, /* tuple */[
              match[0],
              value,
              match[2]
            ]);
}

function changeScaleZ(transformComponent, value) {
  var match = StateLogicService$WonderEditor.getEngineStateToGetData((function (param) {
          return TransformEngineService$WonderEditor.getLocalScale(transformComponent, param);
        }));
  return _setCurrentSceneTreeNodeLocalScale(transformComponent, /* tuple */[
              match[0],
              match[1],
              value
            ]);
}

function _setCurrentSceneTreeNodeLocalRotation(transformComponent, param) {
  var partial_arg_000 = param[0];
  var partial_arg_001 = param[1];
  var partial_arg_002 = param[2];
  var partial_arg = /* tuple */[
    partial_arg_000,
    partial_arg_001,
    partial_arg_002
  ];
  return StateLogicService$WonderEditor.getAndRefreshEngineStateWithFunc((function (param) {
                return TransformEngineService$WonderEditor.setLocalEulerAngles(partial_arg, transformComponent, param);
              }));
}

function changeRotationX(transformComponent, value) {
  StateLogicService$WonderEditor.getAndSetEditorState((function (param) {
          return TransformEditorService$WonderEditor.setLocalEulerAngleX(transformComponent, value, param);
        }));
  var match = StateLogicService$WonderEditor.getEngineStateToGetData((function (param) {
          return TransformEngineService$WonderEditor.getLocalEulerAngles(transformComponent, param);
        }));
  return _setCurrentSceneTreeNodeLocalRotation(transformComponent, /* tuple */[
              value,
              match[1],
              match[2]
            ]);
}

function changeRotationY(transformComponent, value) {
  StateLogicService$WonderEditor.getAndSetEditorState((function (param) {
          return TransformEditorService$WonderEditor.setLocalEulerAngleY(transformComponent, value, param);
        }));
  var match = StateLogicService$WonderEditor.getEngineStateToGetData((function (param) {
          return TransformEngineService$WonderEditor.getLocalEulerAngles(transformComponent, param);
        }));
  return _setCurrentSceneTreeNodeLocalRotation(transformComponent, /* tuple */[
              match[0],
              value,
              match[2]
            ]);
}

function changeRotationZ(transformComponent, value) {
  StateLogicService$WonderEditor.getAndSetEditorState((function (param) {
          return TransformEditorService$WonderEditor.setLocalEulerAngleZ(transformComponent, value, param);
        }));
  var match = StateLogicService$WonderEditor.getEngineStateToGetData((function (param) {
          return TransformEngineService$WonderEditor.getLocalEulerAngles(transformComponent, param);
        }));
  return _setCurrentSceneTreeNodeLocalRotation(transformComponent, /* tuple */[
              match[0],
              match[1],
              value
            ]);
}

function buildShadeComponent(gameObject) {
  var match = GameObjectComponentEngineService$WonderEditor.hasArcballCameraControllerComponent(gameObject, StateEngineService$WonderEditor.unsafeGetState(/* () */0));
  if (match) {
    return React.createElement("div", {
                className: "transform-shade"
              });
  } else {
    return null;
  }
}

var Method = /* module */[
  /* blurPositionEvent */blurPositionEvent,
  /* blurRotationEvent */blurRotationEvent,
  /* blurScaleEvent */blurScaleEvent,
  /* _setCurrentSceneTreeNodeLocalPosition */_setCurrentSceneTreeNodeLocalPosition,
  /* changePositionX */changePositionX,
  /* changePositionY */changePositionY,
  /* changePositionZ */changePositionZ,
  /* _setCurrentSceneTreeNodeLocalScale */_setCurrentSceneTreeNodeLocalScale,
  /* changeScaleX */changeScaleX,
  /* changeScaleY */changeScaleY,
  /* changeScaleZ */changeScaleZ,
  /* _setCurrentSceneTreeNodeLocalRotation */_setCurrentSceneTreeNodeLocalRotation,
  /* changeRotationX */changeRotationX,
  /* changeRotationY */changeRotationY,
  /* changeRotationZ */changeRotationZ,
  /* buildShadeComponent */buildShadeComponent
];

var component = ReasonReact.statelessComponent("MainEditorTransform");

function render(param, param$1, _) {
  var transformComponent = param$1[0];
  var dispatchFunc = param[1];
  var store = param[0];
  return React.createElement("article", {
              className: "wonder-inspector-transform"
            }, React.createElement("div", {
                  className: "inspector-item"
                }, React.createElement("div", {
                      className: "item-header"
                    }, DomHelper$WonderEditor.textEl("Position")), React.createElement("div", {
                      className: "item-content"
                    }, ReasonReact.element(undefined, undefined, TransformTemplate$WonderEditor.make(store, dispatchFunc, transformComponent, changePositionX, changePositionY, changePositionZ, TransformUtils$WonderEditor.getTransformPositionData, blurPositionEvent, true, /* array */[])))), React.createElement("div", {
                  className: "inspector-item"
                }, React.createElement("div", {
                      className: "item-header"
                    }, DomHelper$WonderEditor.textEl("Rotation")), React.createElement("div", {
                      className: "item-content"
                    }, ReasonReact.element(undefined, undefined, TransformTemplate$WonderEditor.make(store, dispatchFunc, transformComponent, changeRotationX, changeRotationY, changeRotationZ, TransformUtils$WonderEditor.getTransformRotationData, blurRotationEvent, true, /* array */[])))), React.createElement("div", {
                  className: "inspector-item"
                }, React.createElement("div", {
                      className: "item-header"
                    }, DomHelper$WonderEditor.textEl("Scale")), React.createElement("div", {
                      className: "item-content"
                    }, ReasonReact.element(undefined, undefined, TransformTemplate$WonderEditor.make(store, dispatchFunc, transformComponent, changeScaleX, changeScaleY, changeScaleZ, TransformUtils$WonderEditor.getTransformScaleData, blurScaleEvent, true, /* array */[])))), buildShadeComponent(param$1[1]));
}

function make(store, dispatchFunc, transformComponent, gameObject, _) {
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
                        ], /* tuple */[
                          transformComponent,
                          gameObject
                        ], self);
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
