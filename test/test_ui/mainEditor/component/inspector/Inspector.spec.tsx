import { shallow } from "enzyme";
import * as React from "react";
import * as sinon from "sinon";
import {getDom, getDomAttribute} from "../../tool/domTool";
import Inspector from "../../../../../src/editor/mainEditor/component/inspector/ui/Inspector";
import {EComponentType} from "../../../../../src/editor/mainEditor/enum/EComponentType";

describe("Inspector Component", () => {
    var ct = null,
        props = null,
        sandbox = null;

    beforeEach(()=>{
        sandbox = sinon.sandbox.create();

        props = {
            currentGameObjectId:-1,
            getAllComponentData:sandbox.stub()
        };
        ct = shallow(<Inspector {...props}/>);
    });
    afterEach(()=>{
        sandbox.restore();
    });

    describe("test container", function(){
        var articles;

        var getArticle = (ct) => getDom(ct,"article");

        beforeEach(function(){
            articles = getArticle(ct);
        });

        describe("test dom", function(){
            var article;

            beforeEach(function(){
                article = articles.at(0);
            });

            it("test should add a article as container", function(){
                expect(articles.length).toEqual(1);
                expect(article).not.toBeUndefined();
            });
            it("test className", function(){
                expect(getDomAttribute(article,"className")).toEqual("main-inspector");
            });
            it("test style",function () {
                expect(getDomAttribute(article,"style").width).toEqual("15%");
            })
        });
    });

    describe("test render component by gameObject", function(){
        var setGameObjectComponents = (gameObjectId:number,components) =>{
            props = {
                currentGameObjectId:gameObjectId,
                getAllComponentData:sandbox.stub().returns(components)
            };
            ct = shallow(<Inspector {...props}/>);
        };

        describe("if has current gameObject", function(){
            describe("show its all components", function(){
                it("test if has transform component", function(){
                    setGameObjectComponents(1,[
                        {type:EComponentType.TRANSFORM,component:{index:0,uid:0}}
                    ]);

                    expect(getDom(ct,"Transform").length).toEqual(1);
                });
                it("test if has material component", function(){
                    setGameObjectComponents(1,[
                        {type:EComponentType.MATERIAL,component:{index:1}}
                    ]);

                    expect(getDom(ct,"Material").length).toEqual(1);
                });
                it("test if has transform and material component", function(){
                    setGameObjectComponents(1,[
                        {type:EComponentType.TRANSFORM,component:{index:0,uid:0}},
                        {type:EComponentType.MATERIAL,component:{index:1}},
                    ]);

                    expect(getDom(ct,"Transform").length).toEqual(1);
                    expect(getDom(ct,"Material").length).toEqual(1);
                });
            });
        });
        
        describe("else", function(){
            var showNoComponents = () => {
                expect(getDom(ct,"Transform").length).toEqual(0);
                expect(getDom(ct,"Material").length).toEqual(0);
            };

            it("not show components, only show split component", function(){
                setGameObjectComponents(1,[
                ]);

                showNoComponents();
                expect(getDom(ct,"Split").length).toEqual(1);
            });
        });
    });

    describe("test Split", function(){
        var splits,
            split;

        beforeEach(function(){
            splits = getDom(ct,"Split");
            split = splits.at(0);
        });

        describe("test dom", function(){
            it("has one split component", function(){
                expect(splits).not.toBeUndefined();
                expect(splits.length).toEqual(1);
            });
            it("should position left", function(){
                expect(getDomAttribute(split, "position")).toEqual("left");
            });
            it("test min,max", function(){
                expect(getDomAttribute(split, "minPercent")).toEqual(15);
                expect(getDomAttribute(split, "maxPercent")).toEqual(25);
            });
        });
    });
});