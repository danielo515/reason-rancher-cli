module type T = {
    type t;
};
    
module Parser = (T:T) => {

    
    [@bs.deriving abstract]
    type options = {
        help: bool,
        /* version: Js.nullable(string), */
        options_first: bool,
        exit: bool,
    };
    
    [@bs.module "docopt"] [@bs.val]
    external docopt: (string, options) => T.t = "docopt";
    
    let parse = (~help=true, ~options_first=false, ~exit=true, doc) =>
    docopt(doc, options(~help, ~options_first, ~exit));
}