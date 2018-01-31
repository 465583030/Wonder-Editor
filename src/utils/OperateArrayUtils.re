let getFirst = (arr) =>
  WonderCommonlib.ArraySystem.unsafeGet(arr, 0)
  |> WonderLog.Contract.ensureCheck(
       (r) =>
         WonderLog.(
           Contract.(
             Operators.(
               test(
                 Log.buildAssertMessage(~expect={j|array[0] element exist|j}, ~actual={j|not|j}),
                 () => r |> assertNullableExist
               )
             )
           )
         ),
       EditorStateDataEdit.getStateIsDebug()
     );

let removeLast = (arr) => {
  WonderLog.Contract.requireCheck(
    () =>
      WonderLog.(
        Contract.(
          Operators.(
            test(
              Log.buildAssertMessage(~expect={j|array length should >= 1|j}, ~actual={j|not|j}),
              () => arr |> Js.Array.length >= 1
            )
          )
        )
      ),
    EditorStateDataEdit.getStateIsDebug()
  );
  arr |> Js.Array.pop |> Js.Option.getExn
};

let removeFirst = (arr) => {
  WonderLog.Contract.requireCheck(
    () =>
      WonderLog.(
        Contract.(
          Operators.(
            test(
              Log.buildAssertMessage(~expect={j|array length should >= 1|j}, ~actual={j|not|j}),
              () => arr |> Js.Array.length >= 1
            )
          )
        )
      ),
    EditorStateDataEdit.getStateIsDebug()
  );
  arr |> Js.Array.shift |> Js.Option.getExn
};

let getNth = (index, arr) =>
  WonderCommonlib.ArraySystem.unsafeGet(arr, index)
  |> WonderLog.Contract.ensureCheck(
       (r) =>
         WonderLog.(
           Contract.(
             Operators.(
               test(
                 Log.buildAssertMessage(
                   ~expect={j|array[$index] element exist|j},
                   ~actual={j|not|j}
                 ),
                 () => r |> assertNullableExist
               )
             )
           )
         ),
       EditorStateDataEdit.getStateIsDebug()
     );

let hasItem = (arr) => arr |> Js.Array.length > 0 ? true : false;

let push = (item, arr) => {
  arr |> Js.Array.push(item) |> ignore;
  arr
};

let hasItemByFunc = (func, arr) => arr |> Js.Array.filter(func) |> hasItem;