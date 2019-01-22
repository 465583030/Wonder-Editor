let _checkIntersectMesh =
    (ray, (_, _, geometry, localToWorldMatrixTypeArray), engineState) =>
  MeshUtils.checkIntersectMesh(
    (geometry, engineState),
    localToWorldMatrixTypeArray,
    /* TODO judge material->side */
    Back,
    (
      GeometryEngineService.getGeometryVertices(geometry, engineState),
      GeometryEngineService.getGeometryIndices16(geometry, engineState),
      GeometryEngineService.getGeometryIndices32(geometry, engineState),
      GeometryEngineService.getIndicesCount(geometry, engineState),
    ),
    ray,
  )
  |> Js.Option.andThen((. intersectedPoint) =>
       Wonderjs.Vector3Service.transformMat4Tuple(
         intersectedPoint,
         localToWorldMatrixTypeArray,
       )
       |. Some
     );

let _isIntersectSphere =
    (
      ray,
      (_, _, geometry, localToWorldMatrixTypeArray),
      (editorState, engineState),
    ) =>
  RayUtils.isIntersectSphere(
    SphereShapeUtils.applyMatrix4(
      PickingEditorService.unsafeGetSphereShape(geometry, editorState),
      localToWorldMatrixTypeArray,
    ),
    ray,
  );

let _getDistanceToCamera = (intersectedPoint, cameraPos, engineState) =>
  Wonderjs.Vector3Service.sub(
    Wonderjs.Vector3Type.Float,
    intersectedPoint,
    cameraPos,
  )
  |> Vector3Service.length;

let _getTopOne = (cameraGameObject, engineState, intersectedDatas) => {
  let cameraPos =
    TransformEngineService.getPosition(
      GameObjectComponentEngineService.unsafeGetTransformComponent(
        cameraGameObject,
        engineState,
      ),
      engineState,
    );

  intersectedDatas
  |> Js.Array.sortInPlaceWith(
       ((_, intersectedPoint1), (_, intersectedPoint2)) =>
       _getDistanceToCamera(intersectedPoint1, cameraPos, engineState)
       -. _getDistanceToCamera(intersectedPoint2, cameraPos, engineState)
       |> NumberType.convertFloatToInt
     )
  |> ArrayService.getFirst
  |> Js.Option.map((. (gameObject, _)) => gameObject);
};

let _getSceneViewSize = editorState => {
  let (_, _, width, height) =
    SceneViewEditorService.unsafeGetViewRect(editorState);

  (width, height);
};

let _convertMouselocationInViewToNDC =
    ((x, y), (viewWidth, viewHeight))
    : InitPickingJobType.mouseData => {
  x:
    (x |> NumberType.convertIntToFloat)
    /. (viewWidth |> NumberType.convertIntToFloat)
    *. 2.
    -. 1.,
  y:
    1.
    -. (y |> NumberType.convertIntToFloat)
    /. (viewHeight |> NumberType.convertIntToFloat)
    *. 2.,
};

let _getPerspectiveCameraData =
    (cameraGameObject, (editorState, engineState))
    : InitPickingJobType.perspectiveCameraData => {
  cameraToWorldMatrix:
    BasicCameraViewEngineService.getBasicCameraViewWorldToCameraMatrix(
      GameObjectComponentEngineService.unsafeGetBasicCameraViewComponent(
        cameraGameObject,
        engineState,
      ),
      engineState,
    )
    |> Wonderjs.Matrix4Service.invert(
         _,
         Wonderjs.Matrix4Service.createIdentityMatrix4(),
       ),
  projectionMatrix:
    PerspectiveCameraProjectionEngineService.unsafeGetPerspectiveCameraProjectionPMatrix(
      GameObjectComponentEngineService.unsafeGetPerspectiveCameraProjectionComponent(
        cameraGameObject,
        engineState,
      ),
      engineState,
    ),
};

let _getAllGameObjectData = engineState =>
  HierarchyGameObjectEngineService.getAllGameObjects(
    SceneEngineService.getSceneGameObject(engineState),
    engineState,
  )
  |> Js.Array.filter(gameObject =>
       GameObjectComponentEngineService.hasGeometryComponent(
         gameObject,
         engineState,
       )
       && InspectorRenderGroupUtils.hasRenderGroupComponents(
            gameObject,
            engineState,
          )
     )
  |> Js.Array.map(gameObject => {
       let transform =
         GameObjectComponentEngineService.unsafeGetTransformComponent(
           gameObject,
           engineState,
         );
       (
         gameObject,
         transform,
         GameObjectComponentEngineService.unsafeGetGeometryComponent(
           gameObject,
           engineState,
         ),
         TransformEngineService.getLocalToWorldMatrixTypeArray(
           transform,
           engineState,
         ),
       );
     });

