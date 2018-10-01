open Axios;

type client = {
  axios: Instance.t,
  env: string,
};

/* type conf = {
       user: string,
       pass: string,
       url: string
   }; */

let client = (~user, ~pass, ~url, env) => {
  env,
  axios:
    makeConfig(
      ~baseURL=url,
      ~withCredentials=true,
      ~auth={"username": user, "password": pass},
      (),
    )
    |> Instance.create,
};

let findByName = (~name) =>
  Js.Array.find(s => Js.String.(toLowerCase(s##name) == toLowerCase(name)));

let usesImage = (~image) =>
  Js.Array.filter(
    Js.String.(
      x => x##launchConfig##imageUuid |> toLowerCase |> endsWith(image)
    ),
  );

let getStacks = client =>
  Js.Promise.(
    Instance.get(client.axios, "v2-beta/projects?name=" ++ client.env)
    |> then_(x =>
         x##data##data[0]##links##stacks |> Instance.get(client.axios)
       )
    |> then_(x => x##data)
  );

let findStack = (~client, stackName) => {
  open Js.Promise;
  getStacks(client)
  |> then_(x =>
       x##data
       |> findByName(~name=stackName)
       |> Belt.Option.getExn
       |> (st => st##links##services |> Instance.get(client.axios))
  )
};

let upgrade = (~stack, ~image, client) => {
  open Js.Promise;
  Js.log("Upgrading " ++ stack ++ " using " ++ image ++ " image");
  findStack(~client, stack)
  |> then_(x =>
       x##data##data
       |> usesImage(~image)
       |> (x => Belt.Result.Ok(x) |> resolve)
     )
  |> catch(_err =>
       Belt.Result.Error(
         "Can not find stack -" ++ stack ++ "- containing service with " ++ image,
       )
       |> resolve
     );
};
let upgradeFinish = (~client, ~stack, _name) => {
  open Js.Promise;
  Js.log("Finishing upgrade of " ++ stack);
  getStacks(client) |> then_(x => Js.log2("Stacks", x) |> resolve);
};
let compose = (_compose, stack) =>
  Js.log("Getting compose file of " ++ stack);