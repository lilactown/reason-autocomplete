type state = {term: string};

let root (state: state) action =>
  switch action {
  | Actions.TermChange term => {...state, term}
  };