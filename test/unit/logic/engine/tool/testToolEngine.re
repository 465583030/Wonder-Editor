open Wonderjs;

open Sinon;

type document;

[@bs.val] external document : document = "";

external documentToObj : document => obj = "%identity";

let _buildFakeDomForPassCanvasId = (sandbox) => {
  /* open Sinon; */
  let canvasDom = {
    "id": "a",
    "nodeType": 1,
    "getContext": createEmptyStub(refJsObjToSandbox(sandbox^))
  };
  /* let div = {"innerHTML": "", "firstChild": canvasDom};
     let body = {"prepend": createEmptyStub(refJsObjToSandbox(sandbox^))};
     createMethodStub(refJsObjToSandbox(sandbox^), documentToObj(document), "createElement")
     |> withOneArg("div")
     |> returns(div)
     |> ignore;
     createMethodStub(refJsObjToSandbox(sandbox^), documentToObj(document), "querySelectorAll")
     |> withOneArg("body")
     |> returns([body])
     |> ignore; */
  createMethodStub(refJsObjToSandbox(sandbox^), documentToObj(document), "querySelectorAll")
  /* |> withOneArg({j|#$canvasId|j}) */
  |> withOneArg({j|#webgl|j})
  |> returns([canvasDom])
  |> ignore
  /* (canvasDom, div, body) */
};

let init =
    (
      ~isTest=Js.Nullable.return(Js.true_),
      ~bufferConfig=Js.Nullable.return({
                      "transformDataBufferCount": Js.Nullable.return(5),
                      "geometryPointDataBufferCount": Js.Nullable.return(5),
                      "basicMaterialDataBufferCount": Js.Nullable.return(5)
                    }),
      ()
    ) =>
  Main.setMainConfig(MainToolEngine.buildMainConfig(~isTest, ~bufferConfig, ()))
  |> (
    (state) => {
      StateData.stateData.state = Some(state);
      state
    }
  );

/* let initWithRenderConfig =
   (
     /* ~renderConfig=(
                     Render_setting.render_setting,
                     Init_pipelines.init_pipelines,
                     Render_pipelines.render_pipelines,
                     Init_jobs.init_jobs,
                     Render_jobs.render_jobs,
                     Shaders.shaders,
                     Shader_libs.shader_libs
                   ), */
     ~isTest=Js.Nullable.return(Js.true_),
     ~bufferConfig=Js.Nullable.return({
                     "transformDataBufferCount": Js.Nullable.return(5),
                     "geometryPointDataBufferCount": Js.Nullable.return(5),
                     "basicMaterialDataBufferCount": Js.Nullable.return(5)
                   }),
     ~renderConfig,
     ()
   ) =>
   StateSystem.createState(~renderConfig=renderConfig, ())
   |> MainSystem.setConfig(MainTool.buildMainConfig(~isTest, ~bufferConfig, ()))
   |> MainSystem.init
   |> (
   (state) => {
     StateData.stateData.state = Some(state);
     state
   }
   ); */
let prepare = (sandbox) => {
  TimeControllerToolEngine.setStartTime(0.);
  _buildFakeDomForPassCanvasId(sandbox) |> ignore
};