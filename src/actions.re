type t =
  | TermChange string
  | SearchResults (array string)
  | ChangeSelected (option int);