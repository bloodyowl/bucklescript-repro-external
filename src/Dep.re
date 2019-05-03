[@bs.obj] external makeProps: (~message: string, unit) => _ = "";

let make = props => {
  let message = props##message;
  message;
};
