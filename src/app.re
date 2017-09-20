[%bs.raw {|require('./app.css')|}];

let component = ReasonReact.statelessComponent "App";

let make ::term ::dispatch ::message _children => {
  let updateTerm event => {
    let newTerm = (ReactDOMRe.domElementToObj (ReactEventRe.Form.target event))##value;
    dispatch (Actions.TermChange newTerm)
  };
  {
    ...component,
    render: fun self =>
      <div className="App">
        <input className="search-bar" _type="text" value=term onChange=updateTerm />
      </div>
  }
};