

import * as React from "react";
import * as ReasonReact from "../../../../../../../../../../../node_modules/reason-react/lib/es6_global/src/ReasonReact.js";
import * as FileBox$WonderEditor from "../../../atom_component/fileBox/ui/FileBox.js";
import * as DomHelper$WonderEditor from "../../../../../../../external/DomHelper.js";
import * as FolderBox$WonderEditor from "../../../atom_component/folderBox/ui/FolderBox.js";
import * as AssetUtils$WonderEditor from "../../../utils/AssetUtils.js";
import * as OptionService$WonderEditor from "../../../../../../../../service/primitive/OptionService.js";
import * as AssetTreeUtils$WonderEditor from "../../utils/AssetTreeUtils.js";
import * as StateEditorService$WonderEditor from "../../../../../../../../service/state/editor/StateEditorService.js";
import * as SparseMapService$WonderCommonlib from "../../../../../../../../../../../node_modules/wonder-commonlib/lib/es6_global/src/SparseMapService.js";
import * as AssetNodeMapEditorService$WonderEditor from "../../../../../../../../service/state/editor/asset/AssetNodeMapEditorService.js";
import * as AssetTreeRootEditorService$WonderEditor from "../../../../../../../../service/state/editor/asset/AssetTreeRootEditorService.js";
import * as AssetCurrentNodeIdEditorService$WonderEditor from "../../../../../../../../service/state/editor/asset/AssetCurrentNodeIdEditorService.js";

function _isSelected(currentNodeId, id) {
  if (currentNodeId) {
    return AssetUtils$WonderEditor.isIdEqual(id, currentNodeId[0]);
  } else {
    return false;
  }
}

function showSpecificTreeNodeChildren(param, param$1, assetTreeNodeChildrenArr) {
  var currentNodeId = param$1[2];
  var nodeMap = param$1[1];
  var dragImg = param$1[0];
  var dispatchFunc = param[1];
  var store = param[0];
  return assetTreeNodeChildrenArr.map((function (param) {
                var id = param[/* id */0];
                var match = SparseMapService$WonderCommonlib.unsafeGet(id, nodeMap);
                var name = match[/* name */0];
                switch (match[/* type_ */1]) {
                  case 0 : 
                      return ReasonReact.element(/* Some */[DomHelper$WonderEditor.getRandomKey(/* () */0)], /* None */0, FolderBox$WonderEditor.make(store, dispatchFunc, /* tuple */[
                                      dragImg,
                                      "./public/img/11.jpg",
                                      id,
                                      name,
                                      _isSelected(currentNodeId, id),
                                      AssetTreeUtils$WonderEditor.getFlag(/* () */0)
                                    ], /* tuple */[
                                      (function (param) {
                                          return AssetTreeUtils$WonderEditor.onDrop(dispatchFunc, param);
                                        }),
                                      AssetTreeUtils$WonderEditor.handleFlag,
                                      AssetUtils$WonderEditor.isTreeNodeRelationError
                                    ], /* array */[]));
                  case 1 : 
                      return ReasonReact.element(/* Some */[DomHelper$WonderEditor.getRandomKey(/* () */0)], /* None */0, FileBox$WonderEditor.make(store, dispatchFunc, /* tuple */[
                                      dragImg,
                                      OptionService$WonderEditor.unsafeGet(match[/* result */2]),
                                      id,
                                      name,
                                      AssetTreeUtils$WonderEditor.getFlag(/* () */0),
                                      _isSelected(currentNodeId, id)
                                    ], /* array */[]));
                  case 2 : 
                      return ReasonReact.element(/* Some */[DomHelper$WonderEditor.getRandomKey(/* () */0)], /* None */0, FileBox$WonderEditor.make(store, dispatchFunc, /* tuple */[
                                      dragImg,
                                      "./public/img/12.jpg",
                                      id,
                                      name,
                                      AssetTreeUtils$WonderEditor.getFlag(/* () */0),
                                      _isSelected(currentNodeId, id)
                                    ], /* array */[]));
                  
                }
              }));
}

function buildContent(param, dragImg) {
  var editorState = StateEditorService$WonderEditor.getState(/* () */0);
  return showSpecificTreeNodeChildren(/* tuple */[
              param[0],
              param[1]
            ], /* tuple */[
              dragImg,
              AssetNodeMapEditorService$WonderEditor.unsafeGetNodeMap(editorState),
              AssetCurrentNodeIdEditorService$WonderEditor.getCurrentNodeId(editorState)
            ], OptionService$WonderEditor.unsafeGet(AssetUtils$WonderEditor.getSpecificTreeNodeById(AssetUtils$WonderEditor.getTargetTreeNodeId(editorState), AssetTreeRootEditorService$WonderEditor.unsafeGetAssetTreeRoot(editorState)))[/* children */1]);
}

var Method = /* module */[
  /* _isSelected */_isSelected,
  /* showSpecificTreeNodeChildren */showSpecificTreeNodeChildren,
  /* buildContent */buildContent
];

var component = ReasonReact.statelessComponent("MainEditorAssetHeader");

function render(param, dragImg, _) {
  return React.createElement("article", {
              key: "assetChildrenNode",
              className: "wonder-asset-assetChildren"
            }, buildContent(/* tuple */[
                  param[0],
                  param[1]
                ], dragImg));
}

function make(store, dispatchFunc, dragImg, _) {
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
                        ], dragImg, self);
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
