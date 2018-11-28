

import * as Curry from "../../../../../../../../../node_modules/bs-platform/lib/es6/curry.js";
import * as TestTool$WonderEditor from "../../../../../../tool/TestTool.js";
import * as GameObjectTool$WonderEditor from "../../../../../../tool/GameObjectTool.js";
import * as MainEditorGeometry$WonderEditor from "../../../../../../../src/core/composable_component/mainEditor/composable_component/inspector/composable_component/sceneTree_Inspector/composable_component/geometry/ui/MainEditorGeometry.js";
import * as StateEditorService$WonderEditor from "../../../../../../../src/service/state/editor/StateEditorService.js";
import * as PrepareDefaultComponentUtils$WonderEditor from "../../../../../../../src/core/utils/engine/PrepareDefaultComponentUtils.js";
import * as GeometryDataAssetEditorService$WonderEditor from "../../../../../../../src/service/state/editor/asset/GeometryDataAssetEditorService.js";

function getBoxTexturedGeometryName() {
  return "Mesh";
}

function getDefaultCubeGeometryComponent($staropt$star, _) {
  var editorState = $staropt$star !== undefined ? $staropt$star : StateEditorService$WonderEditor.getState(/* () */0);
  return GeometryDataAssetEditorService$WonderEditor.getGeometryData(editorState)[/* defaultCubeGeometryComponent */0];
}

function getDefaultSphereGeometryComponent($staropt$star, _) {
  var editorState = $staropt$star !== undefined ? $staropt$star : StateEditorService$WonderEditor.getState(/* () */0);
  return GeometryDataAssetEditorService$WonderEditor.getGeometryData(editorState)[/* defaultSphereGeometryComponent */1];
}

function changeGeometry(sourceGeometry, targetGeometry, $staropt$star, $staropt$star$1, $staropt$star$2, _) {
  var gameObject = $staropt$star !== undefined ? $staropt$star : GameObjectTool$WonderEditor.unsafeGetCurrentSceneTreeNode(/* () */0);
  var store = $staropt$star$1 !== undefined ? $staropt$star$1 : TestTool$WonderEditor.buildEmptyAppState(/* () */0);
  var dispatchFunc = $staropt$star$2 !== undefined ? $staropt$star$2 : TestTool$WonderEditor.getDispatch(/* () */0);
  return Curry._3(MainEditorGeometry$WonderEditor.Method[/* changeGeometry */0], /* tuple */[
              store,
              dispatchFunc
            ], gameObject, /* tuple */[
              sourceGeometry,
              targetGeometry
            ]);
}

function getAllShowGeometrys(gameObject, engineState) {
  return MainEditorGeometry$WonderEditor.Method[/* _getAllShowGeometrys */4](gameObject, engineState);
}

var getDefaultCubeGeometryName = PrepareDefaultComponentUtils$WonderEditor.getDefaultCubeGeometryName;

var getDefaultSphereGeometryName = PrepareDefaultComponentUtils$WonderEditor.getDefaultSphereGeometryName;

export {
  getDefaultCubeGeometryName ,
  getDefaultSphereGeometryName ,
  getBoxTexturedGeometryName ,
  getDefaultCubeGeometryComponent ,
  getDefaultSphereGeometryComponent ,
  changeGeometry ,
  getAllShowGeometrys ,
  
}
/* TestTool-WonderEditor Not a pure module */
