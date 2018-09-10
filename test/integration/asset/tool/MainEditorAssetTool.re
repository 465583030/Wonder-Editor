open AssetTreeNodeType;

open AssetTreeTwoLayerTypeTool;

open AssetTreeThreeLayerTypeTool;

open AssetNodeType;

let buildFakeFileReader = [%bs.raw
  {|
     function (){
       window.FileReader = function(){
         this.result = null;
         this.onload = null;
         this.readAsDataURL = function(file) {
            this.result = file.file;
            this.onload();
         };
         this.readAsText = function(file) {
            this.result = file.file;
            this.onload();
         };
         this.readAsArrayBuffer = function(file) {
            this.result = file.file;
            this.onload();
         };
       }
     }
|}
];

let buildFakeImage = [%bs.raw
  {|
     function (){
       window.Image = function(){
         this.src = null;
         this.onload = null;
         this.complete = true;
       }
     }
|}
];

let _buildJsonResult = parentId => {
  name: "newJson",
  postfix: ".json",
  parentId,
  jsonResult: "json result",
};
let _buildImageObj = src =>
  {"src": src, "getAttribute": prop => src} |> Obj.magic;

let addJsonIntoNodeMap = (index, parentId, editorState) =>
  editorState
  |> AssetJsonNodeMapEditorService.setResult(
       index,
       _buildJsonResult(parentId |. Some),
     );

let addTextureIntoNodeMap = (index, parentId, textureName, editorState) => {
  let (texture, editEngineState, runEngineState) =
    TextureUtils.createAndInitTexture(
      textureName,
      StateLogicService.getEditEngineState(),
      StateLogicService.getRunEngineState(),
    );
  let imageSrc = textureName ++ "img";

  editEngineState
  |> BasicSourceTextureEngineService.setSource(
       _buildImageObj(imageSrc)
       |> ImageType.convertImgToHtmlImage
       |> Obj.magic,
       texture,
     )
  |> StateLogicService.setEditEngineState;

  runEngineState
  |> BasicSourceTextureEngineService.setSource(
       _buildImageObj(imageSrc)
       |> ImageType.convertImgToHtmlImage
       |> Obj.magic,
       texture,
     )
  |> StateLogicService.setRunEngineState;

  editorState
  |> AssetImageBase64MapEditorService.setResult(texture, imageSrc)
  |> AssetTextureNodeMapEditorService.setResult(
       index,
       AssetTextureNodeMapEditorService.buildTextureNodeResult(
         ".tex",
         texture,
         parentId |. Some,
       ),
     );
};

let _increaseIndex = editorState => {
  let editorState = AssetIndexEditorService.increaseIndex(editorState);
  let index = editorState |> AssetIndexEditorService.getIndex;
  (index, editorState);
};

let buildTwoLayerAssetTreeRoot = () => {
  let (rootId, editorState) = StateEditorService.getState() |> _increaseIndex;
  let (id1, editorState) = editorState |> _increaseIndex;
  let (id2, editorState) = editorState |> _increaseIndex;
  let (id3, editorState) = editorState |> _increaseIndex;
  let (id4, editorState) = editorState |> _increaseIndex;
  let (id5, editorState) = editorState |> _increaseIndex;

  editorState
  |> AssetTreeRootEditorService.setAssetTreeRoot({
       id: rootId,
       type_: Folder,
       children: [||],
     })
  |> AssetTreeNodeUtils.addFolderIntoNodeMap(rootId, None)
  |> AssetTreeNodeUtils.addFolderIntoNodeMap(id1, rootId |. Some)
  |> AssetTreeRootEditorService.setAssetTreeRoot({
       id: rootId,
       type_: Folder,
       children: [|{id: id1, type_: Folder, children: [||]}|],
     })
  |> AssetTreeNodeUtils.addFolderIntoNodeMap(id2, rootId |. Some)
  |> AssetTreeRootEditorService.setAssetTreeRoot({
       id: rootId,
       type_: Folder,
       children: [|
         {id: id1, type_: Folder, children: [||]},
         {id: id2, type_: Folder, children: [||]},
       |],
     })
  |> addTextureIntoNodeMap(id3, rootId, "texture3")
  |> addJsonIntoNodeMap(id4, rootId)
  |> addTextureIntoNodeMap(id5, rootId, "texture5")
  |> AssetTreeRootEditorService.setAssetTreeRoot({
       id: rootId,
       type_: Folder,
       children: [|
         {id: id1, type_: Folder, children: [||]},
         {id: id2, type_: Folder, children: [||]},
         {id: id3, type_: Texture, children: [||]},
         {id: id4, type_: Json, children: [||]},
         {id: id5, type_: Texture, children: [||]},
       |],
     })
  |> StateEditorService.setState
  |> ignore;

  {
    root: 0,
    firstLayer: {
      length: 4,
      folderDomIndexArr: [|1, 2|],
      jsonDomIndexArr: [|4|],
      textureData: {
        domIndexArr: [|3, 5|],
        lastIndex: 1,
      },
    },
    treeNodeIdData: {
      folderNodeIdArr: [|rootId, id1, id2|],
      jsonNodeIdArr: [|id4|],
      textureNodeIdArr: [|id3, id5|],
    },
  };
};
let buildTwoLayerAssetTreeRootTest = () => {
  let (rootId, editorState) = StateEditorService.getState() |> _increaseIndex;
  let (id1, editorState) = editorState |> _increaseIndex;
  let (id2, editorState) = editorState |> _increaseIndex;
  let (id3, editorState) = editorState |> _increaseIndex;
  let (id4, editorState) = editorState |> _increaseIndex;
  let (id5, editorState) = editorState |> _increaseIndex;

  editorState
  |> AssetTreeRootEditorService.setAssetTreeRoot({
       id: rootId,
       type_: Folder,
       children: [||],
     })
  |> AssetTreeNodeUtils.addFolderIntoNodeMap(rootId, None)
  |> AssetTreeNodeUtils.addFolderIntoNodeMap(id1, rootId |. Some)
  |> AssetTreeRootEditorService.setAssetTreeRoot({
       id: rootId,
       type_: Folder,
       children: [|{id: id1, type_: Folder, children: [||]}|],
     })
  |> AssetTreeNodeUtils.addFolderIntoNodeMap(id2, rootId |. Some)
  |> AssetTreeRootEditorService.setAssetTreeRoot({
       id: rootId,
       type_: Folder,
       children: [|
         {id: id1, type_: Folder, children: [||]},
         {id: id2, type_: Folder, children: [||]},
       |],
     })
  |> addTextureIntoNodeMap(id3, rootId, "texture3")
  |> addJsonIntoNodeMap(id4, rootId)
  |> addTextureIntoNodeMap(id5, id2, "texture5")
  |> AssetTreeRootEditorService.setAssetTreeRoot({
       id: rootId,
       type_: Folder,
       children: [|
         {id: id1, type_: Folder, children: [||]},
         {
           id: id2,
           type_: Folder,
           children: [|{id: id5, type_: Texture, children: [||]}|],
         },
         {id: id3, type_: Texture, children: [||]},
         {id: id4, type_: Json, children: [||]},
       |],
     })
  |> StateEditorService.setState
  |> ignore;

  {
    root: 0,
    firstLayer: {
      length: 4,
      folderDomIndexArr: [|1, 2|],
      jsonDomIndexArr: [|4|],
      textureData: {
        domIndexArr: [|3, 5|],
        lastIndex: 1,
      },
    },
    treeNodeIdData: {
      folderNodeIdArr: [|rootId, id1, id2|],
      jsonNodeIdArr: [|id4|],
      textureNodeIdArr: [|id3, id5|],
    },
  };
};

