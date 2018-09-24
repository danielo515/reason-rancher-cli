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

Js.log(
  switch (Docopt.parse(help)) {
  | Upgrade(stack, image) => "Make an upgrade " ++ stack ++ image
  | FinishUpgrade(stack, image) => "Finish upgrade " ++ stack ++ switch image {
  | Service(name) => " service " ++ name
  | Image(name) => " image " ++ name
  };
  | Get(compose, stack) =>
    "Get "
    ++ stack
    ++ (
      switch (compose) {
      | DockerCompose => " Docker compose"
      | RancherCompose => " rancher compose"
      }
    )
  | Config(action) => "Config stuff"
  | Invalid => "Fuck you"
  },
);