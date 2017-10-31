'use strict';

import * as Curry                    from "../../../../../node_modules/bs-platform/lib/es6/curry.js";
import * as Immutable                from "../../../../../node_modules/immutable-re/lib/es6_global/src/Immutable.js";
import * as Caml_exceptions          from "../../../../../node_modules/bs-platform/lib/es6/caml_exceptions.js";
import * as Reductive$WonderEditor   from "../utils/reductive.js";
import * as Middleware$WonderEditor  from "../utils/middleware.js";
import * as StringStore$WonderEditor from "./stringStore.js";

var StringAction = Caml_exceptions.create("AppStore-WonderEditor.StringAction");

var ReplaceState = Caml_exceptions.create("AppStore-WonderEditor.ReplaceState");

function appReducter(state, action) {
  if (action[0] === StringAction) {
    return /* record */[/* notACounter */StringStore$WonderEditor.stringReduce(state[/* notACounter */0], action[1])];
  } else if (action[0] === ReplaceState) {
    return action[1];
  } else {
    return state;
  }
}

var TravelBackward = Caml_exceptions.create("AppStore-WonderEditor.TravelBackward");

var TravelForward = Caml_exceptions.create("AppStore-WonderEditor.TravelForward");

var past = [Immutable.Stack[/* empty */20](/* () */0)];

var future = [Immutable.Stack[/* empty */20](/* () */0)];

function goBack(currentState) {
  var match = Curry._1(Immutable.Stack[/* first */14], past[0]);
  if (match) {
    future[0] = Immutable.Stack[/* addFirst */17](currentState, future[0]);
    past[0] = Immutable.Stack[/* removeFirstOrRaise */19](past[0]);
    return match[0];
  } else {
    return currentState;
  }
}

function goForward(currentState) {
  var match = Curry._1(Immutable.Stack[/* first */14], future[0]);
  if (match) {
    past[0] = Immutable.Stack[/* addFirst */17](currentState, past[0]);
    future[0] = Immutable.Stack[/* removeFirstOrRaise */19](future[0]);
    return match[0];
  } else {
    return currentState;
  }
}

function recordHistory(currentState) {
  past[0] = Immutable.Stack[/* addFirst */17](currentState, past[0]);
  future[0] = Immutable.Stack[/* empty */20](/* () */0);
  return /* () */0;
}

function timeTravel(store, next, action) {
  var currentState = Reductive$WonderEditor.Store[/* getState */5](store);
  if (action === TravelBackward) {
    return Curry._1(next, [
                ReplaceState,
                goBack(currentState)
              ]);
  } else if (action === TravelForward) {
    return Curry._1(next, [
                ReplaceState,
                goForward(currentState)
              ]);
  } else {
    Curry._1(next, action);
    var newState = Reductive$WonderEditor.Store[/* getState */5](store);
    if (currentState !== newState) {
      return recordHistory(currentState);
    } else {
      return 0;
    }
  }
}

function thunkedLoggedTimeTravelLogger(store, next) {
  return (function (param) {
      return Middleware$WonderEditor.thunk(store, (function (param) {
                    return Middleware$WonderEditor.logger(store, (function (param) {
                                  return timeTravel(store, next, param);
                                }), param);
                  }), param);
    });
}

var store = Reductive$WonderEditor.Store[/* create */0](appReducter, /* record */[/* notACounter */""], /* Some */[thunkedLoggedTimeTravelLogger], /* () */0);

export {
  StringAction                  ,
  ReplaceState                  ,
  appReducter                   ,
  TravelBackward                ,
  TravelForward                 ,
  past                          ,
  future                        ,
  goBack                        ,
  goForward                     ,
  recordHistory                 ,
  timeTravel                    ,
  thunkedLoggedTimeTravelLogger ,
  store                         ,
  
}
/* past Not a pure module */
