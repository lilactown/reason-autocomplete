type committed =
  | Committed;

let make initialState reducer => {
  open Most;
  let subject = Subject.make ();
  let store = Subject.asStream subject |> scan reducer initialState;
  /* let dispatch action => Subject.next action subject |> ignore; */
  let dispatch (thunk: ('a => 'committed) => 'committed) =>
    thunk (
      fun action => {
        ignore (Subject.next action subject);
        Committed
      }
    );
  (store, dispatch)
};