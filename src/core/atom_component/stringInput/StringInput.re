Css.importCss("./css/stringInput.css");

type state = {
  inputValue: string,
};

type action =
  | Blur
  | Change(string);

module Method = {
  let change = event => {
    let inputVal = ReactDOMRe.domElementToObj(
                     ReactEventRe.Form.target(event),
                   )##value;
    Change(inputVal);
  };
  let blur = _event => Blur;
  let triggerOnChange = (value, onChangeFunc) =>
    switch (onChangeFunc) {
    | None => ()
    | Some(onChange) => onChange(value)
    };
  let triggerOnBlur = (value, onBlurFunc) =>
    switch (onBlurFunc) {
    | None => ()
    | Some(onBlur) => onBlur(value)
    };
};

let component = ReasonReact.reducerComponent("StringInput");

let reducer = (onChangeFunc, onBlurFunc, action, state) =>
  switch (action) {
  | Change(value) =>
    ReasonReactUtils.updateWithSideEffects(
      {...state, inputValue: value}, _state =>
      Method.triggerOnChange(value, onChangeFunc)
    )

  | Blur =>
    Method.triggerOnBlur(state.inputValue, onBlurFunc);
    ReasonReact.NoUpdate;
  };

let render = (label, {state, handle, send}: ReasonReact.self('a, 'b, 'c)) =>
  <article className="wonder-string-input">
    (
      switch (label) {
      | None => ReasonReact.nullElement
      | Some(value) =>
        <span className="component-label">
          (DomHelper.textEl(value ++ " : "))
        </span>
      }
    )
    <input
      className="input-component float-input"
      _type="text"
      value=state.inputValue
      onChange=(_e => send(Method.change(_e)))
      onBlur=(_e => send(Method.blur(_e)))
    />
  </article>;

let make =
    (
      ~defaultValue: option(string)=?,
      ~label: option(string)=?,
      ~onChange: option(string => unit)=?,
      ~onBlur: option(string => unit)=?,
      _children,
    ) => {
  ...component,
  initialState: () =>
    switch (defaultValue) {
    | None => {inputValue: ""}
    | Some(value) => {inputValue: value}
    },
  reducer: reducer(onChange, onBlur),
  render: self => render(label, self),
};