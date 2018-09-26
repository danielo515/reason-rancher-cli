let get: string => option(string) = [%raw (x) => "return process.env[x]"];
[@bs.val] external rancher_url: unit => string = "process.env.RANCHER_URL"