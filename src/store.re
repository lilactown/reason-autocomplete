let dispatch subject action => Most.Subject.next action subject |> ignore;

let make ::initialState ::reducer ::middleware=? () => {
  open Most;
  let subject = Subject.make ();
  let store =
    switch middleware {
    | None => Subject.asStream subject |> scan reducer initialState
    | Some mw =>
      let store = Subject.asStream subject;
      let mwStream = mw store;
      merge store mwStream |> scan reducer initialState
    };
  let dispatch_ = dispatch subject;
  (store, dispatch_)
};