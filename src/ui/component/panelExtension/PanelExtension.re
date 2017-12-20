open DomHelper;

let component = ReasonReact.statelessComponent("UserExtension");

let make =
    (~record: ExtensionParseType.panelType, ~name: string, ~store: AppStore.appState, _children) => {
  ...component,
  didMount: (_self) => {
    record.didMount();
    ReasonReact.NoUpdate
  },
  initialState: () => record.initialState(),
  render: (_self) => {
    record.willRender();
    <div key="fck">
      (ReasonReact.arrayToElement(ParseSystem.buildSpecificComponents(record.render, name, store)))
    </div>
  }
};