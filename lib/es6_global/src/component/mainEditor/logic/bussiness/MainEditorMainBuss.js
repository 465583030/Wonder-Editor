'use strict';

import * as MainEditorMainOper$WonderEditor       from "../operator/MainEditorMainOper.js";
import * as MainEditorSceneEdit$WonderEditor      from "../edit/MainEditorSceneEdit.js";
import * as MainEditorSceneOper$WonderEditor      from "../operator/MainEditorSceneOper.js";
import * as MainEditorDirectorOper$WonderEditor   from "../operator/MainEditorDirectorOper.js";
import * as MainEditorGameObjectOper$WonderEditor from "../operator/MainEditorGameObjectOper.js";

function initEngineMain() {
  return MainEditorMainOper$WonderEditor.init("webgl", true);
}

var initEngineDirector = MainEditorDirectorOper$WonderEditor.init;

function initEditor(param) {
  var match = MainEditorGameObjectOper$WonderEditor.create(param[1]);
  var scene = match[1];
  var editorState = MainEditorSceneEdit$WonderEditor.setScene(scene, param[0]);
  var match$1 = MainEditorSceneOper$WonderEditor.createDefaultSceneGameObjects(match[0]);
  var engineState = MainEditorGameObjectOper$WonderEditor.addChild(scene, match$1[3], MainEditorGameObjectOper$WonderEditor.addChild(scene, match$1[2], MainEditorGameObjectOper$WonderEditor.addChild(scene, match$1[1], match$1[0])));
  return /* tuple */[
          editorState,
          engineState
        ];
}

var loopBody = MainEditorDirectorOper$WonderEditor.loopBody;

export {
  initEngineMain     ,
  initEngineDirector ,
  initEditor         ,
  loopBody           ,
  
}
/* MainEditorMainOper-WonderEditor Not a pure module */
