'use strict';

import * as Most                            from "most";
import * as $$Array                         from "../../../../../../../../../node_modules/bs-platform/lib/es6/array.js";
import * as Curry                           from "../../../../../../../../../node_modules/bs-platform/lib/es6/curry.js";
import * as React                           from "react";
import * as Js_dict                         from "../../../../../../../../../node_modules/bs-platform/lib/es6/js_dict.js";
import * as Caml_obj                        from "../../../../../../../../../node_modules/bs-platform/lib/es6/caml_obj.js";
import * as ReasonReact                     from "../../../../../../../../../node_modules/reason-react/lib/es6_global/src/reasonReact.js";
import * as Log$WonderLog                   from "../../../../../../../../../node_modules/wonder-log/lib/es6_global/src/Log.js";
import * as Css$WonderEditor                from "../../../../../external/Css.js";
import * as File$WonderEditor               from "../../../../../external/File.js";
import * as AppStore$WonderEditor           from "../../../../../ui/store/AppStore.js";
import * as TreeNode$WonderEditor           from "../../../../../atom_component/dragTree/component/treeNode/TreeNode.js";
import * as DomHelper$WonderEditor          from "../../../../../external/DomHelper.js";
import * as FileUtils$WonderEditor          from "../utils/FileUtils.js";
import * as AssetUtils$WonderEditor         from "../utils/AssetUtils.js";
import * as ArrayService$WonderEditor       from "../../../../../../service/atom/ArrayService.js";
import * as StateLogicService$WonderEditor  from "../../../../../../service/stateTuple/logic/StateLogicService.js";
import * as AssetEditorService$WonderEditor from "../../../../../../service/state/editor/AssetEditorService.js";

Css$WonderEditor.importCss("./css/mainEditorAsset.css");

function onSelect(dispatch, id) {
  StateLogicService$WonderEditor.getAndSetEditorState((function (param) {
          return AssetEditorService$WonderEditor.setCurrentTreeNode(id, param);
        }));
  Curry._1(dispatch, AppStore$WonderEditor.ReLoad);
  return /* () */0;
}

function onDrop(_, param) {
  Log$WonderLog.print(/* tuple */[
        "drop",
        param[0],
        param[1]
      ]);
  return /* () */0;
}

function addFolder(dispatch, _) {
  StateLogicService$WonderEditor.getAndSetEditorState((function (editorState) {
          var match = AssetUtils$WonderEditor.increaseIndex(editorState);
          var editorState$1 = match[1];
          return AssetEditorService$WonderEditor.setAsseTree(AssetUtils$WonderEditor.insertNewTreeNodeToTargetTreeNode(AssetUtils$WonderEditor.getTargetTreeNodeId(editorState$1), AssetUtils$WonderEditor.buildAssetTreeNodeByIndex(match[0]), AssetEditorService$WonderEditor.unsafeGetAssetTree(editorState$1)), editorState$1);
        }));
  Curry._1(dispatch, AppStore$WonderEditor.ReLoad);
  return /* () */0;
}

function fileLoad($$event) {
  DomHelper$WonderEditor.preventDefault($$event);
  var fileInfoArr = Js_dict.values($$event.target.files).map(FileUtils$WonderEditor.convertFileJsObjectToFileInfoRecord);
  Most.forEach((function (fileResult) {
          Log$WonderLog.print(fileResult);
          return /* () */0;
        }), Most.flatMap((function (fileInfo) {
              return Most.fromPromise(new Promise((function (resolve, _) {
                                var reader = new FileReader();
                                Curry._2(File$WonderEditor.onload, reader, (function (result) {
                                        return resolve(/* record */[
                                                    /* name */fileInfo[/* name */0],
                                                    /* type_ */fileInfo[/* type_ */1],
                                                    /* result */result
                                                  ]);
                                      }));
                                return FileUtils$WonderEditor.readFileByType(reader, fileInfo);
                              })));
            }), Most.from(fileInfoArr)));
  return /* () */0;
}

function _isCurrentTreeNode(id) {
  var match = StateLogicService$WonderEditor.getEditorState(AssetEditorService$WonderEditor.getCurrentTreeNode);
  if (match) {
    var match$1 = +(match[0] === id);
    if (match$1 !== 0) {
      return /* true */1;
    } else {
      return /* false */0;
    }
  } else {
    return /* false */0;
  }
}

