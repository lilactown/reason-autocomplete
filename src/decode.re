external searchResults : Js.Json.t => (string, array string, array string, array string) =
  "%identity";
/*
 let searchResults: Js.Json.t => array (array string) = [%bs.raw
   {|
   ([term, ...results]) => results
 |}
 ]; */