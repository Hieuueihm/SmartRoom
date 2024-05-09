import React, { useState, useEffect } from "react";
import { View, Switch, StyleSheet } from "react-native";

const SwitchButton = (props) => {
  const [isEnabled, setIsEnabled] = useState(false);
  const [handleUpdateState, setHandleUpdateState] = useState(false);

  if (props.updateStateSwitch && handleUpdateState == false) {
    setIsEnabled(props.updateStateSwitch);
    setHandleUpdateState(true);
  }
  const toggleSwitch = () => {
    setIsEnabled((previousState) => !previousState);
    if (props.handleOnPress) {
      props?.handleOnPress(!isEnabled);
    }
  };
  return (
    <Switch
      style={styles.switch}
      trackColor={{ false: "#767577", true: "#81b0ff" }}
      thumbColor={isEnabled ? "#f5dd4b" : "#f4f3f4"}
      ios_backgroundColor="#3e3e3e"
      onValueChange={toggleSwitch}
      value={isEnabled}
    />
  );
};
const styles = StyleSheet.create({
  switch: {
    transform: [{ scaleX: 1.5 }, { scaleY: 1.5 }], // Tăng kích thước nút bấm
  },
});
export default SwitchButton;
