

import * as Curry from "../../../../../../node_modules/bs-platform/lib/es6/curry.js";
import * as Caml_obj from "../../../../../../node_modules/bs-platform/lib/es6/caml_obj.js";
import * as Js_primitive from "../../../../../../node_modules/bs-platform/lib/es6/js_primitive.js";
import * as ImageUtils$WonderEditor from "../header/utils/ImageUtils.js";
import * as SparseMapService$WonderEditor from "../../../service/atom/SparseMapService.js";
import * as Uint8ArrayService$WonderEditor from "../../../service/primitive/Uint8ArrayService.js";
import * as SparseMapService$WonderCommonlib from "../../../../../../node_modules/wonder-commonlib/lib/es6_global/src/SparseMapService.js";
import * as ConverterEngineService$WonderEditor from "../../../service/state/engine/ConverterEngineService.js";
import * as AllMaterialEngineService$WonderEditor from "../../../service/state/engine/AllMaterialEngineService.js";
import * as LightMaterialEngineService$WonderEditor from "../../../service/state/engine/LightMaterialEngineService.js";
import * as RelateGameObjectAndAssetUtils$WonderEditor from "./RelateGameObjectAndAssetUtils.js";
import * as ImageNodeMapAssetEditorService$WonderEditor from "../../../service/state/editor/asset/ImageNodeMapAssetEditorService.js";
import * as BasicSourceTextureEngineService$WonderEditor from "../../../service/state/engine/BasicSourceTextureEngineService.js";
import * as GameObjectComponentEngineService$WonderEditor from "../../../service/state/engine/GameObjectComponentEngineService.js";
import * as TextureNodeMapAssetEditorService$WonderEditor from "../../../service/state/editor/asset/TextureNodeMapAssetEditorService.js";

function _isTextureNameEqual(name1, texture2, engineState) {
  return RelateGameObjectAndAssetUtils$WonderEditor.isNameEqual(name1, texture2, /* tuple */[
              BasicSourceTextureEngineService$WonderEditor.getBasicSourceTextureName,
              ConverterEngineService$WonderEditor.isDefaultTextureName
            ], engineState);
}

function isImageNameEqual(name1, image2) {
  var name2 = ImageUtils$WonderEditor.getImageName(image2);
  var match = ConverterEngineService$WonderEditor.isDefaultImageName(name1) && ConverterEngineService$WonderEditor.isDefaultImageName(name2);
  if (match) {
    return true;
  } else {
    return name1 === name2;
  }
}

function _isImageValueEqual(image1, image2, getFunc) {
  return Caml_obj.caml_equal(Curry._1(getFunc, image1), Curry._1(getFunc, image2));
}

function isImageDataEqual(param, image2, texture2, imageUint8ArrayDataMap) {
  if (isImageNameEqual(param[0], image2) && Caml_obj.caml_equal(param[1], ImageUtils$WonderEditor.getImageWidth(image2)) && Caml_obj.caml_equal(param[2], ImageUtils$WonderEditor.getImageHeight(image2))) {
    var match = SparseMapService$WonderCommonlib.get(texture2, imageUint8ArrayDataMap);
    if (match !== undefined) {
      return Uint8ArrayService$WonderEditor.isUint8ArrayEqual(param[3], Js_primitive.some(match[1]));
    } else {
      return true;
    }
  } else {
    return false;
  }
}

function isTextureDataEqual(isImageDataEqualFunc, param, texture2, imageUint8ArrayDataMap, engineState) {
  if (_isTextureNameEqual(param[0], texture2, engineState) && param[1] === BasicSourceTextureEngineService$WonderEditor.getWrapS(texture2, engineState) && param[2] === BasicSourceTextureEngineService$WonderEditor.getWrapT(texture2, engineState) && param[3] === BasicSourceTextureEngineService$WonderEditor.getMinFilter(texture2, engineState) && param[4] === BasicSourceTextureEngineService$WonderEditor.getMagFilter(texture2, engineState)) {
    return Curry._4(isImageDataEqualFunc, param[5], BasicSourceTextureEngineService$WonderEditor.unsafeGetSource(texture2, engineState), texture2, imageUint8ArrayDataMap);
  } else {
    return false;
  }
}

function _findTextureAsset(textureAssetDataMap, sourceTexture, imageUint8ArrayDataMap, engineState) {
  var match = SparseMapService$WonderEditor.find((function (param) {
          return isTextureDataEqual(isImageDataEqual, param[1], sourceTexture, imageUint8ArrayDataMap, engineState);
        }), textureAssetDataMap);
  if (match !== undefined) {
    return Js_primitive.some(match[0]);
  }
  
}

