

import * as Block from "../../../../../../../../../node_modules/bs-platform/lib/es6/block.js";
import * as Curry from "../../../../../../../../../node_modules/bs-platform/lib/es6/curry.js";
import * as React from "react";
import * as ReasonReact from "../../../../../../../../../node_modules/reason-react/lib/es6_global/src/ReasonReact.js";
import * as DomHelper$WonderEditor from "../../../../../external/DomHelper.js";
import * as AddableComponentRemoveComponentEventHandler$WonderEditor from "../../../composable_component/inspector/atom_component/addableComponent/ui/eventHandler/AddableComponentRemoveComponentEventHandler.js";

var removeComponent = AddableComponentRemoveComponentEventHandler$WonderEditor.MakeEventHandler[/* pushUndoStackWithNoCopyEngineState */0];

var Method = /* module */[/* removeComponent */removeComponent];

var component = ReasonReact.reducerComponent("ComponentBox");

function reducer() {
  return (function (state) {
      var match = state[/* isShowComponent */0];
      if (match) {
        return /* Update */Block.__(0, [/* record */[
                    /* isShowComponent */false,
                    /* triangleDirection */"triangle-right"
                  ]]);
      } else {
        return /* Update */Block.__(0, [/* record */[
                    /* isShowComponent */true,
                    /* triangleDirection */"triangle-bottom"
                  ]]);
      }
    });
}

function render(reduxTuple, param, param$1, param$2) {
  var send = param$2[/* send */3];
  var state = param$2[/* state */1];
  var type_ = param$1[2];
  var gameObject = param$1[0];
  var match = state[/* isShowComponent */0];
  return React.createElement("article", {
              className: "componentBox-component"
            }, React.createElement("div", {
                  className: "header"
                }, React.createElement("div", {
                      className: "header-triangle",
                      onClick: (function () {
                          return Curry._1(send, /* ShowComponent */0);
                        })
                    }, React.createElement("span", {
                          className: state[/* triangleDirection */1]
                        })), React.createElement("div", {
                      className: "header-title"
                    }, DomHelper$WonderEditor.textEl(param[0])), param[1] ? React.createElement("span", {
                        className: "header-close",
                        onClick: (function () {
                            return Curry._3(removeComponent, reduxTuple, gameObject, type_);
                          })
                      }, DomHelper$WonderEditor.textEl("x")) : null), match ? param$1[1] : null);
}

function make(reduxTuple, header, isClosable, gameObject, gameObjectUIComponent, type_, _) {
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
              return render(reduxTuple, /* tuple */[
                          header,
                          isClosable
                        ], /* tuple */[
                          gameObject,
                          gameObjectUIComponent,
                          type_
                        ], self);
            }),
          /* initialState */(function () {
              return /* record */[
                      /* isShowComponent */true,
                      /* triangleDirection */"triangle-bottom"
                    ];
            }),
          /* retainedProps */component[/* retainedProps */11],
          /* reducer */reducer,
          /* subscriptions */component[/* subscriptions */13],
          /* jsElementWrapped */component[/* jsElementWrapped */14]
        ];
}

export {
  Method ,
  component ,
  reducer ,
  render ,
  make ,
  
}
/* component Not a pure module */
