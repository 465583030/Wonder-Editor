'use strict';

import * as Curry                                   from "../../../../../../../../../../../node_modules/bs-platform/lib/es6/curry.js";
import * as React                                   from "react";
import * as ReasonReact                             from "../../../../../../../../../../../node_modules/reason-react/lib/es6_global/src/reasonReact.js";
import * as AppStore$WonderEditor                   from "../../../../../../../ui/store/AppStore.js";
import * as DomHelper$WonderEditor                  from "../../../../../../../external/DomHelper.js";
import * as EventUtils$WonderEditor                 from "../../../../../../../utils/EventUtils.js";
import * as StateLogicService$WonderEditor          from "../../../../../../../../service/stateTuple/logic/StateLogicService.js";
import * as AssetEditorService$WonderEditor         from "../../../../../../../../service/state/editor/AssetEditorService.js";
import * as CurrentSourceEditorService$WonderEditor from "../../../../../../../../service/state/editor/CurrentSourceEditorService.js";

function onSelect(dispatch, fileId, _) {
  StateLogicService$WonderEditor.getAndSetEditorState((function (editorState) {
          return CurrentSourceEditorService$WonderEditor.setCurrentSource(/* AssetFile */2, AssetEditorService$WonderEditor.setCurrentAssetFileNode(fileId, editorState));
        }));
  Curry._1(dispatch, AppStore$WonderEditor.ReLoad);
  return /* () */0;
}

var Method = /* module */[/* onSelect */onSelect];

var component = ReasonReact.statelessComponent("FileBox");

function render(_, dispatch, imgSrc, fileId, fileName, sign, isSelected, _$1) {
  var className = "file-item " + (
    isSelected !== 0 ? "item-active" : ""
  );
  return React.createElement("article", {
              className: className,
              onClick: (function (_event) {
                  return onSelect(dispatch, fileId, _event);
                })
            }, React.createElement("img", {
                  src: imgSrc,
                  onDragStart: (function (param) {
                      return EventUtils$WonderEditor.dragStart(fileId, sign, param);
                    })
                }), React.createElement("span", {
                  className: "item-text"
                }, DomHelper$WonderEditor.textEl(fileName)));
}

function make(store, dispatch, imgSrc, fileId, fileName, sign, isSelected, _) {
  var newrecord = component.slice();
  newrecord[/* render */9] = (function (self) {
      return render(store, dispatch, imgSrc, fileId, fileName, sign, isSelected, self);
    });
  return newrecord;
}

export {
  Method    ,
  component ,
  render    ,
  make      ,
  
}
/* component Not a pure module */
