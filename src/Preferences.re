[@bs.deriving abstract]
type options = {
  [@bs.optional] file: string,
  [@bs.optional] key: string,
  encrypt: bool,
  format: string,
};

type format =
  | Json
  | Yaml;
let format2str =
  fun
  | Json => "json"
  | Yaml => "yaml";

module type T = {type t;};

module Make = (T: T) => {
  type defaults = option(T.t);

  [@bs.new] [@bs.module]
  external preferences: (string, defaults, options) => T.t = "";

  let read =
      (~key=?, ~defaults=?, ~encrypt=true, ~format=Json, ~file=?, namespace: string) =>
    preferences(
      namespace,
      defaults,
      options(~key?, ~file?, ~encrypt, ~format=format2str(format),()),
    );
};