function getRelatedTextureData(gameObject, replacedTargetTextureMap, textureAssetDataMap, imageUint8ArrayDataMap, param, param$1) {
  var engineState = param$1[1];
  var material = Curry._2(param[0], gameObject, engineState);
  var match = Curry._2(param[1], material, engineState);
  if (match !== undefined) {
    var sourceTexture = match;
    var match$1 = SparseMapService$WonderCommonlib.get(sourceTexture, replacedTargetTextureMap);
    var match$2;
    if (match$1 !== undefined) {
      match$2 = /* tuple */[
        Js_primitive.valFromOption(match$1),
        replacedTargetTextureMap
      ];
    } else {
      var targetTexture = _findTextureAsset(textureAssetDataMap, sourceTexture, imageUint8ArrayDataMap, engineState);
      match$2 = /* tuple */[
        targetTexture,
        SparseMapService$WonderCommonlib.set(sourceTexture, targetTexture, replacedTargetTextureMap)
      ];
    }
    return /* tuple */[
            sourceTexture,
            match$2[0],
            Js_primitive.some(param[2]),
            match$2[1]
          ];
  } else {
    return /* tuple */[
            undefined,
            undefined,
            undefined,
            replacedTargetTextureMap
          ];
  }
}

function doesNeedReplaceTexture(param) {
  if (param[0] !== undefined) {
    return param[1] !== undefined;
  } else {
    return false;
  }
}

function getRelatedTextureDataFromGameObject(gameObject, replacedTargetTextureMap, textureAssetDataMap, imageUint8ArrayDataMap, param) {
  var engineState = param[1];
  var match = GameObjectComponentEngineService$WonderEditor.hasBasicMaterialComponent(gameObject, engineState);
  if (match) {
    return /* tuple */[
            undefined,
            undefined,
            undefined,
            replacedTargetTextureMap
          ];
  } else {
    var match$1 = GameObjectComponentEngineService$WonderEditor.hasLightMaterialComponent(gameObject, engineState);
    if (match$1) {
      return getRelatedTextureData(gameObject, replacedTargetTextureMap, textureAssetDataMap, imageUint8ArrayDataMap, /* tuple */[
                  GameObjectComponentEngineService$WonderEditor.unsafeGetLightMaterialComponent,
                  LightMaterialEngineService$WonderEditor.getLightMaterialDiffuseMap,
                  LightMaterialEngineService$WonderEditor.setLightMaterialDiffuseMap
                ], /* tuple */[
                  param[0],
                  engineState
                ]);
    } else {
      return /* tuple */[
              undefined,
              undefined,
              undefined,
              replacedTargetTextureMap
            ];
    }
  }
}

function replaceToTextureAssetTextureComponent(gameObject, param, param$1) {
  var engineState = param$1[1];
  var setMapFunc = param[1];
  var targetTexture = param[0];
  if (targetTexture !== undefined && setMapFunc !== undefined) {
    var match = AllMaterialEngineService$WonderEditor.getMaterialComponent(gameObject, /* tuple */[
          param$1[0],
          engineState
        ]);
    if (match !== undefined) {
      return Curry._3(setMapFunc, Js_primitive.valFromOption(targetTexture), match, engineState);
    } else {
      return engineState;
    }
  } else {
    return engineState;
  }
}

function _getImageUint8ArrayByTextureComponent(textureComponent, editorState) {
  var match = TextureNodeMapAssetEditorService$WonderEditor.getResultByTextureComponent(textureComponent, editorState);
  if (match !== undefined) {
    return ImageNodeMapAssetEditorService$WonderEditor.getUint8Array(match[/* image */1], ImageNodeMapAssetEditorService$WonderEditor.getImageNodeMap(editorState));
  }
  
}

function _getImageData(image, texture, editorState) {
  return /* tuple */[
          ImageUtils$WonderEditor.getImageName(image),
          ImageUtils$WonderEditor.getImageWidth(image),
          ImageUtils$WonderEditor.getImageHeight(image),
          _getImageUint8ArrayByTextureComponent(texture, editorState)
        ];
}

function getTextureData(texture, param) {
  var engineState = param[1];
  return /* tuple */[
          BasicSourceTextureEngineService$WonderEditor.getBasicSourceTextureName(texture, engineState),
          BasicSourceTextureEngineService$WonderEditor.getWrapS(texture, engineState),
          BasicSourceTextureEngineService$WonderEditor.getWrapT(texture, engineState),
          BasicSourceTextureEngineService$WonderEditor.getMinFilter(texture, engineState),
          BasicSourceTextureEngineService$WonderEditor.getMagFilter(texture, engineState),
          _getImageData(BasicSourceTextureEngineService$WonderEditor.unsafeGetSource(texture, engineState), texture, param[0])
        ];
}

export {
  _isTextureNameEqual ,
  isImageNameEqual ,
  _isImageValueEqual ,
  isImageDataEqual ,
  isTextureDataEqual ,
  _findTextureAsset ,
  getRelatedTextureData ,
  doesNeedReplaceTexture ,
  getRelatedTextureDataFromGameObject ,
  replaceToTextureAssetTextureComponent ,
  _getImageUint8ArrayByTextureComponent ,
  _getImageData ,
  getTextureData ,
  
}
/* ImageUtils-WonderEditor Not a pure module */
