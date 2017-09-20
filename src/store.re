type committed =
  | Committed;

let dispatch subject (thunk: ('a => 'committed) => 'committed) =>
  thunk (
    fun action => {
      ignore (Most.Subject.next action subject);
      Committed
    }
  );

let make initialState reducer => {
  open Most;
  let subject = Subject.make ();
  let store = Subject.asStream subject |> scan reducer initialState;
  let dispatch_ = dispatch subject;
  (store, dispatch_)
};