function _isNotRoot(uid) {
  return StateLogicService$WonderEditor.getEditorState((function (editorState) {
                return +(AssetUtils$WonderEditor.getRootTreeNodeId(editorState) !== uid);
              }));
}

function buildAssetTreeArray(onSelect, onDrop, assetTree) {
  return $$Array.map((function (param) {
                var children = param[/* children */3];
                var name = param[/* name */1];
                var id = param[/* id */0];
                var match = ArrayService$WonderEditor.hasItem(children);
                if (match !== 0) {
                  return ReasonReact.element(/* Some */[DomHelper$WonderEditor.getRandomKey(/* () */0)], /* None */0, TreeNode$WonderEditor.make(/* tuple */[
                                  id,
                                  name,
                                  _isCurrentTreeNode(id)
                                ], /* tuple */[
                                  onSelect,
                                  onDrop
                                ], "asset", /* Some */["./public/img/12.jpg"], /* Some */[_isNotRoot(id)], /* Some */[buildAssetTreeArray(onSelect, onDrop, children)], /* array */[]));
                } else {
                  return ReasonReact.element(/* Some */[DomHelper$WonderEditor.getRandomKey(/* () */0)], /* None */0, TreeNode$WonderEditor.make(/* tuple */[
                                  id,
                                  name,
                                  _isCurrentTreeNode(id)
                                ], /* tuple */[
                                  onSelect,
                                  onDrop
                                ], "asset", /* Some */["./public/img/12.jpg"], /* Some */[_isNotRoot(id)], /* None */0, /* array */[]));
                }
              }), assetTree);
}

var Method = /* module */[
  /* onSelect */onSelect,
  /* onDrop */onDrop,
  /* addFolder */addFolder,
  /* fileLoad */fileLoad,
  /* _isCurrentTreeNode */_isCurrentTreeNode,
  /* _isNotRoot */_isNotRoot,
  /* buildAssetTreeArray */buildAssetTreeArray
];

var component = ReasonReact.statelessComponentWithRetainedProps("MainEditorAsset");

function render(_, dispatch, _$1) {
  return React.createElement("article", {
              key: "asset",
              className: "asset-component"
            }, React.createElement("div", {
                  className: "asset-tree"
                }, React.createElement("div", {
                      className: "tree-header"
                    }, React.createElement("button", {
                          onClick: (function (param) {
                              return addFolder(dispatch, param);
                            })
                        }, DomHelper$WonderEditor.textEl("addFolder")), React.createElement("button", undefined, DomHelper$WonderEditor.textEl("remove")), React.createElement("input", {
                          className: "file-upload",
                          multiple: true,
                          type: "file",
                          onChange: fileLoad
                        })), StateLogicService$WonderEditor.getEditorState((function (editorState) {
                        return buildAssetTreeArray((function (param) {
                                      return onSelect(dispatch, param);
                                    }), (function (param) {
                                      return onDrop(dispatch, param);
                                    }), AssetEditorService$WonderEditor.unsafeGetAssetTree(editorState));
                      }))), React.createElement("div", {
                  className: "asset-content"
                }));
}

function shouldUpdate(param) {
  return Caml_obj.caml_notequal(param[/* oldSelf */0][/* retainedProps */5], param[/* newSelf */1][/* retainedProps */5]);
}

function make(store, dispatch, _) {
  var newrecord = component.slice();
  newrecord[/* shouldUpdate */8] = shouldUpdate;
  newrecord[/* render */9] = (function (self) {
      return render(store, dispatch, self);
    });
  newrecord[/* retainedProps */11] = /* record */[
    /* assetTree */StateLogicService$WonderEditor.getEditorState(AssetEditorService$WonderEditor.getAssetTree),
    /* currentTreeNode */StateLogicService$WonderEditor.getEditorState(AssetEditorService$WonderEditor.getCurrentTreeNode)
  ];
  return newrecord;
}

export {
  Method       ,
  component    ,
  render       ,
  shouldUpdate ,
  make         ,
  
}
/*  Not a pure module */
