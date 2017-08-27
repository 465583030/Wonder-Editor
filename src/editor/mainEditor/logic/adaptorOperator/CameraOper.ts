import { create as createGameObject, addComponent } from "../../adaptor/GameObjectAdaptor";
import {
    setTranslate, perspectiveCamera, setNear, setFar, cameraControll,
    setAspect, setFovy
} from "../../adaptor/CameraAdaptor";
import { GameObject } from "amyjs/dist/es2015/core/Entity/GameObject";
import { Camera } from "amyjs/dist/es2015/Component/Camera/Camera";
import { CameraController } from "amyjs/dist/es2015/Component/Camera/Controll/CameraController";
import { PerspectiveCamera } from "amyjs/dist/es2015/Component/Camera/PerspectiveCamera";

export const createCamera = () => {
    let camera = createGameObject(),
        cameraComponent = createPerspectiveCamera();
    let cameraControll = createCameraControll(cameraComponent);

    setCameraNear(cameraComponent, 1);
    setCameraFar(cameraComponent, 1000);
    setPerspectiveCameraAspect(cameraComponent, 1);
    setPerspectiveCameraFovy(cameraComponent, 45);

    translateCamera(cameraComponent, 0, 0, -3);

    addComponent(camera, cameraControll);

    return camera;
};

export const translateCamera = setTranslate;
export const createPerspectiveCamera = perspectiveCamera;
export const createCameraControll = cameraControll;
export const setCameraNear = setNear;
export const setCameraFar = setFar;
export const setPerspectiveCameraAspect = setAspect;
export const setPerspectiveCameraFovy = setFovy;
