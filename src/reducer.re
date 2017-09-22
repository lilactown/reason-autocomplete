type state = {
  term: string,
  results: array string
};

let root (state: state) action =>
  switch action {
  | Actions.TermChange term => {...state, term}
  | Actions.SearchResults json => state
  };