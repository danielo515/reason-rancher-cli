[@bs.deriving abstract]
type args = {
  /* Upgrade and upgrade-finish options  */
  upgrade: bool,
  [@bs.as "upgrade-finish"] upgradeFinish: bool,
  [@bs.as "<stackName>"] stackName: string,
  [@bs.as "<imageName>"] imageName: string,
  [@bs.as "<serviceName>"] serviceName: string,
  /* Config options */
  config: bool,  
  saveEnv: bool,
  print: bool,
  [@bs.as "--environment"]
  enviroment: string,
  get: bool,
  dockerCompose: bool,
  rancherCompose: bool
};

type stackName = string;
type imageName = string;
type serviceName = string;

type compose =
  | DockerCompose
  | RancherCompose;

type configActions =
  | SaveEnv
  | Print;

type action =
  | Upgrade(stackName, imageName)
  | FinishUpgrade(stackName, string)
  | Get(compose, stackName)
  | Config(configActions)
  | Invalid;

[@bs.module "docopt"] [@bs.val] external docopt: string => args = "docopt";

let parse = str => {
    let args = docopt(str);
    Js.log(args);
    if (upgradeGet(args))
        Upgrade( stackNameGet(args), "pene" )
    else if (upgradeFinishGet(args))
        FinishUpgrade(stackNameGet(args),imageNameGet(args))
    else if (configGet(args))
        Config( saveEnvGet(args) ? SaveEnv : Print )
    else if (getGet(args))
        Get( dockerComposeGet(args) ? DockerCompose : RancherCompose, stackNameGet(args) )
    else
        Invalid
}