import React, { useState, useEffect } from "react";
import { getAllUsers, deleteUser } from "../apis/userAPI";
import CreateModal from "./createModel";
import EditModal from "./editModal";

import { ToastContainer, toast } from "react-toastify";
import "react-toastify/dist/ReactToastify.css";

export function Home() {
  const [userData, setUserData] = useState("");
  const [isDataChange, setIsDataChange] = useState(false);
  const [showModal, setShowModal] = useState(false);
  const [userEditData, setUserEditData] = useState(null);
  const handleGetAllUsers = async () => {
    const result = await getAllUsers();
    if (result.status == 200) {
      setUserData(result.data.data);
    }
  };
  const toggleIsDataChange = (type) => {
    setIsDataChange(!isDataChange);
  };
  useEffect(() => {
    handleGetAllUsers();
  }, [isDataChange]);
  const handleDeleteUser = async (userIdd) => {
    await deleteUser({
      userId: userIdd,
    })
      .then((res) => {
        if (res.status === 200) {
          toast.success("Delete Successfully!");
          toggleIsDataChange();
        }
      })
      .catch((err) => {
        console.error(err);
      });
  };

  return (
    <div className="container my-5">
      <ToastContainer
        position="top-right"
        autoClose={5000}
        hideProgressBar={false}
        newestOnTop={false}
        closeOnClick
        rtl={false}
        pauseOnFocusLoss
        draggable
        pauseOnHover
        theme="dark"
      />
      <h2 className="text-center mb-3">HOME</h2>
      <button
        type="button"
        class="btn btn-primary btn-lg btn-block"
        data-bs-toggle="modal"
        data-bs-target="#CreateModal"
      >
        Create
      </button>
      <CreateModal
        toastProp={toast}
        isDataChange={isDataChange}
        toggleIsDataChange={toggleIsDataChange}
      />
      <EditModal
        toastProp={toast}
        userDataProp={userEditData}
        isDataChange={isDataChange}
        toggleIsDataChange={toggleIsDataChange}
      />
      ;
      <table class="table mt-5">
        <thead>
          <tr>
            <th>STT</th>
            <th>Tên đăng nhâp</th>
            <th>Email</th>
            <th>SĐT</th>
            <th>Tên</th>
            <th>Giới tính</th>
            <th>Địa chỉ</th>
            <th>Role</th>
            <th>Topic</th>
            <th>Options</th>
          </tr>
        </thead>
        <tbody>
          {userData &&
            userData.map((user, index) => (
              <tr key={index}>
                <td>{index + 1}</td>
                <td>{user.userName}</td>
                <td>{user.email}</td>
                <td>{user.phone}</td>
                <td>{user.fullName}</td>
                <td>{user.gender}</td>

                <td>{user.address}</td>
                <td>{user.role}</td>
                <td>
                  {user.topic &&
                    user.topic.map((topic, index) => (
                      <span key={index}>
                        {topic}
                        {index !== user.topic.length - 1 && ", "}
                      </span>
                    ))}
                </td>
                <td>
                  <span className="btn-group">
                    <button
                      type="button"
                      class="btn btn-primary rounded-1"
                      data-bs-toggle="modal"
                      data-bs-target="#EditModal"
                      style={{ marginRight: 10 }}
                      onClick={() => {
                        setUserEditData(user);
                      }}
                    >
                      Edit
                    </button>
                    <button
                      className="btn btn-sm btn-danger btn-block rounded-1"
                      onClick={() => handleDeleteUser(user.userId)}
                    >
                      Delete
                    </button>
                  </span>
                </td>
              </tr>
            ))}
        </tbody>
      </table>
    </div>
  );
}
