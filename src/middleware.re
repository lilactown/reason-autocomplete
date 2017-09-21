let searchForTerm term => {
  let url =
    "http://en.wikipedia.org/w/api.php?action=opensearch&format=json&search="
    ^ term
    ^ "&origin=localhost&origin=*";
  Js.Promise.(Bs_fetch.fetch url |> then_ Bs_fetch.Response.json)
};

let fetch store =>
  Most.(
    debounce 300 store
    |> filter (
         fun actions =>
           switch actions {
           | Actions.TermChange _term => Js.true_
           | _ => Js.false_
           }
       )
    |> flatMap (
         fun (Actions.TermChange term) =>
           fromPromise (searchForTerm term) |> map (fun json => Actions.SearchResults json)
       )
  );