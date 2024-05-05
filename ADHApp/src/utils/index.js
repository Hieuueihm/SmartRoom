import { getItem, removeItem, storeItem } from "./asyncStorage";
import { showToast, toastConfig } from "./toastMessage";

export default utils = {
  AsyncStorage: {
    removeItem,
    getItem,
    storeItem,
  },
  Toast: {
    showToast,
    toastConfig,
  },
};
