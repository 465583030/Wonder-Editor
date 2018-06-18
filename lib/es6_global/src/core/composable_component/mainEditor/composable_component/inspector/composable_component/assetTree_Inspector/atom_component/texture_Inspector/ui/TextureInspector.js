

import * as Block from "../../../../../../../../../../../../../node_modules/bs-platform/lib/es6/block.js";
import * as Curry from "../../../../../../../../../../../../../node_modules/bs-platform/lib/es6/curry.js";
import * as React from "react";
import * as ReasonReact from "../../../../../../../../../../../../../node_modules/reason-react/lib/es6_global/src/ReasonReact.js";
import * as Log$WonderLog from "../../../../../../../../../../../../../node_modules/wonder-log/lib/es6_global/src/Log.js";
import * as Select$WonderEditor from "../../../../../../../../../atom_component/select/Select.js";
import * as DomHelper$WonderEditor from "../../../../../../../../../external/DomHelper.js";
import * as ReasonReactUtils$WonderEditor from "../../../../../../../../../utils/ui/ReasonReactUtils.js";
import * as StateLogicService$WonderEditor from "../../../../../../../../../../service/stateTuple/logic/StateLogicService.js";
import * as AssetTreeInspectorUtils$WonderEditor from "../../../utils/AssetTreeInspectorUtils.js";
import * as BasicSourceTextureEngineService$WonderEditor from "../../../../../../../../../../service/state/engine/BasicSourceTextureEngineService.js";

function changeName($$event) {
  var inputVal = $$event.target.value;
  return /* ChangeName */[inputVal];
}

function changeWrapS(textureId, value) {
  Log$WonderLog.print(/* tuple */[
        "select warps ",
        value
      ]);
  return StateLogicService$WonderEditor.getAndRefreshEditAndRunEngineState((function (param) {
                return BasicSourceTextureEngineService$WonderEditor.setWrapS(value, textureId, param);
              }));
}

function changeWrapT(textureId, value) {
  Log$WonderLog.print(/* tuple */[
        "select warpt ",
        value
      ]);
  return StateLogicService$WonderEditor.getAndRefreshEditAndRunEngineState((function (param) {
                return BasicSourceTextureEngineService$WonderEditor.setWrapT(value, textureId, param);
              }));
}

function _getWrapOptions() {
  return /* array */[
          /* record */[
            /* key */0,
            /* value */"REPEAT"
          ],
          /* record */[
            /* key */1,
            /* value */"MIRRORED_REPEAT"
          ],
          /* record */[
            /* key */2,
            /* value */"CLAMP_TO_EDGE"
          ]
        ];
}

function renderWarpSSelect(textureId) {
  return ReasonReact.element(/* None */0, /* None */0, Select$WonderEditor.make(/* Some */["WarpS Mode"], /* array */[
                  /* record */[
                    /* key */0,
                    /* value */"REPEAT"
                  ],
                  /* record */[
                    /* key */1,
                    /* value */"MIRRORED_REPEAT"
                  ],
                  /* record */[
                    /* key */2,
                    /* value */"CLAMP_TO_EDGE"
                  ]
                ], StateLogicService$WonderEditor.getEngineStateToGetData((function (param) {
                        return BasicSourceTextureEngineService$WonderEditor.getWrapS(textureId, param);
                      })), (function (param) {
                    return changeWrapS(textureId, param);
                  }), /* array */[]));
}

function renderWarpTSelect(textureId) {
  return ReasonReact.element(/* None */0, /* None */0, Select$WonderEditor.make(/* Some */["WarpT Mode"], /* array */[
                  /* record */[
                    /* key */0,
                    /* value */"REPEAT"
                  ],
                  /* record */[
                    /* key */1,
                    /* value */"MIRRORED_REPEAT"
                  ],
                  /* record */[
                    /* key */2,
                    /* value */"CLAMP_TO_EDGE"
                  ]
                ], StateLogicService$WonderEditor.getEngineStateToGetData((function (param) {
                        return BasicSourceTextureEngineService$WonderEditor.getWrapT(textureId, param);
                      })), (function (param) {
                    return changeWrapT(textureId, param);
                  }), /* array */[]));
}

function _getFilterOptions() {
  return /* array */[
          /* record */[
            /* key */0,
            /* value */"NEAREST"
          ],
          /* record */[
            /* key */1,
            /* value */"NEARESTMIPMAPNEAREST"
          ],
          /* record */[
            /* key */2,
            /* value */"NEARESTMIPMAPLINEAR"
          ],
          /* record */[
            /* key */3,
            /* value */"LINEAR"
          ],
          /* record */[
            /* key */4,
            /* value */"LINEARMIPMAPNEAREST"
          ],
          /* record */[
            /* key */5,
            /* value */"LINEARMIPMAPLINEAR"
          ]
        ];
}

function changeFilterMag(textureId, value) {
  Log$WonderLog.print(/* tuple */[
        "select filter mag ",
        value
      ]);
  return StateLogicService$WonderEditor.getAndRefreshEditAndRunEngineState((function (param) {
                return BasicSourceTextureEngineService$WonderEditor.setMagFilter(value, textureId, param);
              }));
}

