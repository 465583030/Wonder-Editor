

import * as React from "react";
import * as ReasonReact from "../../../../../../../../../node_modules/reason-react/lib/es6_global/src/ReasonReact.js";
import * as Css$WonderEditor from "../../../../../external/Css.js";
import * as StoreUtils$WonderEditor from "../../../../../utils/ui/StoreUtils.js";
import * as MainEditorAssetTree$WonderEditor from "../composable_component/assetTree/ui/MainEditorAssetTree.js";
import * as MainEditorAssetHeader$WonderEditor from "../composable_component/header/ui/MainEditorAssetHeader.js";
import * as MainEditorAssetChildrenNode$WonderEditor from "../composable_component/assetChildrenNode/ui/MainEditorAssetChildrenNode.js";

import '../../../../../../../../../src/core/composable_component/mainEditor/composable_component/asset/ui/css/mainEditorAsset.css';

var component = ReasonReact.statelessComponentWithRetainedProps("MainEditorAsset");

function render(param, _) {
  var dispatchFunc = param[1];
  var store = param[0];
  var dragImg = document.createElement("img");
  return React.createElement("article", {
              key: "asset",
              className: "wonder-asset-component"
            }, React.createElement("div", {
                  className: "asset-tree"
                }, ReasonReact.element(undefined, undefined, MainEditorAssetHeader$WonderEditor.make(store, dispatchFunc, /* array */[])), ReasonReact.element(undefined, undefined, MainEditorAssetTree$WonderEditor.make(store, dispatchFunc, dragImg, /* array */[]))), ReasonReact.element(undefined, undefined, MainEditorAssetChildrenNode$WonderEditor.make(store, dispatchFunc, dragImg, 200, /* array */[])));
}

function shouldUpdate(param) {
  return StoreUtils$WonderEditor.shouldComponentUpdate(/* Asset */2, param[/* newSelf */1][/* retainedProps */2][/* updateTypeArr */0]);
}

function make(store, dispatchFunc, _) {
  return /* record */[
          /* debugName */component[/* debugName */0],
          /* reactClassInternal */component[/* reactClassInternal */1],
          /* handedOffState */component[/* handedOffState */2],
          /* willReceiveProps */component[/* willReceiveProps */3],
          /* didMount */component[/* didMount */4],
          /* didUpdate */component[/* didUpdate */5],
          /* willUnmount */component[/* willUnmount */6],
          /* willUpdate */component[/* willUpdate */7],
          /* shouldUpdate */shouldUpdate,
          /* render */(function (self) {
              return render(/* tuple */[
                          store,
                          dispatchFunc
                        ], self);
            }),
          /* initialState */component[/* initialState */10],
          /* retainedProps : record */[/* updateTypeArr */StoreUtils$WonderEditor.getUpdateComponentTypeArr(store)],
          /* reducer */component[/* reducer */12],
          /* subscriptions */component[/* subscriptions */13],
          /* jsElementWrapped */component[/* jsElementWrapped */14]
        ];
}

export {
  component ,
  render ,
  shouldUpdate ,
  make ,
  
}
/*  Not a pure module */

