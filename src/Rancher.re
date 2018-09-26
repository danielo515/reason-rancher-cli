
let upgrade = (stack,image) => Js.log("Upgrading " ++ stack ++ " using " ++ image );
let upgradeFinish = (stack,_name) => Js.log("Finishing upgrade of " ++ stack );
let get = (_compose,stack) => Js.log("Getting compose file of " ++ stack)