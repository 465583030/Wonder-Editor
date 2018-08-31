

import * as TestTool$WonderEditor from "./TestTool.js";
import * as BaseEventTool$WonderEditor from "./ui/BaseEventTool.js";
import * as GameObjectUtils$WonderEditor from "../../src/core/utils/engine/GameObjectUtils.js";
import * as FakeGlToolEngine$WonderEditor from "./engine/FakeGlToolEngine.js";
import * as DefaultSceneUtils$WonderEditor from "../../src/core/utils/engine/DefaultSceneUtils.js";
import * as StateLogicService$WonderEditor from "../../src/service/stateTuple/logic/StateLogicService.js";
import * as BuildComponentTool$WonderEditor from "./BuildComponentTool.js";
import * as SceneEditorService$WonderEditor from "../../src/service/state/editor/scene/SceneEditorService.js";
import * as SceneTreeEventTool$WonderEditor from "./SceneTreeEventTool.js";
import * as StateEditorService$WonderEditor from "../../src/service/state/editor/StateEditorService.js";
import * as CameraEngineService$WonderEditor from "../../src/service/state/engine/CameraEngineService.js";
import * as MainEditorSceneTool$WonderEditor from "./MainEditorSceneTool.js";
import * as SceneTreeNodeDomTool$WonderEditor from "./domIndex/SceneTreeNodeDomTool.js";
import * as GeometryEngineService$WonderEditor from "../../src/service/state/engine/GeometryEngineService.js";
import * as GameObjectLogicService$WonderEditor from "../../src/service/stateTuple/logic/GameObjectLogicService.js";
import * as PrimitiveEngineService$WonderEditor from "../../src/service/state/engine/PrimitiveEngineService.js";
import * as ArcballCameraEngineService$WonderEditor from "../../src/service/state/engine/ArcballCameraEngineService.js";
import * as BasicCameraViewEngineService$WonderEditor from "../../src/service/state/engine/BasicCameraViewEngineService.js";
import * as GameObjectComponentEngineService$WonderEditor from "../../src/service/state/engine/GameObjectComponentEngineService.js";

function _prepareSpecificGameObjectsForEditEngineState(editEngineState) {
  var scene = MainEditorSceneTool$WonderEditor.unsafeGetScene(/* () */0);
  var match = GeometryEngineService$WonderEditor.createGridPlaneGameObject(/* tuple */[
        14,
        2,
        0
      ], /* array */[
        0.9,
        0.9,
        0.9
      ], editEngineState);
  var match$1 = CameraEngineService$WonderEditor.createCameraForEditEngineState(match[0]);
  var camera = match$1[1];
  var match$2 = ArcballCameraEngineService$WonderEditor.create(match$1[0]);
  var editEngineState$1 = match$2[0];
  return GameObjectUtils$WonderEditor.addChild(scene, camera, GameObjectUtils$WonderEditor.addChild(scene, match[1], GameObjectLogicService$WonderEditor.addArcballCameraControllerForEditEngineState(camera, match$2[1], BasicCameraViewEngineService$WonderEditor.activeBasicCameraView(GameObjectComponentEngineService$WonderEditor.getBasicCameraViewComponent(camera, editEngineState$1), editEngineState$1))));
}

function _buildTwoCameraSceneGraphForEditEngineState(cubeGeometry, engineState) {
  var scene = MainEditorSceneTool$WonderEditor.unsafeGetScene(/* () */0);
  var match = CameraEngineService$WonderEditor.createCameraForEditEngineState(engineState);
  var camera1 = match[1];
  var match$1 = CameraEngineService$WonderEditor.createCameraForEditEngineState(match[0]);
  var camera2 = match$1[1];
  var match$2 = PrimitiveEngineService$WonderEditor.createBoxForEditEngineState(cubeGeometry, match$1[0]);
  var box1 = match$2[1];
  return /* tuple */[
          camera1,
          camera2,
          box1,
          GameObjectUtils$WonderEditor.addChild(scene, box1, GameObjectUtils$WonderEditor.addChild(scene, camera2, GameObjectUtils$WonderEditor.addChild(scene, camera1, match$2[0])))
        ];
}

