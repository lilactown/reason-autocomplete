type committed =
  | Committed;

type t 'a =
  | Action 'a
  | Thunk (('a => committed) => committed);

let dispatchThunk subject (thunk: ('a => 'committed) => 'committed) =>
  thunk (
    fun action => {
      ignore (Most.Subject.next action subject);
      Committed
    }
  );

let dispatch subject payload =>
  switch payload {
  | Action action => Most.Subject.next action subject |> ignore
  | Thunk thunk => dispatchThunk subject thunk |> ignore
  };

let make ::initialState ::reducer ::middleware=? () => {
  open Most;
  let subject = Subject.make ();
  let store =
    switch middleware {
    | None => Subject.asStream subject |> scan reducer initialState
    | Some mw =>
      let store = Subject.asStream subject;
      let mwStream = mw store;
      merge store mwStream |> tap Js.log |> scan reducer initialState
    };
  let dispatch_ = dispatch subject;
  (store, dispatch_)
};