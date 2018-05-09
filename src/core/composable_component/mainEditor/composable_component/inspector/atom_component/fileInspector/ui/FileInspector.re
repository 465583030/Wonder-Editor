open FileType;

type state = {
  inputField: ref(option(Dom.element)),
  inputValue: string
};

type action =
  | Blur
  | Change(string);

let setInputFiledRef = (value, {ReasonReact.state}) => state.inputField := Js.Null.to_opt(value);

module Method = {
  let change = (event) => {
    let inputVal = ReactDOMRe.domElementToObj(ReactEventRe.Form.target(event))##value;
    Change(inputVal)
  };
  let blur = (_event) => Blur;
  let triggerBlur = (dispatch, value, currentFile, fileResult) => {
    AssetEditorService.setFileMap(
      StateEditorService.getState()
      |> AssetEditorService.unsafeGetFileMap
      |> SparseMapService.immutableSet(currentFile, {...fileResult, name: value})
    )
    |> StateLogicService.getAndSetEditorState;
    dispatch(AppStore.ReLoad)
  };
  let showFileInfo = (fileResult, {state, handle, reduce}: ReasonReact.self('a, 'b, 'c)) =>
    fileResult
    |> (
      ({name, type_, result}) =>
        switch type_ {
        | Image =>
          <div className="">
            <h1> (DomHelper.textEl("Image")) </h1>
            <hr />
            <span className=""> (DomHelper.textEl("name:")) </span>
            <input
              ref=(handle(setInputFiledRef))
              className="input-component float-input"
              _type="text"
              value=state.inputValue
              onChange=(reduce(change))
              onBlur=(reduce(blur))
            />
          </div>
        | Json =>
          <div>
            <h1> (DomHelper.textEl("Json")) </h1>
            <hr />
            <span className=""> (DomHelper.textEl("name:")) </span>
            <input
              ref=(handle(setInputFiledRef))
              className="input-component float-input"
              _type="text"
              value=state.inputValue
              onChange=(reduce(change))
              onBlur=(reduce(blur))
            />
            <p> (DomHelper.textEl(result)) </p>
          </div>
        }
    );
};

let component = ReasonReact.reducerComponent("FileInspector");

let reducer = (dispatch, currentFile, fileResult, action, state) =>
  switch action {
  | Change(value) => ReasonReact.Update({...state, inputValue: value})
  | Blur =>
    Method.triggerBlur(dispatch, state.inputValue, currentFile, fileResult);
    ReasonReact.NoUpdate
  };

let render = (fileResult, self) =>
  <article key="fileInspector" className="inspector-component">
    (Method.showFileInfo(fileResult, self))
  </article>;

let make =
    (~store: AppStore.appState, ~dispatch, ~currentFile, ~fileResult: fileResultType, _children) => {
  ...component,
  initialState: () => {inputValue: fileResult.name, inputField: ref(None)},
  reducer: reducer(dispatch, currentFile, fileResult),
  render: (self) => render(fileResult, self)
};