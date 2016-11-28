/*
  This script runs during preinstall and ensures that every install receives a
  new GUID to be used as the ToastActivatorCLSID. That way the DLLs will be
  compiled with a unique CLSID baked in.

  Name:     System.AppUserModel.ToastActivatorCLSID -- PKEY_AppUserModel_ToastActivatorCLSID
  Type:     Guid -- VT_CLSID
  FormatID: {9F4C2855-9F79-4B39-A8D0-E1D42DE1D5F3}, 26
*/

require('./replaceguid')()
require('./replaceprotocol')()
