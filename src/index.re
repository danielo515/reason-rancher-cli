let help = "
 rancher-cli

 Options can be read from a stored configuration or provided through environment variables.
 If they exist, enviroment variables have preference over stored configurations.
 Accepted env variables are RANCHER_URL, RANCHER_SECRET_KEY, RANCHER_ACCESS_KEY

 Usage:
    rancher-cli upgrade <stackName> <imageName> [-e  <NAME=value>...] [--rancher-env=<name>]
    rancher-cli upgrade-finish <stackName> (<imageName>|-n <serviceName>)
    rancher-cli get (dockerCompose|rancherCompose) <stackName> [-o <fileName>] [--rancher-env=<name>]
    rancher-cli config saveEnv
    rancher-cli config print
    rancher-cli -v


 Options:
    --rancher-env=<name>            Rancher environment name (stg or int) [default: int]
    -e --environment <NAME=value>   Adds a new environment variable to the list of already existing environment variables
    -o --output      <fileName>     Write the result of the command to a file instead of stdout
    -v --version                    Show the version of the tool
    -n --name        <serviceName>  Selects a service by name. Can contain asterisk (*) wildcards (ej: 'api-*' )
";

[@bs.deriving abstract]
type prefs = {
  mutable user: string,
  mutable pass: string,
  mutable env: string,
  mutable url: string,
};

module Pref =
  Preferences.Make({
    type t = prefs;
  });

let defaults = prefs(~user="", ~pass="", ~env="int", ~url="");

let prefs = Pref.read("com.rancher.cli", ~defaults);

let saveEnv = prefs => {
  open Util;
  withOption(prefs->userSet, Env.get("RANCHER_ACCESS_KEY"));
  withOption(prefs->passSet, Env.get("RANCHER_SECRET_KEY"));
  withOption(prefs->urlSet, Env.get("RANCHER_URL"));
};

switch (Cli.parse(help)) {
| Version => Js.log("This is the current version  ...")
| Upgrade(stack, image) => Rancher.upgrade(stack, image)
| FinishUpgrade(stack, image) => Rancher.upgradeFinish(stack, image)
| Get(compose, stack, outputFile) =>
  Rancher.get(compose, stack);
  Js.log(
    switch (outputFile) {
    | Name(name) => " Output to " ++ name
    | NoFile => " Output to stdout"
    },
  );
| Config(action) =>
  switch (action) {
  | SaveEnv => saveEnv(prefs)
  | Print => Js.log(prefs)
  }
| Invalid => Js.log("Fuck you")
};