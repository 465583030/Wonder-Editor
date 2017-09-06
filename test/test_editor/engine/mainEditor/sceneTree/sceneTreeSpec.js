describe("test sceneTree engine", function(){
    var editorState = null,
        engineState = null,
        sandbox = null,
        gameObject1,
        gameObject2,
        children,
        gl;

    beforeEach(function(){
        sandbox = sinon.sandbox.create();

        testTool.clearAndOpenContractCheck(sandbox);

        editorState = stateEditTool.createState();

        engineState = stateTool.createAndSetFakeGLState(sandbox);

        gl = stateTool.getGLFromFakeGLState(engineState);

        editorState = mainBussTool.initEditor(editorState);
        stateEditTool.setState(editorState);
    });

    afterEach(function(){
        testTool.clear(sandbox);
        sandbox.restore();
    });

    it("reset tree node parent", function(){
        sceneTreeBussTool.resetTreeNodeParent(1,3);

        gameObject1 = tempGameObjectTool.createTempGameObject1(1);
        gameObject2 = tempGameObjectTool.createTempGameObject2(3);
        children = gameObjectAdaptorTool.getChildren(gameObject1);

        expect(children[0]).toEqual(gameObject2);
    });
});