function _buildTwoCameraSceneGraphForRunEngineState(cubeGeometry, editorState, engineState) {
  var scene = MainEditorSceneTool$WonderEditor.unsafeGetScene(/* () */0);
  var match = CameraEngineService$WonderEditor.createCameraForRunEngineState(editorState, engineState);
  var camera1 = match[2];
  var match$1 = CameraEngineService$WonderEditor.createCameraForRunEngineState(match[0], match[1]);
  var camera2 = match$1[2];
  var match$2 = PrimitiveEngineService$WonderEditor.createBoxForRunEngineState(cubeGeometry, match$1[0], match$1[1]);
  var box1 = match$2[2];
  return /* tuple */[
          camera1,
          camera2,
          box1,
          match$2[0],
          GameObjectUtils$WonderEditor.addChild(scene, box1, GameObjectUtils$WonderEditor.addChild(scene, camera2, GameObjectUtils$WonderEditor.addChild(scene, camera1, match$2[1])))
        ];
}

function buildTwoCameraSceneGraphToEngine(sandbox) {
  var editEngineState = _prepareSpecificGameObjectsForEditEngineState(StateLogicService$WonderEditor.getEditEngineState(/* () */0));
  var editorState = DefaultSceneUtils$WonderEditor.computeDiffValue(StateEditorService$WonderEditor.getState(/* () */0));
  var match = DefaultSceneUtils$WonderEditor.prepareDefaultComponentForEditEngineState(editEngineState);
  var match$1 = _buildTwoCameraSceneGraphForEditEngineState(match[1], match[0]);
  StateLogicService$WonderEditor.setEditEngineState(FakeGlToolEngine$WonderEditor.setFakeGl(FakeGlToolEngine$WonderEditor.buildFakeGl(sandbox, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, /* () */0), match$1[3]));
  var match$2 = DefaultSceneUtils$WonderEditor.prepareDefaultComponentForRunEngineState(editorState, StateLogicService$WonderEditor.getRunEngineState(/* () */0));
  var match$3 = _buildTwoCameraSceneGraphForRunEngineState(match$2[2], match$2[0], match$2[1]);
  var runEngineState = match$3[4];
  var camera2 = match$3[1];
  StateLogicService$WonderEditor.setRunEngineState(FakeGlToolEngine$WonderEditor.setFakeGl(FakeGlToolEngine$WonderEditor.buildFakeGl(sandbox, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, /* () */0), BasicCameraViewEngineService$WonderEditor.activeBasicCameraView(GameObjectComponentEngineService$WonderEditor.getBasicCameraViewComponent(camera2, runEngineState), runEngineState)));
  StateEditorService$WonderEditor.setState(match$3[3]);
  return /* tuple */[
          match$3[0],
          camera2,
          match$3[2]
        ];
}

function _buildThreeLayerSceneGraphForEditEngineState(cubeGeometry, engineState) {
  var scene = MainEditorSceneTool$WonderEditor.unsafeGetScene(/* () */0);
  var match = PrimitiveEngineService$WonderEditor.createBoxForEditEngineState(cubeGeometry, engineState);
  var box1 = match[1];
  var match$1 = PrimitiveEngineService$WonderEditor.createBoxForEditEngineState(cubeGeometry, match[0]);
  var match$2 = PrimitiveEngineService$WonderEditor.createBoxForEditEngineState(cubeGeometry, match$1[0]);
  var match$3 = PrimitiveEngineService$WonderEditor.createBoxForEditEngineState(cubeGeometry, match$2[0]);
  return GameObjectUtils$WonderEditor.addChild(scene, match$2[1], GameObjectUtils$WonderEditor.addChild(scene, match$1[1], GameObjectUtils$WonderEditor.addChild(box1, match$3[1], GameObjectUtils$WonderEditor.addChild(scene, box1, match$3[0]))));
}

