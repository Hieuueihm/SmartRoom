import React, { useState, useEffect } from "react";
import { ScrollView, Text, View, Image } from "react-native";
import { fetchWeatherForecast } from "../api/weatherAPI";
import { Dimensions } from "react-native";
import { StyleSheet } from "react-native";
const screenWidth = Dimensions.get("window").width;
const screenHeight = Dimensions.get("window").height;
export default function HomeScreen() {
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
  useEffect(() => {
    fetchWeatherForecast({ cityName: "Hanoi", days: "7" }).then((data) => {
      setWeather(data);
    });
  }, []);
  if (weather) {
    var { current, location, forecast } = weather;
  }
  const screensTopRight = [
    <>
      <Image
        //tuy tinh hinh thoi tiet ma lay anh thich hop
        source={{ uri: `https:${current?.condition.icon}` }}
        style={{
          margin: 18,
          height: 50,
          // backgroundColor: 'red',
          width: 50,
          marginLeft: 0,
        }}
      ></Image>
      <Text
        style={{
          marginTop: 30,
          marginLeft: -30,
          fontSize: 18,
          color: "#716968",
          fontWeight: "bold",
        }}
      >
        {current?.temp_c}
        {"\u2103"}
      </Text>
    </>,
  ];
  return (
    <ScrollView style={styles.container}>
      <View
        //Lấy thành công dữ liệu ngày tháng current
        style={{
          flexDirection: "column",
          marginStart: 10,
          marginEnd: 10,
          width: 210,
        }}
      >
        <Text style={{ color: "#000000", fontSize: 18 }}>
          {dayName}, {dayOfmonth} {monthName} {year}
        </Text>
      </View>
    </ScrollView>
  );
}

const styles = StyleSheet.create({
  container: {
    flex: 1,
    marginTop: screenHeight / 14,
  },
});
