

import * as Curry from "../../../../../../../../../../node_modules/bs-platform/lib/es6/curry.js";
import * as Sinon from "../../../../../../../../../../node_modules/wonder-bs-sinon/lib/es6_global/src/sinon.js";
import * as Sinon$1 from "sinon";
import * as Wonder_jest from "../../../../../../../../../../node_modules/wonder-bs-jest/lib/es6_global/src/wonder_jest.js";
import * as Color$WonderEditor from "../../../../../../../../src/core/external/Color.js";
import * as FloatService$WonderEditor from "../../../../../../../../src/service/atom/FloatService.js";
import * as BaseEventTool$WonderEditor from "../../../../../../../tool/ui/BaseEventTool.js";
import * as ControllerTool$WonderEditor from "../../../../../../../integration/redo_undo/tool/ControllerTool.js";
import * as GameObjectTool$WonderEditor from "../../../../../../../tool/GameObjectTool.js";
import * as DiffComponentTool$WonderEditor from "../../../../../../../tool/DiffComponentTool.js";
import * as EventListenerTool$WonderEditor from "../../../../../../tool/EventListenerTool.js";
import * as StateLogicService$WonderEditor from "../../../../../../../../src/service/stateTuple/logic/StateLogicService.js";
import * as BuildComponentTool$WonderEditor from "../../../../../../../tool/BuildComponentTool.js";
import * as DirectorToolEngine$WonderEditor from "../../../../../../../tool/engine/DirectorToolEngine.js";
import * as PickColorEventTool$WonderEditor from "../../../../../../../tool/PickColorEventTool.js";
import * as MainEditorLightTool$WonderEditor from "../../../../../../../integration/inspector/composable_component/sceneTree_inspector/light/tool/MainEditorLightTool.js";
import * as MainEditorSceneTool$WonderEditor from "../../../../../../../tool/MainEditorSceneTool.js";
import * as PointLightEngineService$WonderEditor from "../../../../../../../../src/service/state/engine/PointLightEngineService.js";
import * as NoWorkerJobConfigToolEngine$WonderEditor from "../../../../../../../tool/engine/NoWorkerJobConfigToolEngine.js";
import * as CurrentSelectSourceEditorService$WonderEditor from "../../../../../../../../src/service/state/editor/CurrentSelectSourceEditorService.js";

describe("controller inspector point light", (function () {
        var sandbox = Sinon.getSandboxDefaultVal(/* () */0);
        var _prepareDefaultSceneAndInit = function () {
          MainEditorSceneTool$WonderEditor.createDefaultScene(sandbox, (function () {
                  return GameObjectTool$WonderEditor.setCurrentSceneTreeNode(StateLogicService$WonderEditor.getEngineStateToGetData(MainEditorSceneTool$WonderEditor.getDirectionLightInDefaultScene));
                }));
          DirectorToolEngine$WonderEditor.prepareAndInitAllEnginState(/* () */0);
          return ControllerTool$WonderEditor.run(/* () */0);
        };
        var _prepareWithJob = function () {
          MainEditorSceneTool$WonderEditor.initStateWithJob(sandbox, NoWorkerJobConfigToolEngine$WonderEditor.buildNoWorkerJobConfig(undefined, undefined, undefined, undefined, undefined, /* () */0), undefined, /* () */0);
          return Curry._1(EventListenerTool$WonderEditor.stubGetElementByIdReturnFakeDom, Curry._1(EventListenerTool$WonderEditor.buildFakeDom, /* () */0));
        };
        beforeEach((function () {
                sandbox[0] = Sinon$1.sandbox.create();
                StateLogicService$WonderEditor.getAndSetEditorState((function (param) {
                        return CurrentSelectSourceEditorService$WonderEditor.setCurrentSelectSource(/* SceneTree */0, param);
                      }));
                Curry._1(EventListenerTool$WonderEditor.stubGetElementByIdReturnFakeDom, Curry._1(EventListenerTool$WonderEditor.buildFakeDom, /* () */0));
                return Curry._1(ControllerTool$WonderEditor.stubRequestAnimationFrame, Sinon.createEmptyStubWithJsObjSandbox(sandbox));
              }));
        afterEach((function () {
                return Curry._1(Sinon.restoreSandbox, sandbox[0]);
              }));
        describe("test set value into edit and run engineState", (function () {
                Wonder_jest.test("test change color", (function () {
                        _prepareWithJob(/* () */0);
                        _prepareDefaultSceneAndInit(/* () */0);
                        MainEditorLightTool$WonderEditor.setLightTypeToBePointLight(/* () */0);
                        var currentGameObjectPointLightComponent = GameObjectTool$WonderEditor.getCurrentGameObjectPointLightComponent(/* () */0);
                        var newColor = {
                          hex: "#7df1e8",
                          rgb: {
                            r: 125,
                            g: 241,
                            b: 232
                          }
                        };
                        PickColorEventTool$WonderEditor.triggerChangePointLightColor(currentGameObjectPointLightComponent, newColor);
                        return Curry._2(Wonder_jest.Expect[/* Operators */23][/* = */5], Wonder_jest.Expect[/* expect */0](/* tuple */[
                                        Color$WonderEditor.getHexString(PointLightEngineService$WonderEditor.getPointLightColor(DiffComponentTool$WonderEditor.getEditEngineComponent(/* PointLight */7, currentGameObjectPointLightComponent), StateLogicService$WonderEditor.getEditEngineState(/* () */0))),
                                        Color$WonderEditor.getHexString(PointLightEngineService$WonderEditor.getPointLightColor(currentGameObjectPointLightComponent, StateLogicService$WonderEditor.getRunEngineState(/* () */0)))
                                      ]), /* tuple */[
                                    newColor.hex,
                                    newColor.hex
                                  ]);
                      }));
                return Wonder_jest.test("test change intensity", (function () {
                              var _getPointLightIntensity = function (component, engineState) {
                                return FloatService$WonderEditor.truncateFloatValue(PointLightEngineService$WonderEditor.getPointLightIntensity(component, engineState), 5);
                              };
                              var currentGameObjectPointLightComponent = GameObjectTool$WonderEditor.getCurrentGameObjectPointLightComponent(/* () */0);
                              var component = BuildComponentTool$WonderEditor.buildPointLight(currentGameObjectPointLightComponent);
                              var intensityDomIndex = MainEditorLightTool$WonderEditor.getIntensityDomIndex(/* () */0);
                              BaseEventTool$WonderEditor.triggerComponentEvent(component, (function (param) {
                                      return MainEditorLightTool$WonderEditor.triggerLightComponentChangeEvent(intensityDomIndex, 10.1, param);
                                    }));
                              BaseEventTool$WonderEditor.triggerComponentEvent(component, (function (param) {
                                      return MainEditorLightTool$WonderEditor.triggerLightComponentBlurEvent(intensityDomIndex, 10.1, param);
                                    }));
                              return Curry._2(Wonder_jest.Expect[/* Operators */23][/* = */5], Wonder_jest.Expect[/* expect */0](/* tuple */[
                                              _getPointLightIntensity(DiffComponentTool$WonderEditor.getEditEngineComponent(/* PointLight */7, currentGameObjectPointLightComponent), StateLogicService$WonderEditor.getEditEngineState(/* () */0)),
                                              _getPointLightIntensity(currentGameObjectPointLightComponent, StateLogicService$WonderEditor.getRunEngineState(/* () */0))
                                            ]), /* tuple */[
                                          10.1,
                                          10.1
                                        ]);
                            }));
              }));
        return /* () */0;
      }));

export {
  
}
/*  Not a pure module */
