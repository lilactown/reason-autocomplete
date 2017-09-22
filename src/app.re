[%bs.raw {|require('./app.css')|}];

let component = ReasonReact.statelessComponent "App";

let selectedStyle = ReactDOMRe.Style.make backgroundColor::"#db4d3f" ();

let isSelected selected current =>
  switch selected {
  | Some i => i == current
  | None => false
  };

let make ::term ::results ::selected ::dispatch _children => {
  let updateTerm event => {
    let newTerm = (ReactDOMRe.domElementToObj (ReactEventRe.Form.target event))##value;
    dispatch (Store.Action (Actions.ChangeTerm newTerm))
  };
  let updateSelected i _event => dispatch (Store.Action (Actions.ChangeSelected (Some i)));
  let choose text _event => dispatch (Store.Action (Actions.ChooseSelected text));
  {
    ...component,
    render: fun _self =>
      <div className="App">
        (ReasonReact.stringToElement "Search: ")
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
                        fun i text =>
                          if (isSelected selected i) {
                            <li key=text style=selectedStyle onClick=(choose text)>
                              (ReasonReact.stringToElement text)
                            </li>
                          } else {
                            <li key=text onMouseOver=(updateSelected i)>
                              (ReasonReact.stringToElement text)
                            </li>
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