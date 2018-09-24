// Generated by BUCKLESCRIPT VERSION 4.0.5, PLEASE EDIT WITH CARE
'use strict';

var Docopt$ReasonRancherCli = require("./Docopt.bs.js");

var help = "\n rancher-cli\n\n Options can be read from a stored configuration or provided through environment variables.\n If they exist, enviroment variables have preference over stored configurations.\n Accepted env variables are RANCHER_URL, RANCHER_SECRET_KEY, RANCHER_ACCESS_KEY\n\n Usage:\n    rancher-cli upgrade <stackName> <imageName> [-e  <NAME=value>...] [--rancher-env=<name>]\n    rancher-cli upgrade-finish <stackName> (<imageName>|-n <serviceName>)\n    rancher-cli get (dockerCompose|rancherCompose) <stackName> [-o <fileName>] [--rancher-env=<name>]\n    rancher-cli config saveEnv\n    rancher-cli config print\n    rancher-cli -v\n\n\n Options:\n    --rancher-env=<name>            Rancher environment name (stg or int) [default: int]\n    -e --environment <NAME=value>   Adds a new environment variable to the list of already existing environment variables\n    -o --output      <fileName>     Write the result of the command to a file instead of stdout\n    -v --version                    Show the version of the tool\n    -n --name        <serviceName>  Selects a service by name. Can contain asterisk (*) wildcards (ej: 'api-*' )\n";

var match = Docopt$ReasonRancherCli.parse(help);

var tmp;

if (typeof match === "number") {
  tmp = "Fuck you";
} else {
  switch (match.tag | 0) {
    case 0 : 
        tmp = "Make an upgrade " + (match[0] + match[1]);
        break;
    case 1 : 
        var image = match[1];
        var tmp$1;
        tmp$1 = image.tag ? " service " + image[0] : " image " + image[0];
        tmp = "Finish upgrade " + (match[0] + tmp$1);
        break;
    case 2 : 
        tmp = "Get " + (match[1] + (
            match[0] ? " rancher compose" : " Docker compose"
          ));
        break;
    case 3 : 
        tmp = "Config stuff";
        break;
    
  }
}

console.log(tmp);

exports.help = help;
/*  Not a pure module */
