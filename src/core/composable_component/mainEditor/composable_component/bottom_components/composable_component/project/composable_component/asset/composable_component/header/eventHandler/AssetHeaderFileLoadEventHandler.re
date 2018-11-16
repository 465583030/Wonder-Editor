module CustomEventHandler = {
  include EmptyEventHandler.EmptyEventHandler;
  type prepareTuple = unit;
  type dataTuple = ReactEventRe.Form.t;
  type return = Js.Promise.t(unit);

  let handleSelfLogic = ((store, dispatchFunc), (), event) =>
    AssetHeaderUtils.fileLoad((store, dispatchFunc), event)
    |> Js.Promise.catch(e => {
         AllHistoryService.undoHistoryState(store, Obj.magic(dispatchFunc))
         |> StateHistoryService.getAndRefreshStateForHistory
         |> ignore;

         let e = Obj.magic(e);
         let editorState = StateEditorService.getState();

         switch (e) {
         | AssetNodeType.LoadException(message) =>
           ConsoleUtils.error(
             LogUtils.buildErrorMessage(
               ~description={j|$message|j},
               ~reason="",
               ~solution={j||j},
               ~params={j||j},
             ),
             editorState,
           )
         | _ =>
           let message = e##message;
           let stack = e##stack;

           ConsoleUtils.error(
             LogUtils.buildErrorMessage(
               ~description={j|$message|j},
               ~reason="",
               ~solution={j||j},
               ~params={j||j},
             ),
             editorState,
           );
           ConsoleUtils.logStack(stack) |> ignore;
         };

         Js.Promise.resolve();
       });
};

module MakeEventHandler = EventHandler.MakeEventHandler(CustomEventHandler);