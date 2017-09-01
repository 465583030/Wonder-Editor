import { Map } from "immutable";
import {ISceneTreeGameObject} from "../interface/ISceneTree";
import {GameObject} from "wonder.js/dist/es2015/core/entityObject/gameObject/GameObject";
import {getSceneChildren} from "../../../logic/adaptorOperator/SceneOper";
import {getSceneTreeDataFromState, saveSceneTreeData} from "../editor/SceneTreeDataEdit";
import {getState} from "../../../logic/editor/StateManagerEdit";
import {hasComponent} from "../../../logic/adaptorOperator/GameObjectOper";
import {CameraController} from "wonder.js/dist/es2015/component/camera/CameraController";

//todo create scene tree data for editor

export const init = (state:Map<any,any>) => {
    var resultState:Map<any,any> = null,
        sceneTreeData = _createSceneTreeData(getSceneChildren());

    resultState = saveSceneTreeData(state,sceneTreeData);

    return resultState;
};

export const getSceneTreeData = () => {
    return getSceneTreeDataFromState(getState());
};

export const registerInit = (state:Map<any, any>) => {
    var registeredInitList:Array<Function> = state.get("registeredInitList");

    registeredInitList.push(init);

    return state.set("registeredInitList", registeredInitList);
};

const _createSceneTreeData = (sceneChildren:Array<GameObject>) => {
    var sceneData:Array<ISceneTreeGameObject> = [];

    sceneChildren.forEach(gameObject => {
        var obj:ISceneTreeGameObject = {
            uid:gameObject.uid,
            name:null
        } as any;

        //todo get gameobject component by uid,store in component array
        //todo recursion children
        if (hasComponent(gameObject,CameraController)){
            obj.name = `mainCamera`;
        }
        else {
            obj.name = `gameobject${gameObject.uid}`;
        }

        sceneData.push(obj);
    });

    return sceneData;
};
