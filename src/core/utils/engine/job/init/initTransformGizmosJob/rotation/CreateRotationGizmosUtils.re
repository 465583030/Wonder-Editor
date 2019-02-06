let _createCircleGeometry = engineState => {
  open Js.Typed_array;

  let radius = DataRotationGizmoSceneViewEditorService.getRadius();
  let segments = 20;

  let rec _generate = ((radius, segments), (vertices, indices), i) =>
    i > segments ?
      (vertices, indices) :
      {
        let rad =
          NumberType.convertIntToFloat(i)
          /. NumberType.convertIntToFloat(segments)
          *. 2.
          *. Js.Math._PI;

        _generate(
          (radius, segments),
          (
            vertices
            |> ArrayService.push(radius *. Js.Math.cos(rad))
            |> ArrayService.push(radius *. Js.Math.sin(rad))
            |> ArrayService.push(0.),
            indices |> ArrayService.push(i),
          ),
          i |> succ,
        );
      };

  let (vertices, indices) = _generate((radius, segments), ([||], [||]), 0);

  let (engineState, geometry) = GeometryEngineService.create(engineState);

  let engineState =
    engineState
    |> GeometryEngineService.setGeometryVertices(
         geometry,
         Float32Array.make(vertices),
       )
    |> GeometryEngineService.setGeometryIndices16(
         geometry,
         Uint16Array.make(indices),
       );

  (engineState, geometry);
};

let _createCircleGizmo = (color, engineState) => {
  let (engineState, geometry) = _createCircleGeometry(engineState);

  let (engineState, gameObject, material, meshRenderer) =
    engineState |> CreateTransformGizmosUtils.createBasicGameObject(geometry);

  let engineState =
    engineState
    |> BasicMaterialEngineService.setColor(color, material)
    |> MeshRendererEngineService.setMeshRendererIsRender(meshRenderer, false)
    |> MeshRendererEngineService.setDrawMode(
         Wonderjs.DrawModeType.Line_strip
         |> Wonderjs.DrawModeType.drawModeToUint8,
         meshRenderer,
       );

  (
    engineState,
    gameObject,
    GameObjectComponentEngineService.unsafeGetTransformComponent(
      gameObject,
      engineState,
    ),
  );
};

let _createCircleGizmos = engineState => {
  let (engineState, yzGizmo, yzGizmoTransform) =
    _createCircleGizmo([|1., 0., 0.|], engineState);
  let (engineState, xzGizmo, xzGizmoTransform) =
    _createCircleGizmo([|0., 1., 0.|], engineState);
  let (engineState, xyGizmo, xyGizmoTransform) =
    _createCircleGizmo([|0., 0., 1.|], engineState);

  let engineState =
    engineState
    |> TransformEngineService.setLocalEulerAngles(
         (0., 90., 0.),
         yzGizmoTransform,
       )
    |> TransformEngineService.setLocalEulerAngles(
         (90., 0., 0.),
         xzGizmoTransform,
       );

  (engineState, (yzGizmo, xzGizmo, xyGizmo));
};

let createRotationGizmos = engineState => {
  let (engineState, (yzGizmo, xzGizmo, xyGizmo)) =
    _createCircleGizmos(engineState);

  let (engineState, wholeGizmo) =
    GameObjectEngineService.create(engineState);

  let engineState =
    engineState
    |> HierarchyGameObjectEngineService.addChild(wholeGizmo, yzGizmo)
    |> HierarchyGameObjectEngineService.addChild(wholeGizmo, xzGizmo)
    |> HierarchyGameObjectEngineService.addChild(wholeGizmo, xyGizmo);

  (engineState, wholeGizmo, (yzGizmo, xzGizmo, xyGizmo));
};