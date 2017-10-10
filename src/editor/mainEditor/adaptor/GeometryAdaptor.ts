import {
    createCustomGeometry, setCustomGeometryIndices, setCustomGeometryNormals, setCustomGeometryTexCoords,
    setCustomGeometryVertices
} from "wonder.js/dist/es2015/component/geometry/CustomGeometry";

export const createTriangle = () => {
    var geo = createCustomGeometry(),
        {
            vertice,
            texCoord,
            normal,
            indice
        } = _computeData(1, 1);

    setCustomGeometryVertices(geo, vertice);
    setCustomGeometryNormals(geo, normal);
    setCustomGeometryTexCoords(geo, texCoord);
    setCustomGeometryIndices(geo, indice);

    return geo;
};

var _computeData = (width: number, height: number) => {
    var left = -width / 2,
        right = width / 2,
        up = height / 2,
        down = -height / 2,
        vertice = null,
        texCoord = null,
        indice = null,
        normal = null;

    vertice = [
        0.0, up, 0,
        left, down, 0,
        right, down, 0
    ];

    indice = [
        0, 1, 2
    ];

    texCoord = [
        0.5, 1.0,
        0.0, 0.0,
        1.0, 0.0
    ];

    normal = [
        0, 0, 1,
        0, 0, 1,
        0, 0, 1
    ];
    return {
        vertice: vertice,
        texCoord: texCoord,
        normal: normal,
        indice: indice
    };
}

// export const createBox = () => {
//     return BoxGeometry.create();
// };
