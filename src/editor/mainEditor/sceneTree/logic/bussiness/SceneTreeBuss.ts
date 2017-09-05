import { Map } from "immutable";
import { ISceneTreeGameObject } from "../interface/ISceneTree";
import { GameObject } from "wonder.js/dist/es2015/core/entityObject/gameObject/GameObject";
import { getSceneChildren } from "../../../logic/adaptorOperator/SceneOper";
import { getSceneTreeDataFromState, saveSceneTreeData } from "../editor/SceneTreeDataEdit";
import { getState, setState } from "../../../logic/editor/StateManagerEdit";
import { getChildren, hasComponent } from "../../../logic/adaptorOperator/GameObjectOper";
import { CameraController } from "wonder.js/dist/es2015/component/camera/CameraController";

//todo create scene tree data for editor

export const init = (state: Map<any, any>) => {
    var resultState: Map<any, any> = state,
        sceneTreeData = _createSceneTreeData(getSceneChildren());

    resultState = saveSceneTreeData(resultState, sceneTreeData);

    return resultState;
};

export const setSceneTreeData = (sceneTreeData: ISceneTreeGameObject[]) => {
    var resultState: Map<any, any> = getState();

    resultState = saveSceneTreeData(resultState, sceneTreeData);

    setState(resultState);
};

export const getSceneTreeData = () => {
    return getSceneTreeDataFromState(getState());
};

export const registerInit = (state: Map<any, any>) => {
    var registeredInitList: Array<Function> = state.get("registeredInitList");

    registeredInitList.push(init);

    return state.set("registeredInitList", registeredInitList);
};

export const dragTreeNode = (draggedId:number,targetId:number,sceneTreeData:ISceneTreeGameObject[]) => {
    var data = [...sceneTreeData],
        dragObj = null;

    const iterateSceneGraph = (data: Array<ISceneTreeGameObject>, uid: number, callback: Function) => {
        data.forEach((item, index, arr) => {
            if (item.uid === uid) {
                return callback(item, index, arr);
            }
            if (item.children) {
                return iterateSceneGraph(item.children, uid, callback);
            }
        });
    };

    const removeFromParent = (item, index, arr) => {
        arr.splice(index, 1);
        dragObj = item;
    };

    const insertToTarget = (item, index, arr) => {
        item.children = item.children || [];
        item.children.push(dragObj);
    };

    iterateSceneGraph(data, draggedId, removeFromParent);
    iterateSceneGraph(data, targetId, insertToTarget);

    return data;
};

const _createSceneTreeData = (sceneGameObjects: Array<GameObject>) => {
    var sceneData: Array<ISceneTreeGameObject> = [];

    sceneGameObjects.forEach(gameObject => {
        var children: any = null,
            obj: ISceneTreeGameObject = {
                uid: gameObject.uid,
                name: null
            } as any;

        //todo get gameobject component by uid,store in component array
        if (hasComponent(gameObject, CameraController)) {
            obj.name = `mainCamera`;
        }
        else {
            obj.name = `gameObject${gameObject.uid}`;
        }

        children = getChildren(gameObject);

        if (children !== void 0 && children.length !== 0) {
            obj.children = _createSceneTreeData(children);
        }

        sceneData.push(obj);
    });

    return sceneData;
};