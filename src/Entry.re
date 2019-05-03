module LazyComponent1 = {
  module type TT = (module type of Dep);
  [@bs.val] external import: string => Js.Promise.t(module TT) = "";

  [@bs.module "react"]
  external lazy_: (unit => Js.Promise.t('a)) => 'a = "lazy";
  // needed until bs's module shape is unified
  [@bs.val] [@bs.scope "Object"] external values: 'a => 'b = "values";

  let makeProps = Dep.makeProps;
  let make =
    lazy_(() =>
      import("./Component1.bs.js")
      |> Js.Promise.then_((res: (module TT)) => {
           module Res = (val res->Obj.magic##default->values->Obj.magic: TT);
           Js.Promise.resolve({"default": Res.make}->Obj.magic);
         })
    );
};
