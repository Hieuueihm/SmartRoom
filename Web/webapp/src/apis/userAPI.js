import APIManager from "./apiManager";

export const getAllUsers = async () => {
  try {
    const result = await APIManager("/getAllUsers", {
      method: "GET",
      headers: {
        "content-type": "application/json",
      },
    });
    return result;
  } catch (error) {
    return error;
  }
};

export const createNewUser = async (data) => {
  try {
    const result = await APIManager("/createNewUser", {
      method: "POST",
      headers: {
        "content-type": "application/json",
      },
      data: data,
    });
    console.log(result);
    return result;
  } catch (error) {
    return error;
  }
};

export const deleteUser = async (data) => {
  try {
    const result = await APIManager("/deleteUser", {
      method: "POST",
      headers: {
        "content-type": "application/json",
      },
      data: data,
    });
    console.log(result);
    return result;
  } catch (error) {
    return error;
  }
};
export const getUserById = async (data) => {
  try {
    const result = await APIManager("/getUserById", {
      method: "POST",
      headers: {
        "content-type": "application/json",
      },
      data: data,
    });
    console.log(result);
    return result;
  } catch (error) {
    return error;
  }
};

export const updateUserById = async (data) => {
  try {
    const result = await APIManager("/updateUserById", {
      method: "POST",
      headers: {
        "content-type": "application/json",
      },
      data: data,
    });
    console.log(result);
    return result;
  } catch (error) {
    return error;
  }
};
