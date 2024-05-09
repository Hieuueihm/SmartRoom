// In App.js in a new project

import * as React from "react";
import { View, Text } from "react-native";
import { NavigationContainer } from "@react-navigation/native";
import { createNativeStackNavigator } from "@react-navigation/native-stack";
import LoginScreen from "./src/screens/login";
import HomeScreen from "./src/screens/home";
import WeatherScreen from "./src/screens/weather";
import { ROUTES } from "./constants";

const Stack = createNativeStackNavigator();

function App() {
  return (
    <NavigationContainer>
      <Stack.Navigator>
        <Stack.Screen
          name={ROUTES.LOGINSCREEN}
          component={LoginScreen}
          options={{ headerShown: false }}
        />
        <Stack.Screen
          name={ROUTES.WEATHERSCREEN}
          component={WeatherScreen}
          options={{ headerShown: false }}
        />
        <Stack.Screen
          name={ROUTES.HOMESCREEN}
          component={HomeScreen}
          options={{ headerShown: false }}
        />
      </Stack.Navigator>
    </NavigationContainer>
  );
}

export default App;
