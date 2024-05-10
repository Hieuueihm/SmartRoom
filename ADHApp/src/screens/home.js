import React, { useState, useEffect } from "react";
import {
  ScrollView,
  Text,
  View,
  Image,
  TouchableOpacity,
  ImageBackground,
} from "react-native";
import { fetchWeatherForecast } from "../api/weatherAPI";
import { Dimensions } from "react-native";
import { StyleSheet } from "react-native";
const screenWidth = Dimensions.get("window").width;
const screenHeight = Dimensions.get("window").height;
import Toast from "react-native-toast-message";
import { handleGetUserById } from "../api/userAPI";

import utils from "../utils";
import AntDesign from "react-native-vector-icons/AntDesign";
import { useNavigation } from "@react-navigation/native";
import { ROUTES } from "../../constants";
import { LinearGradient } from "expo-linear-gradient";
import Ionicons from "react-native-vector-icons/Ionicons";
import SwitchButton from "./switch";
import Slider from "@react-native-community/slider";
// import CircularSlider from "./circularSlider";
import init from "react_native_mqtt";
import AsyncStorage from "@react-native-async-storage/async-storage";

export default function HomeScreen() {
  const navigation = useNavigation();

  const daysOfWeek = [
    "Sunday",
    "Monday",
    "Tuesday",
    "Wednesday",
    "Thursday",
    "Friday",
    "Saturday",
  ];
  const monthsOfYear = [
    "January",
    "February",
    "March",
    "April",
    "May",
    "June",
    "July",
    "August",
    "September",
    "October",
    "November",
    "December",
  ];
  const currentTime = new Date();
  currentTime.setUTCHours(currentTime.getUTCHours());
  const year = currentTime.getFullYear(); // năm
  const month = currentTime.getMonth(); // tháng
  const dayOfmonth = currentTime.getDate(); // ngày trong tháng
  const day = currentTime.getDay(); // Thứ trong tuần, nhưng tra ve cac gia tri 0-6
  const dayName = daysOfWeek[day]; // Chuyen tu du lieu số sang thứ trong tuần
  const monthName = monthsOfYear[month];
  const [weather, setWeather] = useState({});
  const [userId, setUserId] = useState();
  const [userData, setUserData] = useState("");
  const [isVisible, setIsVisible] = useState(false);
  const [conn, setConn] = useState(false);

  const [slider, setSlider] = useState(0);
  useEffect(() => {
    getAllData();
    getCurrentUser();
    client.onConnectionLost = onConnectionLost;
    client.onMessageArrived = onMessageArrived;
    // onConnect();
    client.connect({
      onSuccess: () => {
        console.log("success");

        client.subscribe("/topic/qos0", { qos: 0 });
        setConn(true);
        const message = new Paho.MQTT.Message(options.id + ":" + "dcmm");
        message.destinationName = "/topic/abc";
        client.send(message);
      },
      useSSL: false,
      onFailure: (e) => {
        console.log("here is the error", e);
      },
    });

    return () => {
      clearInterval(timeIntervalGetStateData);
      client.disconnect();
    };
  }, []);

  const fetchWeatherAndCO2 = () => {
    setIsVisible(!isVisible);
  };

  useEffect(() => {
    const intervalId = setInterval(() => {
      fetchWeatherAndCO2();
    }, 3000);
    return () => clearInterval(intervalId);
  }, [isVisible]);

  const getCurrentUser = async () => {
    const userId1 = await utils.AsyncStorage.getItem("userId");
    setUserId(userId1);

    await handleGetUserById({
      userId: userId1,
    })
      .then((res) => {
        if (res && res.status == 200 && res?.data?.success == true) {
          setUserData(res?.data?.data);
        }
      })
      .catch((err) => {
        console.log(err);
      });
  };
  const getAllData = () => {
    {
      fetchWeatherForecast({ cityName: "Hanoi", days: "7" }).then((data) => {
        setWeather(data);
      });
    }
  };
  init({
    size: 10000,
    storageBackend: AsyncStorage,
    defaultExpires: 1000 * 3600 * 24,
    enableCache: true,
    reconnect: true,
    sync: {},
  });
  const options = {
    host: "broker.hivemq.com",
    port: 8000,
    id: "id_" + parseInt(Math.random() * 100000),
  };
  const client = new Paho.MQTT.Client(options.host, options.port, options.id);

  const timeIntervalGetStateData = setInterval(() => {
    getAllData();
  }, 100000);

  function onConnectionLost(responseObject) {
    if (responseObject.errorCode !== 0) {
      console.log("onConnectionLost:" + responseObject.errorMessage);
    }
  }

  function onMessageArrived(message) {
    console.log("onMessageArrived:" + message.payloadString);
  }
  const onFail = () => {
    console.log("faile");
  };

  if (weather) {
    var { current, location, forecast } = weather;
  }

  return (
    <ScrollView style={styles.container}>
      {/*-------------------------------------- top view------------------------------------------------- */}

      <Toast config={utils.Toast.toastConfig} />

      <View style={styles.topViewContainer}>
        <View style={styles.dateAndNameTopView}>
          <Text
            style={{
              color: "#000000",
              fontSize: 18,
              fontStyle: "italic",
              fontWeight: 700,
            }}
          >
            Hello, {userData?.fullName}
          </Text>
          <Text style={{ color: "#000000", fontSize: 22 }}>
            {dayName}, {dayOfmonth} {monthName} {year}
          </Text>
          <View
            style={{
              flex: 1,
              flexDirection: "row",
              justifyContent: "flex-start",
            }}
          >
            <Image
              source={require("../assets//Ellipse 10.png")}
              style={{
                width: screenWidth / 40,
                height: screenHeight / 60,
                marginVertical: screenHeight / 100,
                marginRight: screenWidth / 80,
              }}
            ></Image>
            <Text style={{ color: "#000000", fontSize: 18 }}>
              # devices running
            </Text>
          </View>
        </View>
        <View
          //Lấy thành công dữ liệu ngày tháng current
          style={{
            // backgroundColor: "red",
            flexDirection: "row",
            width: screenWidth / 4,
            flex: 1,
            justifyContent: "space-around",
          }}
        >
          <TouchableOpacity
            style={{
              flexDirection: "column",
              marginHorizontal: screenWidth / 60,
              marginVertical: screenHeight / 120,
            }}
            activeOpacity={0.6}
            onPress={(e) => {
              navigation.navigate(ROUTES.WEATHERSCREEN);
            }}
          >
            <Image
              //tuy tinh hinh thoi tiet ma lay anh thich hop
              source={{ uri: `https:${current?.condition.icon}` }}
              style={{
                height: screenHeight / 20,
                width: screenWidth / 10,
              }}
            ></Image>
            {isVisible ? (
              <>
                <Text style={{ fontSize: 15, fontWeight: 500 }}>
                  {current?.temp_c}
                  {"\u2103"}
                </Text>
              </>
            ) : (
              <>
                <Text
                  style={{
                    fontSize: 15,
                    fontWeight: 500,
                  }}
                >
                  {current?.humidity} %
                </Text>
              </>
            )}
          </TouchableOpacity>
          <TouchableOpacity>
            <AntDesign
              name="poweroff"
              style={{
                fontSize: 24,
                color: "red",
                marginTop: screenHeight / 30,
              }}
            />
          </TouchableOpacity>
        </View>
      </View>
      {/*--------------------------------------end top view------------------------------------------------- */}
      <View style={{ flex: 1, height: screenHeight }}>
        <View
          style={{
            // backgroundColor: "red",
            flexDirection: "column",
            alignItems: "center",
          }}
        >
          <View style={styles.peopleContainer}>
            <Ionicons
              name="people-outline"
              style={{ fontSize: 20, marginRight: screenWidth / 60 }}
            />
            <Text style={styles.text}>0 </Text>
          </View>
        </View>

        <View style={{ flexDirection: "column" }}>
          <View
            style={{
              flexDirection: "row",
              marginHorizontal: screenWidth / 80,
            }}
          >
            <Image
              source={require("../assets/Lamp.png")}
              style={{ marginRight: screenWidth / 100 }}
            />
            <Text style={{ color: "#000", fontSize: 20, fontWeight: 500 }}>
              Lamps
            </Text>
          </View>
          <View
            style={{
              flexDirection: "row",
              // backgroundColor: "red",
              justifyContent: "space-around",
            }}
          >
            <View style={{ flexDirection: "row" }}>
              <Text
                style={{
                  fontSize: 16,
                  marginHorizontal: screenWidth / 100,
                  marginVertical: screenHeight / 60,
                }}
              >
                Status:{" "}
              </Text>
              <SwitchButton />
            </View>

            <Slider
              style={{ width: screenWidth / 2, height: screenHeight / 15 }}
              minimumValue={0}
              disabled={false}
              maximumValue={1}
              minimumTrackTintColor="#ccc"
              maximumTrackTintColor="#000000"
            />
          </View>
        </View>
      </View>
    </ScrollView>
  );
}

