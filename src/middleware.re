let filterMap p s =>
  Most.(
    s
    |> map (fun v => p v)
    |> filter (
         fun v =>
           switch v {
           | Some _payload => Js.true_
           | None => Js.false_
           }
       )
    |> map (fun (Some v) => v)
  );

let searchUrl term =>
  "http://en.wikipedia.org/w/api.php?action=opensearch&format=json&search="
  ^ term
  ^ "&origin=localhost&origin=*";

type fetchReq =
  | Get string
  | Post string Js.Json.t;

let fetch store =>
  Most.(
    store
    |> filterMap (
         fun
         | Get url => Some url
         | _ => None
       )
    |> flatMap (
         fun url => fromPromise Js.Promise.(Bs_fetch.fetch url |> then_ Bs_fetch.Response.json)
       )
  );

let search store =>
  Most.(
    debounce 300 store
    |> filterMap (
         fun actions =>
           switch actions {
           | Actions.TermChange term => Some term
           | _ => None
           }
       )
    |> map (fun term => Get (searchUrl term))
    |> fetch
    |> map Decode.searchResults
    |> map (
         fun payload => {
           let results = payload.(0);
           Actions.SearchResults results
         }
       )
  );