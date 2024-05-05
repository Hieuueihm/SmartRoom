const express = require("express");
const cors = require("cors");
const bodyParser = require("body-parser");
require("dotenv").config();
const apiRoute = require("./src/routes/api");

const app = express();

app.use(bodyParser.json());

app.use(cors({ origin: true, credentials: true }));

const connectDB = require("./src/config/db");

app.use(express.json());

app.use("/api", apiRoute);
app.listen(process.env.PORT);
connectDB();
