const express = require("express");
const router = express.Router();

const {
  handlePostData,
  handleGetAllData,
  handleDeleteUser,
  handleGetUserById,
  handleUpdateUserById,
  handleLogin,
} = require("../controllers/userController");

router.post("/createNewUser", handlePostData);
router.get("/getAllUsers", handleGetAllData);
router.post("/deleteUser", handleDeleteUser);
router.post("/getUserById", handleGetUserById);
router.post("/updateUserById", handleUpdateUserById);
router.post("/login", handleLogin);
module.exports = router;
