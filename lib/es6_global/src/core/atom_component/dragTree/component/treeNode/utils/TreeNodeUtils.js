

import * as Curry from "../../../../../../../../../node_modules/bs-platform/lib/es6/curry.js";
import * as React from "react";
import * as DomHelper$WonderEditor from "../../../../../external/DomHelper.js";

function buildNotDragableUl(treeChildren, isShowChildren, content) {
  return React.createElement("ul", {
              className: "wonder-tree-node"
            }, content, isShowChildren ? treeChildren : null);
}

function getNoBorderCss(param) {
  return "3px solid rgba(0,0,0,0)";
}

function renderChildren(id, isShowChildren, send, togggleChildren) {
  return React.createElement("div", {
              className: "item-triangle",
              onMouseDown: (function ($$event) {
                  DomHelper$WonderEditor.stopPropagation($$event);
                  return Curry._1(send, togggleChildren);
                })
            }, isShowChildren ? React.createElement("img", {
                    src: "./public/img/down.png"
                  }) : React.createElement("img", {
                    src: "./public/img/right.png"
                  }));
}

export {
  buildNotDragableUl ,
  getNoBorderCss ,
  renderChildren ,
  
}
/* react Not a pure module */
