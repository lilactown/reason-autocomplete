type t =
  | ChangeTerm string
  | SearchResults (array string)
  | ChangeSelected (option int)
  | ChooseSelected string;