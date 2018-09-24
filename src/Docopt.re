/* [@bs.deriving jsConverter] */
type args = {.
    upgrade: bool,
    upgradeFinish: bool,
    get: bool,
};

[@bs.module "docopt"] [@bs.val]
external docopt: string => Js.t(args) = "docopt";

let parse = str => docopt(str);