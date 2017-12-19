[@bs.deriving jsConverter]
type panelType = {
  name: string,
  parent: string,
  render: string,
  willRender: unit => unit,
  didMount: unit => unit
};

[@bs.deriving jsConverter]
type funcType;

[@bs.deriving jsConverter]
type t = {
  panelExtension: array(panelType),
  funcExtension: array(funcType),
  name: string
};

external parsePanelTypeToJsObj : panelType => Js.t({..}) = "%identity";

external parseFuncTypeToJsObj : funcType => Js.t({..}) = "%identity";