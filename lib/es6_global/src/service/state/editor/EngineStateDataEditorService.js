'use strict';

import * as EditorStateData$WonderEditor from "../data/editor/EditorStateData.js";

function getEngineStateDataForEdit() {
  return EditorStateData$WonderEditor.editorStateData[/* engineStateDataForEdit */2];
}

function getEngineStateDataForRun() {
  return EditorStateData$WonderEditor.editorStateData[/* engineStateDataForRun */3];
}

function getIsRun() {
  return EditorStateData$WonderEditor.editorStateData[/* isRun */4];
}

function setIsRun(isRun) {
  EditorStateData$WonderEditor.editorStateData[/* isRun */4] = isRun;
  return /* () */0;
}

export {
  getEngineStateDataForEdit ,
  getEngineStateDataForRun  ,
  getIsRun                  ,
  setIsRun                  ,
  
}
/* EditorStateData-WonderEditor Not a pure module */
