'use strict';

import * as Most                          from "most";
import * as Curry                         from "../../../../../../../../../../../node_modules/bs-platform/lib/es6/curry.js";
import * as React                         from "react";
import * as Pervasives                    from "../../../../../../../../../../../node_modules/bs-platform/lib/es6/pervasives.js";
import * as ReasonReact                   from "../../../../../../../../../../../node_modules/reason-react/lib/es6_global/src/reasonReact.js";
import * as Log$WonderLog                 from "../../../../../../../../../../../node_modules/wonder-log/lib/es6_global/src/Log.js";
import * as FileBox$WonderEditor          from "../../fileBox/ui/FileBox.js";
import * as DomHelper$WonderEditor        from "../../../../../../../external/DomHelper.js";
import * as AssetTreeUtils$WonderEditor   from "../../../utils/AssetTreeUtils.js";
import * as ClickStreamUtils$WonderEditor from "../../../../../../../utils/ClickStreamUtils.js";

var onClick = FileBox$WonderEditor.Method[/* onSelect */0];

var Method = /* module */[
  /* onDoubleClick */AssetTreeUtils$WonderEditor.onSelect,
  /* onClick */onClick
];

var component = ReasonReact.statelessComponent("FileBox");

function render(_, _$1, imgSrc, folderId, name, _$2, isSelected, _$3) {
  var className = "file-item " + (
    isSelected !== 0 ? "item-active" : ""
  );
  var id = "folder-" + Pervasives.string_of_int(folderId);
  return React.createElement("article", {
              className: className,
              id: id
            }, React.createElement("img", {
                  src: imgSrc
                }), React.createElement("span", {
                  className: "item-text"
                }, DomHelper$WonderEditor.textEl(name)));
}

function make(store, dispatch, imgSrc, folderId, name, sign, isSelected, _) {
  var newrecord = component.slice();
  newrecord[/* didMount */4] = (function () {
      var clickStream = Most.fromEvent("click", document.getElementById("folder-" + Pervasives.string_of_int(folderId)), true);
      Most.forEach((function () {
              Log$WonderLog.print("double click11");
              return AssetTreeUtils$WonderEditor.onSelect(dispatch, folderId);
            }), ClickStreamUtils$WonderEditor.bindClickStream(/* false */0, clickStream));
      Most.forEach((function ($$event) {
              Log$WonderLog.print("sing click");
              return Curry._3(onClick, dispatch, folderId, $$event);
            }), ClickStreamUtils$WonderEditor.bindClickStream(/* true */1, clickStream));
      return /* NoUpdate */0;
    });
  newrecord[/* render */9] = (function (self) {
      return render(store, dispatch, imgSrc, folderId, name, sign, isSelected, self);
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