const styles = StyleSheet.create({
  background: {
    position: "absolute",

    left: 0,
    right: 0,
    top: 0,
    height: screenHeight,
  },
  container: {
    flex: 1,
    // backgroundColor: "red",
  },
  topViewContainer: {
    flexDirection: "row",
    paddingTop: screenHeight / 14,
    paddingHorizontal: screenWidth / 30,
    height: screenHeight / 4,
    flex: 1,
    borderWidth: 1,
    borderColor: "#AAB6FB",
    borderBottomStartRadius: 20,
    borderBottomEndRadius: 20,
    shadowColor: "#000", // Màu của bóng
    shadowOffset: {
      width: 0,
      height: 2,
    },
    shadowOpacity: 0.25, // Độ trong suốt của bóng
    shadowRadius: 2, // Độ mờ của bóng
    elevation: 1, // Độ nổi của bóng (cần thiết cho Android)
  },
  dateAndNameTopView: {
    flexDirection: "column",
    // backgroundColor: "red",
    height: screenHeight / 8,
    justifyContent: "center",
    // marginHorizontal: screenWidth / 30,
    width: screenWidth / 2,
    flex: 3,
  },
  peopleContainer: {
    flexDirection: "row",
    alignItems: "center",
    backgroundColor: "#fff",
    borderRadius: 20,
    padding: 10,
    borderWidth: 2,
    borderColor: "#E7E7E7",
    width: screenWidth / 2,
    marginVertical: screenHeight / 80,
  },
  icon: {
    width: 24,
    height: 24,
    marginRight: 5,
  },
  text: {
    fontSize: 16,
  },
});
