type t =
  | ChangeTerm string
  | ChangeResults (array string)
  | ChangeSelected (option int)
  | ChooseSelected string;