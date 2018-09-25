[@bs.deriving abstract]
type args = {
  [@bs.as "--version"]
  version: bool,
  /* Upgrade and upgrade-finish options  */
  upgrade: bool,
  [@bs.as "upgrade-finish"]
  upgradeFinish: bool,
  [@bs.as "<stackName>"]
  stackName: string,
  [@bs.as "<imageName>"]
  imageName: string,
  [@bs.as "<serviceName>"]
  serviceName: Js.nullable(string),
  [@bs.as "--environment"]
  enviroment: string,
  /* Config options */
  config: bool,
  saveEnv: bool,
  print: bool,
  /* Read compose files */
  get: bool,
  dockerCompose: bool,
  rancherCompose: bool,
  [@bs.as "--output"]
  output: bool,
  [@bs.as "<fileName>"]
  fileName: string,
};

type stackName = string;
type imageName = string;
type serviceName = string;
type outputFile =
  | Name(string)
  | NoFile;

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
  | Get(compose, stackName, outputFile)
  | Config(configActions)
  | Version
  | Invalid;

let readName = args =>
  switch (args->serviceNameGet |> Js.toOption) {
  | Some(name) => Service(name)
  | None => Image(args->imageNameGet)
  };

module D =
  Docopt.Parser({
    type t = args;
  });

let parse = str => {
  let args = D.parse(str);
  Js.log(args);
  switch (args) {
  | args when args->upgradeGet =>
    Upgrade(stackNameGet(args), args->imageNameGet)
  | args when args->upgradeFinishGet =>
    FinishUpgrade(stackNameGet(args), readName(args))
  | args when args->configGet => Config(saveEnvGet(args) ? SaveEnv : Print)
  | args when args->versionGet => Version
  | args when args->getGet =>
    Get(
      dockerComposeGet(args) ? DockerCompose : RancherCompose,
      stackNameGet(args),
      args->outputGet ? Name(args->fileNameGet) : NoFile,
    )
  | _ => Invalid
  };
};