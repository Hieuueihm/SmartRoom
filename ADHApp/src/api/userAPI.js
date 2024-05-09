import APIManager from "./APIManager";

export const handleLogin = async (data) => {
  try {
    const result = await APIManager("/login", {
      method: "POST",
      headers: {
        Accept: "application/json",
        "content-type": "application/json",
      },
      data: data,
    });
    // console.log(result);
    return result;
  } catch (error) {
    return error;
  }
};

export const handleGetUserById = async (data) => {
  try {
    const result = await APIManager("/getUserById", {
      method: "POST",
      headers: {
        Accept: "application/json",
        "content-type": "application/json",
      },
      data: data,
    });
    // console.log(result);
    return result;
  } catch (error) {
    return error;
  }
};
