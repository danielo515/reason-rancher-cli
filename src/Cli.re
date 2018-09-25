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
  imageName: Js.nullable(string),
  [@bs.as "<serviceName>"]
  serviceName: string,
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
type outputFile = Name(string) | NoFile;

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
  switch (args->imageNameGet |> Js.toOption) {
  | Some(name) => Image(name)
  | None => Service(args->serviceNameGet)
  };

module D = Docopt.Parser({type t = args})

let parse = str => {
  let args = D.parse(str)
  Js.log(args);
  if (upgradeGet(args)) {
    Upgrade(stackNameGet(args), "pene");
  } else if (upgradeFinishGet(args)) {
    FinishUpgrade(stackNameGet(args), readName(args));
  } else if (configGet(args)) {
    Config(saveEnvGet(args) ? SaveEnv : Print);
  } else if (args->versionGet) {
    Version;
  } else if (getGet(args)) {
    Get(
      dockerComposeGet(args) ? DockerCompose : RancherCompose,
      stackNameGet(args),
      args -> outputGet ? Name(args->fileNameGet) : NoFile
    );
  } else {
    Invalid;
  };
};