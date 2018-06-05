

import * as Block from "../../../../../../../../node_modules/bs-platform/lib/es6/block.js";
import * as Curry from "../../../../../../../../node_modules/bs-platform/lib/es6/curry.js";
import * as React from "react";
import * as ReasonReact from "../../../../../../../../node_modules/reason-react/lib/es6_global/src/ReasonReact.js";
import * as Css$WonderEditor from "../../../../external/Css.js";
import * as DomHelper$WonderEditor from "../../../../external/DomHelper.js";
import * as ReactUtils$WonderEditor from "../../../utils/ReactUtils.js";
import * as DragEventUtils$WonderEditor from "../../../../utils/DragEventUtils.js";
import * as StateEditorService$WonderEditor from "../../../../../service/state/editor/StateEditorService.js";
import * as CurrentDragSourceEditorService$WonderEditor from "../../../../../service/state/editor/CurrentDragSourceEditorService.js";

import '../../../../../../../../src/core/atom_component/dragTree/component/treeNode/css/treeNode.css';

var component = ReasonReact.reducerComponent("TreeNode");

function reducer(funcTuple, action) {
  if (typeof action === "number") {
    switch (action) {
      case 0 : 
          return (function () {
              return /* NoUpdate */0;
            });
      case 1 : 
          return (function (state) {
              return /* Update */Block.__(0, [/* record */[/* style */ReactUtils$WonderEditor.addStyleProp("border", "2px dashed blue", state[/* style */0])]]);
            });
      case 2 : 
          return (function (state) {
              return /* Update */Block.__(0, [/* record */[/* style */ReactUtils$WonderEditor.addStyleProp("border", "1px solid red", state[/* style */0])]]);
            });
      case 3 : 
          return (function (state) {
              return /* Update */Block.__(0, [/* record */[/* style */ReactUtils$WonderEditor.addStyleProp("border", "1px solid red", ReactUtils$WonderEditor.addStyleProp("opacity", "1", state[/* style */0]))]]);
            });
      case 4 : 
          return (function (state) {
              return /* Update */Block.__(0, [/* record */[/* style */ReactUtils$WonderEditor.addStyleProp("opacity", "0.2", state[/* style */0])]]);
            });
      
    }
  } else {
    var removedId = action[1];
    var targetId = action[0];
    return (function () {
        var onDrop = funcTuple[1];
        var match = CurrentDragSourceEditorService$WonderEditor.getCurrentDragSource(StateEditorService$WonderEditor.getState(/* () */0));
        var sign = match[0];
        return /* SideEffects */Block.__(1, [(function () {
                      return Curry._1(onDrop, /* tuple */[
                                  targetId,
                                  removedId,
                                  sign
                                ]);
                    })]);
      });
  }
}

function render(attributeTuple, funcTuple, treeChildren, param) {
  var handleRelationError = funcTuple[3];
  var handleSign = funcTuple[2];
  var onSelect = funcTuple[0];
  var dragable = attributeTuple[7];
  var icon = attributeTuple[6];
  var sign = attributeTuple[5];
  var name = attributeTuple[1];
  var uid = attributeTuple[0];
  var send = param[/* send */3];
  var state = param[/* state */1];
  var _getContent = function () {
    return React.createElement("li", {
                style: state[/* style */0],
                onClick: (function () {
                    return Curry._1(onSelect, uid);
                  })
              }, React.createElement("div", {
                    className: "item-ground",
                    draggable: true,
                    onDragEnter: (function (_e) {
                        return Curry._1(send, DragEventUtils$WonderEditor.handleDragEnter(uid, handleSign, handleRelationError, _e));
                      }),
                    onDragLeave: (function (_e) {
                        return Curry._1(send, DragEventUtils$WonderEditor.handleDragLeave(uid, handleSign, handleRelationError, _e));
                      }),
                    onDragOver: DragEventUtils$WonderEditor.handleDragOver,
                    onDrop: (function (_e) {
                        return Curry._1(send, DragEventUtils$WonderEditor.handleDrop(uid, handleRelationError, _e));
                      })
                  }), icon ? React.createElement("img", {
                      src: icon[0]
                    }) : null, DomHelper$WonderEditor.textEl(name));
  };
  if (dragable && !dragable[0]) {
    var content = _getContent(/* () */0);
    return React.createElement("ul", {
                className: "wonder-tree-node"
              }, content, treeChildren ? treeChildren[0] : null);
  } else {
    var content$1 = _getContent(/* () */0);
    return React.createElement("ul", {
                className: "wonder-tree-node",
                draggable: true,
                onDragEnd: (function (_e) {
                    return Curry._1(send, DragEventUtils$WonderEditor.handleDrageEnd(_e));
                  }),
                onDragStart: (function (_e) {
                    return Curry._1(send, DragEventUtils$WonderEditor.handleDragStart(uid, sign, document.createElement("img"), _e));
                  })
              }, content$1, treeChildren ? treeChildren[0] : null);
  }
}

function make(attributeTuple, funcTuple, treeChildren, _) {
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
              return render(attributeTuple, funcTuple, treeChildren, self);
            }),
          /* initialState */(function () {
              if (attributeTuple[2]) {
                if (attributeTuple[3]) {
                  return /* record */[/* style */{
                            background: "red"
                          }];
                } else {
                  return /* record */[/* style */{
                            background: "#c0c0c0"
                          }];
                }
              } else {
                return /* record */[/* style */{
                          border: "1px solid red"
                        }];
              }
            }),
          /* retainedProps */component[/* retainedProps */11],
          /* reducer */(function (param) {
              return reducer(funcTuple, param);
            }),
          /* subscriptions */component[/* subscriptions */13],
          /* jsElementWrapped */component[/* jsElementWrapped */14]
        ];
}

export {
  component ,
  reducer ,
  render ,
  make ,
  
}
/*  Not a pure module */

