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
  let updateSelected id _event => dispatch (Store.Action (Actions.ChangeSelected (Some id)));
  let choose text _event => dispatch (Store.Action (Actions.ChooseSelected text));
  let dispatchKeySelect delta selected event => {
    ReactEventRe.Keyboard.preventDefault event;
    switch selected {
    | Some id => dispatch (Store.Action (Actions.ChangeSelected (Some (id + delta))))
    | None => dispatch (Store.Action (Actions.ChangeSelected (Some 0)))
    }
  };
  let keySelect event =>
    switch (ReactEventRe.Keyboard.key event) {
    | "ArrowDown" => dispatchKeySelect 1 selected event
    | "ArrowUp" => dispatchKeySelect (-1) selected event
    | "Enter" =>
      switch selected {
      | Some id =>
        ReactEventRe.Keyboard.preventDefault event;
        dispatch (Store.Action (Actions.ChooseSelected results.(id)))
      | None => ()
      }
    | _ => ()
    };
  {
    ...component,
    render: fun _self =>
      <div className="App">
        (ReasonReact.stringToElement "Search: ")
        <input
          className="search-bar"
          _type="text"
          value=term
          onChange=updateTerm
          onKeyDown=keySelect
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
                            <li key=text style=selectedStyle onClick=(choose text)>
                              (ReasonReact.stringToElement text)
                            </li>
                          } else {
                            <li key=text onMouseOver=(updateSelected id)>
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