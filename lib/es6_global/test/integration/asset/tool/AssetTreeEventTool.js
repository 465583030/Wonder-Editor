

import * as ArrayService$WonderEditor from "../../../../src/service/atom/ArrayService.js";
import * as BaseEventTool$WonderEditor from "../../../tool/ui/BaseEventTool.js";

function _getFromArray(array, index) {
  return ArrayService$WonderEditor.unsafeGetNth(index, array);
}

function clickRootAssetTreeNode(domChildren) {
  var treeDiv = ArrayService$WonderEditor.unsafeGetNth(0, domChildren);
  var array = treeDiv.children;
  var treeArticle = ArrayService$WonderEditor.unsafeGetNth(1, array);
  var array$1 = treeArticle.children;
  var rootUl = ArrayService$WonderEditor.unsafeGetNth(0, array$1);
  var array$2 = rootUl.children;
  return BaseEventTool$WonderEditor.triggerClickEvent(ArrayService$WonderEditor.unsafeGetNth(0, array$2));
}

function clickAssetTreeNode(index, domChildren) {
  var treeDiv = ArrayService$WonderEditor.unsafeGetNth(0, domChildren);
  var array = treeDiv.children;
  var treeArticle = ArrayService$WonderEditor.unsafeGetNth(1, array);
  var array$1 = treeArticle.children;
  var rootUl = ArrayService$WonderEditor.unsafeGetNth(0, array$1);
  var array$2 = rootUl.children;
  var targetUl = ArrayService$WonderEditor.unsafeGetNth(index, array$2);
  var array$3 = targetUl.children;
  return BaseEventTool$WonderEditor.triggerClickEvent(ArrayService$WonderEditor.unsafeGetNth(0, array$3));
}

function clickAssetTreeChildrenNode(index, domChildren) {
  var content = ArrayService$WonderEditor.unsafeGetNth(1, domChildren);
  var array = content.children;
  return BaseEventTool$WonderEditor.triggerClickEvent(ArrayService$WonderEditor.unsafeGetNth(index, array));
}

function triggerAddFolderClick(domChildren) {
  var treeDiv = ArrayService$WonderEditor.unsafeGetNth(0, domChildren);
  var array = treeDiv.children;
  var headerArticle = ArrayService$WonderEditor.unsafeGetNth(0, array);
  var array$1 = headerArticle.children;
  var headerItem = ArrayService$WonderEditor.unsafeGetNth(0, array$1);
  var array$2 = headerItem.children;
  return BaseEventTool$WonderEditor.triggerClickEvent(ArrayService$WonderEditor.unsafeGetNth(0, array$2));
}

function triggerRemoveNodeClick(domChildren) {
  var treeDiv = ArrayService$WonderEditor.unsafeGetNth(0, domChildren);
  var array = treeDiv.children;
  var headerArticle = ArrayService$WonderEditor.unsafeGetNth(0, array);
  var array$1 = headerArticle.children;
  var headerItem = ArrayService$WonderEditor.unsafeGetNth(1, array$1);
  var array$2 = headerItem.children;
  return BaseEventTool$WonderEditor.triggerClickEvent(ArrayService$WonderEditor.unsafeGetNth(0, array$2));
}

function triggerAddMaterialClick(domChildren) {
  var treeDiv = ArrayService$WonderEditor.unsafeGetNth(0, domChildren);
  var array = treeDiv.children;
  var headerArticle = ArrayService$WonderEditor.unsafeGetNth(0, array);
  var array$1 = headerArticle.children;
  var headerItem = ArrayService$WonderEditor.unsafeGetNth(3, array$1);
  var array$2 = headerItem.children;
  return BaseEventTool$WonderEditor.triggerClickEvent(ArrayService$WonderEditor.unsafeGetNth(0, array$2));
}

export {
  _getFromArray ,
  clickRootAssetTreeNode ,
  clickAssetTreeNode ,
  clickAssetTreeChildrenNode ,
  triggerAddFolderClick ,
  triggerRemoveNodeClick ,
  triggerAddMaterialClick ,
  
}
/* ArrayService-WonderEditor Not a pure module */
