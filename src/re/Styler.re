open Belt;

[%bs.raw {|require('./Styler.css')|}];

type state = {index: int};

type action =
  | Increment
  | Decrement;

let component = ReasonReact.reducerComponent("Styler");
let make =
    (
      ~id,
      ~label,
      ~colors,
      ~styles,
      ~selectedColor,
      ~selectedStyle,
      ~onSelectColor,
      _children,
    ) => {
  ...component,
  initialState: () => {index: 0},
  reducer: (action, state) =>
    switch (action) {
    | Increment =>
      let inc =
        List.length(styles) - 1 > state.index ?
          1 : - List.length(styles) + 1;
      ReasonReact.Update({...state, index: state.index + inc});
    | Decrement =>
      let inc = state.index > 0 ? 1 : - List.length(styles) - 1;
      ReasonReact.Update({...state, index: state.index - inc});
    },
  render: ({send, state}) => {
    let colorItems =
      List.map(colors, color =>
        <ColorSwatch
          value=color
          disabled={color === "#EEEFF5"}
          selected={color === selectedColor}
          onSelect={value => onSelectColor(value)}
        />
      );
    let style = List.get(styles, state.index);
    let svgSource = {j|/avatars/$id/$style|j};

    <div className="Styler-container">
      <span className="Styler-label"> {ReasonReact.string(label)} </span>
      <div className="Styler-picker">
        <button className="Styler-btn" onClick={_ => send(Decrement)}>
          <img className="Styler-arrow" src="/images/arrow.svg" />
        </button>
        <div className="Styler-model">
          <img width="64" height="64" src=svgSource />
        </div>
        <button className="Styler-btn" onClick={_ => send(Increment)}>
          <img
            className="Styler-arrow Styler-arrow--right"
            src="/images/arrow.svg"
          />
        </button>
      </div>
      <div className="Styler-colors">
        {ReasonReact.array(List.toArray(colorItems))}
      </div>
    </div>;
  },
};