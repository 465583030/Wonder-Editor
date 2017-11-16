/* let createState = () => {
       /* todo create editor state in edit layer */
       a:1
   }; */
let createEditorState = () => StateSystemEdit.createState();

/* let getEditorState = () => {

   }; */
let setEditorState = (editorState) =>
  StateSystemEdit.setState(StateDataEdit.stateData, editorState);

/* let getEngineState = () => {

   }; */
/* let setEngineStateToEngineData = (engineState) => {

   }; */
/* todo should get canvasId,isTest from config */
let initEngineMain = () => MainEditorMainOper.init("webgl", Js.true_);

let initEngineDirector = (engineState) => MainEditorDirectorOper.init(engineState);

let initEditor = ((editorState, engineState)) => {
  let (engineState, scene) = MainEditorGameObjectOper.create(engineState);
  let editorState = MainEditorSceneEdit.setScene(scene, editorState);
  let (engineState, camera, box) = MainEditorSceneOper.createDefaultScene(engineState);
  let engineState =
    engineState
    |> MainEditorGameObjectOper.addChild(scene, camera)
    |> MainEditorGameObjectOper.addChild(scene, box);
  (editorState, engineState)
};

let loopBody = (time: float, (editorState, engineState)) => {
  let engineState = MainEditorDirectorOper.loopBody(time, engineState);
  (editorState, engineState)
};