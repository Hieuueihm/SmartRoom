import {
  Button,
  Image,
  StyleSheet,
  Text,
  TextInput,
  View,
  TouchableOpacity,
} from "react-native";
import React, { useState, useEffect } from "react";
import { Dimensions } from "react-native";
import FontAwesome from "react-native-vector-icons/FontAwesome";
import Fontisto from "react-native-vector-icons/Fontisto";
import AntDesign from "react-native-vector-icons/AntDesign";
import { handleLogin } from "../api/userAPI";

import { useNavigation } from "@react-navigation/native";
import Toast from "react-native-toast-message";

import utils from "../utils";
import { ROUTES } from "../../constants";

// Lấy kích thước của màn hình
const screenWidth = Dimensions.get("window").width;
const screenHeight = Dimensions.get("window").height;

const LoginScreen = () => {
  const navigation = useNavigation();

  const [userName, setUserName] = useState("");
  const [password, setPassword] = useState("");

  const handleLoginBtn = async () => {
    // console.log(userName, password);
    if (!userName) {
      utils.Toast.showToast("error", "userName", "Please enter user name");
    } else if (!password) {
      utils.Toast.showToast("error", "password", "Please enter password!");
    } else {
      // console.log(userName, password);
      await handleLogin({
        userName: userName,
        password: password,
      })
        .then((res) => {
          if (res.status === 200 && res.data.success === true) {
            utils.AsyncStorage.storeItem(
              "userId",
              String(res.data.data.userId)
            );

            navigation.navigate(ROUTES.HOMESCREEN);
          } else {
            utils.Toast.showToast(
              "error",
              "login",
              "userName or password incorrect"
            );
          }
        })
        .catch((err) => {
          utils.Toast.showToast("error", "server", "Error from server!");
          console.log(err);
        });
    }
    // navigation.navigate("HOME");
  };
  return (
    <View style={styles.container}>
      <Toast config={utils.Toast.toastConfig} />

      <View style={styles.topImageContainer}>
        <Image
          source={require("../../assets/top_login.png")}
          style={styles.topImage}
        />
      </View>
      <View style={styles.helloContainer}>
        <Text style={styles.helloText}>Hello</Text>
      </View>
      <View>
        <Text style={styles.signInText}>Sign in to your account</Text>
      </View>
      <View style={styles.inputContainer}>
        <FontAwesome
          name={"user"}
          size={24}
          color={"#9A9A9A"}
          style={{ paddingHorizontal: screenWidth / 60 }}
        />
        <TextInput
          style={styles.textInput}
          caretColor="black"
          placeholder="Username"
          placeholderTextColor="#ccc" // Thay đổi màu của placeholder thành màu xám
          onChangeText={(text) => {
            setUserName(text);
          }}
          value={userName}
        />
      </View>

      <View style={styles.inputContainer}>
        <Fontisto
          name={"locked"}
          size={24}
          color={"#9A9A9A"}
          style={{ paddingHorizontal: screenWidth / 60 }}
        />
        <TextInput
          secureTextEntry
          style={styles.textInput}
          caretColor="black"
          placeholder="Password"
          placeholderTextColor="#ccc" // Thay đổi màu của placeholder thành màu xám
          onChangeText={(e) => {
            setPassword(e);
          }}
          value={password}
        />
      </View>
      <View style={styles.signinContainer}>
        <TouchableOpacity
          style={styles.touchableButton}
          onPress={handleLoginBtn}
        >
          <Text style={styles.text}>Sign In</Text>
          <AntDesign name={"arrowright"} style={styles.arrow} />
        </TouchableOpacity>
      </View>
      <View style={styles.topImageContainer}>
        <Image
          source={require("../../assets/bottom_login.png")}
          style={styles.bottomImage}
        />
      </View>
    </View>
  );
};

export default LoginScreen;

const styles = StyleSheet.create({
  container: {
    backgroundColor: "#F5F5F5",
    flex: 1,
    marginTop: screenHeight / 20,
  },
  topImageContainer: { zIndex: -10 },
  topImage: {
    width: "100%",
    height: screenHeight / 6,
  },
  bottomImage: {
    width: "100%",

    marginHorizontal: screenWidth / 3,
    marginTop: screenHeight / 12,
  },
  helloContainer: {},
  helloText: {
    textAlign: "center",
    fontSize: 70,
    fontWeight: "500",
    color: "#262626",
  },
  signInText: {
    textAlign: "center",
    fontSize: 18,
    color: "#262626",
    marginBottom: screenHeight / 20,
  },
  inputContainer: {
    backgroundColor: "#FFFFFF",
    flexDirection: "row",
    borderRadius: 20,
    marginHorizontal: screenHeight / 18,
    elevation: 10,
    marginVertical: screenWidth / 24,
    padding: screenHeight / 60,
  },
  textInput: { flex: 1, color: "black", fontSize: 14 },
  signinContainer: {
    marginTop: screenHeight / 20,
    marginHorizontal: screenWidth / 10,
  },

  touchableButton: {
    backgroundColor: "#009966",
    paddingHorizontal: screenWidth / 18,
    paddingVertical: screenHeight / 80,
    borderRadius: 20,
    shadowColor: "#110000",
    shadowOpacity: 0.5,
    flexDirection: "row",
    justifyContent: "center",
    alignItems: "center",
  },
  text: {
    color: "black",
    fontSize: 24,
    fontWeight: "500",
  },
  arrow: {
    fontSize: 24,
    color: "#110000",
    paddingLeft: screenWidth / 50,
  },
});
