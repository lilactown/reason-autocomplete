let searchUrl term =>
  "http://en.wikipedia.org/w/api.php?action=opensearch&format=json&search="
  ^ term
  ^ "&origin=localhost&origin=*";

type fetchReq =
  | Get string
  | Post string Js.Json.t
  | None;

let fetch store =>
  Most.(
    store
    |> filter (
         fun
         | Get _url => Js.true_
         | _ => Js.false_
       )
    |> flatMap (
         fun
         | Get url => fromPromise Js.Promise.(Bs_fetch.fetch url |> then_ Bs_fetch.Response.json)
       )
  );

let search store =>
  Most.(
    debounce 300 store
    |> filter (
         fun actions =>
           switch actions {
           | Actions.TermChange _term => Js.true_
           | _ => Js.false_
           }
       )
    |> map (fun (Actions.TermChange term) => Get (searchUrl term))
    |> fetch
    |> map (fun results => Actions.SearchResults results)
  );