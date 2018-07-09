open Wonder_jest;

open Expect;

open Expect.Operators;

open CurrentNodeDataType;

open Sinon;

open AssetNodeType;

let _ =
  describe("MainEditorAssetChildrenNode", () => {
    let sandbox = getSandboxDefaultVal();
    let _triggerClickAssetTreeNode = (component, index) =>
      BaseEventTool.triggerComponentEvent(
        component,
        AssetTreeEventTool.clickAssetTreeNode(index),
      );
    let _triggerClickAssetChildrenNode = (component, index) =>
      BaseEventTool.triggerComponentEvent(
        component,
        AssetTreeEventTool.clickAssetTreeChildrenNode(index),
      );

    beforeEach(() => {
      sandbox := createSandbox();
      MainEditorSceneTool.initStateAndGl(~sandbox, ());
    });
    afterEach(() => restoreSandbox(refJsObjToSandbox(sandbox^)));

    describe("test ui component", () => {
      beforeEach(() => {
        MainEditorSceneTool.createDefaultScene(
          sandbox,
          MainEditorAssetTool.initAssetTree(
            MainEditorAssetTool.buildThreeLayerAssetTreeRoot,
          ),
        );
        EventListenerTool.buildFakeDom()
        |> EventListenerTool.stubGetElementByIdReturnFakeDom;
      });

      describe("show currentNodeParent's children", () => {
        afterEach(() =>
          StateAssetService.getState()
          |> CurrentNodeDataAssetService.clearCurrentNodeData
          |> CurrentNodeParentIdAssetService.clearCurrentNodeParentId
          |> StateAssetService.setState
          |> ignore
        );
        test("if currentNodeParent's have no children, show nothing", () => {
          let component = BuildComponentTool.buildAssetComponent();
          _triggerClickAssetTreeNode(component, 1);

          component |> ReactTestTool.createSnapshotAndMatch;
        });
        test("else, show children", () => {
          let component = BuildComponentTool.buildAssetComponent();
          _triggerClickAssetTreeNode(component, 2);

          component |> ReactTestTool.createSnapshotAndMatch;
        });
      });
    });

    describe("test set current node", () => {
      beforeEach(() =>
        EventListenerTool.buildFakeDom()
        |> EventListenerTool.stubGetElementByIdReturnFakeDom
      );
      afterEach(() =>
        StateAssetService.getState()
        |> CurrentNodeDataAssetService.clearCurrentNodeData
        |> CurrentNodeParentIdAssetService.clearCurrentNodeParentId
        |> StateAssetService.setState
        |> ignore
      );

      test("click texture file to be current node", () => {
        MainEditorSceneTool.createDefaultScene(
          sandbox,
          MainEditorAssetTool.initAssetTree(
            MainEditorAssetTool.buildThreeLayerAssetTreeRoot,
          ),
        );
        _triggerClickAssetTreeNode(
          BuildComponentTool.buildAssetComponent(),
          2,
        );
        _triggerClickAssetChildrenNode(
          BuildComponentTool.buildAssetComponent(),
          2,
        );

        let {currentNodeId, nodeType} =
          StateAssetService.getState()
          |> CurrentNodeDataAssetService.unsafeGetCurrentNodeData;

        nodeType |> expect == AssetNodeType.Texture;
      });

      test("click json file to be current node", () => {
        MainEditorSceneTool.createDefaultScene(
          sandbox,
          MainEditorAssetTool.initAssetTree(
            MainEditorAssetTool.buildThreeLayerAssetTreeRoot,
          ),
        );
        _triggerClickAssetTreeNode(
          BuildComponentTool.buildAssetComponent(),
          2,
        );
        _triggerClickAssetChildrenNode(
          BuildComponentTool.buildAssetComponent(),
          3,
        );

        let {currentNodeId, nodeType} =
          StateAssetService.getState()
          |> CurrentNodeDataAssetService.unsafeGetCurrentNodeData;

        nodeType |> expect == AssetNodeType.Json;
      });

      describe("test click folder", () => {
        afterEach(() =>
          StateAssetService.getState()
          |> CurrentNodeDataAssetService.clearCurrentNodeData
          |> CurrentNodeParentIdAssetService.clearCurrentNodeParentId
          |> StateAssetService.setState
          |> ignore
        );

        describe("test single click", () => {
          testPromise("test set folder to be current node", () => {
            MainEditorSceneTool.createDefaultScene(
              sandbox,
              MainEditorAssetTool.initAssetTree(
                MainEditorAssetTool.buildFolderClickSimpleAssetTreeRoot,
              ),
            );
            let fakeDom =
              EventListenerTool.buildFakeDom()
              |> EventListenerTool.stubGetElementByIdReturnFakeDom;

            BuildComponentTool.buildAssetChildrenNode(10);

            EventListenerTool.triggerEvent(fakeDom, "mousedown", {});
            Js.Promise.make((~resolve, ~reject) =>
              Timeout.setTimeout(
                () => {
                  EventListenerTool.triggerEvent(fakeDom, "mousedown", {});
                  switch (
                    StateAssetService.getState()
                    |> CurrentNodeDataAssetService.getCurrentNodeData
                  ) {
                  | None => reject(. "fail" |> Obj.magic)
                  | Some(file) =>
                    resolve(.
                      {
                        let {currentNodeId, nodeType} =
                          StateAssetService.getState()
                          |> CurrentNodeDataAssetService.unsafeGetCurrentNodeData;

                        nodeType |> expect == AssetNodeType.Folder;
                      },
                    )
                  };
                },
                20,
              )
            );
          });
          testPromise("test snapshot", () => {
            MainEditorSceneTool.createDefaultScene(
              sandbox,
              MainEditorAssetTool.initAssetTree(
                MainEditorAssetTool.buildFolderClickSimpleAssetTreeRoot,
              ),
            );
            let fakeDom =
              EventListenerTool.buildFakeDom()
              |> EventListenerTool.stubGetElementByIdReturnFakeDom;

            BuildComponentTool.buildAssetChildrenNode(10);

            EventListenerTool.triggerEvent(fakeDom, "mousedown", {});
            Js.Promise.make((~resolve, ~reject) =>
              Timeout.setTimeout(
                () => {
                  EventListenerTool.triggerEvent(fakeDom, "mousedown", {});
                  switch (
                    StateAssetService.getState()
                    |> CurrentNodeDataAssetService.getCurrentNodeData
                  ) {
                  | None => reject(. "fail" |> Obj.magic)
                  | Some(file) =>
                    resolve(.
                      BuildComponentTool.buildAssetComponent()
                      |> ReactTestTool.createSnapshotAndMatch,
                    )
                  };
                },
                20,
              )
            );
          });
        });

        testPromise(
          "double click folder, set folder to be currentAssetNodeParent and current node(are the same)",
          () => {
            MainEditorSceneTool.createDefaultScene(
              sandbox,
              MainEditorAssetTool.initAssetTree(
                MainEditorAssetTool.buildFolderClickSimpleAssetTreeRoot,
              ),
            );
            let fakeDom =
              EventListenerTool.buildFakeDom()
              |> EventListenerTool.stubGetElementByIdReturnFakeDom;

            BuildComponentTool.buildAssetChildrenNode(10);

            EventListenerTool.triggerEvent(fakeDom, "mousedown", {});
            Js.Promise.make((~resolve, ~reject) =>
              Timeout.setTimeout(
                () => {
                  EventListenerTool.triggerEvent(fakeDom, "mousedown", {});
                  Timeout.setTimeout(
                    () => {
                      EventListenerTool.triggerEvent(
                        fakeDom,
                        "mousedown",
                        {},
                      );
                      resolve(.
                        {
                          _triggerClickAssetTreeNode(
                            BuildComponentTool.buildAssetComponent(),
                            1,
                          );
                          BuildComponentTool.buildAssetComponent()
                          |> ReactTestTool.createSnapshotAndMatch;
                        },
                      );
                    },
                    20,
                  );
                },
                5,
              )
            );
          },
        );
      });
    });
  });