import React, { useEffect, useState } from "react";
import { updateUserById } from "../apis/userAPI";
import { getUserById } from "../apis/userAPI";

import { ToastContainer, toast } from "react-toastify";
import "react-toastify/dist/ReactToastify.css";
export default function EditModal(props) {
  const [userData, setUserData] = useState("");
  const [email, setEmail] = useState("");
  const [userName, setUserName] = useState("");
  const [phone, setPhone] = useState("");
  const [password, setPassword] = useState("");
  const [address, setAdress] = useState("");
  const [topic, setTopic] = useState("");
  const [fullName, setFullName] = useState("");
  const [gender, setGender] = useState("Male");
  const [role, setRole] = useState("User");

  useEffect(() => {
    if (props.userDataProp !== null) {
      setEmail(props.userDataProp.email);
      setUserName(props.userDataProp.userName);
      setPhone(props.userDataProp.phone);
      setPassword(props.userDataProp.password);
      setAdress(props.userDataProp.address);
      setFullName(props.userDataProp.fullName);
      setGender(props.userDataProp.gender);
      setRole(props.userDataProp.role);
      const resultString = props.userDataProp.topic.join(",");

      setTopic(resultString);
    }
  }, [props.userDataProp]);

  const handleChangeIsDataChange = () => {
    props.toggleIsDataChange(!props.isDataChange);
  };

  const validateEmail = (email) => {
    // Sử dụng biểu thức chính quy để kiểm tra định dạng email
    const re = /^[^\s@]+@[^\s@]+\.[^\s@]+$/;
    return re.test(email);
  };
  function convertToArray(inputString) {
    // Tách chuỗi thành mảng dựa trên dấu phẩy và loại bỏ khoảng trắng
    if (typeof inputString != Array) {
      let resultArray = inputString.split(",").map((item) => item.trim());
      return resultArray;
    }
    return inputString;
  }

  const handleSaveChange = async () => {
    if (!validateEmail(email)) {
      props.toastProp.error("Invalid email!");
    } else if (!userName) {
      props.toastProp.error("Please enter user name!");
    } else if (!password) {
      props.toastProp.error("Please enter password!");
    } else if (!fullName) {
      props.toastProp.error("Please enter full name!");
    } else if (!address) {
      props.toastProp.error("Please enter address!");
    } else if (!phone) {
      props.toastProp.error("Please enter phone number!");
    } else if (!topic) {
      props.toastProp.error("Please enter topic!");
    } else {
      await updateUserById({
        userId: props.userDataProp.userId,
        fullName: fullName,
        userName: userName,
        email: email,
        password: password,
        gender: gender,
        role: role,
        address: address,
        phone: phone,
        topic: convertToArray(topic),
      })
        .then((res) => {
          if (res.status === 200) {
            props.toastProp.success("Successfully!");
            handleChangeIsDataChange();
            document.getElementById("closeBtn1").click();
          }
        })
        .catch((err) => console.error(err));
    }
  };
  return (
    <div
      class="modal fade"
      id="EditModal"
      tabindex="-1"
      aria-labelledby="exampleModalLabel"
      aria-hidden="true"
    >
      <div class="modal-dialog">
        <div class="modal-content">
          <div class="modal-header">
            <h1 class="modal-title fs-5" id="exampleModalLabel">
              Edit User
            </h1>
            <button
              type="button"
              class="btn-close"
              data-bs-toggle="modal"
              data-bs-target="#EditModal"
            ></button>
          </div>
          <div class="modal-body">
            <form class="row g-2 mt-2 mb-2">
              <div class="col">
                <label for="inputEmail4" class="form-label">
                  Email
                </label>
                <input
                  type="email"
                  class="form-control"
                  id="inputEmail4"
                  value={email}
                  onChange={(e) => {
                    setEmail(e.target.value);
                  }}
                />
              </div>
              <div class="row g-2">
                <div class="col">
                  <input
                    type="text"
                    class="form-control"
                    placeholder="User name"
                    value={userName}
                    onChange={(e) => {
                      setUserName(e.target.value);
                    }}
                  />
                </div>
                <div class="col">
                  <input
                    type="text"
                    class="form-control"
                    placeholder="Password"
                    value={password}
                    onChange={(e) => {
                      setPassword(e.target.value);
                    }}
                  />
                </div>
              </div>
              <div class="row g-3">
                <div class="col">
                  <input
                    type="text"
                    class="form-control"
                    placeholder="Full name"
                    value={fullName}
                    onChange={(e) => {
                      setFullName(e.target.value);
                    }}
                  />
                </div>
                <div class="col">
                  <input
                    type="text"
                    class="form-control"
                    placeholder="Address"
                    value={address}
                    onChange={(e) => {
                      setAdress(e.target.value);
                    }}
                  />
                </div>
              </div>

              <div class="row g-2">
                <div class="col">
                  <label for="inputCity" class="form-label">
                    Phone number
                  </label>
                  <input
                    type="number"
                    class="form-control"
                    id="inputCity"
                    value={phone}
                    onChange={(e) => {
                      setPhone(e.target.value);
                    }}
                  />
                </div>
                <div class="col-4">
                  <label for="inputState" class="form-label">
                    Gender
                  </label>
                  <select
                    id="inputState"
                    class="form-select"
                    value={gender}
                    onChange={(e) => {
                      setGender(e.target.value);
                    }}
                  >
                    <option value="Male" selected>
                      Male
                    </option>
                    <option value="Female"> Female</option>
                    <option value="Other">Other</option>
                  </select>
                </div>
                <div class="col-3">
                  <label for="inputState" class="form-label">
                    Gender
                  </label>
                  <select
                    id="inputState"
                    class="form-select"
                    value={role}
                    onChange={(e) => setRole(e.target.value)}
                  >
                    <option value="User" selected>
                      User
                    </option>
                    <option value="Admin">Admin</option>
                  </select>
                </div>
              </div>
              <div class="col">
                <label for="inputCity" class="form-label">
                  Topic
                </label>
                <input
                  type="text"
                  class="form-control"
                  id="inputCity"
                  value={topic}
                  onChange={(e) => {
                    setTopic(e.target.value);
                  }}
                />
              </div>
            </form>
          </div>
          <div class="modal-footer">
            <button
              id="closeBtn1"
              type="button"
              class="btn btn-secondary"
              data-bs-dismiss="modal"
            >
              Close
            </button>
            <button
              type="button"
              class="btn btn-primary"
              onClick={handleSaveChange}
            >
              Save changes
            </button>
          </div>
        </div>
      </div>
    </div>
  );
}
