let _calcXScroll =
    (
      sceneTreeContainderJsObj,
      sceneTreeNodeDomOffsetLeft,
      (sceneTreeContainerScrollLeft, sceneTreeContainerOffsetWidth),
    ) =>
  sceneTreeNodeDomOffsetLeft -. sceneTreeContainerScrollLeft <= 10. ?
    {
      let distance =
        sceneTreeNodeDomOffsetLeft <= 100. ?
          0.0 : sceneTreeNodeDomOffsetLeft /. 2.;

      sceneTreeContainderJsObj##scrollLeft#=distance;
    } :
    sceneTreeNodeDomOffsetLeft >= sceneTreeContainerScrollLeft
    +. sceneTreeContainerOffsetWidth
    -. 45. ?
      sceneTreeContainderJsObj##scrollLeft#=(
                                              sceneTreeNodeDomOffsetLeft -. 60.
                                            ) :
      ();

let scrollCurrentSceneTreeNode = (isSelected, gameObject) =>
  isSelected ?
    {
      let sceneTreeContainerDomElement =
        DomHelper.getElementById("wonder-sceneTree-component");
      let sceneTreeNodeDomElement =
        DomHelper.getElementById({j|sceneTreeNode-$gameObject|j});

      let sceneTreeContainderJsObj =
        sceneTreeContainerDomElement |> DomHelperType.convertDomElementToJsObj;

      let sceneTreeContainerScrollTop = sceneTreeContainderJsObj##scrollTop;

      let sceneTreeContainerScrollLeft = sceneTreeContainderJsObj##scrollLeft;

      let sceneTreeContainerOffsetWidth = sceneTreeContainderJsObj##offsetWidth;

      let sceneTreeContainerOffsetHeight = sceneTreeContainderJsObj##offsetHeight;

      let sceneTreeNodeDomClientRect =
        DomHelper.getDomClientRect(sceneTreeNodeDomElement);
      let sceneTreeNodeDomOffsetTop = sceneTreeNodeDomClientRect##offsetTop;
      let sceneTreeNodeDomOffsetLeft = sceneTreeNodeDomClientRect##offsetLeft;

      _calcXScroll(
        sceneTreeContainderJsObj,
        sceneTreeNodeDomOffsetLeft,
        (sceneTreeContainerScrollLeft, sceneTreeContainerOffsetWidth),
      );
    } :
    ();