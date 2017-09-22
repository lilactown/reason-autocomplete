type state = {
  term: string,
  results: array string,
  selected: option int
};

let root (state: state) action =>
  switch action {
  | Actions.TermChange term => {...state, term}
  | Actions.SearchResults results => {...state, results}
  | Actions.ChangeSelected selected => {...state, selected}
  };