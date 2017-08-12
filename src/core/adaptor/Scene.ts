import {Geometry} from "amyjs/dist/commonjs/Component/Geometry/Geometry";
import {Material} from "amyjs/dist/commonjs/Component/Material/Material";
import {BasicMaterial} from "amyjs/dist/commonjs/Component/Material/BasicMaterial";
import {GameObject} from "amyjs/dist/commonjs/core/Entity/GameObject";
import {MeshRenderer} from "amyjs/dist/commonjs/Component/Render/MeshRender/MeshRenderer";
import {getDirector} from "./Director";
import {PerspectiveCamera} from "amyjs/dist/commonjs/Component/Camera/PerspectiveCamera";
import {CameraController} from "amyjs/dist/commonjs/Component/Camera/Controll/CameraController";
import {Color} from "amyjs/dist/commonjs/Math/Color";
import {TriangleGeometry} from "amyjs/dist/commonjs/Component/Geometry/TriangleGeometry";

export const getScene = () => {
    let director = getDirector();

    return director.scene;
};

export const setColor = (r:number,g:number,b:number,a:number) => {
    let director = getDirector();

    director.renderer.setClearColor(r,g,b,a);
};

export const createCameraObject = () => {
    let camera = GameObject.create(),
        cameraComponent = PerspectiveCamera.create();
    let cameraControll = CameraController.create(cameraComponent);

    cameraComponent.aspect = 1;
    cameraComponent.fovy = 45;
    cameraComponent.near = 1;
    cameraComponent.far = 1000;

    cameraComponent.translate(0,0,-5);

    camera.addComponent(cameraControll);

    return camera;
};

export const createGameObject = (geometry?:Geometry,material?:Material) => {
    let geo = null,
        mat = null;

    if(!!material){
        mat = material;
    }
    else{
        mat = BasicMaterial.create();
        mat.color = Color.create("#ff0000");
        mat.opacity = 1;
    }

    if(!!geometry){
        geo = geometry;
    }
    else{
        geo = TriangleGeometry.create();
    }
    geo.material = mat;

    var obj = GameObject.create();

    obj.addComponent(geo);
    obj.addComponent(MeshRenderer.create());

    return obj;
};

export const addGameObject = (gameObject) => {
    let scene = getScene();

    scene.addChild(gameObject);
};

