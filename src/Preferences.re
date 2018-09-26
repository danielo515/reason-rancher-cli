[@bs.deriving abstract]
type options = {
  key: option(string),
  encrypt: bool,
};

module type T = { type t; };

module Make = (T:T) => {

    type defaults = option(T.t);

    [@bs.new] [@bs.module] external preferences: (string, defaults, options) => T.t = "";
    
    let read = (~key=?, ~defaults=?, ~encrypt=true, namespace:string) =>
      preferences(namespace, defaults, options(~key, ~encrypt));
}
