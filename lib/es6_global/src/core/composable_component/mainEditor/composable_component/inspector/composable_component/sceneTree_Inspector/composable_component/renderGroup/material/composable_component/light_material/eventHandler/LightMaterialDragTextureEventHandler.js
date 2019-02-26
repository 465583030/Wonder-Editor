

import * as EventHandler$WonderEditor from "../../../../../../../../../../../../ui/eventHandler/EventHandler.js";
import * as EmptyEventHandler$WonderEditor from "../../../../../../../../../../../../ui/eventHandler/EmptyEventHandler.js";
import * as LightMaterialEngineService$WonderEditor from "../../../../../../../../../../../../../service/state/engine/LightMaterialEngineService.js";
import * as OperateTextureLogicService$WonderEditor from "../../../../../../../../../../../../../service/stateTuple/logic/OperateTextureLogicService.js";
import * as MaterialDragTextureEventHandlerUtils$WonderEditor from "../../utils/MaterialDragTextureEventHandlerUtils.js";

var setUndoValueToCopiedEngineState = EmptyEventHandler$WonderEditor.EmptyEventHandler[1];

function _handleSetMap(materialComponent, textureComponent, engineState) {
  var match = LightMaterialEngineService$WonderEditor.getLightMaterialDiffuseMap(materialComponent, engineState);
  if (match !== undefined) {
    return OperateTextureLogicService$WonderEditor.changeTextureMapAndRefreshEngineState(materialComponent, textureComponent, LightMaterialEngineService$WonderEditor.setLightMaterialDiffuseMap, engineState);
  } else {
    return OperateTextureLogicService$WonderEditor.handleMaterialComponentFromNoMapToHasMap(/* tuple */[
                materialComponent,
                textureComponent
              ], /* tuple */[
                LightMaterialEngineService$WonderEditor.setLightMaterialDiffuseMap,
                LightMaterialEngineService$WonderEditor.reInitLightMaterialsAndClearShaderCache
              ], engineState);
  }
}

function handleSelfLogic(param, materialComponent, draggedNodeId) {
  return MaterialDragTextureEventHandlerUtils$WonderEditor.handleSelfLogic(/* tuple */[
              param[0],
              param[1]
            ], materialComponent, draggedNodeId, _handleSetMap);
}

var CustomEventHandler = /* module */[
  /* setUndoValueToCopiedEngineState */setUndoValueToCopiedEngineState,
  /* _handleSetMap */_handleSetMap,
  /* handleSelfLogic */handleSelfLogic
];

var MakeEventHandler = EventHandler$WonderEditor.MakeEventHandler([
      handleSelfLogic,
      setUndoValueToCopiedEngineState
    ]);

export {
  CustomEventHandler ,
  MakeEventHandler ,
  
}
/* MakeEventHandler Not a pure module */
