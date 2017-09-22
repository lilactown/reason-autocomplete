[%bs.raw {|require('./index.css')|}];

external register_service_worker : unit => unit =
  "default" [@@bs.module "./registerServiceWorker"];

let initialState: Reducer.state = {term: "", results: [||], selected: None};

let (store, dispatch) =
  Store.make ::initialState reducer::Reducer.root middleware::Middleware.search ();

let obs =
  Most.observe
    (
      fun (state: Reducer.state) =>
        ReactDOMRe.renderToElementWithId
          <App term=state.term results=state.results selected=?state.selected dispatch /> "root"
    )
    store;

register_service_worker ();