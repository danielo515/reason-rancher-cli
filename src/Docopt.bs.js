// Generated by BUCKLESCRIPT VERSION 4.0.5, PLEASE EDIT WITH CARE
'use strict';

var Block = require("bs-platform/lib/js/block.js");
var Docopt = require("docopt");

function readName(args) {
  var match = args["<imageName>"];
  if (match == null) {
    return /* Service */Block.__(1, [args["<serviceName>"]]);
  } else {
    return /* Image */Block.__(0, [match]);
  }
}

function parse(str) {
  var args = Docopt.docopt(str);
  console.log(args);
  if (args.upgrade) {
    return /* Upgrade */Block.__(0, [
              args["<stackName>"],
              "pene"
            ]);
  } else if (args["upgrade-finish"]) {
    return /* FinishUpgrade */Block.__(1, [
              args["<stackName>"],
              readName(args)
            ]);
  } else if (args.config) {
    var match = args.saveEnv;
    return /* Config */Block.__(3, [match ? /* SaveEnv */0 : /* Print */1]);
  } else if (args.get) {
    var match$1 = args.dockerCompose;
    return /* Get */Block.__(2, [
              match$1 ? /* DockerCompose */0 : /* RancherCompose */1,
              args["<stackName>"]
            ]);
  } else {
    return /* Invalid */0;
  }
}

exports.readName = readName;
exports.parse = parse;
/* docopt Not a pure module */
