'use strict';

import * as Block                            from "../../../../../../../../../../../node_modules/bs-platform/lib/es6/block.js";
import * as Curry                            from "../../../../../../../../../../../node_modules/bs-platform/lib/es6/curry.js";
import * as React                            from "react";
import * as Js_option                        from "../../../../../../../../../../../node_modules/bs-platform/lib/es6/js_option.js";
import * as ReasonReact                      from "../../../../../../../../../../../node_modules/reason-react/lib/es6_global/src/reasonReact.js";
import * as AppStore$WonderEditor            from "../../../../../../../ui/store/AppStore.js";
import * as DomHelper$WonderEditor           from "../../../../../../../external/DomHelper.js";
import * as AssetUtils$WonderEditor          from "../../../../asset/utils/AssetUtils.js";
import * as StateLogicService$WonderEditor   from "../../../../../../../../service/stateTuple/logic/StateLogicService.js";
import * as AssetEditorService$WonderEditor  from "../../../../../../../../service/state/editor/AssetEditorService.js";
import * as AssetTreeNodeUtils$WonderEditor  from "../../../../asset/utils/AssetTreeNodeUtils.js";
import * as StateEditorService$WonderEditor  from "../../../../../../../../service/state/editor/StateEditorService.js";
import * as SparseMapService$WonderCommonlib from "../../../../../../../../../../../node_modules/wonder-commonlib/lib/es6_global/src/SparseMapService.js";

function setInputNodeRef(value, param) {
  param[/* state */4][/* inputField */0][0] = value === null ? /* None */0 : [value];
  return /* () */0;
}

function change($$event) {
  var inputVal = $$event.target.value;
  return /* Change */[inputVal];
}

function blur() {
  return /* Blur */0;
}

function triggerBlur(dispatch, value, nodeId) {
  var editorState = StateEditorService$WonderEditor.getState(/* () */0);
  var nodeMap = AssetEditorService$WonderEditor.unsafeGetNodeMap(editorState);
  StateEditorService$WonderEditor.setState(AssetEditorService$WonderEditor.setNodeMap(SparseMapService$WonderCommonlib.set(nodeId, AssetTreeNodeUtils$WonderEditor.renameNodeResult(value, SparseMapService$WonderCommonlib.unsafeGet(nodeId, nodeMap)), nodeMap.slice()), editorState));
  return Curry._1(dispatch, AppStore$WonderEditor.ReLoad);
}

function showFolderInfo(nodeResult, param) {
  var state = param[/* state */4];
  var reduce = param[/* reduce */3];
  var handle = param[/* handle */0];
  var match = nodeResult[/* type_ */1];
  switch (match) {
    case 0 : 
        var match$1 = state[/* isAssetTreeRootNode */3];
        return React.createElement("div", {
                    className: ""
                  }, React.createElement("h1", undefined, DomHelper$WonderEditor.textEl("Folder")), React.createElement("hr", undefined), React.createElement("span", {
                        className: ""
                      }, DomHelper$WonderEditor.textEl("name:")), React.createElement("input", {
                        ref: Curry._1(handle, setInputNodeRef),
                        className: "input-component float-input",
                        disabled: match$1 !== 0 ? true : false,
                        type: "text",
                        value: state[/* inputValue */1],
                        onBlur: Curry._1(reduce, blur),
                        onChange: Curry._1(reduce, change)
                      }));
    case 1 : 
        return React.createElement("div", {
                    className: ""
                  }, React.createElement("h1", undefined, DomHelper$WonderEditor.textEl("Image")), React.createElement("hr", undefined), React.createElement("span", {
                        className: ""
                      }, DomHelper$WonderEditor.textEl("name:")), React.createElement("input", {
                        ref: Curry._1(handle, setInputNodeRef),
                        className: "input-component float-input",
                        type: "text",
                        value: state[/* inputValue */1],
                        onBlur: Curry._1(reduce, blur),
                        onChange: Curry._1(reduce, change)
                      }));
    case 2 : 
        return React.createElement("div", undefined, React.createElement("h1", undefined, DomHelper$WonderEditor.textEl("Json")), React.createElement("hr", undefined), React.createElement("span", {
                        className: ""
                      }, DomHelper$WonderEditor.textEl("name:")), React.createElement("input", {
                        ref: Curry._1(handle, setInputNodeRef),
                        className: "input-component float-input",
                        type: "text",
                        value: state[/* inputValue */1],
                        onBlur: Curry._1(reduce, blur),
                        onChange: Curry._1(reduce, change)
                      }), React.createElement("p", undefined, DomHelper$WonderEditor.textEl(Js_option.getExn(nodeResult[/* result */2]))));
    
  }
}

var Method = /* module */[
  /* change */change,
  /* blur */blur,
  /* triggerBlur */triggerBlur,
  /* showFolderInfo */showFolderInfo
];

var component = ReasonReact.reducerComponent("AssetTreeInspector");

function reducer(dispatch, nodeId, action, state) {
  if (action) {
    return /* Update */Block.__(0, [/* record */[
                /* inputField */state[/* inputField */0],
                /* inputValue */action[0],
                /* primitiveName */state[/* primitiveName */2],
                /* isAssetTreeRootNode */state[/* isAssetTreeRootNode */3]
              ]]);
  } else {
    var value = state[/* inputValue */1];
    if (value === "") {
      return /* Update */Block.__(0, [/* record */[
                  /* inputField */state[/* inputField */0],
                  /* inputValue */state[/* primitiveName */2],
                  /* primitiveName */state[/* primitiveName */2],
                  /* isAssetTreeRootNode */state[/* isAssetTreeRootNode */3]
                ]]);
    } else {
      return /* UpdateWithSideEffects */Block.__(3, [
                /* record */[
                  /* inputField */state[/* inputField */0],
                  /* inputValue */state[/* inputValue */1],
                  /* primitiveName */value,
                  /* isAssetTreeRootNode */state[/* isAssetTreeRootNode */3]
                ],
                (function () {
                    return triggerBlur(dispatch, value, nodeId);
                  })
              ]);
    }
  }
}

function render(nodeResult, self) {
  return React.createElement("article", {
              key: "AssetTreeInspector",
              className: "inspector-component"
            }, showFolderInfo(nodeResult, self));
}

function make(_, dispatch, nodeId, nodeResult, _$1) {
  var newrecord = component.slice();
  newrecord[/* render */9] = (function (self) {
      return render(nodeResult, self);
    });
  newrecord[/* initialState */10] = (function () {
      return /* record */[
              /* inputField */[/* None */0],
              /* inputValue */nodeResult[/* name */0],
              /* primitiveName */nodeResult[/* name */0],
              /* isAssetTreeRootNode */AssetUtils$WonderEditor.isIdEqual(StateLogicService$WonderEditor.getEditorState(AssetUtils$WonderEditor.getRootTreeNodeId), nodeId)
            ];
    });
  newrecord[/* reducer */12] = (function (param, param$1) {
      return reducer(dispatch, nodeId, param, param$1);
    });
  return newrecord;
}

export {
  setInputNodeRef ,
  Method          ,
  component       ,
  reducer         ,
  render          ,
  make            ,
  
}
/* component Not a pure module */
