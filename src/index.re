[%bs.raw {|require('./index.css')|}];

external register_service_worker : unit => unit =
  "default" [@@bs.module "./registerServiceWorker"];

let initialState: Reducer.state = {term: ""};

let (store, dispatch) =
  Store.make ::initialState reducer::Reducer.root middleware::Middleware.search ();

let obs =
  Most.observe
    (
      fun (state: Reducer.state) => {
        Js.log state.term;
        ReactDOMRe.renderToElementWithId <App term=state.term dispatch /> "root"
      }
    )
    store;

register_service_worker ();