let buildThreeLayerAssetTreeRoot = () : assetTreeThreeLayerType => {
  let (rootId, editorState) = StateEditorService.getState() |> _increaseIndex;
  let (id1, editorState) = editorState |> _increaseIndex;
  let (id2, editorState) = editorState |> _increaseIndex;
  let (id3, editorState) = editorState |> _increaseIndex;
  let (id4, editorState) = editorState |> _increaseIndex;
  let (id5, editorState) = editorState |> _increaseIndex;
  let (id6, editorState) = editorState |> _increaseIndex;
  editorState
  |> AssetTreeRootEditorService.setAssetTreeRoot({
       id: rootId,
       type_: Folder,
       children: [|
         {id: id1, type_: Folder, children: [||]},
         {
           id: id2,
           type_: Folder,
           children: [|
             {id: id3, type_: Folder, children: [||]},
             {id: id4, type_: Folder, children: [||]},
             {id: id5, type_: Texture, children: [||]},
             {id: id6, type_: Json, children: [||]},
           |],
         },
       |],
     })
  |> AssetTreeNodeUtils.addFolderIntoNodeMap(rootId, None)
  |> AssetTreeNodeUtils.addFolderIntoNodeMap(id1, rootId |. Some)
  |> AssetTreeNodeUtils.addFolderIntoNodeMap(id2, rootId |. Some)
  |> AssetTreeNodeUtils.addFolderIntoNodeMap(id3, id2 |. Some)
  |> AssetTreeNodeUtils.addFolderIntoNodeMap(id4, id2 |. Some)
  |> addTextureIntoNodeMap(id5, id2, "texture5")
  |> addJsonIntoNodeMap(id6, id2)
  |> StateEditorService.setState
  |> ignore;

  {
    root: 0,
    firstLayer: {
      length: 1,
      folderDomIndexArr: [|1, 2|],
      jsonDomIndexArr: [||],
      textureData: {
        domIndexArr: [||],
        lastIndex: 0,
      },
    },
    secondLayer: {
      layerRoot: 2,
      length: 3,
      folderDomIndexArr: [|1, 2|],
      jsonDomIndexArr: [|4|],
      textureData: {
        domIndexArr: [|3|],
        lastIndex: 0,
      },
    },
    treeNodeIdData: {
      folderNodeIdArr: [|rootId, id1, id2, id3, id4|],
      jsonNodeIdArr: [|id6|],
      textureNodeIdArr: [|id5|],
    },
  };
};

/* TODO not need init assettree */
let initAssetTree = () =>
  (
    editorState => {
      let (asseTreeRoot, editorState) =
        editorState |> AssetTreeNodeUtils.initRootAssetTree;
      editorState |> AssetTreeRootEditorService.setAssetTreeRoot(asseTreeRoot);
    }
  )
  |> StateLogicService.getAndSetEditorState;

let clickAssetChildrenNodeToSetCurrentNode = index => {
  let component = BuildComponentTool.buildAssetComponent();

  BaseEventTool.triggerComponentEvent(
    component,
    AssetTreeEventTool.clickAssetTreeChildrenNode(index),
  );
};

let clickAssetTreeNodeToSetCurrentNode = (component, index) =>
  BaseEventTool.triggerComponentEvent(
    component,
    AssetTreeEventTool.clickAssetTreeNode(index),
  );

let fileLoad = AssetHeaderUtils.fileLoad;