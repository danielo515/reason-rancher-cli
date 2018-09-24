[@bs.module "docopt"] [@bs.val]
external docopt: string => Js.t({..}) = "docopt";

let parse = docopt;