const mongoose = require("mongoose");

const userSchema = new mongoose.Schema(
  {
    userId: {
      type: Number,
      unique: true,
    },
    userName: { type: String, unique: true },
    fullName: {
      type: String,
    },
    email: {
      type: String,
      unique: true,
    },
    password: {
      type: String,
    },
    gender: {
      type: String,
      enum: ["Male", "Female", "Other"],
      default: "Other",
    },
    role: {
      type: String,
      enum: ["Admin", "User"],
      default: "Other",
    },
    address: {
      type: String,
    },
    phone: {
      type: String,
    },
    topic: {
      type: [String],
    },
  },
  {
    timestamps: true,
    collection: "users",
  }
);

module.exports = mongoose.model("users", userSchema);
