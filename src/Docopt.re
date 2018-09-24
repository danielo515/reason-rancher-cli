[@bs.deriving abstract]
type args = {
  /* Upgrade and upgrade-finish options  */
  upgrade: bool,
  [@bs.as "upgrade-finish"]
  upgradeFinish: bool,
  [@bs.as "<stackName>"]
  stackName: string,
  [@bs.as "<imageName>"]
  imageName: Js.nullable(string),
  [@bs.as "<serviceName>"]
  serviceName: string,
  /* Config options */
  config: bool,
  saveEnv: bool,
  print: bool,
  [@bs.as "--environment"]
  enviroment: string,
  get: bool,
  dockerCompose: bool,
  rancherCompose: bool,
};

type stackName = string;
type imageName = string;
type serviceName = string;

type name =
  | Image(imageName)
  | Service(serviceName);

type compose =
  | DockerCompose
  | RancherCompose;

type configActions =
  | SaveEnv
  | Print;

type action =
  | Upgrade(stackName, imageName)
  | FinishUpgrade(stackName, name)
  | Get(compose, stackName)
  | Config(configActions)
  | Invalid;

[@bs.module "docopt"] [@bs.val] external docopt: string => args = "docopt";

let readName = args =>
  switch (Js.toOption(args->imageNameGet)) {
  | Some(name) => Image(name)
  | None => Service(args->serviceNameGet)
  };

let parse = str => {
  let args = docopt(str);
  Js.log(args);
  if (upgradeGet(args)) {
    Upgrade(stackNameGet(args), "pene");
  } else if (upgradeFinishGet(args)) {
    FinishUpgrade(stackNameGet(args), readName(args));
  } else if (configGet(args)) {
    Config(saveEnvGet(args) ? SaveEnv : Print);
  } else if (getGet(args)) {
    Get(
      dockerComposeGet(args) ? DockerCompose : RancherCompose,
      stackNameGet(args),
    );
  } else {
    Invalid;
  };
};