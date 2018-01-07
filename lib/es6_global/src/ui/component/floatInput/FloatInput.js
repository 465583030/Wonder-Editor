'use strict';

import * as Block                  from "../../../../../../node_modules/bs-platform/lib/es6/block.js";
import * as Curry                  from "../../../../../../node_modules/bs-platform/lib/es6/curry.js";
import * as React                  from "react";
import * as Caml_format            from "../../../../../../node_modules/bs-platform/lib/es6/caml_format.js";
import * as ReasonReact            from "../../../../../../node_modules/reason-react/lib/es6_global/src/reasonReact.js";
import * as Css$WonderEditor       from "../../../external/Css.js";
import * as DomHelper$WonderEditor from "../../../external/DomHelper.js";

Css$WonderEditor.importCss("./css/floatInput.css");

function change($$event) {
  var inputVal = $$event.target.value;
  switch (inputVal) {
    case "" : 
        return /* Change */[/* Some */[""]];
    case "-" : 
        return /* Change */[/* Some */["-"]];
    default:
      var value = inputVal;
      var regex = (/^-?(0|[1-9][0-9]*)(\.[0-9]{0,6})?$/);
      var match = +regex.test(value);
      if (match !== 0) {
        return /* Change */[/* Some */[value]];
      } else {
        return /* Change */[/* None */0];
      }
  }
}

function triggerOnChangeWithFloatValue(value, onChange) {
  if (onChange) {
    return Curry._1(onChange[0], Caml_format.caml_float_of_string(value));
  } else {
    return /* () */0;
  }
}

var Method = /* module */[
  /* change */change,
  /* triggerOnChangeWithFloatValue */triggerOnChangeWithFloatValue
];

var component = ReasonReact.reducerComponent("FloatInput");

function setInputFiledRef(value, param) {
  param[/* state */4][/* inputField */0][0] = value === null ? /* None */0 : [value];
  return /* () */0;
}

function make(defaultValue, label, onChange, _) {
  var newrecord = component.slice();
  newrecord[/* render */9] = (function (param) {
      var match = param[/* state */4][/* inputValue */1];
      return React.createElement("article", {
                  className: "wonder-float-input"
                }, label ? React.createElement("span", {
                        className: "component-label"
                      }, DomHelper$WonderEditor.textEl(label[0] + " : ")) : null, React.createElement("input", {
                      ref: Curry._1(param[/* handle */0], setInputFiledRef),
                      className: "input-component float-input",
                      type: "text",
                      value: match ? match[0] : "",
                      onChange: Curry._1(param[/* reduce */3], change)
                    }));
    });
  newrecord[/* initialState */10] = (function () {
      if (defaultValue) {
        return /* record */[
                /* inputField */[/* None */0],
                /* inputValue : Some */[defaultValue[0]]
              ];
      } else {
        return /* record */[
                /* inputField */[/* None */0],
                /* inputValue : Some */["0"]
              ];
      }
    });
  newrecord[/* reducer */12] = (function (action, state) {
      var value = action[0];
      if (value) {
        var value$1 = value[0];
        switch (value$1) {
          case "" : 
              return /* UpdateWithSideEffects */Block.__(3, [
                        /* record */[
                          /* inputField */state[/* inputField */0],
                          /* inputValue : None */0
                        ],
                        (function () {
                            return triggerOnChangeWithFloatValue("0", onChange);
                          })
                      ]);
          case "-" : 
              return /* Update */Block.__(0, [/* record */[
                          /* inputField */state[/* inputField */0],
                          /* inputValue : Some */["-"]
                        ]]);
          default:
            return /* UpdateWithSideEffects */Block.__(3, [
                      /* record */[
                        /* inputField */state[/* inputField */0],
                        /* inputValue : Some */[value$1]
                      ],
                      (function () {
                          return triggerOnChangeWithFloatValue(value$1, onChange);
                        })
                    ]);
        }
      } else {
        return /* NoUpdate */0;
      }
    });
  return newrecord;
}

export {
  Method           ,
  component        ,
  setInputFiledRef ,
  make             ,
  
}
/*  Not a pure module */