function changeFilterMin(textureId, value) {
  Log$WonderLog.print(/* tuple */[
        "select filter min ",
        value
      ]);
  return StateLogicService$WonderEditor.getAndRefreshEditAndRunEngineState((function (param) {
                return BasicSourceTextureEngineService$WonderEditor.setMinFilter(value, textureId, param);
              }));
}

function renderFilterMagSelect(textureId) {
  return ReasonReact.element(/* None */0, /* None */0, Select$WonderEditor.make(/* Some */["Filter Mag Mode"], _getFilterOptions(/* () */0), StateLogicService$WonderEditor.getEngineStateToGetData((function (param) {
                        return BasicSourceTextureEngineService$WonderEditor.getMagFilter(textureId, param);
                      })), (function (param) {
                    return changeFilterMag(textureId, param);
                  }), /* array */[]));
}

function renderFilterMinSelect(textureId) {
  return ReasonReact.element(/* None */0, /* None */0, Select$WonderEditor.make(/* Some */["Filter Min Mode"], _getFilterOptions(/* () */0), StateLogicService$WonderEditor.getEngineStateToGetData((function (param) {
                        return BasicSourceTextureEngineService$WonderEditor.getMinFilter(textureId, param);
                      })), (function (param) {
                    return changeFilterMin(textureId, param);
                  }), /* array */[]));
}

var Method = /* module */[
  /* changeName */changeName,
  /* changeWrapS */changeWrapS,
  /* changeWrapT */changeWrapT,
  /* _getWrapOptions */_getWrapOptions,
  /* renderWarpSSelect */renderWarpSSelect,
  /* renderWarpTSelect */renderWarpTSelect,
  /* _getFilterOptions */_getFilterOptions,
  /* changeFilterMag */changeFilterMag,
  /* changeFilterMin */changeFilterMin,
  /* renderFilterMagSelect */renderFilterMagSelect,
  /* renderFilterMinSelect */renderFilterMinSelect
];

var component = ReasonReact.reducerComponent("TextureInspector");

function reducer(dispatchFunc, nodeId, action) {
  if (action) {
    var value = action[0];
    return (function (state) {
        return /* Update */Block.__(0, [/* record */[
                    /* nameInput */value,
                    /* originalName */state[/* originalName */1]
                  ]]);
      });
  } else {
    return (function (state) {
        var value = state[/* nameInput */0];
        if (value === "") {
          return /* Update */Block.__(0, [/* record */[
                      /* nameInput */state[/* originalName */1],
                      /* originalName */state[/* originalName */1]
                    ]]);
        } else {
          return ReasonReactUtils$WonderEditor.updateWithSideEffects(/* record */[
                      /* nameInput */state[/* nameInput */0],
                      /* originalName */value
                    ], (function () {
                        return StateLogicService$WonderEditor.getEditorState((function (param) {
                                      return AssetTreeInspectorUtils$WonderEditor.renameAssetTreeNode(dispatchFunc, value, nodeId, param);
                                    }));
                      }));
        }
      });
  }
}

function render(textureId, param) {
  var send = param[/* send */3];
  return React.createElement("article", {
              key: "TextureInspector",
              className: "wonder-texture-assetTree"
            }, React.createElement("div", {
                  className: ""
                }, React.createElement("h1", undefined, DomHelper$WonderEditor.textEl("Texture")), React.createElement("hr", undefined), React.createElement("div", {
                      className: ""
                    }, React.createElement("span", {
                          className: ""
                        }, DomHelper$WonderEditor.textEl("name:")), React.createElement("input", {
                          className: "input-component float-input",
                          type: "text",
                          value: param[/* state */1][/* nameInput */0],
                          onBlur: (function () {
                              return Curry._1(send, /* BlurName */0);
                            }),
                          onChange: (function (_e) {
                              return Curry._1(send, changeName(_e));
                            })
                        })), React.createElement("div", {
                      className: ""
                    }, renderWarpSSelect(textureId)), React.createElement("div", {
                      className: ""
                    }, renderWarpTSelect(textureId)), React.createElement("div", {
                      className: ""
                    }, renderFilterMagSelect(textureId)), React.createElement("div", {
                      className: ""
                    }, renderFilterMinSelect(textureId))));
}

function make(_, dispatchFunc, name, nodeId, textureId, _$1) {
  return /* record */[
          /* debugName */component[/* debugName */0],
          /* reactClassInternal */component[/* reactClassInternal */1],
          /* handedOffState */component[/* handedOffState */2],
          /* willReceiveProps */component[/* willReceiveProps */3],
          /* didMount */component[/* didMount */4],
          /* didUpdate */component[/* didUpdate */5],
          /* willUnmount */component[/* willUnmount */6],
          /* willUpdate */component[/* willUpdate */7],
          /* shouldUpdate */component[/* shouldUpdate */8],
          /* render */(function (self) {
              return render(textureId, self);
            }),
          /* initialState */(function () {
              return /* record */[
                      /* nameInput */name,
                      /* originalName */name
                    ];
            }),
          /* retainedProps */component[/* retainedProps */11],
          /* reducer */(function (param) {
              return reducer(dispatchFunc, nodeId, param);
            }),
          /* subscriptions */component[/* subscriptions */13],
          /* jsElementWrapped */component[/* jsElementWrapped */14]
        ];
}

export {
  Method ,
  component ,
  reducer ,
  render ,
  make ,
  
}
/* component Not a pure module */
