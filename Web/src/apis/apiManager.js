import axios from "axios";

const APIManager = axios.create({
  baseURL: "http://127.0.0.1:4003/api",
  responseType: "json",
  withCredentials: true,
});
export default APIManager;
