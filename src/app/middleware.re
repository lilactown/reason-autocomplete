let filterMap p s =>
  Most.(
    s
    |> map p
    |> filter (
         fun
         | Some _payload => Js.true_
         | None => Js.false_
       )
    |> map (fun (Some v) => v)
  );

let searchUrl term =>
  "http://en.wikipedia.org/w/api.php?action=opensearch&format=json&search="
  ^ term
  ^ "&origin=localhost&origin=*";


/**
 * Basic `fetch` middleware
 * Simply dispatch a `Get` or `Post` and it fires off a fetch request
 * to the URL.
 */
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


/**
 * More specific `search` middleware
 * Reads in changes to the search input and maps that to
 * the fetch middleware, after which it parses dispatches
 * an action with the new results
 */
let search store =>
  Most.(
    debounce 300 store
    |> filterMap (
         fun
         | Actions.ChangeTerm "" => None
         | Actions.ChangeTerm term => Some term
         | _ => None
       )
    |> map (fun term => Get (searchUrl term))
    |> fetch
    |> map Decode.searchResults
    |> map (fun (_, results, _, _) => Actions.ChangeResults results)
  );