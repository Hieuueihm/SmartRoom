const User = require("../models/userModel");
require("dotenv").config();
async function getNextUserId() {
  // Find the last user and get their userId
  const lastUser = await User.findOne({}, {}, { sort: { userId: -1 } });
  // If there are no users yet, start from 1, otherwise increment the last userId
  return lastUser ? lastUser.userId + 1 : 1;
}

const handlePostData = async (req, res) => {
  try {
    const {
      fullName,
      userName,
      email,
      password,
      gender,
      role,
      address,
      phone,
      topic,
    } = req.body;
    // Tạo một instance mới của User model với dữ liệu từ Postman
    // console.log(req.body);

    const userId = await getNextUserId();

    const newUser = new User();
    newUser.userId = userId;
    newUser.fullName = fullName;
    newUser.userName = userName;
    newUser.email = email;
    newUser.password = password;
    newUser.gender = gender;
    newUser.role = role;
    newUser.address = address;
    newUser.phone = phone;
    newUser.topic = topic;
    // Lưu user mới vào cơ sở dữ liệu
    const savedUser = await newUser.save();
    return res.status(200).json({
      success: true,
      message: "User added successfully",
    });
  } catch (error) {
    // Nếu có lỗi, trả về lỗi cho client
    return res.status(400).json({ success: false, message: error.message });
  }
};
const handleGetAllData = async (req, res) => {
  try {
    const allUsers = await User.find();
    res.status(200).json({ success: true, data: allUsers }); // Trả về tất cả dữ liệu người dùng
  } catch (error) {
    return res.status(400).json({ success: false, message: error.message });
  }
};

const handleDeleteUser = async (req, res) => {
  try {
    const { userId } = req.body; // Lấy userId từ tham số trong URL
    // Xóa người dùng từ CSDL
    if (!userId) {
      return res
        .status(400)
        .json({ success: false, message: "Vui lòng cung cấp userId." });
    }

    // Xóa người dùng từ CSDL dựa trên userId
    const deletedUser = await User.deleteOne({ userId });

    if (deletedUser.deletedCount === 0) {
      return res
        .status(404)
        .json({ success: false, message: "Người dùng không tồn tại." });
    }

    // Trả về thông báo thành công nếu xóa thành công
    return res
      .status(200)
      .json({ success: true, message: "Người dùng đã được xóa thành công." });
  } catch (error) {
    // Xử lý lỗi nếu có lỗi xảy ra trong quá trình xóa
    return res.status(400).json({ success: false, message: error.message });
  }
};

const handleGetUserById = async (req, res) => {
  try {
    const { userId } = req.body; // Lấy userId từ tham số trong URL

    // Kiểm tra xem userId có được cung cấp không
    if (!userId) {
      return res
        .status(400)
        .json({ success: false, message: "Vui lòng cung cấp userId." });
    }

    // Truy vấn người dùng từ CSDL dựa trên userId
    const user = await User.findOne({ userId });

    // Kiểm tra xem người dùng có tồn tại không
    if (!user) {
      return res
        .status(404)
        .json({ success: false, message: "Người dùng không tồn tại." });
    }

    // Trả về thông tin người dùng nếu tìm thấy
    return res.status(200).json({ success: true, data: user });
  } catch (error) {
    // Xử lý lỗi nếu có lỗi xảy ra trong quá trình truy vấn
    return res.status(400).json({ success: false, message: error.message });
  }
};

const handleUpdateUserById = async (req, res) => {
  try {
    const { userId, ...updateFields } = req.body; // Lấy các trường cần cập nhật từ body request

    // Kiểm tra xem userId và các trường cần cập nhật có được cung cấp không
    if (!userId) {
      return res
        .status(400)
        .json({ success: false, message: "Vui lòng cung cấp userId." });
    }
    console.log(updateFields);
    if (!updateFields) {
      return res.status(400).json({
        success: false,
        message: "Vui lòng cung cấp các trường cần cập nhật.",
      });
    }

    // Truy vấn người dùng từ CSDL dựa trên userId
    const user = await User.findOne({ userId });

    // Kiểm tra xem người dùng có tồn tại không
    if (!user) {
      return res
        .status(404)
        .json({ success: false, message: "Người dùng không tồn tại." });
    }

    // Cập nhật thông tin người dùng
    const updatedUser = await User.findOneAndUpdate({ userId }, updateFields, {
      new: true, // Trả về người dùng đã được cập nhật
    });

    // Trả về thông tin người dùng đã được cập nhật nếu thành công
    return res.status(200).json({ success: true, data: updatedUser });
  } catch (error) {
    // Xử lý lỗi nếu có lỗi xảy ra trong quá trình cập nhật
    return res.status(400).json({ success: false, message: error.message });
  }
};

const handleLogin = async (req, res) => {
  try {
    const { userName, password } = req.body;
    if (!userName) {
      return res.status(400).json({
        success: false,
        message: "Missing user name!",
      });
    } else if (!password) {
      return res.status(400).json({
        success: false,
        message: "Missing password!",
      });
    } else {
      const user = await User.findOne(
        {
          userName: userName,
          password: password,
        },
        { password: 0 }
      );
      if (!user) {
        return res.status(400).json({
          success: false,
          message: "User not found!",
        });
      } else {
        return res.status(200).json({
          success: true,
          data: user,
        });
      }
    }
  } catch (error) {
    return res.status(400).json({ success: false, message: error.message });
  }
};
module.exports = {
  handlePostData,
  handleGetAllData,
  handleDeleteUser,
  handleGetUserById,
  handleUpdateUserById,
  handleLogin,
};
