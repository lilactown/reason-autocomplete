type state = {
  term: string,
  results: list string
};

let root (state: state) action =>
  switch action {
  | Actions.TermChange term => {...state, term}
  | Actions.SearchResults json => state
  };