function _buildThreeLayerSceneGraphForRunEngineState(cubeGeometry, editorState, engineState) {
  var scene = MainEditorSceneTool$WonderEditor.unsafeGetScene(/* () */0);
  var match = PrimitiveEngineService$WonderEditor.createBoxForRunEngineState(cubeGeometry, editorState, engineState);
  var box1 = match[2];
  var match$1 = PrimitiveEngineService$WonderEditor.createBoxForRunEngineState(cubeGeometry, match[0], match[1]);
  var match$2 = PrimitiveEngineService$WonderEditor.createBoxForRunEngineState(cubeGeometry, match$1[0], match$1[1]);
  var match$3 = PrimitiveEngineService$WonderEditor.createBoxForRunEngineState(cubeGeometry, match$2[0], match$2[1]);
  return /* tuple */[
          match$3[0],
          GameObjectUtils$WonderEditor.addChild(scene, match$2[2], GameObjectUtils$WonderEditor.addChild(scene, match$1[2], GameObjectUtils$WonderEditor.addChild(box1, match$3[2], GameObjectUtils$WonderEditor.addChild(scene, box1, match$3[1]))))
        ];
}

function buildThreeLayerSceneGraphToEngine(sandbox) {
  var editEngineState = _prepareSpecificGameObjectsForEditEngineState(StateLogicService$WonderEditor.getEditEngineState(/* () */0));
  var editorState = DefaultSceneUtils$WonderEditor.computeDiffValue(StateEditorService$WonderEditor.getState(/* () */0));
  var match = DefaultSceneUtils$WonderEditor.prepareDefaultComponentForEditEngineState(editEngineState);
  var editEngineState$1 = _buildThreeLayerSceneGraphForEditEngineState(match[1], match[0]);
  StateLogicService$WonderEditor.setEditEngineState(FakeGlToolEngine$WonderEditor.setFakeGl(FakeGlToolEngine$WonderEditor.buildFakeGl(sandbox, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, /* () */0), editEngineState$1));
  var match$1 = DefaultSceneUtils$WonderEditor.prepareDefaultComponentForRunEngineState(editorState, StateLogicService$WonderEditor.getRunEngineState(/* () */0));
  var match$2 = _buildThreeLayerSceneGraphForRunEngineState(match$1[2], match$1[0], match$1[1]);
  StateLogicService$WonderEditor.setRunEngineState(FakeGlToolEngine$WonderEditor.setFakeGl(FakeGlToolEngine$WonderEditor.buildFakeGl(sandbox, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, /* () */0), match$2[1]));
  StateEditorService$WonderEditor.setState(match$2[0]);
  return /* () */0;
}

function _buildFourLayerSceneGraphForEditEngineState(cubeGeometry, engineState) {
  var scene = MainEditorSceneTool$WonderEditor.unsafeGetScene(/* () */0);
  var match = PrimitiveEngineService$WonderEditor.createBoxForEditEngineState(cubeGeometry, engineState);
  var box1 = match[1];
  var match$1 = PrimitiveEngineService$WonderEditor.createBoxForEditEngineState(cubeGeometry, match[0]);
  var box2 = match$1[1];
  var match$2 = PrimitiveEngineService$WonderEditor.createBoxForEditEngineState(cubeGeometry, match$1[0]);
  var box3 = match$2[1];
  var match$3 = PrimitiveEngineService$WonderEditor.createBoxForEditEngineState(cubeGeometry, match$2[0]);
  var box4 = match$3[1];
  return /* tuple */[
          box1,
          box2,
          box3,
          box4,
          GameObjectUtils$WonderEditor.addChild(scene, box2, GameObjectUtils$WonderEditor.addChild(box3, box4, GameObjectUtils$WonderEditor.addChild(box1, box3, GameObjectUtils$WonderEditor.addChild(scene, box1, match$3[0]))))
        ];
}

function _buildFourLayerSceneGraphForRunEngineState(cubeGeometry, editorState, engineState) {
  var scene = MainEditorSceneTool$WonderEditor.unsafeGetScene(/* () */0);
  var match = PrimitiveEngineService$WonderEditor.createBoxForRunEngineState(cubeGeometry, editorState, engineState);
  var box1 = match[2];
  var match$1 = PrimitiveEngineService$WonderEditor.createBoxForRunEngineState(cubeGeometry, match[0], match[1]);
  var box2 = match$1[2];
  var match$2 = PrimitiveEngineService$WonderEditor.createBoxForRunEngineState(cubeGeometry, match$1[0], match$1[1]);
  var box3 = match$2[2];
  var match$3 = PrimitiveEngineService$WonderEditor.createBoxForRunEngineState(cubeGeometry, match$2[0], match$2[1]);
  var box4 = match$3[2];
  return /* tuple */[
          box1,
          box2,
          box3,
          box4,
          match$3[0],
          GameObjectUtils$WonderEditor.addChild(scene, box2, GameObjectUtils$WonderEditor.addChild(box3, box4, GameObjectUtils$WonderEditor.addChild(box1, box3, GameObjectUtils$WonderEditor.addChild(scene, box1, match$3[1]))))
        ];
}

