import axios from "axios";

const APIManager = axios.create({
  baseURL: "http://10.0.2.2:4003/api",
  responseType: "json",
  withCredentials: true,
});
export default APIManager;
