'use strict';

import * as Curry                            from "../../../../node_modules/bs-platform/lib/es6/curry.js";
import * as Js_exn                           from "../../../../node_modules/bs-platform/lib/es6/js_exn.js";
import * as Caml_obj                         from "../../../../node_modules/bs-platform/lib/es6/caml_obj.js";
import * as Js_option                        from "../../../../node_modules/bs-platform/lib/es6/js_option.js";
import * as Pervasives                       from "../../../../node_modules/bs-platform/lib/es6/pervasives.js";
import * as Exception$WonderEditor           from "../exception/Exception.js";
import * as EditorStateDataEdit$WonderEditor from "../logic/edit/EditorStateDataEdit.js";

function _getIsTestFromStateData(param) {
  return param[/* isTest */1];
}

function describe(message, func, $staropt$star, _) {
  var preCondition = $staropt$star ? $staropt$star[0] : (function () {
        return /* true */1;
      });
  var match = Curry._1(preCondition, /* () */0);
  if (match !== 0) {
    try {
      return Curry._1(func, /* () */0);
    }
    catch (raw_exn){
      var exn = Js_exn.internalToOCamlException(raw_exn);
      if (exn[0] === Exception$WonderEditor.Check_fail) {
        return Pervasives.failwith("" + (String(message) + ("->" + (String(exn[1]) + ""))));
      } else {
        throw exn;
      }
    }
  } else {
    return /* () */0;
  }
}

function test(message, func) {
  try {
    return Curry._1(func, /* () */0);
  }
  catch (raw_exn){
    var exn = Js_exn.internalToOCamlException(raw_exn);
    if (exn[0] === Exception$WonderEditor.Check_fail) {
      return Pervasives.failwith("" + (String(message) + ("->" + (String(exn[1]) + ""))));
    } else {
      throw exn;
    }
  }
}

function testWithMessageFunc(messageFunc, func) {
  try {
    return Curry._1(func, /* () */0);
  }
  catch (raw_exn){
    var exn = Js_exn.internalToOCamlException(raw_exn);
    if (exn[0] === Exception$WonderEditor.Check_fail) {
      var message = Curry._1(messageFunc, /* () */0);
      return Pervasives.failwith("" + (String(message) + ("->" + (String(exn[1]) + ""))));
    } else {
      throw exn;
    }
  }
}

function requireCheck(f) {
  var match = _getIsTestFromStateData(EditorStateDataEdit$WonderEditor.stateData);
  if (match !== 0) {
    return Curry._1(f, /* () */0);
  } else {
    return /* () */0;
  }
}

function ensureCheck(f, returnVal) {
  var match = _getIsTestFromStateData(EditorStateDataEdit$WonderEditor.stateData);
  if (match !== 0) {
    Curry._1(f, returnVal);
    return returnVal;
  } else {
    return returnVal;
  }
}

function _assert(result, message) {
  if (result !== 0) {
    return /* () */0;
  } else {
    throw [
          Exception$WonderEditor.Check_fail,
          message
        ];
  }
}

function assertTrue(source) {
  return _assert(+(source === /* true */1), "expect to be true, but actual is false");
}

function assertFalse(source) {
  return _assert(+(source === /* false */0), "expect to be false, but actual is true");
}

function assertJsTrue(source) {
  return _assert(Caml_obj.caml_equal(source, true), "expect to be true, but actual is false");
}

function assertJsFalse(source) {
  return _assert(Caml_obj.caml_equal(source, false), "expect to be false, but actual is true");
}

var _isNullableExist = (
function(source) {
    return source !== undefined && source !== null;
}
);

function assertNullableExist(source) {
  return _assert(+Curry._1(_isNullableExist, source), "expect to be exist, but actual not");
}

function assertExist(source) {
  return _assert(Js_option.isSome(source), "expect to be exist, but actual not");
}

function assertNotExist(source) {
  return _assert(Js_option.isNone(source), "expect to be not exist, but actual exist");
}

function _getEqualMessage(source, target) {
  return "\"expect to be " + (String(source) + (", but actual is " + (String(target) + "\"")));
}

function assertEqual(_, source, target) {
  return _assert(Caml_obj.caml_equal(source, target), _getEqualMessage(source, target));
}

function _getNotEqualMessage(source, target) {
  return "\"expect to be " + (String(source) + (", but actual is " + (String(target) + "\"")));
}

function assertNotEqual(_, source, target) {
  return _assert(Caml_obj.caml_notequal(source, target), _getEqualMessage(source, target));
}

function _getEqualMessage$1(source, target) {
  return "expect to be " + (String(source) + (", but actual is " + (String(target) + "")));
}

function assertGt(_, source, target) {
  return _assert(Caml_obj.caml_greaterthan(source, target), "expect " + (String(source) + (" > " + (String(target) + ", but actual isn\'t"))));
}

function assertGte(_, source, target) {
  return _assert(Caml_obj.caml_greaterequal(source, target), "expect " + (String(source) + (" >= " + (String(target) + ", but actual isn\'t"))));
}

function assertLt(_, source, target) {
  return _assert(Caml_obj.caml_lessthan(source, target), "expect " + (String(source) + (" < " + (String(target) + ", but actual isn\'t"))));
}

function assertLte(_, source, target) {
  return _assert(Caml_obj.caml_lessequal(source, target), "expect " + (String(source) + (" <= " + (String(target) + ", but actual isn\'t"))));
}

function $eq(a, b) {
  return assertEqual(/* Int */0, a, b);
}

function $eq$eq$dot(a, b) {
  return assertEqual(/* Float */1, a, b);
}

function $less$great$eq(a, b) {
  return assertNotEqual(/* Int */0, a, b);
}

function $less$great$eq$dot(a, b) {
  return assertNotEqual(/* Float */1, a, b);
}

function $great(a, b) {
  return assertGt(/* Int */0, a, b);
}

function $great$dot(a, b) {
  return assertGt(/* Float */1, a, b);
}

function $great$eq(a, b) {
  return assertGte(/* Int */0, a, b);
}

function $great$eq$dot(a, b) {
  return assertGte(/* Float */1, a, b);
}

function $less(a, b) {
  return assertLt(/* Int */0, a, b);
}

function $less$dot(a, b) {
  return assertLt(/* Float */1, a, b);
}

function $less$eq(a, b) {
  return assertLte(/* Int */0, a, b);
}

function $less$eq$dot(a, b) {
  return assertLte(/* Float */1, a, b);
}

var Operators = /* module */[
  /* = */$eq,
  /* ==. */$eq$eq$dot,
  /* <>= */$less$great$eq,
  /* <>=. */$less$great$eq$dot,
  /* > */$great,
  /* >. */$great$dot,
  /* >= */$great$eq,
  /* >=. */$great$eq$dot,
  /* < */$less,
  /* <. */$less$dot,
  /* <= */$less$eq,
  /* <=. */$less$eq$dot
];

export {
  _getIsTestFromStateData ,
  describe                ,
  test                    ,
  testWithMessageFunc     ,
  requireCheck            ,
  ensureCheck             ,
  _assert                 ,
  assertTrue              ,
  assertFalse             ,
  assertJsTrue            ,
  assertJsFalse           ,
  _isNullableExist        ,
  assertNullableExist     ,
  assertExist             ,
  assertNotExist          ,
  assertEqual             ,
  _getNotEqualMessage     ,
  assertNotEqual          ,
  _getEqualMessage$1        as _getEqualMessage,
  assertGt                ,
  assertGte               ,
  assertLt                ,
  assertLte               ,
  Operators               ,
  
}
/* _isNullableExist Not a pure module */
