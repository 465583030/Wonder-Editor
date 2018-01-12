'use strict';

import * as Curry                             from "../../../../node_modules/bs-platform/lib/es6/curry.js";
import * as React                             from "react";
import * as ReasonReact                       from "../../../../node_modules/reason-react/lib/es6_global/src/reasonReact.js";
import * as Css$WonderEditor                  from "../external/Css.js";
import * as AppStore$WonderEditor             from "./store/AppStore.js";
import * as FileInput$WonderEditor            from "./component/fileInput/FileInput.js";
import * as MainEditor$WonderEditor           from "../component/mainEditor/ui/MainEditor.js";
import * as AppExtensionView$WonderEditor     from "../logic/view/AppExtensionView.js";
import * as ExtensionParseSystem$WonderEditor from "./extension/data/extension_component/ExtensionParseSystem.js";

Css$WonderEditor.importCss("./css/app.css");

function addExtension(text) {
  return AppExtensionView$WonderEditor.setExtension(AppExtensionView$WonderEditor.getStorageParentKey(/* () */0), text);
}

var Method = /* module */[/* addExtension */addExtension];

var component = ReasonReact.statelessComponent("App");

function render(store, dispatch, _) {
  var match = store[/* isDidMounted */1];
  if (match !== 0) {
    var value = AppExtensionView$WonderEditor.getExtension(AppExtensionView$WonderEditor.getStorageParentKey(/* () */0));
    return React.createElement("article", {
                key: "app",
                className: "wonder-app-component"
              }, value ? ExtensionParseSystem$WonderEditor.extensionPanelComponent("App", value[0], store) : null, ReasonReact.element(/* None */0, /* None */0, FileInput$WonderEditor.make(/* Some */["show Input"], /* Some */[(function (value) {
                            return AppExtensionView$WonderEditor.setExtension(AppExtensionView$WonderEditor.getStorageParentKey(/* () */0), value);
                          })], /* array */[])), ReasonReact.element(/* None */0, /* None */0, MainEditor$WonderEditor.make(store, dispatch, /* array */[])));
  } else {
    return React.createElement("article", {
                key: "app",
                className: "app-component"
              });
  }
}

function make(store, dispatch, _) {
  var newrecord = component.slice();
  newrecord[/* didMount */4] = (function () {
      var value = AppExtensionView$WonderEditor.getExtension(AppExtensionView$WonderEditor.getStorageParentKey(/* () */0));
      if (value) {
        var componentsMap = ExtensionParseSystem$WonderEditor.createComponentMap(value[0]);
        Curry._1(dispatch, [
              AppStore$WonderEditor.MapAction,
              /* StoreMap */[/* Some */[componentsMap]]
            ]);
      }
      Curry._1(dispatch, AppStore$WonderEditor.IsDidMounted);
      return /* NoUpdate */0;
    });
  newrecord[/* render */9] = (function (_self) {
      return render(store, dispatch, _self);
    });
  return newrecord;
}

export {
  Method    ,
  component ,
  render    ,
  make      ,
  
}
/*  Not a pure module */
