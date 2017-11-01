'use strict';

import * as Curry                   from "../../../node_modules/bs-platform/lib/es6/curry.js";
import * as ReactDOMRe              from "../../../node_modules/reason-react/lib/es6_global/src/reactDOMRe.js";
import * as ReasonReact             from "../../../node_modules/reason-react/lib/es6_global/src/reasonReact.js";
import * as App$WonderEditor        from "./ui/component/app.js";
import * as Reductive$WonderEditor  from "./ui/utils/reductive.js";
import * as IndexStore$WonderEditor from "./ui/store/indexStore.js";

var make = Reductive$WonderEditor.Provider[/* createMake */0](/* None */0, IndexStore$WonderEditor.store);

var IndexStoreProvider = /* module */[/* make */make];

ReactDOMRe.renderToElementWithId(ReasonReact.element(/* None */0, /* None */0, Curry._2(make, App$WonderEditor.make, /* array */[])), "index");

export {
  IndexStoreProvider ,
  
}
/* make Not a pure module */
