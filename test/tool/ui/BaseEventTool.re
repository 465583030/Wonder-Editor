external toObject : Js.Dict.t('a) => Js.t({..}) = "%identity";

let triggerComponentEvent = (component, triggerEventFunc) => {
  let json = ReactTestRenderer.toJSON(component);
  switch (Js.Json.decodeObject(json)) {
  | None => ()
  | Some(dict) => 
 /* WonderLog.Log.printJson(dict) |> ignore;  */
  triggerEventFunc(toObject(dict)##children)
  };
};

let buildFormEvent = value =>
  {
    "target": {
      "value": value,
      "checked": value,
    },
  } |> Obj.magic;

/* let buildZipFileEvent = () =>
  {
    "target": {
      "files": {
        "0": {
          name: "wonderpackage.wdb",
          file: "",
        },
      },
    },
    "preventDefault": () => (),
  }
  |> Obj.magic; */

let buildWDBFileEvent = (fileName, arrayBuffer) =>
  {
    "target": {
      "files": {
        "0": {
          name: fileName ++ ".wdb",
          file: arrayBuffer,
        },
      },
    },
    "preventDefault": () => (),
  }
  |> Obj.magic;

let buildTwoJsonFileEvent =
    (~jsonName="loadJson", ~jsonResult="loadJson string result", ()) =>
  {
    "target": {
      "files": {
        "0": {
          name: jsonName ++ ".json",
          file: jsonResult,
        },
        "1": {
          name: jsonName ++ ".json",
          file: jsonResult,
        },
      },
    },
    "preventDefault": () => (),
  }
  |> Obj.magic;

let buildFileEvent =
    (
      ~imgName="loadImg.png",
      ~imgSrc="newImgBase64",
      ~jsonName="loadJson",
      ~jsonResult="loadJson string result",
      (),
    ) =>
  {
    "target": {
      "files": {
        "0": {
          name: imgName,
          file: imgSrc,
        },
        "1": {
          name: jsonName ++ ".json",
          file: jsonResult,
        },
      },
    },
    "preventDefault": () => (),
  }
  |> Obj.magic;

let dragedUid = ref(-1);

let buildDragEvent = () =>
  {
    "stopPropagation": () => (),
    "preventDefault": () => (),
    "dataTransfer": {
      "effectAllowed": "move",
      "setData": (key, value) => dragedUid := value,
      "setDragImage": (image, value, value) => (),
      "getData": key => dragedUid^,
    },
  }
  |> Obj.magic;

let _getProps = dom => dom##props;

let triggerClickEvent = dom => _getProps(dom)##onClick();

let triggerClickFromEvent = (dom, event) => _getProps(dom)##onClick(event);

let triggerChangeEvent = (dom, event) => _getProps(dom)##onChange(event);

let triggerBlurEvent = (dom, event) => _getProps(dom)##onBlur(event);

let triggerDragStartEvent = (dom, event) =>
  _getProps(dom)##onDragStart(event);

let triggerDragEndEvent = (dom, event) => _getProps(dom)##onDragEnd(event);

let triggerDragEnterEvent = (dom, event) =>
  _getProps(dom)##onDragEnter(event);

let triggerDragLeaveEvent = (dom, event) =>
  _getProps(dom)##onDragLeave(event);

let triggerDragOverEvent = (dom, event) =>
  _getProps(dom)##onDragOver(event);

let triggerDropEvent = (dom, event) => _getProps(dom)##onDrop(event);