type window;

[@bs.val] external window : Js.t({..}) = "global";

let buildFakeLocalStorage = () => {
  let fakeLocalStorage = WonderCommonlib.HashMapSystem.createEmpty();
  window##localStorage#=fakeLocalStorage
};

let getExtensionTestKey = () => "databaseTest";

let setExtension = AppExtensionView.setExtension;

let getExtension = AppExtensionView.getExtension;