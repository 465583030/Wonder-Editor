

import * as Curry from "../../../../../../node_modules/bs-platform/lib/es6/curry.js";
import * as React from "react";
import * as ReasonReact from "../../../../../../node_modules/reason-react/lib/es6_global/src/ReasonReact.js";
import * as DomHelper$WonderEditor from "../../external/DomHelper.js";

var component = ReasonReact.statelessComponent("Modal");

function render(title, content, param, _) {
  var submitFunc = param[1];
  var closeFunc = param[0];
  var tmp;
  if (submitFunc !== undefined) {
    var submitFunc$1 = submitFunc;
    tmp = React.createElement("div", {
          className: "modal-item-footer"
        }, React.createElement("button", {
              className: "footer-submit",
              onClick: (function () {
                  return Curry._1(submitFunc$1, /* () */0);
                })
            }, DomHelper$WonderEditor.textEl("Submit")));
  } else {
    tmp = null;
  }
  return React.createElement("article", {
              className: "wonder-modal"
            }, React.createElement("div", {
                  className: "modal-item"
                }, React.createElement("div", {
                      className: "modal-item-header"
                    }, DomHelper$WonderEditor.textEl(title), React.createElement("img", {
                          src: "./public/img/close.png",
                          onClick: (function () {
                              return Curry._1(closeFunc, /* () */0);
                            })
                        })), React.createElement("div", {
                      className: "modal-item-content"
                    }, content), tmp));
}

function make(closeFunc, title, content, submitFunc, _) {
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
          /* render */(function (_self) {
              return render(title, content, /* tuple */[
                          closeFunc,
                          submitFunc
                        ], _self);
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
  render ,
  make ,
  
}
/* component Not a pure module */
