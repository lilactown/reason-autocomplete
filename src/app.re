[%bs.raw {|require('./app.css')|}];

let component = ReasonReact.statelessComponent "App";

let selectedStyle = ReactDOMRe.Style.make backgroundColor::"#db4d3f" ();

let make ::term ::results ::selected ::dispatch _children => {
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
          (
            switch results {
            | [||] => ReasonReact.nullElement
            | results =>
              <ul className="results">
                (
                  ReasonReact.arrayToElement (
                    Array.mapi
                      (
                        fun i title =>
                          if (i == selected) {
                            <li key=title style=selectedStyle>
                              (ReasonReact.stringToElement title)
                            </li>
                          } else {
                            <li key=title> (ReasonReact.stringToElement title) </li>
                          }
                      )
                      results
                  )
                )
              </ul>
            }
          )
        </div>
      </div>
  }
};