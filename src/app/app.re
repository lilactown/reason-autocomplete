[%bs.raw {|require('./app.css')|}];

let component = ReasonReact.statelessComponent "App";


/**
 * Event Handlers
 */
let handleChangeTerm dispatch event => {
  let newTerm = (ReactDOMRe.domElementToObj (ReactEventRe.Form.target event))##value;
  dispatch (Actions.ChangeTerm newTerm)
};

let handleChangeSelected dispatch id _event => dispatch (Actions.ChangeSelected (Some id));

let handleChoose dispatch text _event => dispatch (Actions.ChooseSelected text);

let keySelectAction delta selected event => {
  ReactEventRe.Keyboard.preventDefault event;
  switch selected {
  | Some id => Actions.ChangeSelected (Some (id + delta))
  | None => Actions.ChangeSelected (Some 0)
  }
};

let handleKeyPress dispatch results selected event =>
  switch (ReactEventRe.Keyboard.key event) {
  | "ArrowDown" => dispatch (keySelectAction 1 selected event)
  | "ArrowUp" => dispatch (keySelectAction (-1) selected event)
  | "Enter" =>
    switch selected {
    | Some id =>
      ReactEventRe.Keyboard.preventDefault event;
      dispatch (Actions.ChooseSelected results.(id))
    | None => ()
    }
  | _ => ()
  };


/**
 * Component
 */
let isSelected selected current =>
  switch selected {
  | Some i => i == current
  | None => false
  };

let selectedStyle = ReactDOMRe.Style.make backgroundColor::"#db4d3f" ();

let make ::term ::results ::selected ::dispatch _children => {
  ...component,
  render: fun _self =>
    <div className="App">
      (ReasonReact.stringToElement "Search: ")
      <input
        className="search-bar"
        _type="text"
        value=term
        onChange=(handleChangeTerm dispatch)
        onKeyDown=(handleKeyPress dispatch results selected)
      />
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
                      fun id text =>
                        if (isSelected selected id) {
                          <li key=text style=selectedStyle onClick=(handleChoose dispatch text)>
                            (ReasonReact.stringToElement text)
                          </li>
                        } else {
                          <li key=text onMouseOver=(handleChangeSelected dispatch id)>
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
};