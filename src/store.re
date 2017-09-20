let make initialState reducer => {
  open Most;
  let subject = Subject.make ();
  let store = Subject.asStream subject |> scan reducer initialState;
  let dispatch action => Subject.next action subject |> ignore;
  (store, dispatch)
};