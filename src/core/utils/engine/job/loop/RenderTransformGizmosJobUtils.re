/* TODO refactor: remove Wonderjs???
   extract RenderEngineService(wonder.js should extract RenderAPI?)


   TODO refactor: not use engineRenderState here!!!(only use engineState)

   */

module RenderTransformGizmos = {
  let prepareGlState = engineState =>
    engineState |> DeviceManagerEngineService.setDepthTest(false);

  let restoreGlState = engineState =>
    engineState |> DeviceManagerEngineService.setDepthTest(true);

  let _getMaterialComponent = (gameObject, engineState) =>
    GameObjectComponentEngineService.getBasicMaterialComponent(
      gameObject,
      engineState,
    );

  let getRenderDataArr =
      (
        gameObjects,
        ({gameObjectRecord}: Wonderjs.StateDataMainType.state) as engineState,
      ) =>
    Wonderjs.(
      gameObjects
      |> WonderCommonlib.ArrayService.reduceOneParam(
           (. renderDataArr, gameObject) => {
             let transform =
               GetComponentGameObjectService.unsafeGetTransformComponent(
                 gameObject,
                 gameObjectRecord,
               );

             switch (
               GetComponentGameObjectService.getGeometryComponent(.
                 gameObject,
                 gameObjectRecord,
               )
               |> Js.Option.andThen((. geometry) =>
                    _getMaterialComponent(gameObject, engineState)
                    |> Js.Option.andThen((. material) =>
                         GetComponentGameObjectService.getMeshRendererComponent(.
                           gameObject,
                           gameObjectRecord,
                         )
                         |> Js.Option.andThen((. meshRenderer) =>
                              Some((
                                transform,
                                material,
                                meshRenderer,
                                geometry,
                              ))
                            )
                       )
                  )
             ) {
             | None => renderDataArr
             | Some(renderData) =>
               renderDataArr |> ArrayService.push(renderData)
             };
           },
           [||],
         )
    );

  let _getShaderIndex = (materialIndex, engineRenderState) =>
    Wonderjs.(
      ShaderIndexRenderService.getShaderIndex(
        materialIndex,
        ShaderIndexBasicMaterialRenderService.getShaderIndex,
        engineRenderState,
      )
    );

  let draw = (gl, renderDataArr, engineRenderState) =>
    Wonderjs.(
      renderDataArr
      |> WonderCommonlib.ArrayService.reduceOneParam(
           (.
             engineRenderState,
             (
               transformIndex,
               materialIndex,
               meshRendererIndex,
               geometryIndex,
             ),
           ) => {
             let shaderIndex =
               _getShaderIndex(materialIndex, engineRenderState);

             let engineRenderState =
               engineRenderState
               |> UseProgramRenderService.useByShaderIndex(gl, shaderIndex);

             let sendRenderDataSubState =
               CreateSendRenederDataSubStateRenderService.createState(
                 engineRenderState,
               );

             /* TODO private??? change to public???*/
             RenderJobUtils._sendAttributeData(
               gl,
               (shaderIndex, geometryIndex),
               sendRenderDataSubState,
               engineRenderState,
             );

             let getRenderDataSubState =
               CreateGetRenederDataSubStateRenderService.createState(
                 engineRenderState,
               );

             let engineRenderState =
               RenderJobUtils._sendUniformRenderObjectModelData(
                 gl,
                 shaderIndex,
                 transformIndex,
                 getRenderDataSubState,
                 engineRenderState,
               )
               |> RenderJobUtils._sendUniformRenderObjectMaterialData(
                    gl,
                    shaderIndex,
                    materialIndex,
                    getRenderDataSubState,
                  );

             engineRenderState
             |> RenderJobUtils.draw(gl, meshRendererIndex, geometryIndex);

             engineRenderState;
           },
           engineRenderState,
         )
    );
};

let _moveAndRotateTranslationWholeGizmoToCurrentSceneTreeNode =
    (currentGameObject, translationWholeGizmo, editorState, engineState) => {
  let currentGameObjectTransform =
    GameObjectComponentEngineService.unsafeGetTransformComponent(
      currentGameObject,
      engineState,
    );
  let translationWholeGizmoTransform =
    GameObjectComponentEngineService.unsafeGetTransformComponent(
      translationWholeGizmo,
      engineState,
    );

  engineState
  |> TransformEngineService.setPosition(
       translationWholeGizmoTransform,
       TransformEngineService.getPosition(
         currentGameObjectTransform,
         engineState,
       ),
     )
  |> TransformEngineService.setEulerAngles(
       translationWholeGizmoTransform,
       TransformEngineService.getEulerAngles(
         currentGameObjectTransform,
         engineState,
       ),
     );
};

let _computeScaleFactorBasedOnDistanceToCamera =
    (cameraPos, currentGameObjectPos) => {
  let factor = 0.03;

  Vector3Service.length(
    Wonderjs.Vector3Service.sub(
      Wonderjs.Vector3Type.Float,
      cameraPos,
      currentGameObjectPos,
    ),
  )
  *. factor;
};

let _scaleTranslationWholeGizmo =
    (currentGameObject, translationWholeGizmo, editorState, engineState) => {
  let cameraGameObject =
    SceneViewEditorService.unsafeGetEditCamera(editorState);

  let factor =
    _computeScaleFactorBasedOnDistanceToCamera(
      TransformGameObjectEngineService.getPosition(
        cameraGameObject,
        engineState,
      ),
      TransformGameObjectEngineService.getPosition(
        currentGameObject,
        engineState,
      ),
    );

  TransformGameObjectEngineService.setLocalScale(
    translationWholeGizmo,
    (factor, factor, factor),
    engineState,
  );
};

let renderJob = (_, engineState) => {
  let editorState = StateEditorService.getState();

  IsTransformGizmoRenderSceneViewEditorService.isTranslationWholeGizmoRender(
    editorState,
  ) ?
    switch (SceneTreeEditorService.getCurrentSceneTreeNode(editorState)) {
    | None => engineState
    | Some(currentGameObject) =>
      let translationWholeGizmo =
        TransformGizmoSceneViewEditorService.unsafeGetTranslationWholeGizmo(
          editorState,
        );

      let engineState =
        engineState
        |> _moveAndRotateTranslationWholeGizmoToCurrentSceneTreeNode(
             currentGameObject,
             translationWholeGizmo,
             editorState,
           )
        |> _scaleTranslationWholeGizmo(
             currentGameObject,
             translationWholeGizmo,
             editorState,
           )
        |> JobEngineService.execUpdateTransformJob;

      let renderDataArr =
        RenderTransformGizmos.getRenderDataArr(
          HierarchyGameObjectEngineService.getAllGameObjects(
            translationWholeGizmo,
            engineState,
          ),
          engineState,
        );
      let gl = DeviceManagerEngineService.unsafeGetGl(engineState);

      let engineState =
        engineState |> RenderTransformGizmos.prepareGlState;

      let engineRenderState =
        Wonderjs.CreateRenderStateMainService.createRenderState(engineState);

      /* TODO refactor: shouldn't operate renderState in editor!!!  */
      let engineRenderState =
        RenderTransformGizmos.draw(gl, renderDataArr, engineRenderState);

      let engineState =
        engineState |> RenderTransformGizmos.restoreGlState;

      engineState;
    } :
    engineState;
};