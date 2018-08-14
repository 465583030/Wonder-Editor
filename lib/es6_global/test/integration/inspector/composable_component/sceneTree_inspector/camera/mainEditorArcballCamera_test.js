

import * as Curry from "../../../../../../../../node_modules/bs-platform/lib/es6/curry.js";
import * as Sinon from "../../../../../../../../node_modules/wonder-bs-sinon/lib/es6_global/src/sinon.js";
import * as Sinon$1 from "sinon";
import * as Wonder_jest from "../../../../../../../../node_modules/wonder-bs-jest/lib/es6_global/src/wonder_jest.js";
import * as TestTool$WonderEditor from "../../../../../tool/TestTool.js";
import * as FloatService$WonderEditor from "../../../../../../src/service/atom/FloatService.js";
import * as BaseEventTool$WonderEditor from "../../../../../tool/ui/BaseEventTool.js";
import * as InspectorTool$WonderEditor from "../../../../../tool/ui/InspectorTool.js";
import * as GameObjectTool$WonderEditor from "../../../../../tool/GameObjectTool.js";
import * as StateLogicService$WonderEditor from "../../../../../../src/service/stateTuple/logic/StateLogicService.js";
import * as BuildComponentTool$WonderEditor from "../../../../../tool/BuildComponentTool.js";
import * as MainEditorSceneTool$WonderEditor from "../../../../../tool/MainEditorSceneTool.js";
import * as AddableComponentTool$WonderEditor from "../../../atom_component/addableComponent/tool/AddableComponentTool.js";
import * as MainEditorCameraTool$WonderEditor from "../../../../../tool/MainEditorCameraTool.js";
import * as ArcballCameraEngineService$WonderEditor from "../../../../../../src/service/state/engine/ArcballCameraEngineService.js";
import * as CurrentSelectSourceEditorService$WonderEditor from "../../../../../../src/service/state/editor/CurrentSelectSourceEditorService.js";

describe("MainEditor ArcballCameraController", (function () {
        var sandbox = Sinon.getSandboxDefaultVal(/* () */0);
        beforeEach((function () {
                sandbox[0] = Sinon$1.sandbox.create();
                return MainEditorSceneTool$WonderEditor.initState(sandbox, undefined, /* () */0);
              }));
        afterEach((function () {
                return Curry._1(Sinon.restoreSandbox, sandbox[0]);
              }));
        describe("test set currentSceneTreeNode to be camera", (function () {
                beforeEach((function () {
                        MainEditorSceneTool$WonderEditor.createDefaultScene(sandbox, MainEditorSceneTool$WonderEditor.setFirstCameraTobeCurrentSceneTreeNode);
                        return StateLogicService$WonderEditor.getAndSetEditorState((function (param) {
                                      return CurrentSelectSourceEditorService$WonderEditor.setCurrentSelectSource(/* SceneTree */0, param);
                                    }));
                      }));
                describe("test change arcballCameraController distance", (function () {
                        describe("test logic", (function () {
                                return Wonder_jest.test("test change distance should set into engine", (function () {
                                              AddableComponentTool$WonderEditor.addArcballCameraInCamera(/* () */0);
                                              var currentGameObjectArcballCamera = GameObjectTool$WonderEditor.getCurrentGameObjectArcballCamera(/* () */0);
                                              var component = BuildComponentTool$WonderEditor.buildInspectorComponent(TestTool$WonderEditor.buildEmptyAppState(/* () */0), InspectorTool$WonderEditor.buildFakeAllShowComponentConfig(/* () */0));
                                              BaseEventTool$WonderEditor.triggerComponentEvent(component, (function (param) {
                                                      return MainEditorCameraTool$WonderEditor.triggerChangeArcballDistance(21.1, param);
                                                    }));
                                              BaseEventTool$WonderEditor.triggerComponentEvent(component, (function (param) {
                                                      return MainEditorCameraTool$WonderEditor.triggerBlurArcballDistance(21.1, param);
                                                    }));
                                              return Curry._2(Wonder_jest.Expect[/* Operators */23][/* = */5], Wonder_jest.Expect[/* expect */0](FloatService$WonderEditor.truncateFloatValue(StateLogicService$WonderEditor.getEngineStateToGetData((function (param) {
                                                                        return ArcballCameraEngineService$WonderEditor.unsafeGetArcballCameraControllerDistance(currentGameObjectArcballCamera, param);
                                                                      })), 5)), 21.1);
                                            }));
                              }));
                        return /* () */0;
                      }));
                describe("test change arcballCameraController minDistance", (function () {
                        describe("test logic", (function () {
                                return Wonder_jest.test("test change minDistance should set into engine", (function () {
                                              AddableComponentTool$WonderEditor.addArcballCameraInCamera(/* () */0);
                                              var currentGameObjectArcballCamera = GameObjectTool$WonderEditor.getCurrentGameObjectArcballCamera(/* () */0);
                                              var component = BuildComponentTool$WonderEditor.buildInspectorComponent(TestTool$WonderEditor.buildEmptyAppState(/* () */0), InspectorTool$WonderEditor.buildFakeAllShowComponentConfig(/* () */0));
                                              BaseEventTool$WonderEditor.triggerComponentEvent(component, (function (param) {
                                                      return MainEditorCameraTool$WonderEditor.triggerChangeArcballMinDistance(11.1, param);
                                                    }));
                                              BaseEventTool$WonderEditor.triggerComponentEvent(component, (function (param) {
                                                      return MainEditorCameraTool$WonderEditor.triggerBlurArcballMinDistance(11.1, param);
                                                    }));
                                              return Curry._2(Wonder_jest.Expect[/* Operators */23][/* = */5], Wonder_jest.Expect[/* expect */0](FloatService$WonderEditor.truncateFloatValue(StateLogicService$WonderEditor.getEngineStateToGetData((function (param) {
                                                                        return ArcballCameraEngineService$WonderEditor.unsafeGetArcballCameraControllerMinDistance(currentGameObjectArcballCamera, param);
                                                                      })), 5)), 11.1);
                                            }));
                              }));
                        return /* () */0;
                      }));
                return /* () */0;
              }));
        return /* () */0;
      }));

export {
  
}
/*  Not a pure module */