open Wonderjs;

let prepare = (state: StateDataMainType.state) => {
  TimeControllerToolEngine.setStartTime(0.);
  state;
};

let init = (state: StateDataMainType.state) =>
  state |> DirectorAPI._noWorkerInit;

let run = (state: StateDataMainType.state, ~time=0., ()) =>
  state |> DirectorAPI._run(time);

let runWithDefaultTime = (state: StateDataMainType.state) =>
  state |> DirectorAPI._run(0.);

let prepareAllEnginState = () => {
  StateLogicService.getEditEngineState()
  |> prepare
  |> StateLogicService.setEditEngineState;

  StateLogicService.getRunEngineState()
  |> prepare
  |> StateLogicService.setRunEngineState;
};

let initAllEnginState = () => {
  StateLogicService.getEditEngineState()
  |> init
  |> StateLogicService.setEditEngineState;

  StateLogicService.getRunEngineState()
  |> init
  |> StateLogicService.setRunEngineState;
};

let prepareAndInitAllEnginState = () => {
  prepareAllEnginState();
  initAllEnginState();
};