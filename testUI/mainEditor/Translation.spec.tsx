import { shallow} from "enzyme";
import * as React from "react";
import Translation from "../../src/mainEditor/ui/component/Translation";
import * as sinon from "sinon";

describe("Translation Component", () => {
    var ct = null;
    var props = null;
    var sandbox = null;

    beforeEach(()=>{
        sandbox = sinon.sandbox.create();
        props = {
            translate:sandbox.stub()
        };
        ct = shallow(<Translation {...props}/>);
    });
    afterEach(()=>{
        sandbox.restore();
    });

    it("Translation component should have 6 button", () => {
        expect(ct.find("button").length).toEqual(6);
    });
    it("when click button,translate method should be called", function(){
        var btn = ct.find("button").at(0);
        btn.simulate("click");

        expect(props.translate).toCalledOnce();
    });

    describe("test button click,the translate method called with value",function () {
        function testClick(btnIndex,x,y,z){
            var btn = ct.find("button").at(btnIndex);
            btn.simulate("click");

            expect(props.translate).toCalledWith(x,y,z);
        }

        it("when click first button,the x +0.1", function(){
            testClick(0,0.1,0,0);
        });
        it("when click second button,the x -0.1", function(){
            testClick(1,-0.1,0,0);
        });
        it("when click third button,the y +0.1", function(){
            testClick(2,0,0.1,0);
        });
        it("when click fourth button,the y -0.1", function(){
            testClick(3,0,-0.1,0);
        });
        it("when click the fifth button,the z +0.1", function(){
            testClick(4,0,0,0.1);
        });
        it("when click the sixth button,the z -0.1", function(){
            testClick(5,0,0,-0.1);
        });
    })
});