function buildFourLayerSceneGraphToEngine(sandbox) {
  var editEngineState = _prepareSpecificGameObjectsForEditEngineState(StateLogicService$WonderEditor.getEditEngineState(/* () */0));
  var editorState = DefaultSceneUtils$WonderEditor.computeDiffValue(StateEditorService$WonderEditor.getState(/* () */0));
  var match = DefaultSceneUtils$WonderEditor.prepareDefaultComponentForEditEngineState(editEngineState);
  var match$1 = _buildFourLayerSceneGraphForEditEngineState(match[1], match[0]);
  StateLogicService$WonderEditor.setEditEngineState(FakeGlToolEngine$WonderEditor.setFakeGl(FakeGlToolEngine$WonderEditor.buildFakeGl(sandbox, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, /* () */0), match$1[4]));
  var match$2 = DefaultSceneUtils$WonderEditor.prepareDefaultComponentForRunEngineState(editorState, StateLogicService$WonderEditor.getRunEngineState(/* () */0));
  var match$3 = _buildFourLayerSceneGraphForRunEngineState(match$2[2], match$2[0], match$2[1]);
  StateLogicService$WonderEditor.setRunEngineState(FakeGlToolEngine$WonderEditor.setFakeGl(FakeGlToolEngine$WonderEditor.buildFakeGl(sandbox, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, /* () */0), match$3[5]));
  StateEditorService$WonderEditor.setState(match$3[4]);
  return /* tuple */[
          match$3[0],
          match$3[1],
          match$3[2],
          match$3[3]
        ];
}

function clearCurrentGameObjectAndSetTreeSpecificGameObject(clickTreeNodeIndex) {
  StateLogicService$WonderEditor.getAndSetEditorState(SceneEditorService$WonderEditor.clearCurrentSceneTreeNode);
  var component = BuildComponentTool$WonderEditor.buildSceneTree(TestTool$WonderEditor.buildAppStateSceneGraphFromEngine(/* () */0));
  return BaseEventTool$WonderEditor.triggerComponentEvent(component, (function (param) {
                return SceneTreeEventTool$WonderEditor.triggerClickEvent(clickTreeNodeIndex, param);
              }));
}

function buildFourLayerSceneAndGetBox(sandbox) {
  var match = buildFourLayerSceneGraphToEngine(sandbox);
  var firstLayerFirstCubeDomIndex = SceneTreeNodeDomTool$WonderEditor.OperateFourLayer[/* getFirstLayerFirstCubeDomIndex */0](/* () */0);
  clearCurrentGameObjectAndSetTreeSpecificGameObject(firstLayerFirstCubeDomIndex);
  return /* tuple */[
          match[0],
          match[1],
          match[2],
          match[3]
        ];
}

export {
  _prepareSpecificGameObjectsForEditEngineState ,
  _buildTwoCameraSceneGraphForEditEngineState ,
  _buildTwoCameraSceneGraphForRunEngineState ,
  buildTwoCameraSceneGraphToEngine ,
  _buildThreeLayerSceneGraphForEditEngineState ,
  _buildThreeLayerSceneGraphForRunEngineState ,
  buildThreeLayerSceneGraphToEngine ,
  _buildFourLayerSceneGraphForEditEngineState ,
  _buildFourLayerSceneGraphForRunEngineState ,
  buildFourLayerSceneGraphToEngine ,
  clearCurrentGameObjectAndSetTreeSpecificGameObject ,
  buildFourLayerSceneAndGetBox ,
  
}
/* TestTool-WonderEditor Not a pure module */
