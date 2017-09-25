import * as React from "react";
import { addName } from "../../../../../../../../typescript/decorator";
import { buildFieldUIComponent } from "../../../../../config/ComponentFieldParseSystem";

interface IProps {
    component:any;
    translate: Function;
}

@addName("Translation")
export default class Translation extends React.Component<IProps, any>{
    constructor(props: IProps) {
        super(props);
    }

    setX(value: number) {
        this.props.translate(this.props.component,value, 0, 0);
    }

    setY(value: number) {
        this.props.translate(this.props.component,0, value, 0);
    }

    setZ(value: number) {
        this.props.translate(this.props.component,0, 0, value);
    }

    render() {
        // var fieldConfig = this.props.fieldConfig;
        //
        // var fieldArr = buildField(fieldConfig);
        //
        // //todo replace <button>s with fieldArr

        return (
            <article className="translation">
                <p>translate:</p>
                <button onClick={() => this.setX(0.1)}>x:+0.1</button>
                <button onClick={() => this.setX(-0.1)}>x:-0.1</button>
                <button onClick={() => this.setY(0.1)}>y:+0.1</button>
                <button onClick={() => this.setY(-0.1)}>y:-0.1</button>
                <button onClick={() => this.setZ(0.1)}>z:+0.1</button>
                <button onClick={() => this.setZ(-0.1)}>z:-0.1</button>
            </article>
        )
    }
}
