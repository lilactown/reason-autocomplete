[%bs.raw {|require('./app.css')|}];

let component = ReasonReact.statelessComponent "App";

let make ::term ::results ::dispatch _children => {
  let updateTerm event => {
    let newTerm = (ReactDOMRe.domElementToObj (ReactEventRe.Form.target event))##value;
    dispatch (Store.Action (Actions.TermChange newTerm))
  };
  {
    ...component,
    render: fun _self =>
      <div className="App">
        <input className="search-bar" _type="text" value=term onChange=updateTerm />
        <div>
          <ul>
            (
              ReasonReact.arrayToElement (
                Array.map
                  (fun title => <li key=title> (ReasonReact.stringToElement title) </li>) results
              )
            )
          </ul>
        </div>
      </div>
  }
};