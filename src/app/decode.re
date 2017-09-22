/**
 * Based on `Json.Decode.pair`
 */
let quadruple first second third fourth json =>
  if (Js.Array.isArray json) {
    let source: array Js.Json.t = Obj.magic (json: Js.Json.t);
    let length = Js.Array.length source;
    if (length == 4) {
      (
        first (Array.unsafe_get source 0),
        second (Array.unsafe_get source 1),
        third (Array.unsafe_get source 2),
        fourth (Array.unsafe_get source 2)
      )
    } else {
      raise
      @@ Json.Decode.DecodeError {j|Expected array of length 2, got array of length $length|j}
    }
  } else {
    raise @@ Json.Decode.DecodeError ("Expected array, got " ^ Js.Json.stringify json)
  };


/**
 * Search results come back in the form
 * ["term", ["Title of each result"], ["First line of each result"], ["URL of each result"]]
 */
let searchResults = Json.Decode.(quadruple string (array string) (array string) (array string));