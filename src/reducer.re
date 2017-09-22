type state = {
  term: string,
  results: array string,
  selected: option int
};

let root (state: state) action =>
  switch action {
  | Actions.ChangeTerm "" => {...state, term: "", results: [||], selected: None}
  | Actions.ChangeTerm term => {...state, term}
  | Actions.SearchResults results => {...state, results}
  | Actions.ChangeSelected selected => {...state, selected}
  | Actions.ChooseSelected term => {...state, results: [||], selected: None, term}
  };