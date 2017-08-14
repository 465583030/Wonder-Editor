import "rxjs/add/operator/mergeMap";
import "rxjs/add/operator/map";
import "rxjs/add/operator/delay";
import {ajax} from "rxjs/observable/dom/ajax";
import {
    REQUEST, receivePosts, POSITIONX, POSITIONY, POSITIONZ, ANGLE,
    RESET
} from "../action/Action";
import {ExtendUtils} from "wonder-commonlib/dist/commonjs/utils/ExtendUtils";

export const postsEpic = (action$:any) => (
        action$.ofType(REQUEST)
            .mergeMap( (action:any) => {
                return ajax.getJSON(action.url)
                    .map(response => receivePosts(response));
            })
    );


export const position = (state = {x:0,y:0,z:0},action:any)=>{
    var assign = ExtendUtils.assign;

    switch (action.type){
        case POSITIONX : return assign(state,{x:action.num,y:0,z:0});
        case POSITIONY : return assign(state,{y:action.num,x:0,z:0});
        case POSITIONZ : return assign(state,{z:action.num,x:0,y:0});
        case RESET:return null;
        default : return state;
    }
};

export const angle = (state = 0,action:any)=>{
    switch (action.type){
        case ANGLE:return state+action.num;
        case RESET:return null;
        default:return state;
    }
};

