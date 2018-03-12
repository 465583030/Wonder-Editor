'use strict';

import * as Curry                            from "../../../../../../../../../node_modules/bs-platform/lib/es6/curry.js";
import * as Sinon                            from "../../../../../../../../../node_modules/wonder-bs-sinon/lib/es6_global/src/sinon.js";
import * as Sinon$1                          from "sinon";
import * as Wonder_jest                      from "../../../../../../../../../node_modules/wonder-bs-jest/lib/es6_global/src/wonder_jest.js";
import * as TestTool$WonderEditor            from "../../../../../ui/tool/TestTool.js";
import * as TestToolEngine$WonderEditor      from "../../../../../logic/engine/tool/TestToolEngine.js";
import * as MainEditorSceneTool$WonderEditor from "../../../../tool/MainEditorSceneTool.js";

describe("engine: mainEditor inspector", (function () {
        var sandbox = Sinon.getSandboxDefaultVal(/* () */0);
        beforeEach((function () {
                sandbox[0] = Sinon$1.sandbox.create();
                return TestToolEngine$WonderEditor.prepare(sandbox);
              }));
        afterEach((function () {
                return Curry._1(Sinon.restoreSandbox, sandbox[0]);
              }));
        describe("test current gameObject", (function () {
                Wonder_jest.test("if not set currentGameObject, there hasn't currentGameObject", (function () {
                        TestTool$WonderEditor.initMainEditor(sandbox);
                        return Curry._2(Wonder_jest.Expect[/* Operators */23][/* = */5], Wonder_jest.Expect[/* expect */0](MainEditorSceneTool$WonderEditor.hasCurrentGameObject(/* () */0)), /* false */0);
                      }));
                describe("else can get currentGameObject", (function () {
                        beforeEach((function () {
                                TestTool$WonderEditor.initMainEditor(sandbox);
                                return MainEditorSceneTool$WonderEditor.setCurrentGameObject(2);
                              }));
                        Wonder_jest.test("the hasCurrentGameObject should == true", (function () {
                                return Curry._2(Wonder_jest.Expect[/* Operators */23][/* = */5], Wonder_jest.Expect[/* expect */0](MainEditorSceneTool$WonderEditor.hasCurrentGameObject(/* () */0)), /* true */1);
                              }));
                        return Wonder_jest.test("the currentGameObject should == the set one", (function () {
                                      return Curry._2(Wonder_jest.Expect[/* Operators */23][/* = */5], Wonder_jest.Expect[/* expect */0](MainEditorSceneTool$WonderEditor.unsafeGetCurrentGameObject(/* () */0)), 2);
                                    }));
                      }));
                return /* () */0;
              }));
        return /* () */0;
      }));

export {
  
}
/*  Not a pure module */
