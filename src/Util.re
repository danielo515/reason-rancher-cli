
let withOption = (f: ('a => unit), o: option('a) ) => switch o {
| Some(a) => f(a)
| None => ()
};