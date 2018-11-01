open Wonder_jest;

open AssetTreeTwoLayerTypeTool;

open Expect;

open Expect.Operators;

open Sinon;

open AssetTreeNodeType;

open Js.Promise;

let _ =
  describe("MainEditorAssetHeader->load wdb", () => {
    let sandbox = getSandboxDefaultVal();

    let boxTexturedWDBArrayBuffer = ref(Obj.magic(1));
    let sceneWDBArrayBuffer = ref(Obj.magic(1));

    beforeAll(() => {
      boxTexturedWDBArrayBuffer := WDBTool.convertGLBToWDB("BoxTextured");
      sceneWDBArrayBuffer := WDBTool.generateSceneWDB();
    });

    beforeEach(() => {
      sandbox := createSandbox();

      MainEditorSceneTool.initState(~sandbox, ());
      MainEditorSceneTool.createDefaultScene(
        sandbox,
        MainEditorAssetTool.initAssetTree,
      );
    });

    afterEach(() => restoreSandbox(refJsObjToSandbox(sandbox^)));

    describe("test load file", () => {
      beforeEach(() => {
        MainEditorAssetTool.buildFakeFileReader();

        LoadTool.buildFakeTextDecoder(LoadTool.convertUint8ArrayToBuffer);
        LoadTool.buildFakeURL(sandbox^);

        LoadTool.buildFakeLoadImage(.);
      });

      testPromise("should not active wdb->camera", () => {
        let engineState = StateEngineService.unsafeGetState();
        let currentCameraGameObject =
          MainEditorCameraTool.getCurrentCameraGameObject(engineState);

        GameViewEditorService.removeActivedBasicCameraView
        |> StateLogicService.getAndSetEditorState;

        let fileName = "Scene";

        MainEditorAssetUploadTool.loadOneWDB(
          ~fileName,
          ~arrayBuffer=sceneWDBArrayBuffer^,
          (),
        )
        |> then_(uploadedWDBNodeId => {
             let engineState = StateEngineService.unsafeGetState();
             let editorState = StateEditorService.getState();

             (
               GameViewEditorService.getActivedBasicCameraView(editorState),
               MainEditorCameraTool.getCurrentCameraGameObject(engineState),
             )
             |> expect == (None, currentCameraGameObject)
             |> resolve;
           });
      });
      testPromise(
        "test the wdb gameObject and it's children isRender should be false",
        () => {
        let fileName = "BoxTextured";

        MainEditorAssetUploadTool.loadOneWDB(
          ~fileName,
          ~arrayBuffer=boxTexturedWDBArrayBuffer^,
          (),
        )
        |> then_(uploadedWDBNodeId => {
             let editorState = StateEditorService.getState();
             let wdbGameObject =
               MainEditorAssetWDBNodeTool.getWDBGameObject(
                 uploadedWDBNodeId,
                 editorState,
               );

             GameObjectMeshRendererTool.getAllGameObjectMeshRendererComponent(
               wdbGameObject,
             )
             |> StateLogicService.getEngineStateToGetData
             |> Js.Array.map(meshRender =>
                  MeshRendererEngineService.getMeshRendererIsRender(
                    meshRender,
                  )
                  |> StateLogicService.getEngineStateToGetData
                )
             |> Js.Array.filter(isRender => isRender)
             |> Js.Array.length
             |> expect == 0
             |> resolve;
           });
      });

      describe("extract assets from loaded wdb asset", () => {
        beforeEach(() =>
          MainEditorAssetTreeTool.BuildAssetTree.buildEmptyAssetTree()
          |> ignore
        );

        describe("extract material assets", () => {
          describe("test asset tree", () => {
            describe(
              {j|should add "Materials" folder node and add material node into it|j},
              () => {
              testPromise("test load the same wdb once", () =>
                MainEditorAssetUploadTool.loadOneWDB(
                  ~arrayBuffer=boxTexturedWDBArrayBuffer^,
                  (),
                )
                |> then_(uploadedWDBNodeId => {
                     let editorState = StateEditorService.getState();

                     MainEditorAssetTreeTool.Select.selectFolderNode(
                       ~nodeId=
                         MainEditorAssetFolderNodeTool.getNodeIdByName(
                           "Materials",
                           editorState,
                         )
                         |> OptionService.unsafeGet,
                       (),
                     );

                     BuildComponentTool.buildAssetChildrenNode()
                     |> ReactTestTool.createSnapshotAndMatch
                     |> resolve;
                   })
              );
              testPromise("test load the same wdb twice", () =>
                MainEditorAssetUploadTool.loadOneWDB(
                  ~arrayBuffer=boxTexturedWDBArrayBuffer^,
                  (),
                )
                |> then_(uploadedWDBNodeId1 =>
                     MainEditorAssetUploadTool.loadOneWDB(
                       ~arrayBuffer=boxTexturedWDBArrayBuffer^,
                       (),
                     )
                     |> then_(uploadedWDBNodeId2 => {
                          let editorState = StateEditorService.getState();

                          MainEditorAssetTreeTool.Select.selectFolderNode(
                            ~nodeId=
                              MainEditorAssetFolderNodeTool.getNodeIdByName(
                                "Materials",
                                editorState,
                              )
                              |> OptionService.unsafeGet,
                            (),
                          );

                          BuildComponentTool.buildAssetChildrenNode()
                          |> ReactTestTool.createSnapshotAndMatch
                          |> resolve;
                        })
                   )
              );
            });

            testPromise("material asset should has unique name", () => {
              EventListenerTool.buildFakeDom()
              |> EventListenerTool.stubGetElementByIdReturnFakeDom;

              let addedFolderNodeId = MainEditorAssetIdTool.getNewAssetId();

              MainEditorAssetHeaderOperateNodeTool.addFolder();

              MainEditorAssetFolderNodeTool.setFolderName(
                addedFolderNodeId,
                "Materials",
              )
              |> StateLogicService.getAndSetEditorState;

              MainEditorAssetTreeTool.Select.selectFolderNode(
                ~nodeId=addedFolderNodeId,
                (),
              );

              let addedMaterialNodeId = addedFolderNodeId |> succ;

              MainEditorAssetHeaderOperateNodeTool.addMaterial();

              AssetTreeInspectorTool.Rename.renameAssetMaterialNode(
                ~nodeId=addedMaterialNodeId,
                ~name=LoadWDBTool.getBoxTexturedMeshGameObjectMaterialName(),
                (),
              );

              MainEditorAssetUploadTool.loadOneWDB(
                ~arrayBuffer=boxTexturedWDBArrayBuffer^,
                (),
              )
              |> then_(uploadedWDBNodeId1 => {
                   let editorState = StateEditorService.getState();

                   MainEditorAssetTreeTool.Select.selectFolderNode(
                     ~nodeId=addedFolderNodeId,
                     (),
                   );

                   BuildComponentTool.buildAssetChildrenNode()
                   |> ReactTestTool.createSnapshotAndMatch
                   |> resolve;
                 });
            });
          });

          describe("test wdb asset->wdb gameObject->material", () => {
            testPromise(
              "wdb gameObject should use extraced material asset->materialComponent",
              () =>
              MainEditorAssetUploadTool.loadOneWDB(
                ~arrayBuffer=boxTexturedWDBArrayBuffer^,
                (),
              )
              |> then_(uploadedWDBNodeId => {
                   let engineState = StateEngineService.unsafeGetState();
                   let editorState = StateEditorService.getState();

                   let boxTexturedMeshGameObject =
                     LoadWDBTool.getBoxTexturedMeshGameObjectFromAssetNode(
                       uploadedWDBNodeId,
                       editorState,
                     );
                   let material =
                     boxTexturedMeshGameObject
                     |> GameObjectComponentEngineService.unsafeGetLightMaterialComponent(
                          _,
                          engineState,
                        );

                   MainEditorAssetMaterialNodeTool.hasMaterialComponent(
                     material,
                     LoadWDBTool.getBoxTexturedMeshGameObjectMaterialType(),
                     editorState,
                   )
                   |> expect == true
                   |> resolve;
                 })
            );
            testPromise(
              "if already has equaled material asset, wdb gameObject should use it",
              () =>
              MainEditorAssetUploadTool.loadOneWDB(
                ~arrayBuffer=boxTexturedWDBArrayBuffer^,
                (),
              )
              |> then_(uploadedWDBNodeId1 =>
                   MainEditorAssetUploadTool.loadOneWDB(
                     ~arrayBuffer=boxTexturedWDBArrayBuffer^,
                     (),
                   )
                   |> then_(uploadedWDBNodeId2 => {
                        let engineState = StateEngineService.unsafeGetState();
                        let editorState = StateEditorService.getState();

                        let boxTexturedMeshGameObject1 =
                          LoadWDBTool.getBoxTexturedMeshGameObjectFromAssetNode(
                            uploadedWDBNodeId1,
                            editorState,
                          );
                        let material1 =
                          boxTexturedMeshGameObject1
                          |> GameObjectComponentEngineService.unsafeGetLightMaterialComponent(
                               _,
                               engineState,
                             );

                        let boxTexturedMeshGameObject2 =
                          LoadWDBTool.getBoxTexturedMeshGameObjectFromAssetNode(
                            uploadedWDBNodeId2,
                            editorState,
                          );
                        let material2 =
                          boxTexturedMeshGameObject2
                          |> GameObjectComponentEngineService.unsafeGetLightMaterialComponent(
                               _,
                               engineState,
                             );

                        (
                          MainEditorAssetMaterialNodeTool.hasMaterialComponent(
                            material1,
                            LoadWDBTool.getBoxTexturedMeshGameObjectMaterialType(),
                            editorState,
                          ),
                          MainEditorAssetMaterialNodeTool.hasMaterialComponent(
                            material2,
                            LoadWDBTool.getBoxTexturedMeshGameObjectMaterialType(),
                            editorState,
                          ),
                          AssetMaterialNodeMapEditorService.getValidValues(
                            editorState,
                          )
                          |> SparseMapService.length,
                        )
                        |> expect == (true, true, 1)
                        |> resolve;
                      })
                 )
            );
          });

          describe("fix bug", () => {
            let wdbArrayBuffer = ref(Obj.magic(1));

            let _generateShareMaterialWDB = () =>
              WDBTool.generateWDB((editorState, engineState) => {
                let (engineState, geometry) =
                  GeometryEngineService.createCubeGeometry(engineState);
                let (engineState, lightMaterial) =
                  LightMaterialEngineService.create(engineState);

                let (editorState, engineState, box1) =
                  PrimitiveEngineService.createBox(
                    (geometry, lightMaterial),
                    editorState,
                    engineState,
                  );

                let (editorState, engineState, box2) =
                  PrimitiveEngineService.createBox(
                    (geometry, lightMaterial),
                    editorState,
                    engineState,
                  );

                let (engineState, rootGameObject) =
                  GameObjectEngineService.create(engineState);

                let engineState =
                  engineState
                  |> GameObjectUtils.addChild(rootGameObject, box1)
                  |> GameObjectUtils.addChild(rootGameObject, box2);

                (rootGameObject, (editorState, engineState));
              });

            beforeAll(() => wdbArrayBuffer := _generateShareMaterialWDB());

            testPromise(
              "if wdb gameObjects share the same material, should only extrace the shared material once",
              () =>
              MainEditorAssetUploadTool.loadOneWDB(
                ~arrayBuffer=wdbArrayBuffer^,
                (),
              )
              |> then_(uploadedWDBNodeId => {
                   let editorState = StateEditorService.getState();

                   MainEditorAssetTreeTool.Select.selectFolderNode(
                     ~nodeId=
                       MainEditorAssetFolderNodeTool.getNodeIdByName(
                         "Materials",
                         editorState,
                       )
                       |> OptionService.unsafeGet,
                     (),
                   );

                   BuildComponentTool.buildAssetChildrenNode()
                   |> ReactTestTool.createSnapshotAndMatch
                   |> resolve;
                 })
            );
          });
        });

        describe("extract texture assets", () => {
          describe("test asset tree", () => {
            describe(
              {j|should add "Textures" folder node and add texture node into it|j},
              () => {
              testPromise("test load the same wdb once", () =>
                MainEditorAssetUploadTool.loadOneWDB(
                  ~arrayBuffer=boxTexturedWDBArrayBuffer^,
                  (),
                )
                |> then_(uploadedWDBNodeId => {
                     let editorState = StateEditorService.getState();

                     MainEditorAssetTreeTool.Select.selectFolderNode(
                       ~nodeId=
                         MainEditorAssetFolderNodeTool.getNodeIdByName(
                           "Textures",
                           editorState,
                         )
                         |> OptionService.unsafeGet,
                       (),
                     );

                     BuildComponentTool.buildAssetChildrenNode()
                     |> ReactTestTool.createSnapshotAndMatch
                     |> resolve;
                   })
              );
              testPromise("test load the same wdb twice", () =>
                MainEditorAssetUploadTool.loadOneWDB(
                  ~arrayBuffer=boxTexturedWDBArrayBuffer^,
                  (),
                )
                |> then_(uploadedWDBNodeId1 =>
                     MainEditorAssetUploadTool.loadOneWDB(
                       ~arrayBuffer=boxTexturedWDBArrayBuffer^,
                       (),
                     )
                     |> then_(uploadedWDBNodeId2 => {
                          let editorState = StateEditorService.getState();

                          MainEditorAssetTreeTool.Select.selectFolderNode(
                            ~nodeId=
                              MainEditorAssetFolderNodeTool.getNodeIdByName(
                                "Textures",
                                editorState,
                              )
                              |> OptionService.unsafeGet,
                            (),
                          );

                          BuildComponentTool.buildAssetChildrenNode()
                          |> ReactTestTool.createSnapshotAndMatch
                          |> resolve;
                        })
                   )
              );
            });

            testPromise("texture asset should has unique name", () => {
              EventListenerTool.buildFakeDom()
              |> EventListenerTool.stubGetElementByIdReturnFakeDom;

              let assetTreeData =
                MainEditorAssetTreeTool.BuildAssetTree.Texture.buildOneTextureAssetTree();

              let addedFolderNodeId = MainEditorAssetIdTool.getNewAssetId();

              MainEditorAssetHeaderOperateNodeTool.addFolder();

              MainEditorAssetFolderNodeTool.setFolderName(
                addedFolderNodeId,
                "Textures",
              )
              |> StateLogicService.getAndSetEditorState;

              let textureNodeId =
                MainEditorAssetTreeTool.BuildAssetTree.Texture.getFirstTextureNodeId(
                  assetTreeData,
                );

              AssetTreeInspectorTool.Rename.renameAssetTextureNode(
                ~nodeId=textureNodeId,
                ~name=LoadWDBTool.getBoxTexturedMeshGameObjectTextureName(),
                (),
              );

              MainEditorAssetTreeTool.Drag.dragAssetChildrenNodeIntoAssetTreeNode(
                ~startNodeId=textureNodeId,
                ~targetNodeId=addedFolderNodeId,
                (),
              );

              MainEditorAssetTreeTool.Select.selectFolderNode(
                ~nodeId=
                  AssetTreeRootEditorService.getRootTreeNodeId
                  |> StateLogicService.getEditorState,
                (),
              );

              MainEditorAssetUploadTool.loadOneWDB(
                ~arrayBuffer=boxTexturedWDBArrayBuffer^,
                (),
              )
              |> then_(uploadedWDBNodeId1 => {
                   let editorState = StateEditorService.getState();

                   MainEditorAssetTreeTool.Select.selectFolderNode(
                     ~nodeId=addedFolderNodeId,
                     (),
                   );

                   BuildComponentTool.buildAssetChildrenNode()
                   |> ReactTestTool.createSnapshotAndMatch
                   |> resolve;
                 });
            });
          });

          describe("test wdb asset->wdb gameObject->texture", () => {
            testPromise(
              "wdb gameObject should use extraced texture asset->textureComponent",
              () =>
              MainEditorAssetUploadTool.loadOneWDB(
                ~arrayBuffer=boxTexturedWDBArrayBuffer^,
                (),
              )
              |> then_(uploadedWDBNodeId => {
                   let engineState = StateEngineService.unsafeGetState();
                   let editorState = StateEditorService.getState();

                   let boxTexturedMeshGameObject =
                     LoadWDBTool.getBoxTexturedMeshGameObjectFromAssetNode(
                       uploadedWDBNodeId,
                       editorState,
                     );
                   let diffuseMap =
                     boxTexturedMeshGameObject
                     |> GameObjectComponentEngineService.unsafeGetLightMaterialComponent(
                          _,
                          engineState,
                        )
                     |> LightMaterialEngineService.unsafeGetLightMaterialDiffuseMap(
                          _,
                          engineState,
                        );

                   MainEditorAssetTextureNodeTool.hasTextureComponent(
                     diffuseMap,
                     editorState,
                   )
                   |> expect == true
                   |> resolve;
                 })
            );
            testPromise(
              "if already has equaled texture asset, wdb gameObject should use it",
              () =>
              MainEditorAssetUploadTool.loadOneWDB(
                ~arrayBuffer=boxTexturedWDBArrayBuffer^,
                (),
              )
              |> then_(uploadedWDBNodeId1 => {
                   let engineState = StateEngineService.unsafeGetState();
                   let editorState = StateEditorService.getState();

                   let boxTexturedMeshGameObject1 =
                     LoadWDBTool.getBoxTexturedMeshGameObjectFromAssetNode(
                       uploadedWDBNodeId1,
                       editorState,
                     );
                   let material1 =
                     boxTexturedMeshGameObject1
                     |> GameObjectComponentEngineService.unsafeGetLightMaterialComponent(
                          _,
                          engineState,
                        );

                   editorState |> StateEditorService.setState |> ignore;
                   engineState |> StateEngineService.setState |> ignore;

                   MainEditorAssetHeaderOperateNodeTool.removeMaterialNode(
                     ~materialNodeId=
                       MainEditorAssetMaterialNodeTool.findNodeIdByMaterialComponent(
                         material1,
                         LoadWDBTool.getBoxTexturedMeshGameObjectMaterialType(),
                         editorState,
                       )
                       |> OptionService.unsafeGet,
                     (),
                   );

                   MainEditorAssetUploadTool.loadOneWDB(
                     ~arrayBuffer=boxTexturedWDBArrayBuffer^,
                     (),
                   )
                   |> then_(uploadedWDBNodeId2 => {
                        let engineState = StateEngineService.unsafeGetState();
                        let editorState = StateEditorService.getState();

                        let boxTexturedMeshGameObject2 =
                          LoadWDBTool.getBoxTexturedMeshGameObjectFromAssetNode(
                            uploadedWDBNodeId2,
                            editorState,
                          );
                        let diffuseMap2 =
                          boxTexturedMeshGameObject2
                          |> GameObjectComponentEngineService.unsafeGetLightMaterialComponent(
                               _,
                               engineState,
                             )
                          |> LightMaterialEngineService.unsafeGetLightMaterialDiffuseMap(
                               _,
                               engineState,
                             );

                        (
                          MainEditorAssetTextureNodeTool.hasTextureComponent(
                            diffuseMap2,
                            editorState,
                          ),
                          AssetTextureNodeMapEditorService.getValidValues(
                            editorState,
                          )
                          |> SparseMapService.length,
                          AssetImageNodeMapEditorService.getValidValues(
                            editorState,
                          )
                          |> SparseMapService.length,
                        )
                        |> expect == (true, 1, 1)
                        |> resolve;
                      });
                 })
            );
          });
        });
      });

      describe("fix bug", () =>
        testPromise("the wdb->name in the same path should be unique", () => {
          let fileName = "BoxTextured";

          MainEditorAssetUploadTool.loadOneWDB(
            ~fileName,
            ~arrayBuffer=boxTexturedWDBArrayBuffer^,
            (),
          )
          |> then_(uploadedWDBNodeId1 =>
               MainEditorAssetUploadTool.loadOneWDB(
                 ~fileName,
                 ~arrayBuffer=boxTexturedWDBArrayBuffer^,
                 (),
               )
               |> then_(uploadedWDBNodeId2 => {
                    let editorState = StateEditorService.getState();
                    let wdbNodeMap =
                      AssetWDBNodeMapEditorService.getWDBNodeMap(editorState);

                    (
                      AssetWDBNodeMapEditorService.getWDBBaseName(
                        uploadedWDBNodeId1,
                        wdbNodeMap,
                      ),
                      AssetWDBNodeMapEditorService.getWDBBaseName(
                        uploadedWDBNodeId2,
                        wdbNodeMap,
                      ),
                    )
                    |> expect == (fileName, fileName ++ " 1")
                    |> resolve;
                  })
             );
        })
      );
    });
  });