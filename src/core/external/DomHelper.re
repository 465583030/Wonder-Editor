[@bs.val] external requestAnimationFrame : (float => unit) => int = "";

[@bs.val] external cancelAnimationFrame : int => unit = "";

[@bs.send] external toFixed : (float, int) => string = "";

[@bs.val] external makeStringToInt : string => int = "Number";

[@bs.val] external makeStringToFloat : string => float = "Number";

[@bs.val] external makeNumberToString : string => string = "Number";

/* [@bs.val] external readAsDataURL : file => unit = "FileReader"; */
[@bs.val] external makeString : string => string = "String";

type imgType;

[@bs.val] [@bs.scope "document"] external createElement : string => imgType = "createElement";

let setTimeout = [%bs.raw {|
    function (func, time) {
      setTimeout(func, time)
    }
  |}];

let apply = [%bs.raw
  {|
    function(dataArray, func) {
      return func.apply(null, dataArray);
    }
  |}
];

let deleteKeyInDict = [%raw {|function (key,dict) {
    delete dict[key];
    return 0
    }
  |}];

let stopPropagation = (e) : unit => e##stopPropagation() |> ignore;

let preventDefault = (e) : unit => e##preventDefault();

let getRandomKey = () : string => string_of_float(Js.Date.now() *. Js.Math.random());

let intEl = (n) => ReasonReact.stringToElement(string_of_int(n));

let textEl = (str) => ReasonReact.stringToElement(str);