let _computeSphereShapeData = (allGameObjectData, (editorState, engineState)) =>
  allGameObjectData
  |> WonderCommonlib.ArrayService.reduceOneParam(
       (. editorState, (_, _, geometry, localToWorldMatrixTypeArray)) =>
         switch (PickingEditorService.getSphereShape(geometry, editorState)) {
         | None =>
           PickingEditorService.setSphereShape(
             geometry,
             SphereShapeUtils.setFromPoints(
               GeometryEngineService.getGeometryVertices(
                 geometry,
                 engineState,
               ),
             ),
             editorState,
           )
         | Some(_) => editorState
         },
       editorState,
     );

let _findPickedOne =
    (
      {userData}: EventType.customEvent,
      allGameObjectData,
      (editorState, engineState),
    ) => {
  let {locationInView}: EventType.pointEvent =
    InitPickingJobType.userDataToPointEvent(
      userData |> OptionService.unsafeGet,
    );

  let cameraGameObject =
    SceneViewEditorService.unsafeGetEditCamera(editorState);

  let (locationInViewX, locationInViewY) = locationInView;

  let ray =
    RayUtils.createPerspectiveCameraRay(
      _convertMouselocationInViewToNDC(
        locationInView,
        _getSceneViewSize(editorState),
      ),
      _getPerspectiveCameraData(
        cameraGameObject,
        (editorState, engineState),
      ),
    );

  allGameObjectData
  |> Js.Array.filter(data =>
       _isIntersectSphere(ray, data, (editorState, engineState))
     )
  |> Js.Array.map(((gameObject, _, _, _) as data) =>
       (gameObject, _checkIntersectMesh(ray, data, engineState))
     )
  |> Js.Array.filter(((_, checkData)) => Js.Option.isSome(checkData))
  |> Js.Array.map(((gameObject, checkData)) =>
       (gameObject, OptionService.unsafeGet(checkData))
     )
  |> _getTopOne(cameraGameObject, engineState);
};

let _isNotNeedPushToHistoryStack = pickedGameObjectOpt =>
  switch (pickedGameObjectOpt) {
  | None =>
    ! (
      SceneTreeEditorService.hasCurrentSceneTreeNode
      |> StateLogicService.getEditorState
    )
  | Some(pickedGameObject) =>
    switch (
      SceneTreeEditorService.getCurrentSceneTreeNode
      |> StateLogicService.getEditorState
    ) {
    | Some(currentGameObject) when currentGameObject === pickedGameObject =>
      true
    | _ => false
    }
  };

let _handleSceneTreeCurrentNodeAndRedoUndo =
    (pickedGameObjectOpt, engineState) => {
  engineState |> StateEngineService.setState |> ignore;

  /* let pickedGameObjectOpt = None; */
  let dispatchFunc = UIStateService.getDispatch();

  _isNotNeedPushToHistoryStack(pickedGameObjectOpt) ?
    SceneTreeSelectCurrentNodeUtils.select(
      dispatchFunc,
      pickedGameObjectOpt,
    ) :
    SceneTreeSelectCurrentNodeEventHandler.MakeEventHandler.pushUndoStackWithNoCopyEngineState(
      (UIStateService.getState(), dispatchFunc),
      (),
      pickedGameObjectOpt,
    );

  StateEngineService.unsafeGetState();
};

let _handlePickSuccess = (gameObject, engineState) =>
  _handleSceneTreeCurrentNodeAndRedoUndo(Some(gameObject), engineState);

let _handlePickFail = engineState =>
  _handleSceneTreeCurrentNodeAndRedoUndo(None, engineState);

let _handlePicking = (event: EventType.customEvent, engineState) => {
  let editorState = StateEditorService.getState();

  let allGameObjectData = _getAllGameObjectData(engineState);

  let editorState =
    _computeSphereShapeData(allGameObjectData, (editorState, engineState));

  let engineState =
    switch (
      (editorState, engineState) |> _findPickedOne(event, allGameObjectData)
    ) {
    | None => _handlePickFail(engineState)
    | Some(gameObject) => _handlePickSuccess(gameObject, engineState)
    };

  (engineState, event);
};

let initJob = (_, engineState) => {
  let engineState =
    ManageEventEngineService.onCustomGlobalEvent(
      ~eventName=EventEditorService.getPointTapEventName(),
      ~handleFunc=
        (. event, engineState) =>
          MouseEventService.isLeftMouseButton(event) ?
            _handlePicking(event, engineState) : (engineState, event),
      ~state=engineState,
      (),
    );

  engineState;
};